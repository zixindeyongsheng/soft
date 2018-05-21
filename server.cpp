#include"server.h"


void server::server_new_connect()//监听并连接
{
    serve_airconditioner toolair;
    toolair.air_socket = server_sever->nextPendingConnection();
    serve_airconditionerptr.push_back(toolair);
    connect(toolair.air_socket, &QTcpSocket::readyRead, this, &server::server_receive);
    connect(toolair.air_socket, &QTcpSocket::disconnected, this, &server::server_disconnect);
}
void server::server_receive()//接收
{
    QByteArray buffer;
    buffer = ((QTcpSocket*)(sender()))->readAll();
    QTcpSocket* toolsocket=(QTcpSocket*)(sender());
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
    Ac toolac=parser::parse(buffer.data());
    //此处格式转化解析报文
    if(toolac.type==1)//通告报文
        if(toolairconditioner.getstate()==0)
            toolairconditioner.setnowtemp(toolac.tem);//不在运行则温度随房间变化
        else{}
    else//请求报文
    {
        if(toolairconditioner.getroomnumber()=="")
            toolairconditioner.setroomnumber(toolac.num);
        //thelinklistptr->inserthead(toolac);//执行相应的请求创建和插入
    }
    server_send();
}
void server::server_disconnect()//断开连接
{
    QTcpSocket* toolsocket=(QTcpSocket*)(sender());
    for (unsigned int i = 0; i < serve_airconditionerptr.size(); ++i)
        if (serve_airconditionerptr[i].air_socket == toolsocket)
            this->serve_airconditionerptr.erase(serve_airconditionerptr.begin() + i);
}
