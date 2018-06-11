#ifndef BASE_LIST_H
#define BASE_LIST_H
#include <QObject>
#include "servelist.h"
#include "waitlist.h"
#include "LINKLIST.h"
#include <QTimer>
#include <algorithm>
class server;
class producer;
class base_list:public QObject
{
    Q_OBJECT
private slots:
    void refresh();
public:
    int max = 5;
    base_list(server&);
    servelist sv_lst;
    waitlist wt_lst;
    int servenum();//size of serve list
    bool can_be_served();
    void inserthead(Ac val);
    LISTINT& search();
    QTimer *timer;
    producer * pdc;
    servelist& get_sv_ref();
    waitlist& get_wt_ref();
private:
signals:

};
#endif // BASE_LIST_H
