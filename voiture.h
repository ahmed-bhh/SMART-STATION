#ifndef VOITURE_H
#define VOITURE_H
#include<QString>
#include<QSqlQuery>
#include <QSqlQueryModel>
#include<QtCharts>

class Voiture
{
private:
    QString MATRICULE, GENRE, MARQUE,HRE, HRS;
public:
    Voiture();
    Voiture(QString,QString,QString,QString,QString);
    //getters
    QString getMatricule();
    QString getMarque();
    QString getGenre();
    QString getHE();
    QString getHS();
    //setters
    void setmatricule(QString);
    void setmarque(QString);
    void setgenre(QString);
    void sethe(QString);
    void seths(QString);
    //method:
    bool ajouter();
    QSqlQueryModel* afficher();
    bool supprimer(QString);
    bool modiffier(QString,QString,QString,QString,QString);
    //métier:
    int calculer();

};

#endif // VOITURE_H


