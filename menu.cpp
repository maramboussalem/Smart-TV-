#include "menu.h"
#include "ui_menu.h"
<<<<<<< HEAD
#include "employee.h"
#include "emissions.h"
#include "evenement1.h"
=======

#include "employee.h"
#include "emission.h"
#include "evenement.h"
>>>>>>> 18d955075ebf7e49d498a0f477c7a42083282ca3
#include "publicite.h"
#include "sponsors.h"
#include "equipement.h"

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
Employee employeeDialog;
employeeDialog.exec();
}

void Menu::on_pushButtonEmission_clicked()
{
<<<<<<< HEAD

Emissions *em = new Emissions(this); // Create an instance
em->show(); // Show the instance
=======
Emission emissionDialog;
emissionDialog.exec();
>>>>>>> 18d955075ebf7e49d498a0f477c7a42083282ca3
}

void Menu::on_pushButtonEvenement_clicked()
{
<<<<<<< HEAD
   Evenement1 *event = new Evenement1(this); // Create an instance
   event->show(); // Show the instance
=======
Evenement evenementDialog;
evenementDialog.exec();
>>>>>>> 18d955075ebf7e49d498a0f477c7a42083282ca3
}

void Menu::on_pushButtonPublicite_clicked()
{
 Publicite publiciteDialog;
 publiciteDialog.exec();
}

void Menu::on_pushButtonSponsors_clicked()
{
Sponsors sponsorsDialog;
sponsorsDialog.exec();
}

void Menu::on_pushButtonEquipement_clicked()
{
Equipement equipementDialog;
equipementDialog.exec();
}
