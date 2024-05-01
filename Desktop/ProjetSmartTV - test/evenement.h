#ifndef EVENEMENT_H
#define EVENEMENT_H

#include <QDialog>

namespace Ui {
class Evenement;
}

class Evenement : public QDialog
{
    Q_OBJECT

public:
    explicit Evenement(QWidget *parent = nullptr);
    ~Evenement();

private:
    Ui::Evenement *ui;
};

#endif // EVENEMENT_H
