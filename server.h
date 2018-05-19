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
	int hoc;//����1/����0
    QTcpServer server_sever;

private slots:
	void server_new_connect()//����������
	{
		serve_airconditioner toolair = new serve_airconditioner();
		toolair->air_socket = server_sever->nextPendingConnection();
		serve_airconditionerptr.push_back(toolair);
		QObject::connect(toolair->air_socket, &QTcpSocket::readyRead, this, server::server_receive);
		QObject::connect(toolair->air_socket, &QTcpSocket::disconnected, this, server::server_disconnected);
	}
	void server_receive()//����
	{
		QByteArray buffer;
		buffer = sender()->readyAll();
		//�˴���ʽת����������
	}
	void server_disconnect()//�Ͽ�����
	{
        QTcpSocket toolsocket=sender();
		for (int i = 0; i < serve_airconditionerptr.size(); ++i)
			if (serve_airconditionerptr[0].air_socket == toolsocket)
				this->serve_airconditionerptr.erase(a.begin() + i, a.begin() + i + 1);
	}
public:
	server()//���캯��
	{
		server_sever = new QTcpServer();
		server_server->listen(QHostAddress::Any, port);
		QObject::connect(server_sever, &QTcpServer::newConnection, this, &server::server_new_connect);
	}
	//���ڷ��ͣ�δ���ж��ڹ��ܣ�
    void server_send()
	{
		QByteArray buffer;

		for(int i=0;i<serve_airconditionerptr.airconditionerptr.size();++i)
			if (serve_airconditionerptr[i].gettheinforable == 1)
			{
				//����serve_airconditionerptr[i]��get������ȡ������Ϣ
				serve_airconditionerptr[i]->write(data);
			}
	}
	

	//��������
	void setfeelist(int fee1, int fee2, int fee3,int hoc)//���÷���
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
