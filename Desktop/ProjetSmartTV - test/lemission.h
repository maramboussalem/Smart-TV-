#ifndef LEMISSION_H
#define LEMISSION_H

#include <QDialog>

namespace Ui {
class lemission;
}

class lemission : public QDialog
{
    Q_OBJECT

public:
    explicit lemission(QWidget *parent = nullptr);
    ~lemission();

private:
    Ui::lemission *ui;
};

#endif // LEMISSION_H
