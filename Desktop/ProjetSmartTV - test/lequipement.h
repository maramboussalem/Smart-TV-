#ifndef LEQUIPEMENT_H
#define LEQUIPEMENT_H

#include <QDialog>

namespace Ui {
class lequipement;
}

class lequipement : public QDialog
{
    Q_OBJECT

public:
    explicit lequipement(QWidget *parent = nullptr);
    ~lequipement();

private:
    Ui::lequipement *ui;
};

#endif // LEQUIPEMENT_H
