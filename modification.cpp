#include "modification.h"

#include <thread>
#include <mutex>
#include <condition_variable>
#include "LINKLIST.h"
#include <list>
#include "server.h"
#include <vector>
#include <algorithm>
#include "parse.h"
using namespace std;
struct comp:binary_function<serve_airconditioner, string, bool>{
    bool operator()(serve_airconditioner &v, string str)const{
            if (v.getroomnumber() == str) {
                return true;
            }else
                return false;
    }
};
mutex mtx;
condition_variable produce, consume;
int maxSize = 5;
list<Ac> q;
LinkList * s;
list<Ac>::iterator it;
server * sv;
void producer(){
    while (true) {
        this_thread::sleep_for(chrono::milliseconds(100));
        unique_lock<mutex> lck(mtx);
        while (q.size() >=5) {
            produce.wait(lck);
        }
        //q.push_back(s -> first)
        consume.notify_all();

    }
}

void consumer(){
    while (true) {
        this_thread::sleep_for(chrono::milliseconds(100));

        unique_lock<mutex> lck(mtx);
        while (q.size() == 0) {
            consume.wait(lck);
        }
        it = q.begin();
        Ac temp = *it;
        vector<serve_airconditioner> airconds = sv->serve_airconditionerptr;
        vector<serve_airconditioner>::iterator it2 = find_if(airconds.begin(), airconds.end(), bind2nd(comp(), temp.num));
        (it2)->putair((sv)->getfeelist(), (sv)->gethoc());
        temp.tem = (it2)->getaimtemp();
        temp.cost = it2->getfee();
        temp.s = it2->getstate();
        temp.wind = it2->getwindspeed();
        it2->air_socket->write(parser::parse(temp));
        q.erase(it);
        produce.notify_all();
    }
}
void start(){
    thread a(producer);
    thread b(consumer);
    a.join();
    b.join();
}
