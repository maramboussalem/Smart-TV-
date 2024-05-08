#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
<<<<<<< HEAD
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include "arduino.h"
=======
>>>>>>> 18d955075ebf7e49d498a0f477c7a42083282ca3

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
<<<<<<< HEAD
    explicit MainWindow(QWidget *parent = nullptr);
=======
    MainWindow(QWidget *parent = nullptr);
>>>>>>> 18d955075ebf7e49d498a0f477c7a42083282ca3
    ~MainWindow();

private slots:
    void on_Connecter_clicked();
<<<<<<< HEAD
    void on_Retour_clicked();
    bool loginUser(const QString &nom, const QString &password);
    void update_label();

private:
    Ui::MainWindow *ui;
    QSqlDatabase mydb;
    QByteArray data;

    Arduino A;
};

=======

private:
    Ui::MainWindow *ui;
};
>>>>>>> 18d955075ebf7e49d498a0f477c7a42083282ca3
#endif // MAINWINDOW_H
