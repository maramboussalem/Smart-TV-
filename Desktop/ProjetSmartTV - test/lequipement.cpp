#include "lequipement.h"
#include "ui_lequipement.h"
#include <QMainWindow>
#include <QMessageBox>
#include <QMap>
lequipement::lequipement(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::lequipement)
{
    ui->setupUi(this);
}

lequipement::~lequipement()
{
    delete ui;
}

void lequipement::on_Connecter_clicked()
{
    // Obtenir l'adresse e-mail saisie et le mot de passe correspondant
        QString email = ui->lineEdit_email->text();
        QString password = ui->lineEdit_motdepasse->text();

        // Créer une structure de données pour stocker les adresses e-mail et les mots de passe correspondants
        QMap<QString, QString> emailPasswords;
        emailPasswords.insert("employes@gmail.com", "eya123");
        emailPasswords.insert("equippement@gmail.com", "yessmine123");
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

void lequipement::on_Retour_clicked()
{
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Qt With Katern", "Êtes-vous sûr de vouloir fermer l'application ?", QMessageBox::Yes | QMessageBox::No);
    if (reply == QMessageBox::Yes)
    {
        QApplication::quit();
    }
}
