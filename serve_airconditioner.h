#pragma once
#include<iostream>
#include<string.h>
#include"infor.h"
using namespace std;

static int PUTAIRTIME = 1;//制冷周期


class serve_airconditioner 
{
private:
	float aimtemp;
	float nowtemp;
	float fee;
	int state;//是否正在运作
	int windspeed;//设定风速
	string roomnumber;
	infor theinfor;//下一次需要发送的报文
	int theinforable;//报文有效性

public:
	int putair(int *feelist);//制冷则返回1，否则返回0
	void judge()//判断是否达到设定温度
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