#include <QApplication>
#include"server.h"
//#include<QThread>
#include <synchapi.h>

int main(int argc, char* argv[])
{
    QApplication a(argc, argv);

    server toolserver;

    return a.exec();
}
