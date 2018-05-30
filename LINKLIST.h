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
    //int state;//运行状态
    //int j;//链表中的位置，默认为0（不在链表中）
    Ac() {}
    Ac(string n, int t, int ss, double temp, int w,double c) :num(n), type(t), s(ss), tem(temp), wind(w),cost(c) {}// state(s) {};

};


//创建一个list容器的实例LISTINT
typedef list<Ac> LISTINT;


class LinkList {
public:
    LinkList();
    void inserthead(Ac val);//链表头部插入节点
    //void insert(Ac val);//插入节点
    void remov(Ac val);//删除节点
    LISTINT& search();//搜索服务节点
    int length();//链表长度
private:
    //创建一个list容器的实例LISTINT
    LISTINT listone;
    LISTINT listzero;
    LISTINT listtwo;
    LISTINT listserve;
    map<string, LISTINT::iterator> mymap1;
    map<string, LISTINT::iterator>mymap2;
    map<string, LISTINT::iterator>mymap0;
    LISTINT::iterator current0;//保存服务的第一个指针
    LISTINT::iterator current2;
    LISTINT::iterator current1;
    int running;//服务能力个数
};
#endif
