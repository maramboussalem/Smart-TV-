#include "employee.h"
#include "ui_employee.h"
#include "employes.h"
#include <QApplication>
#include <QMessageBox>
#include <QtCharts>
#include <QPainter>
#include <QtNetwork/QDnsMailExchangeRecord>
#include <QtSql/QSqlQuery>
#include <QSqlDatabase>
employee::employee(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::employee)
{
    ui->setupUi(this);
     ui->tableView->setModel(etmp.afficher());
     //ui->tableView->setModel(etmp.afficher());
     smtp = new Smtp("eya.ketata@esprit.tn", "221JFT2454", "smtp.gmail.com", 465); // Initialisez Smtp avec vos informations
}

employee::~employee()
{
    delete ui;
    delete smtp;
}

void employee::on_pushButton_Ajouter_clicked()
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

void employee::on_pushButton_Modifier_clicked()
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

void employee::on_pushButton_supprimer_clicked()
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

void employee::on_pushButton_Statistique_clicked()
{
    employes etmp;
        etmp.Statistique();
}

void employee::on_pushButton_Trie_clicked()
{
    employes etmp;
        etmp.trie();
}

void employee::on_pushButton_Recherche_clicked()
{
    int id_E = ui->lineEdit_IdE->text().toInt();
       employes etmp;
       etmp.Recherche(id_E);
}

void employee::on_pushButton_Email_clicked()
{
    employes etmp;
        QString email = ui->lineEdit_email->text();
        etmp.Email(email);
}

void employee::on_pushButton_Email_Envoie_clicked()
{
    // Utilisez l'e-mail et le mot de passe fournis pour créer une instance de la classe Smtp
        Smtp* smtp = new Smtp("eya.ketata@esprit.tn", "221JFT2454", "smtp@esprit.tn", 587);

        QString email = ui->lineEdit_email_envo->text(); // Adresse e-mail du destinataire
        QString body = "Bonjour."; // Corps de l'e-mail

        // Envoyez l'e-mail en utilisant l'instance smtp
        if (email.isEmpty()) {
            QMessageBox::warning(this, "Erreur", "Veuillez saisir une adresse e-mail.");
        } else {
            smtp->sendMail("eya.ketata@esprit.tn", email, "Sujet", body);
            QMessageBox::information(this, "Succès", "E-mail envoyé avec succès !");
        }
}

void employee::on_pushButton_PDF_clicked()
{
    QPdfWriter pdf("C:/Users/Mega-PC/Desktop/connectioneya/employes.pdf");
        QPainter painter(&pdf);

        // Styles
        QFont titleFont("Times New Roman", 30);
        QFont headerFont("Times New Roman", 8); // Augmenter la taille de la police pour les en-têtes
        QFont dataFont("Arial", 6); // Augmenter la taille de la police pour les données

        // Dessiner le titre
        painter.setFont(titleFont);
        painter.drawText(3000, 1400, "Liste des Employes");

        // Dessiner les bordures
        painter.setPen(Qt::black);

        // Dessiner les en-têtes de colonne
        QStringList headers = {"Id_E", "Nom", "Prénom", "Email", "Date de naissance", "Téléphone", "Adresse"};
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

       employes etmp;
        QSqlQueryModel *model = etmp.afficher(); // Récupérer le modèle de données
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

void employee::on_pushButton_Recherche_M_clicked()
{
    QString adresse = ui->lineEdit_adresse->text();

            employes e;
            QSqlQueryModel *model = e.rechercher_M(adresse);

            if (model->rowCount() == 0)
            {
                QMessageBox::information(this, "Aucune employes trouvée", "Aucune employes trouvée pour cette adresse.");
            }
            else
            {
                ui->tableView_employes->setModel(model);
            }
}
