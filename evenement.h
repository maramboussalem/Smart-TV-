#ifndef EVENEMENT_H
#define EVENEMENT_H
#include "entite_evenment.h"
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

private slots:
    void on_ajouter_button_clicked();

   void on_supprimer_button_clicked();

   void on_modifier_button_clicked();


   void on_Rechercher_button_clicked();

private:
    Ui::Evenement *ui;
    Entite_evenment ev;
};

#endif // EVENEMENT_H
