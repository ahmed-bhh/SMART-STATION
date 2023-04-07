#ifndef EMPLOYES_H
#define EMPLOYES_H
#include<QSqlQuery>
#include<QSqlQueryModel>
#include<QTableWidget>
class employes
{
    QString nom, prenom,mail;
    int id,cin,age;
public:
    //constructeurs
    employes();
    employes(int,int,int,QString,QString,QString);
    //getters
    QString getNom(){return nom;}
    QString getPrenom(){return prenom;}
    QString getMail(){return mail;}
    int getID(){return id;}
    int getCin(){return cin;}
    int getAge(){return age;}

    //setters
    void setNom(QString n){nom=n;}
    void setPrenom(QString p) {prenom=p;}
    void setMail(QString m) {mail=m;}
    void setID(int id){this->id=id;}
    void setCin(int cin){this->id=cin;}
    void setAge(int age){this->age=age;}

    //CRUD
    bool ajouter();
    QSqlQueryModel * afficher();
    bool supprimer(int);
    //bool modifier(int);
    bool modifier(int id,int cin,int age,QString nom,QString prenom,QString mail);
    QSqlQueryModel* wombo_combo();
    QSqlQueryModel *trideccroissant();
    QSqlQueryModel *tricroissant();
    QSqlQueryModel * rechercher (const QString &aux);
    int calculer_tot_employes();
     bool test_Cin(QString cin);



};

#endif // EMPLOYES_H
