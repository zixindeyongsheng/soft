#include<iostream>
#include<string.h>
#include<vector>
using namespace std;
#include"serve_airconditioner.h"

class server
{
private:
	vector<serve_airconditioner> serve_airconditionerptr;
	int serve_airconditionernum;
	int feelist[2][3];
	int hoc;//����1/����0

public:
	//����������
	//��������
	//���ڷ���
	//���ڽ���
	//����
	void setfeelist(int fee1, int fee2, int fee3,int hoc)//���÷���
	{
		this->feelist[hoc][0] = fee1;
		this->feelist[hoc][1] = fee2;
		this->feelist[hoc][2] = fee3;
	}
};