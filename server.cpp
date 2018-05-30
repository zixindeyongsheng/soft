#include"server.h"
void split(const string& src, const string& separator, vector<string>& dest);

void server::server_new_connect()//监听并连接
{
    serve_airconditioner toolair;
    toolair.air_socket = server_sever->nextPendingConnection();
    serve_airconditionerptr.push_back(toolair);
    connect(toolair.air_socket, &QTcpSocket::readyRead, this, &server::server_receive);
    connect(toolair.air_socket, &QTcpSocket::disconnected, this, &server::server_disconnect);
    qDebug()<<"message:an user connected!";
}

void server::server_receive()//接收
{
    QByteArray buffer;
    buffer = ((QTcpSocket*)(sender()))->readAll();
    QTcpSocket* toolsocket=(QTcpSocket*)(sender());
    string toolstring=buffer.toStdString();
    qDebug()<<"receive:"<<toolstring.data();
    vector<string> desk;
    split(toolstring,"}",desk);
    int aimptr=-1;
    serve_airconditioner *toolariconditionerptr2;
    for(unsigned int i=0;i<serve_airconditionerptr.size() && aimptr==-1;++i)
        if(toolsocket==serve_airconditionerptr[i].air_socket)
        {
            toolariconditionerptr2=&serve_airconditionerptr[i];
            aimptr=i;
        }
    if(aimptr==-1)
        return;//错误处理
    serve_airconditioner& toolairconditioner=*toolariconditionerptr2;
    for(unsigned int i=0;i<desk.size();++i)
    {
        Ac toolac=parser::parse((desk[i]+"}").data());
        //此处格式转化解析报文
        if(toolac.type==1)//通告报文
            //if(toolairconditioner.getstate()==0)
            toolairconditioner.setnowtemp(toolac.tem);//不在运行则温度随房间变化
           // else{}
        else//请求报文
        {
            if(toolairconditioner.getroomnumber()=="")
                toolairconditioner.setroomnumber(toolac.num);
            qDebug()<<"new insert!!!";
            thelinklistptr->inserthead(toolac);//执行相应的请求创建和插入
        }
        server_send(toolairconditioner);
    }
}

void server::server_disconnect()//断开连接
{
    QTcpSocket* toolsocket=(QTcpSocket*)(sender());
    for (unsigned int i = 0; i < serve_airconditionerptr.size(); ++i)
        if (serve_airconditionerptr[i].air_socket == toolsocket)
            this->serve_airconditionerptr.erase(serve_airconditionerptr.begin() + i);
    qDebug()<<"message:an user disconnected!";
}


void server::monitor_new_connect(){
    this->server_monitor_socket=this->server_monitor->nextPendingConnection();
    connect(this->server_monitor_socket,&QTcpSocket::readyRead,this,&server::monitor_receive);
    connect(this->server_monitor_socket,&QTcpSocket::disconnected,this,&server::monitor_disconnect);
    qDebug()<<"message:monitor connected";
}

void server::monitor_receive(){
    QByteArray buffer;
    buffer = ((QTcpSocket*)(sender()))->readAll();
    string toolstring=buffer.toStdString();
    vector<string> desk;
    split(toolstring,",",desk);
    string roomarray="{\"rooms\":[";
    string switchinfo;
    string tgtinfo;
    string crtinfo;
    string windinfo;
    string costinfo;
    string roomstringinfo;
    int finded=0;
    for(unsigned int i=0;i<serve_airconditionerptr.size();++i)
    {
        int count=0;
        serve_airconditioner& toolairconditioner=serve_airconditionerptr[i];
        string roomstring=toolairconditioner.getroomnumber();
        if(roomstring!="")
        {
            if(count==0)
                count=1;
            else
                printf(",");
            roomarray+="\""+roomstring+"\"";
            if(roomstring==desk[1] && desk.size()>=2)
            {
                roomstringinfo="\"room\":"+roomstring;
                switchinfo="\"switch\":"+to_string(toolairconditioner.gets());
                tgtinfo="\"tgtTemperature\":"+to_string(toolairconditioner.getaimtemp());
                crtinfo="\"crtTemperature\":"+to_string(toolairconditioner.getnowtemp());
                windinfo="\"wind\":"+to_string(toolairconditioner.getwindspeed());
                costinfo="\"cost\":"+to_string(toolairconditioner.getfee());
                finded=1;
            }
        }
    }
    string sendingstring;
    if(finded==1)
        sendingstring=roomarray+"]"+",\"roomInfo\":{"+roomstringinfo+","+switchinfo+","+tgtinfo+","+crtinfo+","+windinfo+","+costinfo+"}}";
    else
        sendingstring=roomarray+"]"+",\"roomInfo\":\"\"}";
    QByteArray sendingbuffer=(QString::fromStdString(sendingstring)).toLatin1();
    this->server_monitor_socket->write(sendingbuffer);
    qDebug()<<"send:"<<sendingstring.data();
}
void server::monitor_disconnect(){
    qDebug()<<"message:monitor disconnected";
}


void split(const string& src, const string& separator, vector<string>& dest)
 {
     string str = src;
     string substring;
     string::size_type start = 0, index;

     do
     {
         index = str.find_first_of(separator,start);
         if (index != string::npos)
         {
             substring = str.substr(start,index-start);
             dest.push_back(substring);
            start = str.find_first_not_of(separator,index);
             if (start == string::npos) return;
         }
     }while(index != string::npos);

     //the last token
     substring = str.substr(start);
     dest.push_back(substring);
 }

void server::server_send()//全部发送
{
    sendmutex.lock();
    for(unsigned int i=0;i<serve_airconditionerptr.size();++i)
    {
        Ac toolac;
        toolac.s=serve_airconditionerptr[i].gets();
        toolac.tem=serve_airconditionerptr[i].getaimtemp();
        toolac.cost=serve_airconditionerptr[i].getfee();
        toolac.wind=serve_airconditionerptr[i].getwindspeed();
        QByteArray buffer=(QString::fromStdString(parser::parse(toolac))).toLatin1();
        serve_airconditionerptr[i].air_socket->write(buffer);
        qDebug()<<"send:"<<(buffer.toStdString()).data();
    }
    sendmutex.unlock();
}
void server::server_send(serve_airconditioner toolariconditioner)//单个发送
{
    sendmutex.lock();
    Ac toolac;
    toolac.s=toolariconditioner.gets();
    toolac.tem=toolariconditioner.getaimtemp();
    toolac.cost=toolariconditioner.getfee();
    toolac.wind=toolariconditioner.getwindspeed();
    QByteArray buffer=(QString::fromStdString(parser::parse(toolac))).toLatin1();
    toolariconditioner.air_socket->write(buffer);
    qDebug()<<"send:"<<(buffer.toStdString()).data();
    sendmutex.unlock();
}
