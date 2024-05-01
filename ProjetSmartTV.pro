QT       += core gui sql
QT       += core gui multimedia multimediawidgets
QT       += charts
QT       += printsupport
QT       += location
QT       += core gui  serialport
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets quickwidgets

CONFIG += c++11

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
    emissions.cpp \
    employee.cpp \
    entite_emission.cpp \
    entite_evenment.cpp \
    equipement.cpp \
    evenement1.cpp \
    main.cpp \
    mainwindow.cpp \
    map.cpp \
    menu.cpp \
    publicite.cpp \
    qsubtitles.cpp \
    sponsors.cpp

HEADERS += \
    arduino.h \
    connection.h \
    emissions.h \
    employee.h \
    entite_emission.h \
    entite_evenment.h \
    equipement.h \
    evenement1.h \
    mainwindow.h \
    map.h \
    menu.h \
    publicite.h \
    qsubtitles.h \
    sponsors.h

FORMS += \
    emissions.ui \
    employee.ui \
    equipement.ui \
    evenement1.ui \
    mainwindow.ui \
    map.ui \
    menu.ui \
    publicite.ui \
    sponsors.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    1.qrc \
    Background.qrc \
    BackgroundRouge.qrc \
    Buttons.qrc \
    Emission.qrc \
    Evenement.qrc \
    Logo.qrc \
    Maps.qrc
