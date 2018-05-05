#pragma once
#include<iostream>
#include<string.h>
#include"infor.h"
using namespace std;

static int PUTAIRTIME = 1;//��������


class serve_airconditioner 
{
private:
	float aimtemp;
	float nowtemp;
	float fee;
	int state;//�Ƿ���������
	int windspeed;//�趨����
	string roomnumber;
	infor theinfor;//��һ����Ҫ���͵ı���
	int theinforable;//������Ч��

public:
	int putair(int *feelist);//�����򷵻�1�����򷵻�0
	void judge()//�ж��Ƿ�ﵽ�趨�¶�
	{
		if (fabs(aimtemp - nowtemp) < 0.1*PUTAIRTIME)
			this->state = 0;
	}
	float getaimtemp()
	{
		return this->aimtemp;
	}
	float getnowtemp()
	{
		return this->nowtemp;
	}
	float getfee()
	{
		return this->fee;
	}
	int getwindspeed()
	{
		return this->windspeed;
	}
	infor gettheinfor()
	{
		return this->theinfor;
	}
	int gettheinforable()
	{
		return this->theinforable;
	}
	string getroomnumber() {
		return this->roomnumber;
	}

	void setaimtemp(float temp)
	{
		this->aimtemp = temp;
	}
	void setnowtemp(float temp)
	{
		this->nowtemp = temp;
	}
	void setfee(float fee)
	{
		this->fee = fee;
	}
	void setwindspeed(int windspeed)
	{
		this->windspeed = windspeed;
	}
	void settheinfor(infor theinfor)
	{
		this->theinfor = theinfor;
	}
	void settheinforable(int theinforable)
	{
		this->theinforable = theinforable;
	}
	void setroomnumber(string roomnumber)
	{
		this->roomnumber = roomnumber;
	}
};