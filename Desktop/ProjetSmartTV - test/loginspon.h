#ifndef LOGINSPON_H
#define LOGINSPON_H

#include <QMainWindow>

namespace Ui {
class loginspon;
}

class loginspon : public QMainWindow
{
    Q_OBJECT

public:
    explicit loginspon(QWidget *parent = nullptr);
    ~loginspon();

private:
    Ui::loginspon *ui;
};

#endif // LOGINSPON_H
