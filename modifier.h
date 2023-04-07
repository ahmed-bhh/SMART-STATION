#ifndef MODIFIER_H
#define MODIFIER_H

#include <QDialog>
#include"voiture.h"
#include"maquette.h"
#include<QWidget>
#include<QMessageBox>
#include<QTextStream>
#include<QIntValidator>
namespace Ui {
class modifier;
}

class modifier : public QDialog
{
    Q_OBJECT

public:
    explicit modifier(QWidget *parent = nullptr);
    ~modifier();

private slots:
    void on_matricule_edit_clicked();

    void on_choix_matricule_activated(const QString &arg1);

    void on_aff_mat_clicked();

private:
    Ui::modifier *ui;
    Voiture V;
};

#endif // MODIFIER_H

