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
		it = mymap0.find(val.num);
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

LISTINT::iterator  LinkList::search()//搜索服务节点
{
	LISTINT::iterator j;
	int i = 0;
	listserve.clear();//删除所有已在元素
	if (listtwo.empty()) {//如果风速2为空
		if (listone.empty()) {//如果风速1为空
			return listzero.end();
		}
		else {//风速1不为空
			j = current1;
			if (j == listone.end()) {//如果服务节点定位在尾节点
				j = listone.begin();
				for (i = 1; i <=  running; i++) {
					listserve.push_back(*j);
					j++;
					if (j == listone.end()) {//服务数量小于服务能力
						current1 = listserve.begin();//下一次从头服务
						return listserve.begin();
					}
				}
				current1 = ++j;
				return listserve.begin();
			}
			else {//服务节点不在尾节点
				j = current1;
				for (i = 1; i < running; i++) {
					listserve.push_back(*j);
					j++;
					if (j == listone.end()) {//剩余服务数量小于服务能力
						current1 = listserve.begin();//下一次从头服务
					}
					else {
						current1 = ++j;
					}
				}

			}
		}
	}
	else {//风速2不为空
		j = current2;
		if (j == listtwo.end()) {//第一次调用风速2链表
			j = listtwo.begin();
			if (/*j == listtwo.end()&&*/listtwo.size() < running) {//风速2数量不够
				for (j = listtwo.begin(); j != listtwo.end(); j++) {
					listserve.push_back(*j);
					i++;
				}
				current2 = listtwo.begin();
				j = current1;
				if (j == listone.end()) {//如果服务节点定位在尾节点
					j = listone.begin();
					for (; i < running; i++) {
						listserve.push_back(*j);
						j++;
						if (j == listone.end()) {//服务数量小于服务能力
							current1 = listserve.begin();//下一次从头服务
							return listserve.begin();
						}
						else {
							current1 = j;
						}
					}
					current1 = ++j;
				}
				else {//服务节点不在尾节点
					if (listone.size() > running - i) {
						for (; i < running; i++) {
							listserve.push_back(*j);
							j++;
							if (j == listone.end()) {//剩余服务数量小于服务能力
								j = listserve.begin();//下一次从头服务
								current1 = j;
							}
							else {
								current1 = ++j;
							}
						}

					}
					else {
						for (j = listone.begin(); j != listone.end(); j++) {
							listserve.push_back(*j);
							current1 = listone.begin();
						}
					}
					return listserve.begin();
				}
			}
			else {//风速2数量足够
				for (i = 1; i < running; i++) {
					listserve.push_back(*j);
					j++;
				}
				current2 = ++j;
			}
			return listserve.begin();
		}
		else {//服务不在尾节点
			j = current2;
			if (listtwo.size() > running) {
				for (i = 1; i < running; i++) {
					listserve.push_back(*j);
					j++;
					if (j == listtwo.end()) {
						j = listtwo.begin();
					}
				}
				current2 = ++j;
			}
			else {
				for (j = listtwo.begin(); j != listtwo.end(); j++) {
					i++;
					listserve.push_back(*j);
				}
				j = current1;
				if (j == listone.end()) {//如果服务节点定位在尾节点
					j = listone.begin();
					for (; i < running; i++) {
						listserve.push_back(*j);
						j++;
						if (j == listone.end()) {//服务数量小于服务能力
							current1 = listserve.begin();//下一次从头服务
							return listserve.begin();
							//return;
						}
						else {
							current1 = ++j;
						}
					}
				}
				else {//服务节点不在尾节点
					if (listone.size() > running - i) {
						for (; i < running; i++) {
							listserve.push_back(*j);
							j++;
							if (j == listone.end()) {//剩余服务数量小于服务能力
								j = listserve.begin();//下一次从头服务
								current1 = j;
							}
							else {
								current1 = ++j;
							}
						}
					}
				}
			}
		}
	}
	return listserve.begin();
}
