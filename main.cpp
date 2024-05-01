#include "mainwindow.h"
#include "connection.h"
#include <QApplication>
#include <QMessageBox>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Connection c ;

    MainWindow w;

     bool test = c.createconnection();

     if(test)
     {w.show();
         QMessageBox::information(nullptr, QObject::tr("Database is open"),
                     QObject::tr("Connection successful.\n"
                                 "Click Cancel to exit."), QMessageBox::Cancel);

 }
     else
         QMessageBox::critical(nullptr, QObject::tr("Database is not open"),
                     QObject::tr("Connection failed.\n"
                                 "Click Cancel to exit."), QMessageBox::Cancel);



     return a.exec();
}

