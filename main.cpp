#include "maquette.h"
#include"login.h"
#include <QApplication>
#include <QMessageBox>
#include "connection.h"
#include "chatserver.h"
using namespace ApexAlliance;
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    maquette w;
    login l;
    Connection cnx;

    bool test=cnx.createconnect();
    ChatServer Server;
        if(!Server.startServer(3333)){
            qDebug()<<"Error:"<<Server.errorString();
            //return 1;

        }
        qDebug()<<"Server   started ...";
    if(test)
    {l.show();
        QMessageBox::information(nullptr, QObject::tr("database is open"),
                    QObject::tr("connection successful.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);

}
    else
        QMessageBox::critical(nullptr, QObject::tr("database is not open"),
                    QObject::tr("connection failed.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);



    return a.exec();
}
