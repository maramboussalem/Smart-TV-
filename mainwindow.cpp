#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "equipements.h"
#include <QApplication>
#include <QMessageBox>
#include <QLineEdit>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->tableViewafficherEquipement->setModel(Etmp.afficher());
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_ajouter_clicked()
{
    int id_equipement = ui->lineEdit_idequipement->text().toInt();
    QString reference = ui->lineEdit_ref->text();
    QString type = ui->lineEdit_type->text();
    QString quantite = ui->lineEdit_quant->text();
    QString prix = ui->lineEdit_prix->text();

    equipements E(id_equipement,reference,type,quantite,prix);
    bool test = E.ajouter();

    if (test)
    {
        // Mettre à jour l'affichage après l'ajout
        ui->tableViewafficherEquipement->setModel(Etmp.afficher());

        QMessageBox::information(nullptr, QObject::tr("OK"),
                                QObject::tr("Ajout effectué\n"
                                            "Click Cancel to exit."), QMessageBox::Cancel);
    }
    else
    {
        QMessageBox::critical(nullptr, QObject::tr("NOT OK"),
                              QObject::tr("Ajout non effectué\n"
                                          "Click Cancel to exit."), QMessageBox::Cancel);
    }
}

void MainWindow::on_pushButton_14_clicked()
{
    int id_equipement=ui->lineEdit_idequipement->text().toInt();
        bool test=Etmp.supprimer(id_equipement);
        if(test)
        {
            ui->tableViewafficherEquipement->setModel(Etmp.afficher());

            QMessageBox::information(nullptr, QObject::tr("OK"),
                        QObject::tr("Suppression effectuée\n"
                                    "Click Cancel to exit."), QMessageBox::Cancel);

        }
        else
            QMessageBox::critical(nullptr, QObject::tr("NOT OK"),
                        QObject::tr("Suppression non effectué\n"
                                    "Click Cancel to exit."), QMessageBox::Cancel);

}



void MainWindow::on_pushButton_ajouter_2_clicked()
{
    int id_equipement =ui->lineEdit_7->text().toInt();
    QString reference =ui->lineEdit_9->text();
      QString quantite =ui->lineEdit_8->text();
    QString type = ui->lineEdit_10->text();

    QString prix = ui->lineEdit_5->text();
   equipements equipemntsObject;

    // Passer les valeurs nécessaires à la fonction modifier
    bool test = equipemntsObject.modifier(id_equipement , reference, type, quantite,prix);

    if (test)
    {
        // Refresh the model
        ui->tableViewafficherEquipement->setModel(equipemntsObject.afficher());  // Utilisez directement afficher() ici

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

void MainWindow::on_pushButton_clicked()
{
    // Récupérer l'ID depuis le champ lineEdit_7
    int id_equipement = ui->lineEdit_7->text().toInt();

    // Créer une instance de la classe equipements
    equipements equipemntsObject;

    // Utiliser la fonction rechercherEquipement pour obtenir les détails de l'équipement
    equipements e = equipemntsObject.rechercherEquipement(id_equipement);

    // Mettre à jour les champs de l'interface graphique avec les détails de l'équipement trouvé
    ui->lineEdit_9->setText(e.getRefrence()); // Correction here
    ui->lineEdit_8->setText(e.getType()); // Correction here
    ui->lineEdit_10->setText(e.getQuantite());
    ui->lineEdit_5->setText(e.getPrix()); // Correction here

    // Mettre à jour le tableau affichant les équipements
    ui->tableViewafficherEquipement->setModel(equipemntsObject.afficher());
}
