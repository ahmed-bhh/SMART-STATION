#ifndef CLIENT_H
#define CLIENT_H
#include <QString>
#include <QSqlQueryModel>
class Client
{
public:
    Client();
    Client(int,QString,QString,int);
    int getCIN();
    QString getNOM();
    QString getPRENOM();
    int getNUMERO_TEL();

    void setCIN(int);
    void setNOM(QString);
    void setPRENOM(QString);
    void setNUMERO_TEL(int);

    bool ajouter();
    QSqlQueryModel* afficher();
    bool supprimer(int);
    bool modifier (int CIN, QString NOM, QString PRENOM, int NUMERO_TEL);
      QSqlQueryModel * rechercher(QString);
      QSqlQueryModel *tri_CIN();
      QSqlQueryModel *tri_nom();
      QSqlQueryModel *tri_prenom();
      QSqlQueryModel *tri_num();
      QSqlQueryModel *wombo_combo();

private:
    int CIN, NUMERO_TEL;
 QString NOM,PRENOM;


};

#endif // CLIENT_H
