#include <QApplication>
#include"server.h"
#include "linklist.h"
#include"modification.h"
int main(int argc, char* argv[])
{
    QApplication a(argc, argv);
    LinkList *lk = new LinkList();
//    Ac *sb = new Ac();
//    Ac * ss = new Ac();
//    lk->inserthead(*sb);
//    lk->inserthead(*ss);
//    server  *toolserver = new server(lk);
    //server toolserver(NULL);

     server toolserver;
     toolserver.putlinklist(lk);

//    (toolserver->get_vec_ptr()).push_back(serve_airconditioner(sb->num));
//    (toolserver->get_vec_ptr()).push_back(serve_airconditioner(ss->num));

    toolserver.sethoc(1);
    toolserver.setfeelist(0,0.1,0.2,1);
    QThread t;
    producer p(lk, &toolserver);
    p.start();
    return a.exec();
}
