#ifndef MODIFICATION_H
#define MODIFICATION_H
#include "LINKLIST.h"
#include "server.h"
#include <QtCore/QCoreApplication>
#include <QThread>
class producer:public QThread
{
Q_OBJECT
public:
    producer(LinkList * a, server *b);
    void run();

};

#endif // MODIFICATION_H
