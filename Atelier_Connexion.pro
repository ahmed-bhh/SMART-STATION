#-------------------------------------------------
#
# Project created by QtCreator 2018-10-26T21:45:23
#
#-------------------------------------------------

QT       += core gui sql \
    quick
QT       += core gui charts
QT      += printsupport
QT  += core network
QT  +=svg
QT += core gui multimedia multimediawidgets
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Atelier_Connexion
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11
CONFIG  += c++11 console
CONFIG -= app_bundle
SOURCES += \
    accident.cpp \
    chatserver.cpp \
    chatsocket.cpp \
    client.cpp \
    dumessengerconnectiondialog.cpp \
    emplacement.cpp \
    employes.cpp \
    exportexcel.cpp \
    login.cpp \
        main.cpp \
        mainwindow.cpp \
    connection.cpp \
    maquette.cpp \
    modifier.cpp \
    notif.cpp \
    qrcode.cpp \
    voiture.cpp

HEADERS += \
    QrCode.hpp \
    accident.h \
    chatserver.h \
    chatsocket.h \
    client.h \
    dumessengerconnectiondialog.h \
    emplacement.h \
    employes.h \
    exportexcel.h \
    login.h \
        mainwindow.h \
    connection.h \
    maquette.h \
    modifier.h \
    notif.h \
    qrcode.h \
    qrcodeh.h \
    voiture.h

FORMS += \
        dumessengerconnectiondialog.ui \
        login.ui \
        mainwindow.ui \
        maquette.ui \
        modifier.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

STATECHARTS +=
