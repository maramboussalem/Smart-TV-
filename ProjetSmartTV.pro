<<<<<<< HEAD
QT       += core gui sql
QT       += core gui multimedia multimediawidgets
QT       += charts
QT       += printsupport
QT       += location
QT       += core gui  serialport
QT       += network

QT += core gui widgets charts

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets quickwidgets

=======
QT       += core gui
QT+= sql
#QT += charts
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
#QT += quick
#QT += quickwidgets
>>>>>>> 18d955075ebf7e49d498a0f477c7a42083282ca3
CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS
<<<<<<< HEAD
=======
QT += printsupport
>>>>>>> 18d955075ebf7e49d498a0f477c7a42083282ca3

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
<<<<<<< HEAD
    arduino.cpp \
    connection.cpp \
    emissions.cpp \
    employee.cpp \
    entite_emission.cpp \
    entite_employee.cpp \
    entite_equipement.cpp \
    entite_evenment.cpp \
    entite_pub.cpp \
    entite_sponsors.cpp \
    equipement.cpp \
    evenement1.cpp \
    main.cpp \
    mainwindow.cpp \
    map.cpp \
    menu.cpp \
    publicite.cpp \
    qsubtitles.cpp \
    smtp.cpp \
    sponsors.cpp \
    videoplayer.cpp

HEADERS += \
    arduino.h \
    connection.h \
    emissions.h \
    employee.h \
    entite_emission.h \
    entite_employee.h \
    entite_equipement.h \
    entite_evenment.h \
    entite_pub.h \
    entite_sponsors.h \
    equipement.h \
    evenement1.h \
    mainwindow.h \
    map.h \
    menu.h \
    publicite.h \
    qsubtitles.h \
    smtp.h \
    sponsors.h \
    videoplayer.h

FORMS += \
    emissions.ui \
    employee.ui \
    equipement.ui \
    evenement1.ui \
    mainwindow.ui \
    map.ui \
    menu.ui \
    publicite.ui \
    sponsors.ui \
    videoplayer.ui
=======
    connection.cpp \
    emission.cpp \
    employee.cpp \
    entite_emission.cpp \
    entite_evenment.cpp \
    equipement.cpp \
    evenement.cpp \
    main.cpp \
    mainwindow.cpp \
    menu.cpp \
    publicite.cpp \
    sponsors.cpp

HEADERS += \
    connection.h \
    emission.h \
    employee.h \
    entite_emission.h \
    entite_evenment.h \
    equipement.h \
    evenement.h \
    mainwindow.h \
    menu.h \
    publicite.h \
    sponsors.h

FORMS += \
    emission.ui \
    employee.ui \
    equipement.ui \
    evenement.ui \
    mainwindow.ui \
    menu.ui \
    publicite.ui \
    sponsors.ui
>>>>>>> 18d955075ebf7e49d498a0f477c7a42083282ca3

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
<<<<<<< HEAD
    1.qrc \
    Background.qrc \
    BackgroundRouge.qrc \
    Buttons.qrc \
    Emission.qrc \
    Evenement.qrc \
    Logo.qrc \
    Maps.qrc \
    l.qrc \
    sta.qrc
=======
    Background.qrc \
    BackgroundRouge.qrc \
    Buttons.qrc \
    Images.qrc \
    Logo.qrc \
    Metiers.qrc \
    Tri.qrc \
    e1.qrc \
    h.qrc \
    map.qrc
>>>>>>> 18d955075ebf7e49d498a0f477c7a42083282ca3
