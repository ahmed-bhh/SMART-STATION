#include "emplacement.h"
#include <QSqlQuery>
#include <QtDebug>
#include <QObject>
#include <iostream>
#include <QCamera>
#include <QCameraViewfinder>
#include <QCameraImageCapture>
#include <QVBoxLayout>
#include <QMenu>
#include <QAction>
#include <QFileDialog>

#include <QSqlQueryModel>
#include <QtCharts>
#include <QChartView>
#include <QLineSeries>

using namespace std;

Emplacement::Emplacement()
{
    id = 0 ;
    localisation = " ";
    nb_max = 0;
    prix = 0.0;
}

Emplacement::Emplacement (int id, QString localisation, int nb_max, float prix)
{
    this->id = id;
    this->localisation = localisation;
    this->nb_max = nb_max;
    this->prix = prix;
}

int Emplacement::getid(){ return id;}
QString Emplacement::getlocalisation(){return localisation;}
int Emplacement::getnb_max(){return nb_max;}
float Emplacement::getprix(){return prix;}
void Emplacement::setid(int id){this->id = id;}
void Emplacement::setlocalisation (QString localisation){this->localisation = localisation;}
void Emplacement::setnb_max (int nb_max){this->nb_max = nb_max;}
void Emplacement::setprix(float prix){this->prix = prix;}

bool Emplacement::ajouter()
{

    QSqlQuery query;
    QString id_string = QString::number(id);

    QString nb_max_string = QString::number(nb_max);
     QString prix_string = QString::number(prix);
        query.prepare("INSERT INTO EMPLACEMENT (ID, LOCALISATION, NB_MAX, PRIX) "
                      "VALUES (:id, :localisation, :nb_max, :prix)");
        query.bindValue(":id", id_string);
        query.bindValue(":localisation", localisation);
        query.bindValue(":nb_max", nb_max_string);
        query.bindValue(":prix", prix_string);
        return query.exec();


}

bool Emplacement::supprimer(int id)
{
    QSqlQuery query;
    QString id_string = QString:: number(id);

        query.prepare("Delete from emplacement where ID = :id");

        query.bindValue(":id", id_string);
        return query.exec();
}

QSqlQueryModel* Emplacement::afficher()
{

    QSqlQueryModel *model = new QSqlQueryModel;
       model->setQuery("SELECT * FROM emplacement");
       model->setHeaderData(0, Qt::Horizontal, QObject::tr("Identifiant"));
       model->setHeaderData(1, Qt::Horizontal, QObject::tr("Localisation"));
       model->setHeaderData(2, Qt::Horizontal, QObject::tr("Nombre maximale"));
       model->setHeaderData(3, Qt::Horizontal, QObject::tr("Prix"));

       return model;
}

bool Emplacement::modifier(int id, QString localisation, int nb_max, float prix)
{
    QSqlQuery query;
     QString id_string = QString :: number(id);
      QString nb_max_string = QString :: number(nb_max);
      QString prix_string = QString :: number(prix);

         query.prepare("UPDATE EMPLACEMENT SET ID = :id, LOCALISATION = :localisation, NB_MAX = :nb_max, PRIX = :prix  WHERE ID = :id ");
         query.bindValue(":id", id_string);
         query.bindValue(":localisation", localisation);
         query.bindValue(":nb_max", nb_max_string);
         query.bindValue(":prix", prix_string);

         return query.exec();
}

QSqlQueryModel * Emplacement::triPrix()
{
    QSqlQueryModel *model= new QSqlQueryModel;
    QSqlQuery *q = new QSqlQuery();
    q->prepare("select * from EMPLACEMENT order by PRIX asc");
    q->exec();
    model->setQuery(*q);
    return  model;
}

QSqlQueryModel * Emplacement::triLocalisation()
{
    QSqlQueryModel *model= new QSqlQueryModel;
    QSqlQuery *q = new QSqlQuery();
    q->prepare("select * from EMPLACEMENT order by LOCALISATION asc");
    q->exec();
    model->setQuery(*q);
    return  model;
}

QSqlQueryModel * Emplacement::triId()
{
    QSqlQueryModel *model= new QSqlQueryModel;
    QSqlQuery *q = new QSqlQuery();
    q->prepare("select * from EMPLACEMENT order by ID asc");
    q->exec();
    model->setQuery(*q);
    return  model;
}

QSqlQueryModel * Emplacement::triNb_max()
{
    QSqlQueryModel *model= new QSqlQueryModel;
    QSqlQuery *q = new QSqlQuery();
    q->prepare("select * from EMPLACEMENT order by NB_MAX asc");
    q->exec();
    model->setQuery(*q);
    return  model;
}



float Emplacement::calculerBudget()
{


    float total_price = 0.0;



    QSqlQuery query;
    query.prepare ("SELECT SUM(PRIX) FROM EMPLACEMENT ");

    query.exec();


    if(query.next())
    {
         total_price = query.value(0).toInt();

    }

  return total_price;
}
