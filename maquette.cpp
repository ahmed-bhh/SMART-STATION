#include "maquette.h"
#include<iostream>
#include "ui_maquette.h"
#include"voiture.h"
#include<QMessageBox>
#include<QTextStream>
#include<QIntValidator>
#include"modifier.h"
#include<QFile>
#include<QTextStream>
#include<QPixmap>
#include <QPrinter>
#include <QPrintDialog>
#include"exportexcel.h"
#include"qrcode.h"
#include<QTextDocument>
#include "emplacement.h"
#include<QDebug>
#include <QtPrintSupport/QPrinter>
#include <QCamera>
#include <QCameraViewfinder>
#include <QCameraImageCapture>
#include <QVBoxLayout>
#include <QMenu>
#include <QAction>
#include <QFileDialog>
#include <QPixmap>
#include <iostream>


using namespace std;
using qrcodegen::QrCode;

maquette::maquette(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::maquette)
{
    ui->setupUi(this);
    mSocket=new QTcpSocket(this);
    connect(mSocket,&QTcpSocket::readyRead,[&]()
    { QTextStream T(mSocket);
       auto text=T.readAll();
       ui->textEdit->append(text);
    });

    /*************ahmed***************************/


        ui->comboBox_supprimer->setModel(Etmp.wombo_combo());
    ui->tab_employes->setModel(Etmp.afficher());

ui->edit_id->setValidator(new QIntValidator(1000, 99999999, this));
ui->edit_cin->setValidator( new QIntValidator(100, 99999999, this));
ui->edit_num_tel->setValidator( new QIntValidator(100, 99999999, this));
ui->edit_nom->setMaxLength(15);
ui->edit_prenom->setMaxLength(15);
ui->edit_mail->setMaxLength(30);
ui->edit_num_tel->setMaxLength(8);

QRegularExpression rx("\\b[A-Z._%+-]+@[A-Z.-]+\\.[A-Z]\\b",
               QRegularExpression::CaseInsensitiveOption);
ui->edit_mail->setValidator(new QRegularExpressionValidator(rx, this));

QRegularExpression rx1("\\b[A-Z._%+-]+@[A-Z.-]+\\.[A-Z]\\b",
                              QRegularExpression::CaseInsensitiveOption);
    ui->edit_nom->setValidator(new QRegularExpressionValidator(rx1, this));
    QRegularExpression rx2("\\b[A-Z._%+-]+@[A-Z.-]+\\.[A-Z]\\b",
                                  QRegularExpression::CaseInsensitiveOption);
    ui->edit_prenom->setValidator(new QRegularExpressionValidator(rx2, this));



    QRegularExpression rx6("\\b[A-Z._%+-]+@[A-Z.-]+\\.[A-Z]\\b",
                                                                        QRegularExpression::CaseInsensitiveOption);
                                              ui->edit_mail->setValidator(new QRegularExpressionValidator(rx6, this));



    ui->modfier_id->setValidator(new QIntValidator(1000, 99999999, this));
    ui->modifier_cin->setValidator( new QIntValidator(100, 99999999, this));
    ui->modifier_num->setValidator( new QIntValidator(100, 99999999, this));
        ui->modifier_nom->setMaxLength(15);
        ui->modifier_prenom->setMaxLength(15);
        ui->modifier_mail->setMaxLength(30);
         ui->modifier_num->setMaxLength(8);

         QRegularExpression rx3("\\b[A-Z._%+-]+@[A-Z.-]+\\.[A-Z]\\b",
                                       QRegularExpression::CaseInsensitiveOption);
             ui->modifier_mail->setValidator(new QRegularExpressionValidator(rx3, this));

                        QRegularExpression rx4("\\b[A-Z._%+-]+@[A-Z.-]+\\.[A-Z]\\b",
                                                      QRegularExpression::CaseInsensitiveOption);
                            ui->modifier_nom->setValidator(new QRegularExpressionValidator(rx4, this));
                            QRegularExpression rx5("\\b[A-Z._%+-]+@[A-Z.-]+\\.[A-Z]\\b",
                                                          QRegularExpression::CaseInsensitiveOption);
                            ui->modifier_prenom->setValidator(new QRegularExpressionValidator(rx5, this));

                            timer = new QTimer(this);
                                                                          connect(timer,SIGNAL(timeout()),this,SLOT(myfunction()));
                                                                          timer->start(1000);

        /****************************ahmed**********************/

    ui->tab_voiture->setModel(V.afficher());
    ui->heure_E->setValidator(new QIntValidator(0, 23, this));
         ui->heure_S->setValidator(new QIntValidator(0, 23, this));
/********************************/
         ui->le_nb_max->setValidator(new QIntValidator(2, 999999, this));
             ui->le_prix->setValidator(new QIntValidator(3, 999999, this));

             ui->tab_emplacement->setModel(E.afficher());
             ui->le_id->setValidator(new QIntValidator(0, 999999, this));


             //stat
              //E.statistique()->setParent(ui->horizontalFrame);

              //Camera
              mCamera = new QCamera (this);
              mCameraViewfinder = new QCameraViewfinder(this);
              mCameraImageCapture = new QCameraImageCapture(mCamera, this);
              mLayout = new QVBoxLayout;
              mOptionMenu = new QMenu ("Option", this);
              mTurnOnAction = new QAction ("Turn on", this);
              mTurnOffAction = new QAction ("Turn off", this);
              mCaptureAction = new QAction ("Capture", this);

              mOptionMenu->addActions({mTurnOnAction, mTurnOffAction, mCaptureAction});
              ui->pb_option_Lina->setMenu(mOptionMenu);
              mCamera->setViewfinder(mCameraViewfinder);
              mLayout->addWidget(mCameraViewfinder);
              mLayout->setMargin(0);
              ui->scrollArea->setLayout(mLayout);
              connect (mTurnOnAction, &QAction::triggered, [&]()
              {
                 mCamera->start();
              });
              connect (mTurnOffAction, &QAction::triggered, [&]()
              {
                  mCamera->stop();
              });
              connect (mCaptureAction, &QAction::triggered, [&]()
              {
                  auto filename=QFileDialog::getSaveFileName(this, "capture", "/", "Image (*.jpg; *.jpeg)");

                  if (filename.isEmpty())
                  {
                      return;
                  }
                  mCameraImageCapture->setCaptureDestination(QCameraImageCapture::CaptureToFile);
                  QImageEncoderSettings imageEncoderSettings;
                  imageEncoderSettings.setCodec("image/jpeg");
                  imageEncoderSettings.setResolution(1600,1200);
                  mCameraImageCapture->setEncodingSettings(imageEncoderSettings);
                  mCamera->setCaptureMode(QCamera::CaptureStillImage);
                  mCamera->start();
                  mCamera->searchAndLock();
                  mCameraImageCapture->capture(filename);
                  mCamera->unlock();
              });
              ui->tableView->setModel(A.afficher());
}

maquette::~maquette()
{
    delete ui;
}

void maquette::on_PB_Ajout_clicked()
{
    QString matricule=ui->Matricule->text();
    QString marque=ui->Marque->text();
    QString genre=ui->Genre->text();
    QString hrE=ui->heure_E->text();
    QString hrS=ui->heure_S->text();
    Voiture V(matricule,marque,genre,hrE,hrS);
    bool test = V.ajouter();
           if (test)
           {
               ui->tab_voiture->setModel(V.afficher());

               QMessageBox::information (nullptr, QObject::tr("OK"),
                           QObject::tr("Ajout effectué\n"
                                           "Click cancel to exist."), QMessageBox::Cancel);
           }
           else
               QMessageBox::critical(nullptr, QObject::tr("Not OK"),
                                     QObject::tr("Ajout non effectué.\n"
                                                 "Click Cancel to exit."),QMessageBox::Cancel);
}

void maquette::on_PB_supp_clicked()
{
    Voiture V;
    QString MATRICULE=ui->M_supp->text();
    bool test=V.supprimer(MATRICULE);
            QMessageBox msgBox;
            if(test)
            {
                ui->tab_voiture->setModel(V.afficher());
                msgBox.setText("Suppression avec succes.");
            }


            else
                    msgBox.setText("echec de suppression.");
            msgBox.exec();
}


 void maquette::on_btn_edit_clicked()
{
    modifier W;
    W.show();
    W.exec();

}

void maquette::on_btn_afficher_clicked()
{
    ui->tab_voiture->setModel(V.afficher());
}

void maquette::on_btn_calculer_clicked()
{
    Voiture V;
    int nbr_v;
    nbr_v=V.calculer();
    ui->res_calc->display(nbr_v);
}


void maquette::on_btn_stat_clicked()
{

    QSqlQueryModel * model= new QSqlQueryModel();
                        model->setQuery("select * from VOITURE where HRE < 10 ");
                        float heure1=model->rowCount();
                        model->setQuery("select * from VOITURE where HRE  between 10 and 14 ");
                        float heure2=model->rowCount();
                        model->setQuery("select * from VOITURE where HRE >14 ");
                        float heure3=model->rowCount();
                        float total=heure1+heure2+heure3;
                        QString a=QString("moins de 10 hr "+QString::number((heure1*100)/total,'f',2)+"%" );
                        QString b=QString("entre 10 et 14 hr "+QString::number((heure2*100)/total,'f',2)+"%" );
                        QString c=QString("+14 hr "+QString::number((heure3*100)/total,'f',2)+"%" );
                        QPieSeries *series = new QPieSeries();
                        series->append(a,heure1);
                        series->append(b,heure2);
                        series->append(c,heure3);
                if (heure1!=0)
                {QPieSlice *slice = series->slices().at(0);
                 slice->setLabelVisible();
                 slice->setPen(QPen());}
                if ( heure2!=0)
                {
                         // Add label, explode and define brush for 2nd slice
                         QPieSlice *slice1 = series->slices().at(1);
                         //slice1->setExploded();
                         slice1->setLabelVisible();
                }
                if(heure3!=0)
                {
                         // Add labels to rest of slices
                         QPieSlice *slice2 = series->slices().at(2);
                         //slice1->setExploded();
                         slice2->setLabelVisible();
                }
                        // Create the chart widget
                        QChart *chart = new QChart();
                        // Add data to chart with title and hide legend
                        chart->addSeries(series);
                        chart->setTitle("Pourcentage Par heure :Nombre Des voiture "+ QString::number(total));
                        chart->legend()->hide();
                        // Used to display the chart
                        QChartView *chartView = new QChartView(chart);
                        chartView->setRenderHint(QPainter::Antialiasing);
                        chartView->resize(1000,500);
                        chartView->show();


}


void maquette::on_btn_export_clicked()
{
    QString fileName = QFileDialog::getSaveFileName(this, tr("Excel file"), qApp->applicationDirPath (),
                                                        tr("Excel Files (*.xls)"));
        if (fileName.isEmpty())
            return;

        exportExcel obj(fileName, "mydata", ui->tab_voiture);

        //colums to export
        obj.addField(0, "MATRICULE", "char(20)");
        obj.addField(1, "ANNONCE", "char(20)");
        obj.addField(2, "DOMAINE", "char(20)");
        obj.addField(3, "EXPERIENCE", "char(20)");
        obj.addField(4, "SALAIRE", "char(20)");




        int retVal = obj.export2Excel();
        if( retVal > 0)
        {
            QMessageBox::information(this, tr("Done"),
                                     QString(tr("%1 records exported!")).arg(retVal)
                                     );
        }
}

void maquette::on_btn_imp_clicked()
{
    QString strStream;
                             QTextStream out(&strStream);

                             const int rowCount = ui->tab_voiture->model()->rowCount();
                             const int columnCount = ui->tab_voiture->model()->columnCount();
                             QString TT = QDate::currentDate().toString("yyyy/MM/dd");
                             out <<"<html>\n"
                                   "<head>\n"
                                    "<meta Content=\"Text/html; charset=Windows-1251\">\n"
                                 << "<title>ERP - COMmANDE LIST<title>\n "
                                 << "</head>\n"
                                 "<body bgcolor=#ffffff link=#5000A0>\n"
                                 "<h1 style=\"text-align: center;\"><strong> ******LISTE DES  licence commerciale ******"+TT+" </strong></h1>"
                                 "<table style=\"text-align: center; font-size: 20px;\" border=1>\n "
                                   "</br> </br>";
                             // headers
                             out << "<thead><tr bgcolor=#d6e5ff>";
                             for (int column = 0; column < columnCount; column++)
                                 if (!ui->tab_voiture->isColumnHidden(column))
                                     out << QString("<th>%1</th>").arg(ui->tab_voiture->model()->headerData(column, Qt::Horizontal).toString());
                             out << "</tr></thead>\n";

                             // data table
                             for (int row = 0; row < rowCount; row++) {
                                 out << "<tr>";
                                 for (int column = 0; column < columnCount; column++) {
                                     if (!ui->tab_voiture->isColumnHidden(column)) {
                                         QString data =ui->tab_voiture->model()->data(ui->tab_voiture->model()->index(row, column)).toString().simplified();
                                         out << QString("<td bkcolor=0>%1</td>").arg((!data.isEmpty()) ? data : QString("&nbsp;"));
                                     }
                                 }
                                 out << "</tr>\n";
                             }
                             out <<  "</table>\n"
                                 "</body>\n"
                                 "</html>\n";

                             QTextDocument *document = new QTextDocument();
                             document->setHtml(strStream);

                             QPrinter printer;

                             QPrintDialog *dialog = new QPrintDialog(&printer, nullptr);
                             if (dialog->exec() == QDialog::Accepted) {
                                 document->print(&printer);
                             }

                             delete document;


}

void maquette::on_btn_upload_2_clicked()
{
    QString filename=QFileDialog::getOpenFileName(this, tr("choose"), "", tr("image (*.png *.jpg *.jpeg *.bmp *.gif)"));
    if(QString::compare(filename,QString())!=0)
    {
        QImage image;
        bool valid = image.load(filename);
        if(valid)
        {
            ui->image->setPixmap(QPixmap::fromImage(image));
        }
        else
        {
            QMessageBox::critical(nullptr, QObject::tr("Not OK"),
                                  QObject::tr("Image non effectué.\n"
                                              "Click Cancel to exit."),QMessageBox::Cancel);
        }
    }
}

/***********************************AHMED*****************************************************/
void maquette::on_bt_ajouter_clicked()
{

    int id = ui->edit_id ->text().toInt();
    int cin = ui->edit_cin ->text().toInt();
    int age = ui->edit_num_tel ->text().toInt();
    QString nom=ui->edit_nom->text();
    QString prenom=ui->edit_prenom->text();
    QString mail=ui->edit_mail->text();
    if (nom==NULL)
             {

                 QMessageBox::information(this," ERREUR "," VEUILLEZ VERIFIER CHAMP nom!!!!") ;
                 QMessageBox::critical(0, qApp->tr("Ajout"),

                                 qApp->tr("Probleme d'ajout"), QMessageBox::Cancel);



             }

          else if (prenom==NULL)
           {

               QMessageBox::information(this," ERREUR "," VEUILLEZ VERIFIER CHAMP prenom!!!!") ;
               QMessageBox::critical(0, qApp->tr("Ajout"),

                               qApp->tr("Probleme d'ajout"), QMessageBox::Cancel);



           }
    else if (cin==NULL)
     {

         QMessageBox::information(this," ERREUR "," VEUILLEZ VERIFIER CHAMP cin!!!!") ;
         QMessageBox::critical(0, qApp->tr("Ajout"),

                         qApp->tr("Probleme d'ajout"), QMessageBox::Cancel);



     }
    else if (id==NULL)
     {

         QMessageBox::information(this," ERREUR "," VEUILLEZ VERIFIER CHAMP id!!!!") ;
         QMessageBox::critical(0, qApp->tr("Ajout"),

                         qApp->tr("Probleme d'ajout"), QMessageBox::Cancel);



     }
        else if (mail==NULL)
         {

             QMessageBox::information(this," ERREUR "," VEUILLEZ VERIFIER CHAMP mail!!!!") ;
             QMessageBox::critical(0, qApp->tr("Ajout"),

                             qApp->tr("Probleme d'ajout"), QMessageBox::Cancel);



         }


       else if (age==NULL)
             {

                 QMessageBox::information(this," ERREUR "," VEUILLEZ VERIFIER CHAMP age !!!!") ;
                 QMessageBox::critical(0, qApp->tr("Ajout"),

                                 qApp->tr("Probleme d'ajout"), QMessageBox::Cancel);

             }






else {


    employes E(id,cin,age,nom,prenom,mail);
            bool test=E.ajouter();
            if(test)
            {
                 ui->comboBox_supprimer->setModel(Etmp.wombo_combo());
                ui->tab_employes->setModel(Etmp.afficher());

                QMessageBox::information(nullptr, QObject::tr("ok"),
                            QObject::tr("ajout effectué\n"
                                        "Click Cancel to exit."), QMessageBox::Cancel);
                ui->edit_nom->clear();
                ui->edit_cin->clear();
                ui->edit_id->clear();
               ui->edit_prenom->clear();
                ui->edit_mail->clear();
               ui->edit_num_tel->clear();


            }
            else
                QMessageBox::critical(nullptr, QObject::tr("not ok"),
                            QObject::tr("ajout non effectué\n"
                                        "Click Cancel to exit."), QMessageBox::Cancel);


                }
}



void maquette::on_bt_supprimer_clicked()
{
    bool test=Etmp.supprimer(ui->comboBox_supprimer->currentText().toInt());

    if(test)
    {
        ui->comboBox_supprimer->setModel(Etmp.wombo_combo());
         ui->tab_employes->setModel(Etmp.afficher());
        QMessageBox::information(nullptr, QObject::tr("ok"),
                    QObject::tr("suppression effectué\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);
        ui->modifier_nom->clear();
        //ui->l_id_supp->clear();
        ui->modifier_cin->clear();
        ui->modfier_id->clear();
       ui->modifier_prenom->clear();
        ui->modifier_mail->clear();
       ui->modifier_num->clear();


    }
    else
        QMessageBox::critical(nullptr, QObject::tr("not ok"),
                    QObject::tr("suppression non effectué\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);


}



void maquette::on_pushButton_modifier_clicked()
{
    bool    test;
    int id = ui->modfier_id ->text().toInt();
    int cin = ui->modifier_cin ->text().toInt();
    int age = ui->modifier_num ->text().toInt();
    QString nom=ui->modifier_nom->text();
    QString prenom=ui->modifier_prenom->text();
    QString mail=ui->modifier_mail->text();
    if (nom==NULL)
             {

                 QMessageBox::information(this," ERREUR "," VEUILLEZ VERIFIER CHAMP nom!!!!") ;
                 QMessageBox::critical(0, qApp->tr("Ajout"),

                                 qApp->tr("Probleme de modification"), QMessageBox::Cancel);



             }

          else if (prenom==NULL)
           {

               QMessageBox::information(this," ERREUR "," VEUILLEZ VERIFIER CHAMP prenom!!!!") ;
               QMessageBox::critical(0, qApp->tr("Ajout"),

                               qApp->tr("Probleme de modification"), QMessageBox::Cancel);



           }
    else if (cin==NULL)
     {

         QMessageBox::information(this," ERREUR "," VEUILLEZ VERIFIER CHAMP cin!!!!") ;
         QMessageBox::critical(0, qApp->tr("Ajout"),

                         qApp->tr("Probleme de modification"), QMessageBox::Cancel);



     }
    else if (id==NULL)
     {

         QMessageBox::information(this," ERREUR "," VEUILLEZ VERIFIER CHAMP id!!!!") ;
         QMessageBox::critical(0, qApp->tr("Ajout"),

                         qApp->tr("Probleme de modification"), QMessageBox::Cancel);



     }
        else if (mail==NULL)
         {

             QMessageBox::information(this," ERREUR "," VEUILLEZ VERIFIER CHAMP mail!!!!") ;
             QMessageBox::critical(0, qApp->tr("Ajout"),

                             qApp->tr("Probleme de modification"), QMessageBox::Cancel);



         }


       else if (age==NULL)
             {

                 QMessageBox::information(this," ERREUR "," VEUILLEZ VERIFIER CHAMP age !!!!") ;
                 QMessageBox::critical(0, qApp->tr("Ajout"),

                                 qApp->tr("Probleme de modification"), QMessageBox::Cancel);

             }

    else{

       test=Etmp.modifier(id,cin,age,nom,prenom,mail);
          if (test)
          {
                  ui->tab_employes->setModel(Etmp.afficher());
              QMessageBox::information(nullptr,QObject::tr("OK"),
                                   QObject::tr("modification établie"),
                                   QMessageBox::Ok);
              ui->modifier_nom->clear();
              //ui->l_id_supp->clear();
              ui->modifier_cin->clear();
              ui->modfier_id->clear();
             ui->modifier_prenom->clear();
              ui->modifier_mail->clear();
             ui->modifier_num->clear();
          }
          else{
          QMessageBox::critical(nullptr,QObject::tr("ERROR404"),
                                  QObject::tr("modification non établie"),
                                  QMessageBox::Cancel);}
    }
}

void maquette::on_pushButton_imprimer_clicked()
{
    QPrinter printer;
    QPrintDialog dialog(&printer,this);
    dialog.setWindowTitle("print document");
    if(ui->tab_employes) //hedhi ma habetch tekhdem khater ma yakrach fil textCursor().hasSelection()
    {
        dialog.addEnabledOption(QAbstractPrintDialog::PrintSelection);
    }

if(dialog.exec()!=QDialog::Accepted)
{
    return;
}
}

void maquette::on_tab_employes_clicked(const QModelIndex &index)
{
    ui->modfier_id->setText(ui->tab_employes->model()->data(ui->tab_employes->model()->index(index.row(),0)).toString());
  //  ui->l_id_supp->setText(ui->tab_employes->model()->data(ui->tab_employes->model()->index(index.row(),0)).toString());
     ui->modifier_nom->setText(ui->tab_employes->model()->data(ui->tab_employes->model()->index(index.row(),1)).toString());
      ui->modifier_prenom->setText(ui->tab_employes->model()->data(ui->tab_employes->model()->index(index.row(),2)).toString());
       ui->modifier_cin->setText(ui->tab_employes->model()->data(ui->tab_employes->model()->index(index.row(),3)).toString());
        ui->modifier_num->setText(ui->tab_employes->model()->data(ui->tab_employes->model()->index(index.row(),4)).toString());
        ui->modifier_mail->setText(ui->tab_employes->model()->data(ui->tab_employes->model()->index(index.row(),5)).toString());

}

void maquette::on_pushButton_impression_clicked()
{
    QString strStream;
                         QTextStream out(&strStream);

                          const int rowCount = ui->tab_employes->model()->rowCount();
                          const int columnCount = ui->tab_employes->model()->columnCount();
                         out <<  "<html>\n"
                         "<head>\n"
                                          "<meta Content=\"Text/html; charset=Windows-1251\">\n"
                                          <<  QString("<title>%1</title>\n").arg("strTitle")
                                          <<  "</head>\n"
                                          "<body bgcolor=#ffffff link=#5000A0>\n"

                                         //     "<align='right'> " << datefich << "</align>"
                                          "<center> <H1>Liste des employes</H1></br></br><table border=1 cellspacing=0 cellpadding=2>\n";

                                      // headers
                                      out << "<thead><tr bgcolor=#f0f0f0> <th>Numero</th>";
                                      out<<"<cellspacing=10 cellpadding=3>";
                                      for (int column = 0; column < columnCount; column++)
                                          if (!ui->tab_employes->isColumnHidden(column))
                                              out << QString("<th>%1</th>").arg(ui->tab_employes->model()->headerData(column, Qt::Horizontal).toString());
                                      out << "</tr></thead>\n";

                                      // data table
                                      for (int row = 0; row < rowCount; row++) {
                                          out << "<tr> <td bkcolor=0>" << row+1 <<"</td>";
                                          for (int column = 0; column < columnCount; column++) {
                                              if (!ui->tab_employes->isColumnHidden(column)) {
                                                  QString data = ui->tab_employes->model()->data(ui->tab_employes->model()->index(row, column)).toString().simplified();
                                                  out << QString("<td bkcolor=0>%1</td>").arg((!data.isEmpty()) ? data : QString("&nbsp;"));
                                              }
                                          }
                                          out << "</tr>\n";
                                      }
                                      out <<  "</table> </center>\n"
                                          "</body>\n"
                                          "</html>\n";

                                QString fileName = QFileDialog::getSaveFileName((QWidget* )0, "Sauvegarder en PDF", QString(), "*.pdf");
                                  if (QFileInfo(fileName).suffix().isEmpty()) { fileName.append(".pdf"); }

                                 QPrinter printer (QPrinter::PrinterResolution);
                                  printer.setOutputFormat(QPrinter::PdfFormat);
                                 printer.setPaperSize(QPrinter::A4);
                                printer.setOutputFileName(fileName);

                                 QTextDocument doc;
                                  doc.setHtml(strStream);
                                  doc.setPageSize(printer.pageRect().size()); // This is necessary if you want to hide the page number
                                  doc.print(&printer);
}

void maquette::on_pushButton_stat_clicked()
{
    QSqlQueryModel * model= new QSqlQueryModel();
                        model->setQuery("select * from EMPLOYE where AGE < 25 ");
                        float age=model->rowCount();
                        model->setQuery("select * from EMPLOYE where AGE  between 25 and 45 ");
                        float agee=model->rowCount();
                        model->setQuery("select * from EMPLOYE where AGE>45 ");
                        float ageee=model->rowCount();
                        float total=age+agee+ageee;
                        QString a=QString("moins de 25 ans "+QString::number((age*100)/total,'f',2)+"%" );
                        QString b=QString("entre 25 et 45 Ans"+QString::number((agee*100)/total,'f',2)+"%" );
                        QString c=QString("+45 Ans"+QString::number((ageee*100)/total,'f',2)+"%" );
                        QPieSeries *series = new QPieSeries();
                        series->append(a,age);
                        series->append(b,agee);
                        series->append(c,ageee);
                if (age!=0)
                {QPieSlice *slice = series->slices().at(0);
                 slice->setLabelVisible();
                 slice->setPen(QPen());}
                if ( agee!=0)
                {
                         // Add label, explode and define brush for 2nd slice
                         QPieSlice *slice1 = series->slices().at(1);
                         //slice1->setExploded();
                         slice1->setLabelVisible();
                }
                if(ageee!=0)
                {
                         // Add labels to rest of slices
                         QPieSlice *slice2 = series->slices().at(2);
                         //slice1->setExploded();
                         slice2->setLabelVisible();
                }
                        // Create the chart widget
                        QChart *chart = new QChart();
                        // Add data to chart with title and hide legend
                        chart->addSeries(series);
                        chart->setTitle("Pourcentage Par Age :Nombre Des employe "+ QString::number(total));
                        chart->legend()->hide();
                        // Used to display the chart
                        QChartView *chartView = new QChartView(chart);
                        chartView->setRenderHint(QPainter::Antialiasing);
                        chartView->resize(1000,500);
                        chartView->show();
}

void maquette::on_pushButton_tri_croissant_clicked()
{
    ui->tab_employes->setModel(Etmp.tricroissant());
}

void maquette::on_pushButton_tri_decroissant_clicked()
{
    ui->tab_employes->setModel(Etmp.trideccroissant());
}

void maquette::on_lineEdit_recherche_textChanged(const QString &arg1)
{
    if(ui->lineEdit_recherche->text() == "")
        {
            ui->tab_employes->setModel(Etmp.afficher());
        }
        else
        {
             ui->tab_employes->setModel(Etmp.rechercher(ui->lineEdit_recherche->text()));
        }
}

void maquette::on_pushButton_calcul_clicked()
{
    ui->lcdNumber_calcul->display(Etmp.calculer_tot_employes());
}

void maquette::on_QrCode_clicked()
{
    if(ui->tab_employes->currentIndex().row()==-1)
               QMessageBox::information(nullptr, QObject::tr("QrCode"),
                                        QObject::tr("Veuillez Choisir un(e) visiteur(e) du Tableau.\n"
                                                    "Click Ok to exit."), QMessageBox::Ok);
           else
           {
                int id=ui->tab_employes->model()->data(ui->tab_employes->model()->index(ui->tab_employes->currentIndex().row(),0)).toInt();
                const QrCode qr = QrCode::encodeText(std::to_string(id).c_str(), QrCode::Ecc::LOW);
                std::ofstream myfile;
                myfile.open ("qrcode.svg") ;
                myfile << qr.toSvgString(1);
                myfile.close();
                QSvgRenderer svgRenderer(QString("qrcode.svg"));
                QPixmap pix( QSize(90, 90) );
                QPainter pixPainter( &pix );
                svgRenderer.render( &pixPainter );
                ui->label_21->setPixmap(pix);
           }
}

void maquette::on_pb_connecter_clicked()
{
    dumessengerconnectiondialog D(this);
    if(D.exec()==QDialog::Rejected)
    {
        return;

    }
    mSocket->connectToHost(D.hostname(),D.port());

}

void maquette::on_pb_envoyer_clicked()
{
    QTextStream T(mSocket);
    T<<ui->le_nickname->text()<<": "<<ui->le_message->text();
    mSocket->flush();
    ui->le_message->clear();
}

void maquette::myfunction()

{

    QTime time =QTime::currentTime();

    QString time_text = time.toString("hh:mm:ss");

    ui->label_time1->setText(time_text);

    ui->label_time1_2->setText(time_text);

    ui->label_time1_3->setText(time_text);


}

void maquette::on_button_afficher_Ahmed_clicked()
{
    ui->tab_employes->setModel(Etmp.afficher());
    ui->comboBox_supprimer->setModel(Etmp.wombo_combo());
}








/*****************houyem**************/




void maquette::on_pb_ajouter_clicked()
{
    int CIN =ui->le_CIN->text().toInt();
    QString NOM=ui->le_nom->text();
    QString PRENOM=ui->le_prenom->text();
    int NUMERO_TEL=ui->le_numTel->text().toInt();
  Client C(CIN,NOM,PRENOM,NUMERO_TEL);
  if (CIN == 0)
  {
      QMessageBox::critical(nullptr, QObject::tr("Not OK"),
                            QObject::tr("CIN vide .\n"
                                        "Click Cancel to exist."),QMessageBox::Cancel);
  }
  else
      if (NOM == NULL)
      {
          QMessageBox::critical(nullptr, QObject::tr("Not OK"),
                                QObject::tr("NOM vide .\n"
                                            "Click Cancel to exist."),QMessageBox::Cancel);
      }

      else
          if (PRENOM == NULL)
      {
          QMessageBox::critical(nullptr, QObject::tr("Not OK"),
                                QObject::tr("PRENOM vide .\n"
                                            "Click Cancel to exist."),QMessageBox::Cancel);
      }

      else
          if (NUMERO_TEL == 0)
      {
          QMessageBox::critical(nullptr, QObject::tr("Not OK"),
                                QObject::tr("NUMERO_TEL vide .\n"
                                            "Click Cancel to exist."),QMessageBox::Cancel);
      }


  bool test = C.ajouter();
  notif m("CLIENT","client ajouté avec succés");

                m.afficher();
  QMessageBox msgBox;
  if (test)
  {
      ui->tab_client->setModel(C.afficher());
        ui->sup->setModel(C.wombo_combo());

                 QMessageBox::information (nullptr, QObject::tr("OK"),
                             QObject::tr("Ajout effectué\n"
                                             "Click cancel to exist."), QMessageBox::Cancel);
             }
             else
                 QMessageBox::critical(nullptr, QObject::tr("Not OK"),
                                       QObject::tr("Ajout non effectué.\n"
                                                   "Click Cancel to exist."),QMessageBox::Cancel);

}

void maquette::on_pb_modifier_clicked()
{
    int CIN=ui->le_CIN->text().toInt();
    QString NOM=ui->le_nom->text();
    QString PRENOM=ui->le_prenom->text();
    int NUMERO_TEL=ui->le_numTel->text().toInt();
    Client C;
    bool test=C.modifier(CIN,NOM,PRENOM,NUMERO_TEL );

    if(test)
    {
         ui->tab_client->setModel(C.afficher());
         ui->sup->setModel(C.wombo_combo());
        QMessageBox::information(nullptr,QObject::tr("ok"),
                                 QObject::tr("modification effectue\n""click cancel to exit."),
                                 QMessageBox::Cancel);

    }

    else
        QMessageBox::critical(nullptr,QObject::tr("not ok"),
                                 QObject::tr("modification non effectue\n""click cancel to exit."),
                                 QMessageBox::Cancel);

}

void maquette::on_pb_supprimer_clicked()
{
    Client C;

      int CIN=ui->sup->currentText().toInt();



      bool test=C.supprimer(CIN);
      QMessageBox msgBox;
      if (test)
        {   ui->tab_client->setModel(C.afficher());
    ui->sup->setModel(C.wombo_combo());
                 msgBox.setText("Suppression avec succes.");
      }
                            else
                 msgBox.setText("Echec de suppression.");

             msgBox.exec();
}

void maquette::on_pb_rechercher_clicked()
{
    QString rech =ui->le_CIN_rech->text();
        ui->tab_client->setModel(C.rechercher(rech));
}

void maquette::on_pb_tri_CIN_clicked()
{
    Client *C = new Client();
    ui->tab_client->setModel(C->tri_CIN());
}

void maquette::on_pb_tri_nom_clicked()
{
    Client *C = new Client();
    ui->tab_client->setModel(C->tri_nom());
}

void maquette::on_pb_tri_prenom_clicked()
{
    Client *C = new Client();
    ui->tab_client->setModel(C->tri_prenom());
}

void maquette::on_pb_tri_num_clicked()
{
    Client *C = new Client();
    ui->tab_client->setModel(C->tri_num());
}

void maquette::on_qrcodegen_clicked()
{
    int tabeq=ui->tab_client_2->currentIndex().row();
              QVariant cinn=ui->tab_client_2->model()->data(ui->tab_client_2->model()->index(tabeq,0));
              QString CIN= cinn.toString();
              QSqlQuery qry;
              qry.prepare("select * from CLIENT where CIN=:CIN");
              qry.bindValue(":CIN",CIN);
              qry.exec();
                 QString  iden,NOM,PRENOM,NUMERO_TEL ,ide;

              while(qry.next()){

                  CIN=qry.value(1).toString();
                  NOM=qry.value(2).toString();
                  PRENOM=qry.value(3).toString();
                  NUMERO_TEL=qry.value(4).toString();


              }
              ide=QString(CIN);
                     ide="CIN:"+iden+"NOM:"+NOM+"PRENOM:"+PRENOM,"NUMTEL:"+NUMERO_TEL;
              QrCode qr = QrCode::encodeText(ide.toUtf8().constData(), QrCode::Ecc::HIGH);

              // Read the black & white pixels
              QImage im(qr.getSize(),qr.getSize(), QImage::Format_RGB888);
              for (int y = 0; y < qr.getSize(); y++) {
                  for (int x = 0; x < qr.getSize(); x++) {
                      int color = qr.getModule(x, y);  // 0 for white, 1 for black

                      // You need to modify this part
                      if(color==0)
                          im.setPixel(x, y,qRgb(254, 254, 254));
                      else
                          im.setPixel(x, y,qRgb(0, 0, 0));
                  }
              }
              im=im.scaled(200,200);
              ui->qrcodecommande->setPixmap(QPixmap::fromImage(im));
}

void maquette::on_pb_affichage_clicked()
{
    ui->tab_client_2->setModel(C.afficher());
}

void maquette::on_pb_imprimer_clicked()
{
    QPrinter printer;
    QPrintDialog dialog(&printer, this);
    dialog.setWindowTitle("Print Document");
    if(ui->textEdit->textCursor().hasSelection())
        dialog.addEnabledOption(QAbstractPrintDialog::PrintSelection);
    if(dialog.exec() != QDialog::Accepted)
    {
        return ;
    }
}

void maquette::on_tab_client_activated(const QModelIndex &index)
{
    ui->le_CIN->setText(ui->tab_client->model()->data(ui->tab_client->model()->index(index.row(),0)).toString());
    ui->le_nom->setText(ui->tab_client->model()->data(ui->tab_client->model()->index(index.row(),1)).toString());
    ui->le_prenom->setText(ui->tab_client->model()->data(ui->tab_client->model()->index(index.row(),2)).toString());
    ui->le_numTel->setText(ui->tab_client->model()->data(ui->tab_client->model()->index(index.row(),3)).toString());

}

void maquette::on_pb_ajouter_Lina_clicked()
{
    int id = ui->le_id->text().toInt();
           QString localisation = ui->le_localisation->text();
           int nb_max = ui->le_nb_max->text().toInt();
           float prix = ui->le_prix->text().toInt();
           Emplacement E(id, localisation, nb_max, prix);

           if (id == 0)
           {
               QMessageBox::critical(nullptr, QObject::tr("Not OK"),
                                     QObject::tr("ID vide .\n"
                                                 "Click Cancel to exist."),QMessageBox::Cancel);
           }
           else if (nb_max == 0)
           {
               QMessageBox::critical(nullptr, QObject::tr("Not OK"),
                                     QObject::tr("nombre maximale vide .\n"
                                                 "Click Cancel to exist."),QMessageBox::Cancel);
           }
           else if (prix == 0)
           {
               QMessageBox::critical(nullptr, QObject::tr("Not OK"),
                                     QObject::tr("prix vide .\n"
                                                 "Click Cancel to exist."),QMessageBox::Cancel);
           }
           else if (localisation == NULL)
           {
               QMessageBox::critical(nullptr, QObject::tr("Not OK"),
                                     QObject::tr("localisation vide .\n"
                                                 "Click Cancel to exist."),QMessageBox::Cancel);
           }
           else
           {
               bool test = E.ajouter();
               if (test)
               {

                   //Refresh
                   ui->tab_emplacement->setModel(E.afficher());


                   QMessageBox::information (nullptr, QObject::tr("OK"),
                               QObject::tr("Ajout effectué\n"
                                               "Click cancel to exist."), QMessageBox::Cancel);
               }
               else
                   QMessageBox::critical(nullptr, QObject::tr("Not OK"),
                                         QObject::tr("Ajout non effectué.\n"
                                                     "Click Cancel to exist."),QMessageBox::Cancel);
           }

}

void maquette::on_pb_modifier__Lina_clicked()
{
    int id = ui->le_id->text().toInt();
        QString localisation = ui->le_localisation->text();
        int nb_max = ui->le_nb_max->text().toInt();
        float prix = ui->le_prix->text().toInt();

        if (id == 0)
        {
            QMessageBox::critical(nullptr, QObject::tr("Not OK"),
                                  QObject::tr("ID vide .\n"
                                              "Click Cancel to exist."),QMessageBox::Cancel);
        }
        else if (nb_max == 0)
        {
            QMessageBox::critical(nullptr, QObject::tr("Not OK"),
                                  QObject::tr("nombre maximale vide .\n"
                                              "Click Cancel to exist."),QMessageBox::Cancel);
        }
        else if (prix == 0)
        {
            QMessageBox::critical(nullptr, QObject::tr("Not OK"),
                                  QObject::tr("prix vide .\n"
                                              "Click Cancel to exist."),QMessageBox::Cancel);
        }
        else if (localisation == NULL)
        {
            QMessageBox::critical(nullptr, QObject::tr("Not OK"),
                                  QObject::tr("localisation vide .\n"
                                              "Click Cancel to exist."),QMessageBox::Cancel);
        }
        else
        {
            bool test = E.modifier(id,localisation,nb_max, prix);
            if (test)
            {

                //Refresh
                ui->tab_emplacement->setModel(E.afficher());

                QMessageBox::information (nullptr, QObject::tr("OK"),
                            QObject::tr("modification effectué\n"
                                            "Click cancel to exist."), QMessageBox::Cancel);


            }
            else
            {
                QMessageBox::critical(nullptr, QObject::tr("Not OK"),
                                      QObject::tr("modification non effectué.\n"
                                                  "Click Cancel to exist."),QMessageBox::Cancel);
            }}
}

void maquette::on_pb_supprimer__Lina_clicked()
{
    QString p = ui->sup->currentText();
        int id = p.toInt();
        if (id == 0)
        {
            QMessageBox::critical(nullptr, QObject::tr("Not OK"),
                                  QObject::tr("ID vide .\n"
                                              "Click Cancel to exist."),QMessageBox::Cancel);
        }
        else
        {

            bool test = E.supprimer(id);
            if (test)
            {
                //Refresh
                ui->tab_emplacement->setModel(E.afficher());

                QMessageBox::information (nullptr, QObject::tr("OK"),
                            QObject::tr("Suppression effectué\n"
                                            "Click cancel to exist."), QMessageBox::Cancel);
            }
            else
                {
                    QMessageBox::critical(nullptr, QObject::tr("Not OK"),
                                      QObject::tr("Suppression non effectué.\n"
                                                  "Click Cancel to exist."),QMessageBox::Cancel);
            }
        }

}

void maquette::on_pb_afficher_Lina_clicked()
{
    bool test = E.afficher();
        if (test)
        {
            //Refresh
            ui->tab_emplacement->setModel(E.afficher());

            QMessageBox::information (nullptr, QObject::tr("OK"),
                        QObject::tr("affichage effectué\n"
                                        "Click cancel to exist."), QMessageBox::Cancel);
        }
        else
            QMessageBox::critical(nullptr, QObject::tr("Not OK"),
                                  QObject::tr("affichage non effectué.\n"
                                              "Click Cancel to exist."),QMessageBox::Cancel);
}

void maquette::on_pb_id_afficher_Lina_clicked()
{
    ui->sup->setModel(E.afficher());
}

void maquette::on_pb_calculer_Lina_clicked()
{
    ui->res_calculer->display(E.calculerBudget());
}

void maquette::on_pb_stat_Lina_clicked()
{
    QSqlQueryModel * model= new QSqlQueryModel();

        model->setQuery("select * from EMPLACEMENT where PRIX < 100 ");
        float prix=model->rowCount();
        model->setQuery("select * from EMPLACEMENT where PRIX  between 100 and 200 ");
        float prix1=model->rowCount();
        model->setQuery("select * from EMPLACEMENT where PRIX>200 ");
        float prix2=model->rowCount();
        float total=prix+prix1+prix2;
        QString a = QString("moins de 100 DT  "+QString::number((prix*100)/total,'f',2)+"%" );
        QString b = QString("entre 100 et 200 DT "+QString::number((prix1*100)/total,'f',2)+"%" );
        QString c = QString("+200 DT "+QString::number((prix2*100)/total,'f',2)+"%" );
        QPieSeries *series = new QPieSeries();
        series->append(a,prix);
        series->append(b,prix1);
        series->append(c,prix2);
        if (prix!= 0)
        {
            QPieSlice *slice = series->slices().at(0);
            slice->setLabelVisible();
            slice->setPen(QPen());
        }
        if ( prix1!=0)
        {
                 // Add label, explode and define brush for 2nd slice
                 QPieSlice *slice1 = series->slices().at(1);
                 //slice1->setExploded();
                 slice1->setLabelVisible();
        }
        if(prix2!=0)
        {
                 // Add labels to rest of slices
                 QPieSlice *slice2 = series->slices().at(2);
                 //slice1->setExploded();
                 slice2->setLabelVisible();
        }
                // Create the chart widget
                QChart *chart = new QChart();
                // Add data to chart with title and hide legend
                chart->addSeries(series);
                chart->setTitle("Pourcentage Par PRIX :Nombre Des EMPLACEMENT "+ QString::number(total));
                chart->legend()->hide();
                // Used to display the chart
                QChartView *chartView = new QChartView(chart);
                chartView->setRenderHint(QPainter::Antialiasing);
                chartView->resize(1000,500);
                chartView->show();
}

void maquette::on_pb_triLocalisation_Lina_clicked()
{
    Emplacement *E = new Emplacement();
           ui->tab_emplacement->setModel(E->triLocalisation());
}

void maquette::on_pb_triId_Lina_clicked()
{
    Emplacement *E = new Emplacement();
           ui->tab_emplacement->setModel(E->triId());
}

void maquette::on_pb_triNbMax_Lina_clicked()
{
    Emplacement *E = new Emplacement();
           ui->tab_emplacement->setModel(E->triNb_max());
}

void maquette::on_pb_triPrix_Lina_clicked()
{
    Emplacement *E = new Emplacement();
           ui->tab_emplacement->setModel(E->triPrix());
}

void maquette::on_pb_localisation_afficher_Lina_clicked()
{
    QSqlQueryModel *model = new QSqlQueryModel;
        model->setQuery("SELECT LOCALISATION FROM EMPLACEMENT");

        ui->Localisation_combobox_Lina->setModel(model);
}

void maquette::on_pb_localisation_Lina_clicked()
{
    QString p=ui->Localisation_combobox_Lina->currentText();
        QDesktopServices::openUrl(QUrl("http://maps.google.com.sg/maps?q="+p+"&oe=utf-8&rls=org.mozilla:en-US:official&client=firefox-a&um=1&ie=UTF-8&hl=en&sa=N&tab=wl"));
}

void maquette::on_tab_emplacement_activated(const QModelIndex &index)
{
    ui->le_id->setText(ui->tab_emplacement->model()->data(ui->tab_emplacement->model()->index(index.row(),0)).toString());

        ui->le_localisation->setText(ui->tab_emplacement->model()->data(ui->tab_emplacement->model()->index(index.row(),1)).toString());
        ui->le_nb_max->setText(ui->tab_emplacement->model()->data(ui->tab_emplacement->model()->index(index.row(),2)).toString());
        ui->le_prix->setText(ui->tab_emplacement->model()->data(ui->tab_emplacement->model()->index(index.row(),3)).toString());
}

void maquette::on_PB_Ajout_2_clicked()
{
    QString matricule=ui->matricule->text();
        QString chauffeur=ui->chauffeur->text();
        QString lieu=ui->lieu->text();
        QString fautif=ui->fautif->text();
        QString dat=ui->date->text();
        Accident A(matricule,chauffeur,lieu,fautif,dat);
        bool test = A.ajouter();
               if (test)
               {
                   ui->tableView->setModel(A.afficher());

                   QMessageBox::information (nullptr, QObject::tr("OK"),
                               QObject::tr("Ajout effectué\n"
                                               "Click cancel to exist."), QMessageBox::Cancel);
               }
               else
                   QMessageBox::critical(nullptr, QObject::tr("Not OK"),
                                         QObject::tr("Ajout non effectué.\n"
                                                     "Click Cancel to exit."),QMessageBox::Cancel);
}

void maquette::on_PB_supp_2_clicked()
{
    Accident A;
        QString MATRICULE=ui->matricule_s->text();
        bool test=A.supprimer(MATRICULE);
                QMessageBox msgBox;

                if(test)
                {
                    ui->tableView->setModel(A.afficher());
                    msgBox.setText("Suppression avec succes.");
                }


                else
                        msgBox.setText("echec de suppression.");
                msgBox.exec();
}

void maquette::on_PB_modifier_clicked()
{
    QString matricule= ui->matricule->text();
               QString chauffeur= ui->chauffeur->text();
               QString lieu= ui->lieu->text();
               QString fautif= ui->fautif->text();
               QString dat= ui->date->text();
               Accident A1(matricule,chauffeur,lieu,fautif,dat);
               bool test=A1.modifier();
               if (test)
                        {
                                ui->tableView->setModel(A.afficher());
                            QMessageBox::information(nullptr,QObject::tr("OK"),
                                                 QObject::tr("modification établie"),
                                                 QMessageBox::Ok);}
                        else{
                        QMessageBox::critical(nullptr,QObject::tr("ERROR404"),
                                                QObject::tr("modification non établie"),
                                                QMessageBox::Cancel);}
}

void maquette::on_PDF_clicked()
{
    QPrinter printer;
    printer.setOutputFormat(QPrinter::PdfFormat);
    printer.setOutputFileName("PDFaccidents.pdf");
         QPdfWriter pdf("C:/Users/Aziz/Desktop/classe_acc/PDFaccidents.pdf");
        QPainter painter(&pdf);
        QImage logo(":/logo/VVS.png");
    painter.drawImage(50,50,logo);

                                    int i = 4000;
                                      painter.setPen(Qt::red);
                                      painter.setFont(QFont("Arial", 30));
                                      painter.drawText(2300,1200,"Liste Des Accidents");
                                      painter.setPen(Qt::black);
                                      painter.setFont(QFont("Arial", 50));
                                      painter.drawRect(1500,200,7300,2600);
                                      painter.drawRect(0,3000,9600,500);
                                      painter.setFont(QFont("Arial", 9));
                                      painter.drawText(300,3300,"MATRICULE");
                                      painter.drawText(2300,3300,"CHAUFFEUR");
                                      painter.drawText(4300,3300,"LIEU");
                                      painter.drawText(6300,3300,"FAUTIF");
                                      painter.drawText(8300,3300,"DAT");




                                      QSqlQuery query;
                                      query.prepare("select * from ACCIDENT");
                                      query.exec();
                                      while (query.next())
                                      {
                                          painter.drawText(300,i,query.value(0).toString());
                                          painter.drawText(2300,i,query.value(1).toString());
                                          painter.drawText(4300,i,query.value(2).toString());
                                          painter.drawText(6300,i,query.value(3).toString());
                                          painter.drawText(8300,i,query.value(4).toString());



                                         i = i +500;
                                      }
                                      int reponse = QMessageBox::question(this, "Génerer PDF", "<PDF Enregistré>...Vous Voulez Affichez Le PDF ?", QMessageBox::Yes |  QMessageBox::No);
                                          if (reponse == QMessageBox::Yes)
                                          {
                                              QDesktopServices::openUrl(QUrl::fromLocalFile("C:/Users/Aziz/Desktop/classe_acc/PDFaccidents.pdf"));

                                              painter.end();
                                          }
                                          if (reponse == QMessageBox::No)
                                          {
                                               painter.end();
                                          }
}

void maquette::on_rechercher_clicked()
{
    QString matricule = ui->matricule_re->text();
         ui->tableView->setModel(A.afficher_matricule(matricule));
}

void maquette::on_imprimer_clicked()
{
    QPrinter rd;
            QPrintDialog d(&rd,this);
            d.setWindowTitle("Print Accident");
            d.addEnabledOption(QAbstractPrintDialog::PrintSelection);
            if (d.exec() != QDialog::Accepted)
                return ;
}

void maquette::on_calculer_clicked()
{
    ui->lcdNumber_calculer->display(A.calculernbacc());
}

/*void maquette::on_browse_clicked()
{
        files.clear();
        QFileDialog dialog(this);
        dialog.setDirectory(QDir::homePath());
        dialog.setFileMode(QFileDialog::ExistingFiles);
        if (dialog.exec())
            files = dialog.selectedFiles();
        QString fileListString;
        foreach(QString file, files)
            fileListString.append( """ + QFileInfo(file).fileName() + "" " );
        ui->fichier->setText( fileListString );
}
void maquette::on_email_clicked()
{
    QString ch;
        ch=ui->rec->text();
       if(ch.contains("@", Qt::CaseInsensitive)==true)
        {mail* Mail = new mail ("medaziz.zalila@esprit.tn",ui->pass->text(), "smtp.gmail.com");
          connect(Mail, SIGNAL(status(QString)), this, SLOT(mailSent(QString)));
          if( !files.isEmpty() )
              Mail->sendMail("medaziz.zalila@esprit.tn", ui->rec->text() , ui->objet->text(),ui->msg->text(),files );
          else
              Mail->sendMail("medaziz.zalila@esprit.tn", ui->rec->text() , ui->objet->text(),ui->msg->text());
    }
       else
           QMessageBox::information(nullptr,QObject::tr("mail non envoyé"),
                                    QObject::tr("mail non envoyé. \n"
                                                "Click Cancel to exist."),QMessageBox::Cancel);
}
*/
