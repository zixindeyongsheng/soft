#include<iostream>
#include<string.h>
#include<vector>
#include<QTcpSocket>
#include<QTcpServer>
#include"serve_airconditioner.h"
#include"D:\Downloads\LINKLIST.h"
using namespace std;

class server
{
private:
	vector<serve_airconditioner> serve_airconditionerptr;
	int serve_airconditionernum;
	int feelist[2][3];
	int hoc;//制冷1/制热0
    QTcpServer* server_sever;

private slots:
	void server_new_connect()//监听并连接
	{
		serve_airconditioner toolair = new serve_airconditioner();
        toolair.air_socket = server_sever->nextPendingConnection();
		serve_airconditionerptr.push_back(toolair);
        QObject::connect(toolair.air_socket, SIGNAL(QTcpSocket::readyRead()), this, SLOT(server::server_receive()));
        QObject::connect(toolair.air_socket, SIGNAL(QTcpSocket::disconnected()), this, SLOT(server::server_disconnected()));
	}
	void server_receive()//接收
	{
		QByteArray buffer;
        buffer = ((QTcpSocket*)(QObject::sender()))->readAll();
        QTcpSocket* toolsocket=(QTcpSocket*)(QObject::sender());
        int aimptr=-1;
        for(i=0;i<serve_airconditionerptr.size() && aimptr==-1;++i)
            if(toolsocket==serve_airconditionerptr[i].air_socket)
                aimptr=i;
        if(aimptr==-1)
            return;//错误处理
        Ac toolac;
		//此处格式转化解析报文
        if(toolac.type==1)//通告报文
            if(serve_airconditionerptr[i].getstate()==0)
                serve_airconditionerptr[i].nowtemp=toolac.tem;//不在运行则温度随房间变化
            else;
        else//请求报文
        {
            if(serve_airconditionerptr[i].getroomnumber()=="")
                serve_airconditionerptr[i].setroomnumber()=="";
            //执行相应的请求创建和插入
        }
	}
	void server_disconnect()//断开连接
    {
        QTcpSocket* toolsocket=(QTcpSocket*)(QObject::sender());
		for (int i = 0; i < serve_airconditionerptr.size(); ++i)
            if (serve_airconditionerptr[i].air_socket == toolsocket)
            {
                serve_airconditioner& toolair = serve_airconditionerptr[i];
                this->serve_airconditionerptr.erase(serve_airconditionerptr.begin() + i);
                delete toolair;
            }
	}
public:
	server()//构造函数
	{
		server_sever = new QTcpServer();
        server_sever->listen(QHostAddress::Any, port);//
        QObject::connect(server_sever, SIGNAL(QTcpServer::newConnection()), this, SLOT(server::server_new_connect()));
	}
    //定期发送（未具有定期功能）
    void server_send()
	{
		QByteArray buffer;

        for(int i=0;i<serve_airconditionerptr.size();++i)
            if (serve_airconditionerptr[i].gettheinforable() == 1)
			{
				//利用serve_airconditionerptr[i]的get函数获取报文信息
                serve_airconditionerptr[i].air_socket->write(data);
			}
	}
	

	//定期制冷
	void setfeelist(int fee1, int fee2, int fee3,int hoc)//设置费率
	{
		this->feelist[hoc][0] = fee1;
		this->feelist[hoc][1] = fee2;
		this->feelist[hoc][2] = fee3;
	}
	void sethoc(int hoc)
	{
		this->hoc = hoc;
	}
	int ** getfeelist()
	{
		return (int **)(this->feelist);
	}
	int setfeelist()
	{
		return this->hoc;
	}
};
