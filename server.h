#include<iostream>
#include<string.h>
#include<vector>
#include<QTcpServer>
#include<QObject>
#include"serve_airconditioner.h"
#include"LINKLIST.h"
#include"parse.hpp"
using namespace std;

class server:public QObject
{
Q_OBJECT

private:
	vector<serve_airconditioner> serve_airconditionerptr;
	int serve_airconditionernum;
	int feelist[2][3];
	int hoc;//制冷1/制热0
    QTcpServer* server_sever;
    LinkList* thelinklistptr;
public:
	server()//构造函数
	{
        server_sever = new QTcpServer(this);
        server_sever->listen(QHostAddress::Any, 8080);
        connect(server_sever, &QTcpServer::newConnection, this, &server::server_new_connect);
        //emit(server_sever->newConnection());

    }
    server(LinkList* thelinklistptr)
    {
        server();
        this->thelinklistptr=thelinklistptr;
    }
    ~server()
    {
        if(server_sever!=NULL)
            delete server_sever;
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

private slots:
    void server_new_connect();//监听并连接
    void server_receive();//接收
    void server_disconnect();//断开连接
};
