#ifndef LSPONSORE_H
#define LSPONSORE_H

#include <QDialog>

namespace Ui {
class lsponsore;
}

class lsponsore : public QDialog
{
    Q_OBJECT

public:
    explicit lsponsore(QWidget *parent = nullptr);
    ~lsponsore();

private:
    Ui::lsponsore *ui;
};

#endif // LSPONSORE_H
