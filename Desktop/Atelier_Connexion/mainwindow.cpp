#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "emissions.h"
#include <QApplication>
#include <QMessageBox>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->table_AfficherEmission->setModel(Etmp.afficher());
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_Ajouter_clicked()
{

    int id_emission=ui->lineEdit_IdEmission->text().toInt();
    QString titre=ui->lineEdit_Titre->text();
    QString categorie=ui->lineEdit_Categorie->text();
    QString realisateur=ui->lineEdit_Realisateur->text();
    QString duree=ui->lineEdit_Duree->text();
    QDate date_emission=ui->dateEdit->date();
    QString description=ui->lineEdit_Description->text();

    Emissions E(id_emission,titre,categorie,realisateur,duree,date_emission,description);
    bool test=E.ajouter();

    if(test)
    {
        ui->table_AfficherEmission->setModel(Etmp.afficher());

        QMessageBox::information(nullptr, QObject::tr("OK"),
                    QObject::tr("Ajout effectué\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);

    }
    else
        QMessageBox::critical(nullptr, QObject::tr("NOT OK"),
                    QObject::tr("Ajout non effectué\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);

}

void MainWindow::on_pushButton_supprimer_clicked()
{
    int id_emission=ui->lineEdit_IdEmission->text().toInt();
    bool test=Etmp.supprimer(id_emission);
    if(test)
    {
        ui->table_AfficherEmission->setModel(Etmp.afficher());

        QMessageBox::information(nullptr, QObject::tr("OK"),
                    QObject::tr("Suppression effectuée\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);

    }
    else
        QMessageBox::critical(nullptr, QObject::tr("NOT OK"),
                    QObject::tr("Suppression non effectué\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);

}

void MainWindow::on_pushButton_Modifier_clicked()
{
    int id_emission=ui->lineEdit_IdEmission_M->text().toInt();
    QString titre=ui->lineEdit_Titre_M->text();
    QString categorie=ui->lineEdit_Categorie_M->text();
    QString realisateur=ui->lineEdit_Realisateur_M->text();
    QString duree=ui->lineEdit_Duree_M->text();
    QDate date_emission=ui->dateEdit_M->date();
    QString description=ui->lineEdit_Description_M->text();

    Emissions E(id_emission, titre, categorie, realisateur, duree, date_emission, description);

    bool test = E.modifier(id_emission, titre, categorie, realisateur, duree, date_emission, description);

    if (test)
    {
        ui->table_AfficherEmission->setModel(Etmp.afficher());
        QMessageBox::information(nullptr, QObject::tr("OK"),
                                 QObject::tr("Modification effectuée.\n"
                                             "Click Cancel to exit."), QMessageBox::Cancel);
    }
    else
    {
        QMessageBox::critical(nullptr, QObject::tr("Not OK"),
                              QObject::tr("Modification non effectuée.\n"
                                          "Click Cancel to exit."), QMessageBox::Cancel);
    }
}


void MainWindow::on_pushButtonRecherche_clicked()
{

}
