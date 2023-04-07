#ifndef MAQUETTE_H
#define MAQUETTE_H

#include <QDialog>
#include<voiture.h>
#include<QWidget>
#include"employes.h"
#include<QTcpSocket>
#include<QTimer>
#include<QSqlQuery>
#include<QSqlQueryModel>
#include"employes.h"
#include<QPrintDialog>
#include<QPrinter>
#include <QPainter>
#include <QPdfWriter>
#include <QDesktopServices>
#include <QUrl>
#include <QTextCursor>
#include <QItemSelectionModel>
#include <QItemSelectionModel>
#include<QMessageBox>
#include<QIntValidator>
#include<QTextStream>
#include<QtCharts>
#include<QFileDialog>
#include<QPieSeries>
#include<QTextDocument>
#include <string>
#include <vector>
#include<QDirModel>
#include <qrcode.h>
#include <string>
#include <iostream>
#include <fstream>
#include <QtSvg/QSvgRenderer>
#include "dumessengerconnectiondialog.h"
#include "ui_dumessengerconnectiondialog.h"
#include <QTcpSocket>
#include <QAbstractSocket>
#include<QTimer>
#include<QDebug>
#include"client.h"
#include"notif.h"
#include "emplacement.h"
#include"accident.h"
#include <QUrl>

namespace Ui {
class maquette;
}
class QCamera;
class QCameraViewfinder;
class QCameraImageCapture;
class QVBoxLayout;
class  QMenu;
class QAction;
class QMapControl;
class maquette : public QDialog
{
    Q_OBJECT

public:
    explicit maquette(QWidget *parent = nullptr);
    ~maquette();

private slots:
    void myfunction();
    void on_PB_Ajout_clicked();
    void on_PB_supp_clicked();
    void on_btn_edit_clicked();

    void on_btn_afficher_clicked();



    void on_btn_calculer_clicked();

    void on_btn_stat_clicked();




    void on_btn_export_clicked();

    void on_btn_imp_clicked();


    void on_btn_upload_2_clicked();

/*******ahmed button**********/
    void on_bt_ajouter_clicked();

    void on_bt_supprimer_clicked();

    void on_pushButton_modifier_clicked();

    void on_pushButton_imprimer_clicked();

    void on_tab_employes_clicked(const QModelIndex &index);

    void on_pushButton_impression_clicked();

    void on_pushButton_stat_clicked();

    void on_pushButton_tri_croissant_clicked();

    void on_pushButton_tri_decroissant_clicked();

    void on_lineEdit_recherche_textChanged(const QString &arg1);

    void on_pushButton_calcul_clicked();

    void on_QrCode_clicked();

    void on_pb_connecter_clicked();

    void on_pb_envoyer_clicked();

    void on_button_afficher_Ahmed_clicked();

    void on_pb_ajouter_clicked();

    void on_pb_modifier_clicked();

    void on_pb_supprimer_clicked();

    void on_pb_rechercher_clicked();

    void on_pb_tri_CIN_clicked();

    void on_pb_tri_nom_clicked();

    void on_pb_tri_prenom_clicked();

    void on_pb_tri_num_clicked();

    void on_qrcodegen_clicked();

    void on_pb_affichage_clicked();

    void on_pb_imprimer_clicked();
    void on_tab_client_activated(const QModelIndex &index);

    void on_pb_ajouter_Lina_clicked();

    void on_pb_modifier__Lina_clicked();

    void on_pb_supprimer__Lina_clicked();

    void on_pb_afficher_Lina_clicked();

    void on_pb_id_afficher_Lina_clicked();

    void on_pb_calculer_Lina_clicked();

    void on_pb_stat_Lina_clicked();

    void on_pb_triLocalisation_Lina_clicked();

    void on_pb_triId_Lina_clicked();

    void on_pb_triNbMax_Lina_clicked();

    void on_pb_triPrix_Lina_clicked();

    void on_pb_localisation_afficher_Lina_clicked();

    void on_pb_localisation_Lina_clicked();

    void on_tab_emplacement_activated(const QModelIndex &index);

    void on_PB_Ajout_2_clicked();

    void on_PB_supp_2_clicked();

    void on_PB_modifier_clicked();

    void on_PDF_clicked();

    void on_rechercher_clicked();

    void on_imprimer_clicked();

    void on_calculer_clicked();

private:
    Ui::maquette *ui;
    Voiture V;
    employes Etmp;
    QTcpSocket *mSocket;
    QTimer *timer;
    Client C;
    Emplacement E;
     Accident A;

        QCamera *mCamera;
        QCameraViewfinder *mCameraViewfinder;
        QCameraImageCapture *mCameraImageCapture;
        QVBoxLayout *mLayout;
        QMenu *mOptionMenu;
        QAction *mTurnOnAction;
        QAction *mTurnOffAction;
        QAction *mCaptureAction;

             QStringList files;

};

#endif // MAQUETTE_H
