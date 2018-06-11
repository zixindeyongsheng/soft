#include "waitlist.h"

waitlist::waitlist()
{
}
void waitlist::inserthead(Ac val){
    it = find_if(container.begin(), container.end(),bind2nd(comp(), &val));
    if(it == container.end()){
        val.counter = trigger_num;
        Ac * elem = new Ac(val);
        container.push_back(elem);
    }
    else{
        (*it)->assign(&val);
    }

}
Ac* waitlist::refresh(){
    bool met = false;
    Ac *ret = nullptr;
    for(it = container.begin();it != container.end();){
        if(!met && (*it)->counter <= 1){
            met = true;
            ret = *it;
            it = container.erase(it);
            continue;
        }
        (*it)->counter --;
        ++it;
    }
    return ret;
}
