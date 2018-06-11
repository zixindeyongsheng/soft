#include "modification.h"
#include <qdebug.h>
#include<thread>
#include <QSemaphore>
#include<QMetaType>
#include <vector>
#include <algorithm>
#include "parse.hpp"
#include "server.h"
using namespace std;
struct comp2:binary_function<serve_airconditioner, string, bool>{
    bool operator()(serve_airconditioner &v, string str)const{
            if (v.getroomnumber() == str) {
                return true;
            }else
                return false;
    }
};

producer::producer(base_list *a, server *b){
    s = a->get_sv_ref();
    w = a->get_wt_ref();
    max = a->max;
    sv = b;
    airconds = sv->serve_airconditionerptr;
}

void producer::run(){
        for(it = s.container.begin();it != s.container.end();){
            temp = *(*it);
            it2 = find_if(airconds.begin(), airconds.end(), bind2nd(comp2(), temp.num));
            if(it2 == airconds.end()){
                qDebug()<<"havn't' find out";
                ++it;
                continue;
            }
            it2->sets(temp.s);
            it2->setwindspeed(temp.wind);
            it2->setaimtemp(temp.tem);
            if(it2->getnowtemp() == temp.tem){
                t = w.container.begin();
                e = w.container.end();
                w.inserthead(*(*it));
                if(t!=e){
                    Ac tm(*(*it));
                    (*it)->assign(*t);
                    (*it)->counter = 0;
                }else{
                    s.container.remove(*it);
                    continue;
                }

            }
            (it2)->putair(sv->getfeelist(), (sv)->gethoc());
            emit sv->signal_send(*it2);
            ++it;
        }

}
