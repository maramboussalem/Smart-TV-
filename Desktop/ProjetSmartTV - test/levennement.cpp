#include "levennement.h"
#include "ui_levennement.h"

levennement::levennement(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::levennement)
{
    ui->setupUi(this);
}

levennement::~levennement()
{
    delete ui;
}
