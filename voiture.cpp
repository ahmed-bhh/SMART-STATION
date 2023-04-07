#include "voiture.h"
#include<QDebug>
#include<QSqlQuery>
#include<QObject>
#include<QTableView>
#include<QModelIndex>

Voiture::Voiture()
{
    MATRICULE=" ";
    MARQUE=" ";
    GENRE=" ";
    HRE="";
    HRS="";
}
Voiture::Voiture(QString MATRICULE,QString MARQUE,QString GENRE,QString HRE, QString HRS)
{
    this->MATRICULE=MATRICULE;
    this->MARQUE=MARQUE;
    this->GENRE=GENRE;
    this->HRE=HRE;
    this->HRS=HRS;
}
QString Voiture::getMatricule()
{
    return MATRICULE;
}
QString Voiture::getMarque()
{
    return MARQUE;
}
QString Voiture::getGenre()
{
    return GENRE;
}
QString Voiture::getHE()
{
    return HRE;
}
QString Voiture::getHS()
{
    return HRS;
}
void Voiture::setmatricule(QString MATRICULE)
{
    this->MATRICULE=MATRICULE;
}
void Voiture::setmarque(QString MARQUE)
{
    this->MARQUE=MARQUE;
}
void Voiture::setgenre(QString GENRE)
{
    this->GENRE=GENRE;
}
void Voiture::sethe(QString HRE)
{
    this->HRE=HRE;
}
void Voiture::seths(QString HRS)
{
    this->HRS=HRS;
}
bool Voiture::ajouter()
{

      QSqlQuery query;
      query.prepare("INSERT INTO VOITURE (MATRICULE, MARQUE, GENRE, HRE, HRS) "
                    "VALUES (:MATRICULE, :MARQUE, :GENRE, :HRE, :HRS)");
      query.bindValue(":MATRICULE", MATRICULE);
      query.bindValue(":MARQUE", MARQUE);
      query.bindValue(":GENRE", GENRE);
      query.bindValue(":HRE", HRE);
      query.bindValue(":HRS", HRS);
      return  query.exec();

}
bool Voiture::supprimer(QString MATRICULE)
{
    QSqlQuery query;
         query.prepare("Delete from VOITURE where MATRICULE=:MATRICULE");
         query.bindValue(":MATRICULE", MATRICULE);
         return query.exec();
}
QSqlQueryModel* Voiture::afficher()
{
    QSqlQueryModel* model=new QSqlQueryModel;

          model->setQuery("SELECT* FROM VOITURE");
          model->setHeaderData(0, Qt::Horizontal, QObject::tr("MATRICULE"));
          model->setHeaderData(1, Qt::Horizontal, QObject::tr("MARQUE"));
           model->setHeaderData(2, Qt::Horizontal, QObject::tr("GENRE"));
            model->setHeaderData(3, Qt::Horizontal, QObject::tr("HRE"));
             model->setHeaderData(4, Qt::Horizontal, QObject::tr("HRS"));

    return model;
}

bool Voiture::modiffier(QString matricule,QString marque,QString genre,QString hrE,QString hrS)
{

    QSqlQuery query;

    query.prepare("UPDATE VOITURE SET MARQUE=:MARQUE, GENRE=:GENRE, HRE=:HRE, HRS=:HRS WHERE MATRICULE=:MATRICULE");
    query.bindValue(":MATRICULE", matricule);
      query.bindValue(":MARQUE", marque);
      query.bindValue(":GENRE", genre);
      query.bindValue(":HRE", hrE);
      query.bindValue(":HRS", hrS);

            return    query.exec();

}
//métier :
int Voiture::calculer()
{
    int rows=0;
    QSqlQuery query;
    query.prepare("SELECT COUNT(*) FROM VOITURE");
    query.exec();

    if(query.next()){
        rows = query.value(0).toInt();
    }

    return rows;
}

