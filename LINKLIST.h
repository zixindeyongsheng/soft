#pragma once
#ifndef LINKLIST_H
#define LINKLIST_H
#include<string>
#include <iostream>   
#include <list>   
#include <numeric>   
#include <algorithm> 
#include <map>
using namespace std;

//����һ��list������ʵ��LISTINT   
typedef list<Ac> LISTINT;

class Ac {
public:
	string num;//IP�򷿼��
	int type;//��������
	int s;//����
	double tem;//�¶�
	int wind;//����
	double cost;//���
	//int state;//����״̬
	//int j;//�����е�λ�ã�Ĭ��Ϊ0�����������У�
	Ac() {}
	Ac(string n, int t, int ss, double temp, int w, int s,double c) :num(n), type(t), s(ss), tem(temp), wind(w),cost(c) {}// state(s) {};

};


class LinkList {
public:
	LinkList();
	void inserthead(Ac val);//����ͷ������ڵ�
	//void insert(Ac val);//����ڵ�
	void remov(Ac val);//ɾ���ڵ�
	LISTINT::iterator search();//��������ڵ�
	int length();//������
private:
	//����һ��list������ʵ��LISTINT   
	LISTINT listone;
	LISTINT listzero;
	LISTINT listtwo;
	LISTINT listserve;
	map<string, LISTINT::iterator> mymap1;
	map<string, LISTINT::iterator>mymap2;
	map<string, LISTINT::iterator>mymap0;
	LISTINT::iterator current0;//�������ĵ�һ��ָ��
	LISTINT::iterator current2;
	LISTINT::iterator current1;
	int running;//������������
};
#endif


/*

hash_map<int, string> mymap = new hash_map<int, string>;
*mymap[9527]="�Ʋ���������";
*mymap[1000000]="�����̵�����";
*mymap[10000]="����Ĺ��ʵ���";
...
if(mymap.find(10000) != mymap.end()){
*/