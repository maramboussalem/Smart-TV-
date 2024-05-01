#include "lemployes.h"
#include "ui_lemployes.h"

lemployes::lemployes(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::lemployes)
{
    ui->setupUi(this);
}

lemployes::~lemployes()
{
    delete ui;
}
