#include"serve_airconditioner.h"

int serve_airconditioner::putair(int *feelist)
{
	this->judge();
	if (this->state == 1)
	{
		if (nowtemp > aimtemp)
			this->nowtemp -= this->windspeed*0.1*PUTAIRTIME;
		else
			this->nowtemp += this->windspeed*0.1*PUTAIRTIME;
		this->fee += feelist[this->windspeed]*PUTAIRTIME;
		this->theinforable = 1;
		return 1;
	}
	else
		return 0;
}