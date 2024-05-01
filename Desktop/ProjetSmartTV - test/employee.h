#ifndef EMPLOYEE_H
#define EMPLOYEE_H

#include <QMainWindow>

namespace Ui {
class employee;
}

class employee : public QMainWindow
{
    Q_OBJECT

public:
    explicit employee(QWidget *parent = nullptr);
    ~employee();

private:
    Ui::employee *ui;
};

#endif // EMPLOYEE_H
