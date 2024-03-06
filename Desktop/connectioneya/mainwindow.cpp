#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "employes.h"
#include <QApplication>
#include <QMessageBox>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
      ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->tableView->setModel(etmp.afficher());
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_Ajouter_clicked()
{
    int id_E = ui->lineEdit_IdE->text().toInt();
    QString nom = ui->lineEdit_nom->text();
    QString prenom = ui->lineEdit_prenom->text();
    QString email = ui->lineEdit_email->text();
    QDate date_naissance = ui->dateEdit->date();
    QString telephonne = ui->lineEdit_tele->text();
    QString adresse = ui->lineEdit_adresse->text();

    employes e(id_E,nom,prenom,email,date_naissance,telephonne,adresse);
    bool test = e.ajouter();
    if (test)
    {
        ui->tableView->setModel(etmp.afficher());
        QMessageBox::information(this, QObject::tr("OK"),
                                 QObject::tr("Ajout effectué\nClick Cancel to exit."),
                                 QMessageBox::Cancel);
    }
    else
    {
        QMessageBox::critical(this, QObject::tr("Not OK"),
                              QObject::tr("Ajout non effectué.\nClick Cancel to exit."),
                              QMessageBox::Cancel);
    }
}

void MainWindow::on_pushButton_supprimer_clicked()
{
    int id_E = ui->lineEdit_IdE->text().toInt();
    bool test = etmp.supprimer(id_E);
    if (test)
    {
        QMessageBox::information(this, QObject::tr("OK"),
                                 QObject::tr("Suppression effectuée\nClick Cancel to exit."),
                                 QMessageBox::Cancel);
    }
    else
    {
        QMessageBox::critical(this, QObject::tr("Not OK"),
                              QObject::tr("Suppression non effectuée\nClick Cancel to exit."),
                              QMessageBox::Cancel);
    }
}

void MainWindow::on_pushButton_Modifier_clicked()
{
    int id_E = ui->lineEdit_IdE_M->text().toInt();
       QString nom = ui->lineEdit_nom_M->text();
       QString prenom = ui->lineEdit_prenom_M->text();
       QString email = ui->lineEdit_email_M->text();
       QDate date_naissance = ui->dateEdit_M->date();
       QString telephonne = ui->lineEdit_tel_M->text();
       QString adresse = ui->lineEdit_adresse_M->text();


       employes e(id_E, nom, prenom, email,date_naissance, telephonne, adresse);
       bool test = e.modifier(id_E, nom, prenom, email, date_naissance, telephonne, adresse);
       if (test)
       {
            ui->tableView->setModel(etmp.afficher());
           QMessageBox::information(this, QObject::tr("OK"),
                                    QObject::tr("Modification effectuée\nClick Cancel to exit."),
                                    QMessageBox::Cancel);
       }
       else
       {
           QMessageBox::critical(this, QObject::tr("Not OK"),
                                 QObject::tr("Modification non effectuée\nClick Cancel to exit."),
                                 QMessageBox::Cancel);
   }
}
