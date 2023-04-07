#include "dumessengerconnectiondialog.h"
#include "ui_dumessengerconnectiondialog.h"

dumessengerconnectiondialog::dumessengerconnectiondialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::dumessengerconnectiondialog)
{
    ui->setupUi(this);
}

dumessengerconnectiondialog::~dumessengerconnectiondialog()
{
    delete ui;
}


void dumessengerconnectiondialog::on_pb_accepter_clicked()
{
    mHostname=ui->hostname->text();
    mPort=ui->port->value();
    accept();
}
