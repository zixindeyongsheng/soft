#pragma once
#include<iostream>
#include<string.h>
#include<QTcpSocket>
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
	int theinforable;//������Ч��
	
public:
    QTcpSocket air_socket;
	int putair(int **feelist,int hoc);//�����򷵻�1�����򷵻�0
	void judge(int hoc)//�ж��Ƿ�ﵽ�趨�¶�
	{
		if (hoc == 1)//�����¶ȸ����趨��������������
			if (aimtemp < nowtemp)
				this->state = 1;
			else
				this->state = 0;
		else//�����¶ȵ����趨�¶���������������
			if (aimtemp < nowtemp)
				this->state = 0;
			else
				this->state = 1;
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
	void settheinforable(int theinforable)
	{
		this->theinforable = theinforable;
	}
	void setroomnumber(string roomnumber)
	{
		this->roomnumber = roomnumber;
	}
};
