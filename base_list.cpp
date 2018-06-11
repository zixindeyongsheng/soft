#include "base_list.h"
#include "server.h"
#include "modification.h"
base_list::base_list(server& toolserver)
{
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(refresh()));
    timer->start(1000);
    pdc = new producer(this, &toolserver);
}
LISTINT& base_list::search(){
    return wt_lst.container;
}

int base_list::servenum(){
    return sv_lst.serve_num();
}

bool base_list::can_be_served(){
    if(servenum() > max)
        return false;
    else
        return true;
}

void base_list::inserthead(Ac val){
    list<Ac*>::iterator it;
    if(can_be_served()){
        sv_lst.inserthead(val);
    }else{
        if(val.wind <= 1)
            wt_lst.inserthead(val);
        else{
            it = sv_lst.container.begin();
            wt_lst.inserthead(*(*it));
            (*it)->assign(&val);
        }
    }
}
void base_list::refresh(){
    sv_lst.refresh();
    Ac* candidate = wt_lst.refresh();
    if(candidate){
        list<Ac*>::iterator it = sv_lst.container.begin();
        (*it)->assign(candidate);
        wt_lst.inserthead(*(*it));
    }
    pdc->run();
}
servelist& base_list::get_sv_ref(){
    return sv_lst;
}

waitlist& base_list::get_wt_ref(){
    return wt_lst;
}


