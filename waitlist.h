#ifndef WAITLIST_H
#define WAITLIST_H
#include <queue>
#include <list>
#include "LINKLIST.h"
using namespace std;

class waitlist
{
public:
    waitlist();
    list<Ac*> container;
    list<Ac*>::iterator it;
    Ac* refresh();
    void inserthead(Ac val);
    int trigger_num = 10;
};


#endif // WAITLIST_H
