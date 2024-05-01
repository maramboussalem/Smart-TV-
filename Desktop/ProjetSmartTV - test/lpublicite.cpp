#include "lpublicite.h"
#include "ui_lpublicite.h"

lpublicite::lpublicite(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::lpublicite)
{
    ui->setupUi(this);
}

lpublicite::~lpublicite()
{
    delete ui;
}
