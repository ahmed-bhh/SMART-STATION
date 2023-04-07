#include "client.h"
#include <QSqlQuery>
#include <QtDebug>
#include <QObject>


Client::Client()
{
CIN = 0;
NOM=" ";
PRENOM=" ";
NUMERO_TEL=0;
}

Client::Client(int CIN,QString NOM,QString PRENOM,int NUMERO_TEL)
{
    this->CIN=CIN;
  this->NOM=NOM;
    this->PRENOM=PRENOM;
    this->NUMERO_TEL=NUMERO_TEL;
}

int Client::getCIN(){return CIN;}
QString Client::getNOM(){return NOM;}
QString Client::getPRENOM(){return PRENOM;}
int Client::getNUMERO_TEL(){return NUMERO_TEL;}
void Client::setCIN(int CIN){this->CIN=CIN;}
void Client::setNOM(QString NOM){this->NOM=NOM;}
void Client::setPRENOM(QString PRENOM){this->PRENOM=PRENOM;}
void Client::setNUMERO_TEL(int NUMERO_TEL){this->NUMERO_TEL=NUMERO_TEL;}

bool Client::ajouter()
{
    QSqlQuery query;
     QString CIN_string = QString::number(CIN);
     QString NUMERO_TEL_string = QString::number(NUMERO_TEL);
         query.prepare("INSERT INTO CLIENT (CIN, NOM, PRENOM, NUMERO_TEL) "
                       "VALUES (:CIN, :Nom, :Prenom, :NumeroTel)");
         query.bindValue(":CIN", CIN_string);
         query.bindValue(":Nom", NOM);
         query.bindValue(":Prenom", PRENOM);
         query.bindValue(":NumeroTel", NUMERO_TEL_string);
         return query.exec();
}

bool Client::supprimer(int CIN)
{
    QSqlQuery query;
     QString CIN_string = QString::number(CIN);
         query.prepare("Delete from CLIENT where CIN= :CIN");
         query.bindValue(":CIN", CIN_string);

         return query.exec();
}

QSqlQueryModel* Client::afficher()
{
  QSqlQueryModel* model= new QSqlQueryModel();

        model->setQuery("SELECT* FROM client");
        model->setHeaderData(0, Qt::Horizontal,QObject::tr("CIN"));
        model->setHeaderData(1, Qt::Horizontal,QObject::tr("NOM"));
        model->setHeaderData(2, Qt::Horizontal,QObject::tr("PRENOM"));
        model->setHeaderData(3, Qt::Horizontal,QObject::tr("NUMERO_TEL"));

 return model;
}

bool Client::modifier(int CIN, QString NOM, QString PRENOM, int NUMERO_TEL)
{
    QSqlQuery query;
     QString CIN_string = QString::number(CIN);
     QString NUMERO_string = QString::number(NUMERO_TEL);
         query.prepare("UPDATE CLIENT SET CIN=:CIN, NOM=:NOM, PRENOM=:PRENOM, NUMERO_TEL=:NUMERO_TEL where CIN=:CIN");
         query.bindValue(":CIN", CIN_string);
         query.bindValue(":NOM", NOM);
         query.bindValue(":PRENOM", PRENOM);
         query.bindValue(":NUMERO_TEL", NUMERO_string);

         return query.exec();
}

QSqlQueryModel *Client::rechercher(QString rech)
{
    QSqlQueryModel * model= new QSqlQueryModel();

        model->setQuery("select * from CLIENT where CIN LIKE '%"+rech+"%'");
    return model;
}


QSqlQueryModel * Client::tri_CIN()
{
    QSqlQueryModel *model= new QSqlQueryModel;
    QSqlQuery *q=new QSqlQuery();
    q->prepare("select * from CLIENT order by CIN  asc");
    q->exec();
    model->setQuery(*q);
    return  model;
}

QSqlQueryModel * Client::tri_nom()
{
    QSqlQueryModel *model= new QSqlQueryModel;
    QSqlQuery *q=new QSqlQuery();
    q->prepare("select * from CLIENT order by NOM  asc");
    q->exec();
    model->setQuery(*q);
    return  model;
}

QSqlQueryModel * Client::tri_prenom()
{
    QSqlQueryModel *model= new QSqlQueryModel;
    QSqlQuery *q=new QSqlQuery();
    q->prepare("select * from CLIENT order by PRENOM  asc");
    q->exec();
    model->setQuery(*q);
    return  model;
}

QSqlQueryModel * Client::tri_num()
{
    QSqlQueryModel *model= new QSqlQueryModel;
    QSqlQuery *q=new QSqlQuery();
    q->prepare("select * from CLIENT order by NUMERO_TEL  asc");
    q->exec();
    model->setQuery(*q);
    return  model;
}

QSqlQueryModel * Client::wombo_combo()
{
    QSqlQueryModel  *model= new QSqlQueryModel;
    model->setQuery("SELECT CIN FROM client");
    return model;
}
