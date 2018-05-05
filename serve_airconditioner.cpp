#include"serve_airconditioner.h"

int serve_airconditioner::putair(int *feelist)
{
	this->judge();
	if (this->state = 1)
	{
		this->nowtemp -= this->windspeed*0.1;
		this->fee += feelist[this->windspeed];
		this->theinfor._fee = this->fee;
		this->theinfor._temputre = this->nowtemp;
		this->theinforable = 1;
		return 1;
	}
	else
		return 0;
}