#include <QApplication>
#include"server.h"
//#include<QThread>
#include <synchapi.h>

int main(int argc, char* argv[])
{
    server toolserver;
    while(true)
    {
        toolserver.server_send();
    }

    system("pause");
    return 0;
}
