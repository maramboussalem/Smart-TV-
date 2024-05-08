#include "emission.h"
#include "ui_emission.h"
#include "entite_emission.h"
#include <QMessageBox>

Entite_emission::Entite_emission(){}
Emission::Emission(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Emission)
{
    ui->setupUi(this);
    ui->tableView->setModel(em.afficher());
}

Emission::~Emission()
{
    delete ui;
}
// ajout
void Emission::on_pushButton_9_clicked()
{
    int id = ui->id->text().toInt();
    QString titre = ui->titre->text();
    QString category = ui->category->currentText();
    QString realisateur = ui->realisateur->text();
   // QString langue = ui->langue->text();
    QString description = ui->description->toPlainText();
    QString duree = ui->duree->text();
    QString horraire = ui->horraire->text();
    QString date = ui->date->text();
    Entite_emission em (id, titre, category,realisateur,date,duree , description,horraire);
    bool test = em.ajouter();
    if(test) {
       //  ui->tableView->setModel(em.afficher());
        ui->tableView->setModel(em.afficher());
        QMessageBox::information(nullptr,QObject::tr("insertion"),
                               QObject::tr("insertion avec success.\n"),QMessageBox::Cancel);

    }
    else {
        QMessageBox::critical(nullptr,QObject::tr("insertion"),
                               QObject::tr("insertion echoue.\n"),QMessageBox::Cancel);
    }
}
// suppression
void Emission::on_pushButton_14_clicked()
{
    int id = ui->id_suppression->text().toInt();
    bool test = em.supprimer(id);

    if(test) {
        ui->tableView->setModel(em.afficher());
        QMessageBox::information(nullptr,QObject::tr("suppression"),
                               QObject::tr("delete succesful.\n"),QMessageBox::Cancel);

    }
    else {
        QMessageBox::critical(nullptr,QObject::tr("delete"),
                               QObject::tr("delete failed.\n"),QMessageBox::Cancel);

    }
}

void Emission::on_pushButton_10_clicked()
{
    int id = ui->id_up->text().toInt();
    QString titre = ui->titre_up->text();
    QString category = ui->category_up->currentText();
    QString realisateur = ui->realisateur_up->text();
   // QString langue = ui->langue->text();
    QString description = ui->description_up->toPlainText();
    QString duree = ui->duree_up->text();
    QString horraire = ui->horraire_up->text();
    QString date = ui->date_up->text();
    Entite_emission em (id, titre, category,realisateur,date,duree , description,horraire);
    bool test = em.modifier();
    if(test) {
       //  ui->tableView->setModel(em.afficher());
        ui->tableView->setModel(em.afficher());
        QMessageBox::information(nullptr,QObject::tr("insertion"),
                               QObject::tr("insertion avec success.\n"),QMessageBox::Cancel);

    }
    else {
        QMessageBox::critical(nullptr,QObject::tr("insertion"),
                               QObject::tr("insertion echoue.\n"),QMessageBox::Cancel);
    }
}
