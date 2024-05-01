#ifndef LEMPLOYES_H
#define LEMPLOYES_H

#include <QDialog>

namespace Ui {
class lemployes;
}

class lemployes : public QDialog
{
    Q_OBJECT

public:
    explicit lemployes(QWidget *parent = nullptr);
    ~lemployes();

private:
    Ui::lemployes *ui;
};

#endif // LEMPLOYES_H
