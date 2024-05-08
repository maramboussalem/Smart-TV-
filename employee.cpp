#include "employee.h"
#include "ui_employee.h"
<<<<<<< HEAD
#include <QApplication>
#include <QMessageBox>
#include <QtCharts>
#include <QPainter>
#include <QtNetwork/QDnsMailExchangeRecord>
#include <QtSql/QSqlQuery>
#include <QSqlDatabase>
#include "entite_employee.h"
=======

>>>>>>> 18d955075ebf7e49d498a0f477c7a42083282ca3
Employee::Employee(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Employee)
{
    ui->setupUi(this);
<<<<<<< HEAD
    ui->tableView_2->setModel(etmp.afficher());
    smtp = new Smtp("eya.ketata@esprit.tn", "221JFT2454", "smtp.gmail.com", 465); // Initialisez Smtp avec vos informations
=======
>>>>>>> 18d955075ebf7e49d498a0f477c7a42083282ca3
}

Employee::~Employee()
{
    delete ui;
<<<<<<< HEAD
    delete smtp;
}
void Employee::on_pushButton_Modifier_clicked()
{
       int id_E = ui->lineEdit_IdE_M_2->text().toInt();
       QString nom = ui->lineEdit_nom_M_2->text();
       QString prenom = ui->lineEdit_prenom_M_2->text();
       QString email = ui->lineEdit_email_M_2->text();
       QDate date_naissance = ui->dateEdit_M_2->date();
       QString password = ui->lineEdit_tel_M_2->text();
       QString adresse = ui->lineEdit_adresse_M_2->text();


       entite_employee e(id_E, nom, prenom, email,date_naissance, password, adresse);
       bool test = e.modifier(id_E, nom, prenom, email, date_naissance, password, adresse);
       if (test)
       {
            ui->tableView_2->setModel(etmp.afficher());
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

void Employee::on_pushButton_Recherche_clicked()
{
    int id_E = ui->lineEdit_IdE_2->text().toInt();
       entite_employee etmp;
       etmp.Recherche(id_E);
}

void Employee::on_pushButton_Statistique_clicked()
{
    entite_employee etmp;
        etmp.Statistique();
}

void Employee::on_pushButton_Email_clicked()
{
    entite_employee etmp;
        QString email = ui->lineEdit_email_2->text();
        etmp.Email(email);
}

void Employee::on_pushButton_clicked()//ref
{
ui->tableView_2->setModel(etmp.afficher());

}

void Employee::on_pushButton_Ajouter_2_clicked()
{
    int id_E = ui->lineEdit_IdE_2->text().toInt();
    QString nom = ui->lineEdit_nom_2->text();
    QString prenom = ui->lineEdit_prenom_2->text();
    QString email = ui->lineEdit_email_2->text();
    QDate date_naissance = ui->dateEdit_2->date();
    QString password = ui->lineEdit_tele_2->text();
    QString adresse = ui->lineEdit_adresse_2->text();

    entite_employee e(id_E,nom,prenom,email,date_naissance,password,adresse);
    bool test = e.ajouter();
    if (test)
    {
        //ui->tableView_employes_2->setModel(etmp.afficher());
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

void Employee::on_pushButton_supprimer_clicked()
{
    int id_E = ui->lineEdit_IdE_2->text().toInt();
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

void Employee::on_pushButton_Recherche_M_2_clicked()
{
    QString adresse = ui->lineEdit_adresse_2->text();

            entite_employee e;
            QSqlQueryModel *model = e.rechercher_M(adresse);

            if (model->rowCount() == 0)
            {
                QMessageBox::information(this, "Aucune employes trouvée", "Aucune employes trouvée pour cette adresse.");
            }
            else
            {
                //ui->tableView_employes_2->setModel(model);
            }
}

void Employee::on_pushButton_Email_2_clicked()
{
    entite_employee etmp;
        QString email = ui->lineEdit_email_2->text();
        etmp.Email(email);
}

void Employee::on_pushButton_Email_Envoie_2_clicked()
{
    // Utilisez l'e-mail et le mot de passe fournis pour créer une instance de la classe Smtp
        Smtp* smtp = new Smtp("eya.ketata@esprit.tn", "221JFT2454", "smtp@esprit.tn", 587);

        QString email = ui->lineEdit_emaill_envoi_2->text(); // Adresse e-mail du destinataire
        QString body = "Bonjour."; // Corps de l'e-mail

        // Envoyez l'e-mail en utilisant l'instance smtp
        if (email.isEmpty()) {
            QMessageBox::warning(this, "Erreur", "Veuillez saisir une adresse e-mail.");
        } else {
            smtp->sendMail("eya.ketata@esprit.tn", email, "Sujet", body);
            QMessageBox::information(this, "Succès", "E-mail envoyé avec succès !");
        }
}

void Employee::on_pushButton_Trie_2_clicked()
{
    entite_employee etmp;
        etmp.trie();
}

void Employee::on_pushButton_Recherche_2_clicked()
{
    int id_E = ui->lineEdit_IdE_2->text().toInt();
       entite_employee etmp;
       etmp.Recherche(id_E);
}

void Employee::on_pushButton_Statistique_2_clicked()
{
    entite_employee etmp;
        etmp.Statistique();
}

void Employee::on_pushButton_supprimer_2_clicked()
{
    int id_E = ui->lineEdit_IdE_2->text().toInt();
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

void Employee::on_pushButton_2_clicked()
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

       entite_employee etmp;
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
=======
>>>>>>> 18d955075ebf7e49d498a0f477c7a42083282ca3
}
