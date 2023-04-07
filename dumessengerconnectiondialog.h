#ifndef DUMESSENGERCONNECTIONDIALOG_H
#define DUMESSENGERCONNECTIONDIALOG_H

#include <QDialog>

namespace Ui {
class dumessengerconnectiondialog;
}

class dumessengerconnectiondialog : public QDialog
{
    Q_OBJECT

public:
    explicit dumessengerconnectiondialog(QWidget *parent = nullptr);
    ~dumessengerconnectiondialog();
    QString hostname()const;
    quint16 port()const;

private slots:
    void on_pb_accepter_clicked();

private:
    Ui::dumessengerconnectiondialog *ui;
    QString mHostname;
    quint16 mPort;
};
inline  QString dumessengerconnectiondialog:: hostname()const
{
    return mHostname;
}
inline quint16 dumessengerconnectiondialog::port()const
{
    return mPort;
}
#endif // DUMESSENGERCONNECTIONDIALOG_H
