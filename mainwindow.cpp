#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "menu.h"
#include <QMessageBox>
<<<<<<< HEAD
#include <QDebug>
#include <QSqlError>
#include "employee.h"
#include "entite_employee.h"
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    int ret=A.connect_arduino(); // lancer la connexion à arduino
    switch(ret){
    case(0):qDebug()<< "arduino is available and connected to : "<< A.getarduino_port_name();
        break;
    case(1):qDebug() << "arduino is available but not connected to :" <<A.getarduino_port_name();
       break;
    case(-1):qDebug() << "arduino is not available";
    }
     QObject::connect(A.getserial(),SIGNAL(readyRead()),this,SLOT(update_label()));
=======
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
>>>>>>> 18d955075ebf7e49d498a0f477c7a42083282ca3
}

MainWindow::~MainWindow()
{
    delete ui;
}
<<<<<<< HEAD
void MainWindow::update_label()
{
    data = A.read_from_arduino();

    // Si les données reçues sont des chiffres de 0 à 9
    if (data >= "0" && data <= "9")
    {
        // Ajouter les chiffres au champ lineEdit_motdepasse
        ui->lineEdit_motdepasse->setText(ui->lineEdit_motdepasse->text() + data);
    }
    // Si la donnée reçue est "ENTER"
    else if (data == "ENTER")
    {
        // Connecter
        on_Connecter_clicked();
    }
    // Autres actions à ajouter ici si nécessaire
}
bool MainWindow::loginUser(const QString &Email, const QString &password)
{
    if (Email == "eya@employee.tn" && password == "111") {
           Employee employeeDialog;
           employeeDialog.exec();
           A.write_to_arduino("111\n"); // Appel à la fonction A.write_to_arduino avec les identifiants "eya" et "111"
           return true;
       }
       else if (Email == "yasmine@equipement.tn" && password == "222") {
           A.write_to_arduino("222\n");
           return true;
       }
       else if (Email == "maram@emission.tn" && password == "333") {
           A.write_to_arduino("333\n");
           return true;
       }
       else if (Email == "ala@evenement.tn" && password == "444") {
           A.write_to_arduino("444\n");
           return true;
       }
       else if (Email == "ranine@publicite.tn" && password == "555") {
           A.write_to_arduino("555\n");
           return true;
       }
       else if (Email == "rached@sponsor.tn" && password == "666") {
           A.write_to_arduino("666\n");
           return true;
       }
       else if (Email.isEmpty() || password.isEmpty()) {
           // Nom ou mot de passe vide
           return false;
       }
       else {
           // Les informations d'identification sont incorrectes
           return false;
       }
}
void MainWindow::on_Connecter_clicked()
{
    QString Email = ui->lineEdit_nom->text();
    QString password = ui->lineEdit_motdepasse->text();
    data = A.read_from_arduino();
    bool loginResult = loginUser(Email, password);
    if (!loginResult) {
      // Identifiants incorrects
        QMessageBox::warning(this, "Erreur", "Nom ou mot de passe incorrect.");
     } else {
       // Connexion réussie
        Menu menuDialog;
        menuDialog.exec();
     }
}
void MainWindow::on_Retour_clicked()
{
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Connection", "Êtes-vous sûr de vouloir fermer l'application ?", QMessageBox::Yes | QMessageBox::No);
    if (reply == QMessageBox::Yes)
    {
        QApplication::quit();
    }
}

=======


void MainWindow::on_Connecter_clicked()
{
    Menu menuDialog;
    menuDialog.exec();
}
>>>>>>> 18d955075ebf7e49d498a0f477c7a42083282ca3
