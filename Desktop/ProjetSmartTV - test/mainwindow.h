#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include "arduino.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_Connecter_clicked();
    void on_Retour_clicked();
    bool loginUser(const QString &nom, const QString &password);
    void update_label();
    void on_pushButton_clicked();

private:
    Ui::MainWindow *ui;
    QSqlDatabase mydb;
    QByteArray data; // variable contenant les données reçues

    arduino A; // objet temporaire
    void CloseConnection();
    bool OpenConnection();
};

#endif // MAINWINDOW_H
