#include "menu.h"
#include "ui_menu.h"
#include "employes.h"
#include "emission.h"
#include "evenement.h"
#include "publicite.h"
#include "sponsors.h"
#include "equipement.h"
#include "lemission.h"
#include "lemployes.h"
#include "lequipement.h"
#include "levennement.h"
#include "lpublicite.h"
#include "lsponsore.h"
#include "employes.h"
#include <QApplication>
#include <QMessageBox>
#include <QtCharts>
#include <QPainter>
#include <QtNetwork/QDnsMailExchangeRecord>
#include <QtSql/QSqlQuery>
#include <QSqlDatabase>
#include "employee.h"
#include "employement.h"
Menu::Menu(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Menu)
{
    ui->setupUi(this);
}

Menu::~Menu()
{
    delete ui;

}
void Menu::on_pushButtonEmployee_clicked()
{
     lemployes  lemployeDialog;
     lemployeDialog.exec();

}

void Menu::on_pushButtonEmission_clicked()
{
    lemission lemissionsDialog;
        lemissionsDialog.exec();
}

void Menu::on_pushButtonEvenement_clicked()
{
    levennement levennementDialog;
        levennementDialog.exec();
}

void Menu::on_pushButtonPublicite_clicked()
{
    lpublicite lpubliciteDialog;
        lpubliciteDialog.exec();
}

void Menu::on_pushButtonSponsors_clicked()
{
    lsponsore lsponsoreDialog;
        lsponsoreDialog.exec();
}

void Menu::on_pushButtonEquipement_clicked()
{
    lequipement lequipementDialog;
        lequipementDialog.exec();
}
