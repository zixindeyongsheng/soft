#ifndef MODIFICATION_H
#define MODIFICATION_H
#include "LINKLIST.h"
#include "server.h"
#include <QtCore/QCoreApplication>
#include <QThread>
#include "base_list.h"
class producer:public QThread
{
Q_OBJECT
public:
    producer(base_list * a, server *b);
    void run();
    LISTINT::iterator it;
    list<Ac*>::iterator t,e;
    Ac temp;
    int max;
    servelist s;
    waitlist w;
    server * sv;
    vector<serve_airconditioner> airconds;
    vector<serve_airconditioner>::iterator it2;

};

#endif // MODIFICATION_H
