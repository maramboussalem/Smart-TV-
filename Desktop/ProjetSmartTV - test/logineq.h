#ifndef LOGINEQ_H
#define LOGINEQ_H

#include <QMainWindow>

namespace Ui {
class logineq;
}

class logineq : public QMainWindow
{
    Q_OBJECT

public:
    explicit logineq(QWidget *parent = nullptr);
    ~logineq();

private:
    Ui::logineq *ui;
};

#endif // LOGINEQ_H
