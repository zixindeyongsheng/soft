#include"LINKLIST.h"
#include<string>
#include<iostream>
using namespace std;

LinkList::LinkList() {
	current0 = listzero.end();
	current1 = listone.end();
	current2 = listtwo.end();
	running = 5;//服务能力5
}

void LinkList::inserthead(Ac val)//前插入节点,int j为search后的插入位置
{
	int x;
	LISTINT::iterator j;
	map<string, LISTINT::iterator>::iterator it;
	if (val.wind == 0) {//风速为零
		j = current0;//插入位置一定为服务头前
	    it = mymap0.find(val.num);//查重
		if (it == mymap0.end()) {//不重复
			if (listzero.empty()||j==listzero.end()) {//为空或服务在当前的头直接插入到头
					listzero.push_back(val);
					j = listzero.end();
					j--;
				}
				else{
					listzero.insert(j, val);
					j--;//插入节点的位置
				}
				mymap0[val.num] = j;
				//val.state = 0;//设置状态为为服务
		}
		it = mymap1.find(val.num);//是否在其他链表中
		if (it != mymap1.end()) {
			mymap1[val.num] = listone.erase(mymap1[val.num]);
			mymap1.erase(val.num);
		}
		it = mymap2.find(val.num);
		if (it != mymap2.end()) {
			mymap2[val.num] = listtwo.erase(mymap2[val.num]);
			mymap2.erase(val.num);
		}
	}
	else if (val.wind == 1) {
		it = mymap1.find(val.num);//查重
	    j = current1;//插入位置一定为服务头前
		if (it == mymap1.end()) {//不重复
			if (listone.empty()|| j == listone.end()) {//为空或服务在当前的头直接插入到头
				listone.push_back(val);
				j = listone.end();
				j--;
			}
			else {
				listone.insert(j, val);
				j--;//插入节点的位置
			}
			mymap1[val.num] = j;
			//val.state = 0;//设置状态为为服务
		}
		it = mymap0.find(val.num);//是否在其他链表中
		if (it != mymap0.end()) {
			mymap0[val.num] = listzero.erase(mymap0[val.num]);
			mymap0.erase(val.num);
		}
		it = mymap2.find(val.num);
		if (it != mymap2.end()) {
			mymap2[val.num] = listtwo.erase(mymap2[val.num]);
			mymap2.erase(val.num);
		}
	}
	else {
		it = mymap2.find(val.num);//查重
		j = current2;//插入位置一定为服务头前
		if (it == mymap2.end()) {//不重复
			if (listtwo.empty()||j == listtwo.end()) {//为空或服务在当前的头直接插入到头
				listtwo.push_back(val);
				j = listtwo.end();
				j--;
			}
			else {
				listtwo.insert(j, val);
				j--;//插入节点的位置
			}
			mymap2[val.num] = j;
			//val.state = 0;//设置状态为为服务
		}
		if (it != mymap0.end()) {
			mymap0[val.num] = listzero.erase(mymap0[val.num]);
			mymap0.erase(val.num);
		}
		it = mymap1.find(val.num);
		if (it != mymap1.end()) {
			mymap1[val.num] = listone.erase(mymap1[val.num]);
			mymap1.erase(val.num);
		}
	}
	
}


/*void LinkList::insert(Ac val)//后插入节点
{
	int x;
	LISTINT::iterator j;
	j = search(val);
	if (val.wind == 0) {//风速为零
		if (listzero.empty()) {//为空直接插入到尾部
			listzero.push_back(val);
			j = listzero.begin();
		}
		else {
			listzero.insert(j, val);
			j--;//插入节点的位置
		}
		mymap0[val.num] = j;
		//val.state = 0;//设置状态为为服务
	}
	else if (val.wind == 1) {
		if (listone.empty()) {//为空直接插入到尾部
			listone.push_back(val);
			j = listone.begin();
		}
		else {
			listone.insert(j, val);
			j--;//插入节点的位置
		}
		mymap1[val.num] = j;
		//val.state = 0;//设置状态为为服务
	}
	else {
		if (listtwo.empty()) {//为空直接插入到尾部
			listtwo.push_back(val);
			j = listtwo.begin();
		}
		else {
			listtwo.insert(j, val);
			j--;//插入节点的位置
		}
		mymap2[val.num] = j;
		//val.state = 0;//设置状态为为服务
	}
}*/

void LinkList::remov(Ac val)//删除节点
{
	LISTINT::iterator j;
	if (val.wind == 0) {
		j = mymap0[val.num];
		mymap0.erase(val.num);
		j=listzero.erase(j);
	}
	else if (val.wind == 1) {
		j = mymap1[val.num];
		mymap1.erase(val.num);
		j = listone.erase(j);
	}
	else {
		j = mymap2[val.num];
		mymap2.erase(val.num);
		j = listtwo.erase(j);
	}
}


int LinkList::length()//链表长度
{
	return listone.size();
}

LISTINT::iterator  LinkList::search(int wind)//搜索服务节点
{
	LISTINT::iterator j;
	int i;
	if (wind == 0) {
		j = current0;
		if (listzero.empty()) {
			cout << "无需服务项目" << endl;
		}
		else if (j == listzero.end()) {
			j = listzero.begin();
			return j;
		}
		else {
			for (i = 1; i < running; i++)
				j++;
			return j;
		}

	}
}
