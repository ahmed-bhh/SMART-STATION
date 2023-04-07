#include "notif.h"
#include <QSystemTrayIcon>
#include <QString>

notif::notif()
{
CIN=0;
}

notif::notif(QString NOM , QString PRENOM)
{
    this->NOM=NOM;
    this->PRENOM=PRENOM;
}

void notif::afficher()
{

    QSystemTrayIcon *notifyIcon = new QSystemTrayIcon;
    notifyIcon->setIcon(QIcon("C:\\Users\\HOUYEM\\Desktop\\UberStation_2A24\\client\\user.png"));

    notifyIcon->showMessage(NOM,PRENOM,QSystemTrayIcon::Information,15000);
     notifyIcon->show();;

}


