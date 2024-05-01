#include "sponsors.h"
#include "ui_sponsors.h"

Sponsors::Sponsors(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Sponsors)
{
    ui->setupUi(this);
}

Sponsors::~Sponsors()
{
    delete ui;
}
