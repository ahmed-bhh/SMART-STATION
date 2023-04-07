#ifndef NOTIF_H
#define NOTIF_H
#include <QSystemTrayIcon>
#include <QString>

class notif
{
public:
    notif();

notif(QString,QString);
void afficher();

private:
int CIN,NUMERO_TEL;
QString NOM,PRENOM;
};

#endif // NOTIF_H
