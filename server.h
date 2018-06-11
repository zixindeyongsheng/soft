#ifndef se
#define se

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
class base_list;
typedef base_list LinkList;
using namespace std;
class server:public QObject
{
Q_OBJECT

private:
    int serve_airconditionernum;
    float feelist[2][3];
    int hoc;//制冷1/制热0
    QTcpServer* server_sever;
    QTcpServer* server_monitor;
    LinkList* thelinklistptr;
    QTcpSocket* server_monitor_socket;
    QMutex sendmutex;

public:
    vector<serve_airconditioner> serve_airconditionerptr;
    server();//构造函数
    void putlinklist(LinkList* thelinklistptr2);
    ~server();

    void setfeelist(float fee1, float fee2, float fee3,int hoc);
    void sethoc(int hoc);
    float * getfeelist();
    int gethoc();

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
