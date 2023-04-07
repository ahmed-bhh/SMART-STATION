#include "modifier.h"
#include"voiture.h"
#include "ui_modifier.h"


modifier::modifier(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::modifier)
{
    ui->setupUi(this);
}

modifier::~modifier()
{
    delete ui;
}

void modifier::on_matricule_edit_clicked()
{

        bool test;

        QString matricule=ui->matricule_line->text();
        QString marque=ui->marque_line->text();
        QString genre=ui->genre_line->text();
        QString hrE=ui->hre_line->text();
        QString hrS=ui->hrs_line->text();
            test=this->V.modiffier(matricule,marque,genre,hrE,hrS);
              if (test)
              {
                    ui->table_View->setModel(V.afficher());
                    ui->choix_matricule->setModel(V.afficher());
                  QMessageBox::information(nullptr,QObject::tr("OK"),
                                       QObject::tr("modification établie"),
                                       QMessageBox::Ok);}
              else{
              QMessageBox::critical(nullptr,QObject::tr("ERROR404"),
                                      QObject::tr("modification non établie"),
                                      QMessageBox::Cancel);}

}

void modifier::on_aff_mat_clicked()
{
    ui->choix_matricule->setModel(V.afficher());
}
