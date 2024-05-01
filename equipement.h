#ifndef EQUIPEMENT_H
#define EQUIPEMENT_H
#include "entite_evenment.h"
#include <QDialog>
#include <map.h>
#include <QDialog>

namespace Ui {
class Equipement;
}

class Equipement : public QDialog
{
    Q_OBJECT

public:
    explicit Equipement(QWidget *parent = nullptr);
    ~Equipement();

private:
    Ui::Equipement *ui;
};

#endif // EQUIPEMENT_H
