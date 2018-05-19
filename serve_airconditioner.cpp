#include"serve_airconditioner.h"

int serve_airconditioner::putair(int **feelist,int hoc)
{
	this->judge(hoc);
	if (this->state == 1)
	{
		if (hoc == 1)//ÖÆÀä
			this->nowtemp -= this->windspeed*0.1*PUTAIRTIME;
		else//ÖÆÈÈ
			this->nowtemp += this->windspeed*0.1*PUTAIRTIME;
		this->fee += feelist[hoc][this->windspeed]*PUTAIRTIME;
		this->theinforable = 1;
		return 1;
	}
	else
		return 0;
}
