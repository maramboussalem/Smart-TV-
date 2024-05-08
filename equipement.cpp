#include "equipement.h"
#include "ui_equipement.h"
#include <QApplication>
#include <QMessageBox>
#include <QLineEdit>
#include <QPdfWriter>
#include <QPainter>
#include <QFile>
#include <QFileDialog>
#include "entite_equipement.h"
Equipement::Equipement(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Equipement)
{
    ui->setupUi(this);
       ui->tableViewafficherEquipement->setModel(Etmp.afficher());
}

Equipement::~Equipement()
{
    delete ui;
}
void Equipement::on_pushButton_ajouter_clicked()
{
    int id_equipement = ui->lineEdit_idequipement->text().toInt();
    QString type = ui->lineEdit_type->text();
    QString quantite = ui->lineEdit_quant->text();
    QString prix = ui->lineEdit_prix->text();
    QString image = ui->image->text();
    entite_equipement E(id_equipement,type,quantite,prix,image);
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

void Equipement::on_pushButton_14_clicked()
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



void Equipement::on_pushButton_ajouter_2_clicked()
{
    int id_equipement =ui->lineEdit_7->text().toInt();
    QString quantite =ui->lineEdit_8->text();
    QString type = ui->lineEdit_10->text();
    QString prix = ui->lineEdit_5->text();
    QString image = ui->image->text();
   entite_equipement equipemntsObject;

    // Passer les valeurs nécessaires à la fonction modifier
    bool test = equipemntsObject.modifier(id_equipement, type, quantite, prix,image);

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
void Equipement::on_pushButton_actu_clicked()
{
    entite_equipement e;
    ui->tableViewafficherEquipement->setModel(e.afficher());
}

void Equipement::on_pushButton_clicked()
{
    entite_equipement equipemntsObject;
    QString type=ui->search->text();
    ui->tableViewafficherEquipement->setModel(equipemntsObject.rechercherPartype(type));
}

void Equipement::on_tric_clicked()
{
    entite_equipement E;
    QSqlQueryModel *model = E.trierParPrix();
    ui->tableViewafficherEquipement->setModel(model);

}

void Equipement::on_tric_2_clicked()
{
    entite_equipement E;
    QSqlQueryModel *model = E.trierParPrixd();
    ui->tableViewafficherEquipement->setModel(model);
}

void Equipement::on_tric_3_clicked()
{
    QPdfWriter pdf("C:/Users/user/Desktop/Smart-TV-equipement (2)/Smart-TV-equipement/equipement.pdf");
            QPainter painter(&pdf);

            // Styles
            QFont titleFont("Times New Roman", 30);
            QFont headerFont("Times New Roman", 8); // Augmenter la taille de la police pour les en-têtes
            QFont dataFont("Arial", 6); // Augmenter la taille de la police pour les données

            // Dessiner le titre
            painter.setFont(titleFont);
            painter.drawText(3000, 1400, "Liste des Equipements");

            // Dessiner les bordures
            painter.setPen(Qt::black);

            // Dessiner les en-têtes de colonne
            QStringList headers = {"id_equipement", "reference", "type", "quantite","prix"};
            painter.setFont(headerFont);
            int x = 300; // Position horizontale initiale
            int y = 3300; // Position verticale
            int columnWidth = 1300; // Largeur de chaque colonne

            for (int col = 0; col < headers.size(); ++col)
            {
                // Dessiner le rectangle autour de l'en-tête
                painter.drawRect(x, y, columnWidth, 150); // Augmenter la hauteur de l'en-tête

                // Dessiner le texte centré dans la colonne
                painter.drawText(x, y, columnWidth, 150, Qt::AlignCenter, headers[col]);

                // Déplacer la position horizontale pour la prochaine colonne
                x += columnWidth;
            }

            // Dessiner les données de la table
            painter.setFont(dataFont);
            x = 300; // Réinitialiser la position horizontale
            y = 3450; // Définir la position verticale pour les données

            entite_equipement Etmp;
            QSqlQueryModel *model = Etmp.afficher(); // Récupérer le modèle de données
            for (int row = 0; row < model->rowCount(); ++row)
            {
                x = 300; // Réinitialiser la position horizontale pour chaque ligne
                for (int col = 0; col < model->columnCount(); ++col)
                {
                    // Dessiner le rectangle autour de la cellule
                    painter.drawRect(x, y, columnWidth, 300); // Augmenter la hauteur de la cellule

                    // Récupérer les données de la cellule
                    QModelIndex index = model->index(row, col);
                    QString data = model->data(index).toString();

                    // Dessiner le texte centré dans la cellule
                    painter.drawText(x, y, columnWidth, 150, Qt::AlignCenter, data);

                    // Déplacer la position horizontale pour la prochaine cellule
                    x += columnWidth;
                }
                // Déplacer la position verticale pour la prochaine ligne
                y += 150; // Augmenter l'espacement entre les lignes
            }

            QMessageBox::information(this, tr("PDF Enregistré!"), tr("PDF Enregistré!.\n" "Click Ok to exit."), QMessageBox::Ok);
}

void Equipement::on_stat_clicked()
{
    entite_equipement Etmp;
    Etmp.statistiquesParQuantite();
}


void Equipement::on_SelectImage_clicked()
{
    QString filePath = QFileDialog::getOpenFileName(this, tr("Select Image File"), QDir::homePath(), tr("Images (*.jpg *.png *.jpeg)"));

            if (!filePath.isEmpty())
            {
                ui->image->setText(filePath);
            }
}

void Equipement::on_selectimage_clicked()
{
    QString filePath = QFileDialog::getOpenFileName(this, tr("Select Image File"), QDir::homePath(), tr("Images (*.jpg *.png *.jpeg)"));

            if (!filePath.isEmpty())
            {
                ui->image->setText(filePath);
            }
}

void Equipement::on_pushButton_3_clicked()
{

}
