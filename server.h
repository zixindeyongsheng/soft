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
	int feelist[3];

public:
	//监听并连接
	//定期制冷
	//定期发送
	//定期接收
	//定期
	void setfeelist(int fee1, int fee2, int fee3)
	{
		this->feelist[0] = fee1;
		this->feelist[1] = fee2;
		this->feelist[2] = fee3;
	}
};