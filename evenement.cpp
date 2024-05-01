#include "evenement.h"
#include "ui_evenement.h"
#include <QMessageBox>
#include <entite_evenment.h>
//Entite_evenment::Entite_evenment(){}
Evenement::Evenement(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Evenement)
{
    ui->setupUi(this);
    ui->tableView->setModel(ev.afficher());
    ui->titre_modif->setEnabled(false);
    ui->date_modif->setEnabled(false);
    ui->description_modif->setEnabled(false);
    ui->category_modif->setEnabled(false);
}

Evenement::~Evenement()
{
    delete ui;
}
// ajouter
void Evenement::on_ajouter_button_clicked()
{
    int id = ui->id->text().toInt();
    QString titre = ui->titre->text();
    QString category = ui->category->text();
    QString description = ui->description->toPlainText();
    QDateTime date = ui->date->dateTime();
    Entite_evenment ev (id, titre, category,date, description);
    bool test = ev.ajouter();
    if(test) {
        ui->id->clear();
        ui->titre->clear();
        ui->description->clear();
        ui->category->clear();
        ui->date->clear();
        ui->tableView->setModel(ev.afficher());
        QMessageBox::information(nullptr,QObject::tr("insertion"),
                               QObject::tr("insertion avec success.\n"),QMessageBox::Cancel);


    }
    else {
        QMessageBox::critical(nullptr,QObject::tr("insertion"),
                               QObject::tr("insertion echoue.\n"),QMessageBox::Cancel);
    }
}
// supprimer
void Evenement::on_supprimer_button_clicked()
{
    int id = ui->id_supprime->text().toInt();
       Entite_evenment ev;  // Declare the object
       ev = ev.rechercher(id);
        if (ev.getId()==-1){
            QMessageBox::critical(nullptr,QObject::tr("delete"),
                                   QObject::tr("delete failed : you must use a an exist id.\n"),QMessageBox::Cancel);
        }
        else {
              bool test = ev.supprimer(id);

                if(test) {
                     ui->tableView->setModel(ev.afficher());
                    QMessageBox::information(nullptr,QObject::tr("suppression"),
                                       QObject::tr("delete succesful.\n"),QMessageBox::Cancel);
                         }
                else {
                        QMessageBox::critical(nullptr,QObject::tr("delete"),
                                       QObject::tr("delete failed.\n"),QMessageBox::Cancel);
                }
        }

}
 //modifier
void Evenement::on_modifier_button_clicked()
{
    int id = ui->id_modif->text().toInt();
    QString titre = ui->titre_modif->text();
    QString category = ui->category_modif->text();
    QDateTime date = ui->date_modif->dateTime();
    QString description = ui->description_modif->toPlainText();
    Entite_evenment em (id, titre, category,date,description);
    bool test = em.modifier();
    if(test) {
        ui->tableView->setModel(ev.afficher());
        QMessageBox::information(nullptr,QObject::tr("insertion"),
                               QObject::tr("modification avec success.\n"),QMessageBox::Cancel);

    }
    else {
        QMessageBox::critical(nullptr,QObject::tr("insertion"),
                               QObject::tr("modification echoue.\n"),QMessageBox::Cancel);
    }
}

void Evenement::on_Rechercher_button_clicked()
{
    int id = ui->id_modif->text().toInt();
    Entite_evenment ev ;
    ev = ev.rechercher(id);
    if(ev.getId()==-1)
    {
        // handle error
        QMessageBox::critical(nullptr,QObject::tr("Error"),
                               QObject::tr("Vous devez inserer un id existant.\n"),QMessageBox::Cancel);
    }
    else {
        // i will enable the inputs
        ui->titre_modif->setEnabled(true);
        ui->date_modif->setEnabled(true);
        ui->description_modif->setEnabled(true);
        ui->category_modif->setEnabled(true);
        // update the inputs with the data getted from the database
        ui->id_modif->setEnabled(false);
        ui->titre_modif->setText(ev.getTitre());
        ui->date_modif->setDateTime(ev.getDate());
        ui->description_modif->setText(ev.getDescription());
        ui->category_modif->setText(ev.getCategory());

    }

}
