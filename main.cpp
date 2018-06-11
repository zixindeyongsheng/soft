#include <QApplication>
#include"server.h"
#include "LINKLIST.h"
#include "base_list.h"
int main(int argc, char* argv[])
{
    QApplication a(argc, argv);
    server toolserver;
    LinkList *lk = new LinkList(toolserver);
    toolserver.putlinklist(lk);

//    (toolserver->get_vec_ptr()).push_back(serve_airconditioner(sb->num));
//    (toolserver->get_vec_ptr()).push_back(serve_airconditioner(ss->num));

    toolserver.sethoc(0);
    toolserver.setfeelist(0,0.1,0.2,0);
    return a.exec();
}
