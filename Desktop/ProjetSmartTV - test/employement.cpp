#include "employement.h"
#include "ui_employement.h"

employement::employement(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::employement)
{
    ui->setupUi(this);
}

employement::~employement()
{
    delete ui;
}
