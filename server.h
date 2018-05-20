#include<iostream>
#include<string.h>
#include<vector>
#include<QTcpSocket>
#include<QTcpServer>
#include<QObject>
#include"serve_airconditioner.h"
#include"LINKLIST.h"
#include"parse.hpp"
using namespace std;

class server:public QObject
{
private:
	vector<serve_airconditioner> serve_airconditionerptr;
	int serve_airconditionernum;
	int feelist[2][3];
	int hoc;//制冷1/制热0
    QTcpServer* server_sever;
    LinkList* thelinklistptr;

private slots:
	void server_new_connect()//监听并连接
	{
        serve_airconditioner toolair;
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
        for(unsigned int i=0;i<serve_airconditionerptr.size() && aimptr==-1;++i)
            if(toolsocket==serve_airconditionerptr[i].air_socket)
                aimptr=i;
        if(aimptr==-1)
            return;//错误处理
        Ac toolac=parser::parse(buffer.data());
		//此处格式转化解析报文
        if(toolac.type==1)//通告报文
            if(serve_airconditionerptr[aimptr].getstate()==0)
                serve_airconditionerptr[aimptr].nowtemp=toolac.tem;//不在运行则温度随房间变化
            else{}
        else//请求报文
        {
            if(serve_airconditionerptr[aimptr].getroomnumber()=="")
                serve_airconditionerptr[aimptr].setroomnumber(toolac.num);
            thelinklistptr->inserthead(toolac);//执行相应的请求创建和插入
        }
	}
	void server_disconnect()//断开连接
    {
        QTcpSocket* toolsocket=(QTcpSocket*)(QObject::sender());
        for (unsigned int i = 0; i < serve_airconditionerptr.size(); ++i)
            if (serve_airconditionerptr[i].air_socket == toolsocket)
                this->serve_airconditionerptr.erase(serve_airconditionerptr.begin() + i);
	}
public:
	server()//构造函数
	{
		server_sever = new QTcpServer();
        server_sever->listen(QHostAddress::Any, 8080);//
        QObject::connect(server_sever, SIGNAL(QTcpServer::newConnection()), this, SLOT(server::server_new_connect()));
	}
    server(LinkList* thelinklistptr)
    {
        server();
        this->thelinklistptr=thelinklistptr;
    }
    //定期发送（未具有定期功能）
    void server_send()
    {
        for(unsigned int i=0;i<serve_airconditionerptr.size();++i)
        {
            Ac toolac;
            toolac.s=serve_airconditionerptr[i].gets();
            toolac.tem=serve_airconditionerptr[i].getaimtemp();
            toolac.cost=serve_airconditionerptr[i].getfee();
            toolac.wind=serve_airconditionerptr[i].getwindspeed();
            QByteArray buffer(parser::parse(toolac));
            serve_airconditionerptr[i].air_socket->write(buffer);
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
    int gethoc()
	{
		return this->hoc;
	}
};
