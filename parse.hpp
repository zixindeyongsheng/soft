#ifndef pa
#define pa
#include <string>

#include "LINKLIST.h"
using namespace std;

class parser{
public:
    static Ac parse(const char*);
    static const string parse(Ac);

};
#endif
