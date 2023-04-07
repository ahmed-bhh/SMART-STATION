#include "employes.h"

employes::employes()
{

}

employes::employes(int id, int cin,int age, QString nom,QString prenom,QString mail)
{
    this->id=id;
    this->nom=nom;
    this->prenom=prenom;
    this->cin=cin;
    this->age=age;
    this->mail=mail;
}
bool employes::ajouter()
{
    QSqlQuery query;
    QString res=QString::number(id);
    QString res1=QString::number(cin);
    QString res2=QString::number(age);
    query.prepare("insert into EMPLOYE(id, nom,prenom,cin,age,mail)""values(:id,:nom,:prenom,:cin,:age,:mail)");

    query.bindValue(":id",res);
    query.bindValue(":nom",nom);
    query.bindValue(":prenom",prenom);
    query.bindValue(":mail",mail);
    query.bindValue(":cin",res1);
    query.bindValue(":age",res2);
    return  query.exec();

}
QSqlQueryModel * employes::afficher()
{
    QSqlQueryModel * model=new QSqlQueryModel();
    model->setQuery("select* from EMPLOYE");
    model->setHeaderData(0,Qt::Horizontal,QObject::tr("ID"));
    model->setHeaderData(1,Qt::Horizontal,QObject::tr("Nom"));
    model->setHeaderData(2,Qt::Horizontal,QObject::tr("Prenom"));
    return model;
}
bool employes::supprimer(int id)
{
    QSqlQuery query;
    QString res=QString::number(id);
    query.prepare("Delete from EMPLOYE where ID=:id");
    query.bindValue(":id",res);
    return query.exec();
}
/*
bool employes::modifier(int a,int b,int c,QString d,QString e,QString f)
{

    QString res=QString::number(a);
    QString res1=QString::number(b);
    QString res2=QString::number(c);
    QSqlQuery query;
            query.prepare("UPDATE clients SET nom=:nom, prenom=:prenom, cin=:cin, age=:age, mail=:mail,  WHERE id=:id");

            query.bindValue(":id",res);
            query.bindValue(":nom",d);
            query.bindValue(":prenom",e);
            query.bindValue(":mail",f);
            query.bindValue(":cin",res1);
            query.bindValue(":age",res2);
            query.exec();

    return query.exec();
}
*/
bool employes::modifier(int id,int cin,int age,QString nom,QString prenom,QString mail)
{
    /*
QSqlQuery query;
QString res=QString::number(idd);
QString res1=QString::number(cin);
QString res2=QString::number(age);
query.prepare("Update EMPLOYE set id=:id, nom=:nom, prenom=:prenom, cin=:cin, age=:age, mail=:mail,  WHERE id=:id ");

query.bindValue(":id",res);
query.bindValue(":nom",nom);
query.bindValue(":prenom",prenom);
query.bindValue(":mail",mail);
query.bindValue(":cin",res1);
query.bindValue(":age",res2);
return    query.exec();
*/
    QSqlQuery query;
//QString idc=QString::number(id);
    QString res=QString::number(id);
    QString res1=QString::number(cin);
    QString res2=QString::number(age);
    query.prepare("UPDATE EMPLOYE SET nom= :nom, prenom= :prenom, cin= :cin, age= :age, mail= :mail where id= :id ");

    query.bindValue(":id",res);
    query.bindValue(":nom",nom);
    query.bindValue(":prenom",prenom);
    query.bindValue(":mail",mail);
    query.bindValue(":cin",res1);
    query.bindValue(":age",res2);

            return    query.exec();

}
QSqlQueryModel* employes::wombo_combo(){

    QSqlQueryModel* model=new QSqlQueryModel();
    model->setQuery("select ID from EMPLOYE");
    return model;
}

QSqlQueryModel * employes::tricroissant()
{QSqlQueryModel * model= new QSqlQueryModel();

model->setQuery("select * FROM EMPLOYE ORDER BY age ASC");
model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
model->setHeaderData(1, Qt::Horizontal, QObject::tr("nom"));
model->setHeaderData(2, Qt::Horizontal, QObject::tr("prenom"));
model->setHeaderData(3, Qt::Horizontal, QObject::tr("cin"));
model->setHeaderData(4, Qt::Horizontal, QObject::tr("age"));
model->setHeaderData(5, Qt::Horizontal, QObject::tr("mail"));

    return model;
}
QSqlQueryModel * employes::trideccroissant()
{QSqlQueryModel * model= new QSqlQueryModel();

model->setQuery("select * FROM EMPLOYE ORDER BY age DESC");
model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
model->setHeaderData(1, Qt::Horizontal, QObject::tr("nom"));
model->setHeaderData(2, Qt::Horizontal, QObject::tr("prenom"));
model->setHeaderData(3, Qt::Horizontal, QObject::tr("cin"));
model->setHeaderData(4, Qt::Horizontal, QObject::tr("age"));
model->setHeaderData(5, Qt::Horizontal, QObject::tr("mail"));

    return model;
}
QSqlQueryModel * employes::rechercher (const QString &aux)

{
    QSqlQueryModel * model = new QSqlQueryModel();

    model->setQuery("select * from EMPLOYE where ((id || nom || prenom || cin || age || mail ) LIKE '%"+aux+"%')");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("nom"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("prenom"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("cin"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("age"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("mail"));


    return model;
}
int employes::calculer_tot_employes()
{
    int rows=0;
    QSqlQuery query;
    query.prepare("SELECT COUNT(*) FROM EMPLOYE");
    query.exec();

    if(query.next()){
        rows = query.value(0).toInt();
    }

    return rows;
}
bool employes::test_Cin(QString cin){
    if(cin.size()!=8)
    return true;

    for(int i = 0; i < cin.size(); i++) {


    if (!(cin[i] >= '0' && cin[i] <= '9'))
        return false ;

}
    return true;
}
