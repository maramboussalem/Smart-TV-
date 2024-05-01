#include "lemission.h"
#include "ui_lemission.h"

lemission::lemission(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::lemission)
{
    ui->setupUi(this);
}

lemission::~lemission()
{
    delete ui;
}
