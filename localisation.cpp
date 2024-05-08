#include "localisation.h"
#include "ui_localisation.h"

localisation::localisation(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::localisation)
{
    ui->setupUi(this);
}

localisation::~localisation()
{
    delete ui;
}
