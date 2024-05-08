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

<<<<<<< HEAD
=======
   void on_rechercher_button_affichage_clicked();

   void on_pdf_button_clicked();

  // void on_comboBox_3_currentTextChanged(const QString &arg1);

   void on_Tri_categorie_currentTextChanged(const QString &arg1);

   void on_calendarWidget_clicked(const QDate &date);

   void on_localisation_button_clicked();

>>>>>>> 18d955075ebf7e49d498a0f477c7a42083282ca3
private:
    Ui::Evenement *ui;
    Entite_evenment ev;
};

#endif // EVENEMENT_H
