#include "lsponsore.h"
#include "ui_lsponsore.h"

lsponsore::lsponsore(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::lsponsore)
{
    ui->setupUi(this);
}

lsponsore::~lsponsore()
{
    delete ui;
}
