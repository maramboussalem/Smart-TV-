#include "login.h"
#include "ui_login.h"

LoginDialog::login(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::login)
{
    ui->setupUi(this);
}

LoginDialog::~Login()
{
    delete ui;
}

void LoginDialog::on_buttonBox_accepted()
{
    accept(); // Accepter la boîte de dialogue lorsque l'utilisateur appuie sur le bouton "OK"
}

void LoginDialog::on_buttonBox_rejected()
{
    reject(); // Rejeter la boîte de dialogue lorsque l'utilisateur appuie sur le bouton "Annuler"
}
