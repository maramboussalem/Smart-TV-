#include "lequipement.h"
#include "ui_lequipement.h"

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
