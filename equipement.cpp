#include "equipement.h"
#include "ui_equipement.h"

Equipement::Equipement(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Equipement)
{
    ui->setupUi(this);
}

Equipement::~Equipement()
{
    delete ui;
}
