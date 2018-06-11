#ifndef LINKLIST_H
#define LINKLIST_H
#include<string>
#include <iostream>
#include <list>
#include <numeric>
#include <algorithm>
#include <map>
using namespace std;
class Ac {
public:
    string num;//IP或房间号
    int type;//报文种类
    int s;//开关
    double tem;//温度
    int wind;//风速
    double cost;//金额
    int counter = 0;
    Ac() {}
    Ac(string n, int t, int ss, double temp, int w,double c) :num(n), type(t), s(ss), tem(temp), wind(w),cost(c) {}// state(s) {};


    void assign(Ac * it){
        num = it->num;
        type = it->type;
        s = it->s;
        tem = it->tem;
        wind = it->wind;
        cost = it->cost;
        counter = it->counter;
    }

};
struct comp:binary_function<Ac*, Ac*, bool>{
    bool operator()(Ac*v, Ac*r)const{
            if (v->num  == r->num) {
                return true;
            }else
                return false;
    }
};

//创建一个list容器的实例LISTINT
typedef list<Ac*> LISTINT;
#endif
