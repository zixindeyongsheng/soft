#pragma once
#include<iostream>
#include<string.h>
#include<QTcpSocket>
using namespace std;




class serve_airconditioner 
{
private:
	float aimtemp;

	float fee;
	int state;//是否正在运作
    int s;
	int windspeed;//设定风速
	string roomnumber;
	int theinforable;//报文有效性
    float nowtemp;
public:

    QTcpSocket* air_socket;
    serve_airconditioner(){
        aimtemp=25;
        nowtemp=25;
        fee=0;
        state=0;//是否正在运作
        windspeed=0;//设定风速
        roomnumber="";
        theinforable=0;//报文有效性
        air_socket=NULL;
        s=0;
    }
    ~serve_airconditioner(){

    }
	int putair(int **feelist,int hoc);//运行则返回1，否则返回0
	void judge(int hoc)//判断是否达到设定温度
	{
        if(s == 1)//空调开启状态
        {
            if (hoc == 1)//制冷温度高于设定则启动，否则开启
                if (aimtemp < nowtemp)
                    this->state = 1;
                else
                    this->state = 0;
            else//制热温度低于设定温度则启动，否则开启
                if (aimtemp < nowtemp)
                    this->state = 0;
                else
                    this->state = 1;
        }

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
	int gettheinforable()
	{
		return this->theinforable;
	}
    string getroomnumber()
    {
		return this->roomnumber;
	}
    int getstate()
    {
        return this->state;
    }
    int gets()
    {
        return this->s;
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
	void settheinforable(int theinforable)
	{
		this->theinforable = theinforable;
	}
	void setroomnumber(string roomnumber)
	{
		this->roomnumber = roomnumber;
	}
    void setstate(int state)
    {
        this->state=state;
    }
    void sets(int s)
    {
        this->s=s;
    }
};
