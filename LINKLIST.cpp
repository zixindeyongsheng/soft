#include"LINKLIST.h"
#include<string>
#include<iostream>
using namespace std;

LinkList::LinkList() {
	current0 = listzero.end();
	current1 = listone.end();
	current2 = listtwo.end();
	running = 5;//��������5
}

void LinkList::inserthead(Ac val)//ǰ����ڵ�,int jΪsearch��Ĳ���λ��
{
	int x;
	LISTINT::iterator j;
	map<string, LISTINT::iterator>::iterator it;
	if (val.wind == 0) {//����Ϊ��
		j = current0;//����λ��һ��Ϊ����ͷǰ
	    it = mymap0.find(val.num);//����
		if (it == mymap0.end()) {//���ظ�
			if (listzero.empty()||j==listzero.end()) {//Ϊ�ջ�����ڵ�ǰ��ͷֱ�Ӳ��뵽ͷ
					listzero.push_back(val);
					j = listzero.end();
					j--;
				}
				else{
					listzero.insert(j, val);
					j--;//����ڵ��λ��
				}
				mymap0[val.num] = j;
				//val.state = 0;//����״̬ΪΪ����
		}
		it = mymap1.find(val.num);//�Ƿ�������������
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
		it = mymap1.find(val.num);//����
	    j = current1;//����λ��һ��Ϊ����ͷǰ
		if (it == mymap1.end()) {//���ظ�
			if (listone.empty()|| j == listone.end()) {//Ϊ�ջ�����ڵ�ǰ��ͷֱ�Ӳ��뵽ͷ
				listone.push_back(val);
				j = listone.end();
				j--;
			}
			else {
				listone.insert(j, val);
				j--;//����ڵ��λ��
			}
			mymap1[val.num] = j;
			//val.state = 0;//����״̬ΪΪ����
		}
		it = mymap0.find(val.num);//�Ƿ�������������
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
		it = mymap2.find(val.num);//����
		j = current2;//����λ��һ��Ϊ����ͷǰ
		if (it == mymap2.end()) {//���ظ�
			if (listtwo.empty()||j == listtwo.end()) {//Ϊ�ջ�����ڵ�ǰ��ͷֱ�Ӳ��뵽ͷ
				listtwo.push_back(val);
				j = listtwo.end();
				j--;
			}
			else {
				listtwo.insert(j, val);
				j--;//����ڵ��λ��
			}
			mymap2[val.num] = j;
			//val.state = 0;//����״̬ΪΪ����
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


void LinkList::remov(Ac val)//ɾ���ڵ�
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


int LinkList::length()//������
{
	return listone.size();
}

LISTINT& LinkList::search()//��������ڵ�
{
	LISTINT::iterator j;
	int i = 0;
	listserve.clear();//ɾ����������Ԫ��
	if (listtwo.empty()) {//�������2Ϊ��
		if (listone.empty()) {//�������1Ϊ��
            return listzero;
		}
		else {//����1��Ϊ��
			j = current1;
			if (/*j == listtwo.end()&&*/listone.size() < running) {//����1��������
				for (j = listone.begin(); j != listone.end(); j++) {
					listserve.push_back(*j);
					i++;
				}
				current1 = listone.begin();
                return listserve;
			}
			else {//����1�����㹻
				if (current1 == listone.end())
					j = listone.begin();
				else
					j = current1;
				for (i = 1; i <= running; i++) {
					listserve.push_back(*j);
					j++;
					if (j == listone.end()) {//ʣ���������С�ڷ�������
						j = listone.begin();//��һ�δ�ͷ����
					}
					else {
						current1 = j;
					}
				}

			}
		}
	}
	else {//����2��Ϊ��
		j = current2;
		if (j == listtwo.end()) {//��һ�ε��÷���2����
			j = listtwo.begin();
			if (/*j == listtwo.end()&&*/listtwo.size() < running) {//����2��������
				for (j = listtwo.begin(); j != listtwo.end(); j++) {
					listserve.push_back(*j);
					i++;
				}
				current2 = listtwo.begin();
				j = current1;
				if (j == listone.end()) {//�������ڵ㶨λ��β�ڵ�
					if (listone.size() == 0)
                        return listserve;
					else
						j = listone.begin();
					for (; i < running; i++) {
						listserve.push_back(*j);
						j++;
						if (j == listone.end()) {//��������С�ڷ�������
							current1 = listone.begin();//��һ�δ�ͷ����
                            return listserve;
						}
						else {
							current1 = j;
						}
					}
					current1 = j;
				}
				else {//����ڵ㲻��β�ڵ�
					if (listone.size() > running - i) {
						for (; i < running; i++) {
							listserve.push_back(*j);
							j++;
							if (j == listone.end()) {//ʣ���������С�ڷ�������
								j = listserve.begin();//��һ�δ�ͷ����
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
                    return listserve;
				}
			}
			else {//����2�����㹻
				for (i = 1; i <= running; i++) {
					listserve.push_back(*j);
					j++;
				}
				current2 = j;
			}
            return listserve;
		}
		else {//������β�ڵ�
			j = current2;
			if (listtwo.size() > running) {
				for (i = 1; i <= running; i++) {
					listserve.push_back(*j);
					j++;
					if (j == listtwo.end()) {
						j = listtwo.begin();
					}
				}
				current2 = j;
			}
			else {
				for (j = listtwo.begin(); j != listtwo.end(); j++) {
					i++;
					listserve.push_back(*j);
				}
				j = current1;
				if (j == listone.end()) {//�������ڵ㶨λ��β�ڵ�
					if (listone.size() == 0)
                        return listserve;
					else
						j = listone.begin();
					for (; i < running; i++) {
						listserve.push_back(*j);
						j++;
						if (j == listone.end()) {//��������С�ڷ�������
							current1 = listserve.begin();//��һ�δ�ͷ����
                            return listserve;
							//return;
						}
						else {
							current1 = ++j;
						}
					}
				}
				else {//����ڵ㲻��β�ڵ�
					if (listone.size() > running - i) {
						for (; i < running; i++) {
							listserve.push_back(*j);
							j++;
							if (j == listone.end()) {//ʣ���������С�ڷ�������
								j = listone.begin();//��һ�δ�ͷ����
								current1 = j;
							}
							else {
								current1 = j;
							}
						}
					}
					else {
						j = listone.begin();
						for (j = listone.begin(); j != listone.end();j++) {
							listserve.push_back(*j);
						}
					}
				}
			}
		}
	}
    return listserve;
}
