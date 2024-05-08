#include "gestionemployee.h"
#include "ui_gestionemployee.h"

Gestionemployee::Gestionemployee(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Gestionemployee)
{
    ui->setupUi(this);
}

Gestionemployee::~Gestionemployee()
{
    delete ui;
}

void Gestionemployee::on_pushButtonEmployee_I_clicked()
{

}
