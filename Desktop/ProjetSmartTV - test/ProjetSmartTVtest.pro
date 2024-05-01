QT       += core gui sql network
QT += charts
QT += network

QT       += core gui  serialport
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11
CONFIG += pdf

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0
SOURCES += \
    arduino.cpp \
    connection.cpp \
    emission.cpp \
    employee.cpp \
    employement.cpp \
    employes.cpp \
    equipement.cpp \
    evenement.cpp \
    lemission.cpp \
    lemployes.cpp \
    lequipement.cpp \
    levennement.cpp \
    lpublicite.cpp \
    lsponsore.cpp \
    main.cpp \
    mainwindow.cpp \
    menu.cpp \
    publicite.cpp \
    smtp.cpp \
    sponsors.cpp

HEADERS += \
    arduino.h \
    connection.h \
    emission.h \
    employee.h \
    employement.h \
    employes.h \
    equipement.h \
    evenement.h \
    lemission.h \
    lemployes.h \
    lequipement.h \
    levennement.h \
    lpublicite.h \
    lsponsore.h \
    mainwindow.h \
    menu.h \
    publicite.h \
    smtp.h \
    sponsors.h

FORMS += \
    emission.ui \
    employee.ui \
    employement.ui \
    equipement.ui \
    evenement.ui \
    lemission.ui \
    lemployes.ui \
    lequipement.ui \
    levennement.ui \
    lpublicite.ui \
    lsponsore.ui \
    mainwindow.ui \
    menu.ui \
    publicite.ui \
    sponsors.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    Background.qrc \
    BackgroundRouge.qrc \
    Buttons.qrc \
    Images.qrc \
    Logo.qrc \
    Metiers.qrc \
    Tri.qrc \
    e1.qrc \
    h.qrc
