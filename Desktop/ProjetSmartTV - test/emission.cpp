#include "emission.h"
#include "ui_emission.h"

Emission::Emission(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Emission)
{
    ui->setupUi(this);
}

Emission::~Emission()
{
    delete ui;
}
