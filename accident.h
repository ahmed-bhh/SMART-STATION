#ifndef ACCIDENT_H
#define ACCIDENT_H

#include<QString>
#include <QSqlQueryModel>
class Accident
{
private:
    QString MATRICULE, CHAUFFEUR, LIEU,FAUTIF, DAT;
public:
    Accident();
    Accident(QString,QString,QString,QString,QString);
    //getters
    QString getmatricule();
    QString getchauffeur();
    QString getlieu();
    QString getfautif();
    QString getdat();
    //setters
    void setmatricule(QString);
    void setchauffeur(QString);
    void setlieu(QString);
    void setfautif(QString);
    void setdat(QString);
    bool ajouter();
    QSqlQueryModel* afficher();
    QSqlQueryModel* afficher_matricule(QString matricule);
    bool supprimer(QString);
    bool modifier();
    int calculernbacc();
};

#endif // VOITURE_H
