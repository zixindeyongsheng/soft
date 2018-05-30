#include "modification.h"
#include <qdebug.h>
#include<thread>
#include <QSemaphore>
#include<QMetaType>
#include <vector>
#include <algorithm>
#include "parse.hpp"
using namespace std;
struct comp:binary_function<serve_airconditioner, string, bool>{
    bool operator()(serve_airconditioner &v, string str)const{
            if (v.getroomnumber() == str) {
                return true;
            }else
                return false;
    }
};

list<Ac> q;
LinkList * s;
server * sv;

producer::producer(LinkList *a, server *b){
    s = a;
    sv = b;
}

void producer::run(){
    qDebug()<<"run success";
 //   connect(this,SIGNAL(signal_sender(serve_airconditioner)),&sv,SLOT(server::server_send(serve_airconditioner)));
    qRegisterMetaType<serve_airconditioner>("serve_airconditioner");
    while (true) {
        sleep(1);
        LISTINT fetchlist = s->search();
        //qDebug()<<"end search";
        LISTINT::iterator it;
        Ac temp;
        //qDebug()<<__LINE__;
        vector<serve_airconditioner>& airconds = sv->serve_airconditionerptr;
       // qDebug()<<__LINE__;
        vector<serve_airconditioner>::iterator it2;
        for(it = fetchlist.begin();it != fetchlist.end();++it){
            //qDebug()<<__LINE__;
            temp = *it;
            //qDebug()<<__LINE__;
            it2 = find_if(airconds.begin(), airconds.end(), bind2nd(comp(), temp.num));
            if(it2 == airconds.end()){
                qDebug()<<"havn't' find out";
                continue;
            }
            it2->sets(temp.s);
            it2->setwindspeed(temp.wind);
            it2->setaimtemp(temp.tem);
            (it2)->putair(sv->getfeelist(), (sv)->gethoc());
           // qDebug()<<__LINE__;
//            temp.tem = (it2)->getaimtemp();
//            temp.cost = it2->getfee();
//            temp.s = it2->getstate();
//            temp.wind = it2->getwindspeed();
//            //qDebug()<<__LINE__;
//            const char * sb = parser::parse(temp).c_str();
            //qDebug()<<sb;
            //it2->air_socket->write(sb);
            //sv->server_send(*it2);
            emit sv->signal_send(*it2);

        }

    }
}

