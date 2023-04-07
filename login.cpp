#include "login.h"
#include "ui_login.h"
#include "maquette.h"
#include "employes.h"
#include <QMessageBox>
#include <QDialog>

login::login(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::login)
{
    ui->setupUi(this);
}

login::~login()
{
    delete ui;
}

bool login::on_pushButton_login_clicked()
{
    bool test=false;

    QString username = ui->nom_login->text();
    QString password = ui->mdp_login->text();
    if(username=="smart"&&password=="123") //if(qry.exec( "select * from compte where NOM='"+username +"' PRENOM='"+password +"'")!=true)
    {
        test=true;
        QMessageBox::information(this,"login","nom et prenom valider");
        this->hide();
        maquette w;
        w.setModal(true);
        w.exec();


    }
    else
    {
        QMessageBox::information(this,"login","nom et prenom non valider");
    }

    return test;
}
