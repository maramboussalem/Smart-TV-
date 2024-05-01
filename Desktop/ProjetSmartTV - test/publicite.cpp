#include "publicite.h"
#include "ui_publicite.h"

Publicite::Publicite(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Publicite)
{
    ui->setupUi(this);
}

Publicite::~Publicite()
{
    delete ui;
}
