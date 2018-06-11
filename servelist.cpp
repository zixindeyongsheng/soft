#include "servelist.h"
#include<QDebug>
#include"LINKLIST.h"
void servelist::refresh(){
    list<Ac*>::iterator it;
    for(it = container.begin();it != container.end(); ++it){
        qDebug()<<(*it)->num.c_str();
        (*it)->counter++;
    }
}
void servelist::inserthead(Ac val){
    it = find_if(container.begin(), container.end(),bind2nd(comp(), &val));
    if(it == container.end()){
        val.counter = 0;
        Ac * elem = new Ac(val);
        container.push_back(elem);
    }
    else{
        (*it)->assign(&val);
    }

}
int servelist::serve_num(){

    return container.size();
}
