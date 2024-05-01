#include "employee.h"
#include "ui_employee.h"

Employee::Employee(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Employee)
{
    ui->setupUi(this);
}

Employee::~Employee()
{
    delete ui;
}
