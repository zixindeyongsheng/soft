#include<iostream>
#include<string.h>
#include<vector>
#include<QTcpSocket>
#include<QTcpServer>
using namespace std;
#include"serve_airconditioner.h"

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
		QObject::connect(toolair->air_socket, &QTcpSocket::readyRead, this, server::server_receive);
		QObject::connect(toolair->air_socket, &QTcpSocket::disconnected, this, server::server_disconnected);
	}
	void server_receive()//接收
	{
		QByteArray buffer;
        buffer = ((QTcpSocket*)sender())->readAll();
		//此处格式转化解析报文
	}
	void server_disconnect()//断开连接
	{
        QTcpSocket* toolsocket=(QTcpSocket*)sender();
		for (int i = 0; i < serve_airconditionerptr.size(); ++i)
			if (serve_airconditionerptr[0].air_socket == toolsocket)
                this->serve_airconditionerptr.erase(serve_airconditionerptr[0].begin() + i, serve_airconditionerptr[0].begin() + i + 1);
	}
public:
	server()//构造函数
	{
		server_sever = new QTcpServer();
		server_server->listen(QHostAddress::Any, port);
		QObject::connect(server_sever, &QTcpServer::newConnection, this, &server::server_new_connect);
	}
	//定期发送（未具有定期功能）
    void server_send()
	{
		QByteArray buffer;

		for(int i=0;i<serve_airconditionerptr.airconditionerptr.size();++i)
			if (serve_airconditionerptr[i].gettheinforable == 1)
			{
				//利用serve_airconditionerptr[i]的get函数获取报文信息
				serve_airconditionerptr[i]->write(data);
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
