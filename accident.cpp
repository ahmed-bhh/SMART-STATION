#include "accident.h"
#include<QDebug>
#include<QSqlQuery>
#include<QObject>
#include<QTableView>

using namespace std;
Accident::Accident()
{
    MATRICULE=" ";
    CHAUFFEUR=" ";
    LIEU=" ";
    FAUTIF="";
    DAT="";
}
Accident::Accident(QString MATRICULE,QString CHAUFFEUR,QString LIEU,QString FAUTIF, QString DAT)
{
  this->MATRICULE=MATRICULE;
    this->CHAUFFEUR=CHAUFFEUR;
    this->LIEU=LIEU;
    this->FAUTIF=FAUTIF;
    this->DAT=DAT;
}
QString Accident::getmatricule()
{
    return MATRICULE;
}
QString Accident::getchauffeur()
{
    return CHAUFFEUR;
}
QString Accident::getlieu()
{
    return LIEU;
}
QString Accident::getfautif()
{
    return FAUTIF;
}
QString Accident::getdat()
{
    return DAT;
}

void Accident::setmatricule(QString MATRICULE)
{
    this->MATRICULE=MATRICULE;
}
void Accident::setchauffeur(QString CHAUFFEUR)
{
    this->CHAUFFEUR=CHAUFFEUR;
}
void Accident::setlieu(QString LIEU)
{
    this->LIEU=LIEU;
}
void Accident::setfautif(QString FAUTIF)
{
    this->FAUTIF=FAUTIF;
}
void Accident::setdat(QString DAT)
{
    this->DAT=DAT;
}
bool Accident::ajouter()
{

      QSqlQuery query;
      query.prepare("INSERT INTO ACCIDENT(MATRICULE, CHAUFFEUR,LIEU, FAUTIF, DAT) "
                    "VALUES (:MATRICULE, :CHAUFFEUR, :LIEU, :FAUTIF, :DAT)");
      query.bindValue(":MATRICULE", MATRICULE);
      query.bindValue(":CHAUFFEUR", CHAUFFEUR);
      query.bindValue(":LIEU", LIEU);
      query.bindValue(":FAUTIF", FAUTIF);
      query.bindValue(":DAT", DAT);
      return  query.exec();

}
bool Accident::supprimer(QString MATRICULE)
{
    QSqlQuery query;
         query.prepare("Delete from ACCIDENT where MATRICULE=:MATRICULE");
         query.bindValue(":MATRICULE", MATRICULE);
         return query.exec();
}
QSqlQueryModel* Accident::afficher( )
{
    QSqlQueryModel* model=new QSqlQueryModel;

          model->setQuery("SELECT* FROM ACCIDENT");
          model->setHeaderData(0, Qt::Horizontal, QObject::tr("MATRICULE"));
          model->setHeaderData(1, Qt::Horizontal, QObject::tr("CHAUFFEUR"));
           model->setHeaderData(2, Qt::Horizontal, QObject::tr("LIEU"));
            model->setHeaderData(3, Qt::Horizontal, QObject::tr("FAUTIF"));
             model->setHeaderData(4, Qt::Horizontal, QObject::tr("DAT  "));

    return model;
}
bool Accident::modifier()
{

    QSqlQuery query;
    query.prepare("UPDATE  ACCIDENT SET MATRICULE=:MATRICULE,CHAUFFEUR=:CHAUFFEUR, LIEU=:LIEU,FAUTIF=:FAUTIF,DAT=:DAT WHERE MATRICULE=:MATRICULE");
    query.bindValue(":MATRICULE",MATRICULE);
    query.bindValue(":CHAUFFEUR", CHAUFFEUR);
    query.bindValue(":LIEU", LIEU);
    query.bindValue(":FAUTIF",FAUTIF);
    query.bindValue(":DAT",DAT);

    return query.exec();
}
QSqlQueryModel* Accident::afficher_matricule(QString matricule)
{
    QSqlQuery query;
    query.prepare("SELECT * FROM ACCIDENT WHERE MATRICULE=:matricule ");
    query.bindValue(":matricule",matricule);
    QSqlQueryModel* model= new QSqlQueryModel();
    query.exec();
    model->setQuery(query);
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("matricule"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("chauffeur"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("lieu"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("fautif"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("dat"));
    return model;
}
int Accident::calculernbacc()
{


    int total_accident = 0;



    QSqlQuery query;
    query.prepare ("SELECT COUNT(*) FROM ACCIDENT ");

    query.exec();


    if(query.next())
    {
         total_accident = query.value(0).toInt();

    }

  return total_accident;
}
