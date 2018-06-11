#ifndef SERVELIST_H
#define SERVELIST_H
#include <list>
class Ac;
class servelist
{
public:
    servelist(){}
    int max = 5;
    std::list<Ac*> container;
    std::list<Ac*>::iterator it;
    void inserthead(Ac val);
    int serve_num();
    void refresh();
};

#endif // SERVELIST_H
