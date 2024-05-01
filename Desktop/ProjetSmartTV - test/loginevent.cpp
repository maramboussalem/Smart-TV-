#include "loginevent.h"
#include "ui_loginevent.h"
#include <QMainWindow>
#include <QMessageBox>
#include <QMap>
loginevent::loginevent(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::loginevent)
{
    ui->setupUi(this);
}

loginevent::~loginevent()
{
    delete ui;
}

void loginevent::on_Connecter_clicked()
{
    // Obtenir l'adresse e-mail saisie et le mot de passe correspondant
        QString email = ui->lineEdit_email->text();
        QString password = ui->lineEdit_motdepasse->text();

        // Créer une structure de données pour stocker les adresses e-mail et les mots de passe correspondants
        QMap<QString, QString> emailPasswords;
        emailPasswords.insert("employes@gmail.com", "eya123");
        emailPasswords.insert("evennnement@gmail.com", "Ala123");
        // Vérifier si l'adresse e-mail saisie est dans la liste des adresses valides
        if (emailPasswords.contains(email)) {
            // Vérifier si le mot de passe est correct pour cette adresse e-mail
            if (emailPasswords[email] == password) {
                // Si le mot de passe est correct, fermer la boîte de dialogue
                close();
            } else {
                QMessageBox::warning(this, "Erreur", "Mot de passe incorrect.");
            }
        } else {
            QMessageBox::warning(this, "Erreur", "Adresse e-mail non valide.");
        }
}

void loginevent::on_Retour_clicked()
{
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Qt With Katern", "Êtes-vous sûr de vouloir fermer l'application ?", QMessageBox::Yes | QMessageBox::No);
    if (reply == QMessageBox::Yes)
    {
        QApplication::quit();
    }
}
