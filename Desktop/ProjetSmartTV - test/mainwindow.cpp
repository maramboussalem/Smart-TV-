#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "menu.h"
#include <QMessageBox>
#include <QDebug>
#include <QSqlError>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    OpenConnection();
    int ret=A.connect_arduino(); // lancer la connexion à arduino
    switch(ret){
    case(0):qDebug()<< "arduino is available and connected to : "<< A.getarduino_port_name();
        break;
    case(1):qDebug() << "arduino is available but not connected to :" <<A.getarduino_port_name();
       break;
    case(-1):qDebug() << "arduino is not available";
    }
     QObject::connect(A.getserial(),SIGNAL(readyRead()),this,SLOT(update_label())); // permet de lancer
     //le slot update_label suite à la reception du signal readyRead (reception des données).
}

MainWindow::~MainWindow()
{
    CloseConnection();
    delete ui;
}
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


bool MainWindow::loginUser(const QString &nom, const QString &password)
{
    if (nom == "eya" && password == "111") {
           A.write_to_arduino("111\n"); // Appel à la fonction A.write_to_arduino avec les identifiants "eya" et "111"
           return true;
       }
       else if (nom == "yasmine" && password == "222") {
           A.write_to_arduino("222\n");
           return true;
       }
       else if (nom == "maram" && password == "333") {
           A.write_to_arduino("333\n");
           return true;
       }
       else if (nom == "ala" && password == "444") {
           A.write_to_arduino("444\n");
           return true;
       }
       else if (nom == "ranine" && password == "555") {
           A.write_to_arduino("555\n");
           return true;
       }
       else if (nom == "rached" && password == "666") {
           A.write_to_arduino("666\n");
           return true;
       }
       else if (nom.isEmpty() || password.isEmpty()) {
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
    QString nom = ui->lineEdit_nom->text();
        QString password = ui->lineEdit_motdepasse->text();
        data = A.read_from_arduino();
        bool loginResult = loginUser(nom, password);

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
    reply = QMessageBox::question(this, "Qt With Katern", "Êtes-vous sûr de vouloir fermer l'application ?", QMessageBox::Yes | QMessageBox::No);
    if (reply == QMessageBox::Yes)
    {
        QApplication::quit();
    }
}

bool MainWindow::OpenConnection()
{
    mydb = QSqlDatabase::addDatabase("QODBC");
    mydb.setDatabaseName("SMARTTV");
    if (!mydb.open()) {
        ui->label->setText("Failed connection");
        return false;
    } else {
        ui->label->setText("Connected...");
        return true;
    }
}

void MainWindow::CloseConnection()
{
    mydb.close();
    mydb.removeDatabase("");
}

/*void MainWindow::on_pushButton_clicked()
{
    A.write_to_arduino("111\n"); // Ajouter \n pour indiquer la fin de la chaîne
}*/
