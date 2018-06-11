#include"serve_airconditioner.h"
static int PUTAIRTIME = 1;//制冷周期

int serve_airconditioner::putair(float feelist[],int hoc)
{
    this->judge(hoc);
    if (this->state == 1)
    {
        if (hoc == 1)//制冷
            this->nowtemp -= this->windspeed*0.1*PUTAIRTIME;
        else//制热
            this->nowtemp += this->windspeed*0.1*PUTAIRTIME;
        this->fee += (float)feelist[this->windspeed]*PUTAIRTIME;
        this->theinforable = 1;
        return 1;
    }
    else
        return 0;
}
