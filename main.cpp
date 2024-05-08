#include "mainwindow.h"
#include "connection.h"
#include <QApplication>
<<<<<<< HEAD
#include <QMessageBox>
=======
>>>>>>> 18d955075ebf7e49d498a0f477c7a42083282ca3

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Connection c ;
<<<<<<< HEAD

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

=======
    bool test = c.createconnection();
    MainWindow w;
    w.show();
    return a.exec();
}
>>>>>>> 18d955075ebf7e49d498a0f477c7a42083282ca3
