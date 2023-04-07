#ifndef EMPLACEMENT_H
#define EMPLACEMENT_H


#include <QString>
#include <QSqlQueryModel>
#include <QtCharts>
#include <QChartView>
#include <QLineSeries>


class Emplacement
{
public:
    Emplacement();
    Emplacement (int, QString, int, float);
    int getid();
    float getprix();
    QString getlocalisation();
    int getnb_max();
    void setid(int);
    void setlocalisation (QString);
    void setnb_max (int);
    void setprix (float);
    bool ajouter();
    QSqlQueryModel * afficher();
    bool supprimer (int);
    bool modifier(int, QString , int, float);
    QSqlQueryModel * triPrix();
    QSqlQueryModel * triLocalisation();
    QSqlQueryModel * triNb_max();
    QSqlQueryModel * triId();
    float calculerBudget();





private:
    int id, nb_max;
    QString localisation;
    float prix;
};
#endif // EMPLACEMENT_H
