#ifndef se
#define se
#include<iostream>
#include<string.h>
#include<string>
#include<vector>
#include <QTcpServer>
#include <QTcpSocket>
#include<QString>
#include<QByteArray>
#include<QObject>
#include<qmutex.h>
#include<QDebug>
#include"serve_airconditioner.h"
#include"LINKLIST.h"
#include"parse.hpp"
using namespace std;

class server:public QObject
{
Q_OBJECT

private:
    int serve_airconditionernum;
    int feelist[2][3];
    int hoc;//制冷1/制热0
    QTcpServer* server_sever;
    QTcpServer* server_monitor;
    LinkList* thelinklistptr;
    QTcpSocket* server_monitor_socket;
    QMutex sendmutex;

public:
    vector<serve_airconditioner> serve_airconditionerptr;
	server()//构造函数
	{
        server_sever = new QTcpServer();
        server_sever->listen(QHostAddress::Any, 8080);
        connect(server_sever, &QTcpServer::newConnection, this, &server::server_new_connect);
        server_monitor=new QTcpServer();
        server_monitor->listen(QHostAddress::Any,8499);
        connect(server_monitor,&QTcpServer::newConnection,this,&server::monitor_new_connect);
        connect(this,SIGNAL(signal_send(serve_airconditioner)),this,SLOT(server_send(serve_airconditioner)));
    }
//    server(LinkList* thelinklistptr)
//    {
//        server();
//        //this->thelinklistptr=thelinklistptr;
//    }
    putlinklist(LinkList* thelinklistptr2)
    {
        this->thelinklistptr=thelinklistptr2;
    }
    ~server()
    {
        server_sever->close();
        server_sever->deleteLater();
    }
    //定期发送（未具有定期功能）

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
    //用于用户的server
    void server_new_connect();//监听并连接
    void server_receive();//接收
    void server_disconnect();//断开连接
    //用于监视器的server
    void monitor_new_connect();
    void monitor_receive();
    void monitor_disconnect();
public slots:
    void server_send();
    void server_send(serve_airconditioner toolariconditioner);
signals:
    void signal_send(serve_airconditioner toolariconditioner);
};
#endif
