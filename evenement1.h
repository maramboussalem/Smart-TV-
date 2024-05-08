#ifndef EVENEMENT_H
#define EVENEMENT_H
#include "entite_evenment.h"
#include <QDialog>
#include <map.h>
#include <QMainWindow>
#include <QVariant>
namespace Ui {
class Evenement1;
}

class Evenement1 : public QMainWindow
{
    Q_OBJECT

public:
    explicit Evenement1(QWidget *parent = nullptr);
    ~Evenement1();

private slots:
    void on_Location_clicked();

    void on_ajouter_button_clicked();

    void on_modifier_button_clicked();

    void on_supprimer_button_clicked();

    void on_Rechercher_button_clicked();

    void on_calendarWidget_clicked(const QDate &date);


//    void on_rechercher_button_affichage_clicked();
//    void on_pdf_button_clicked();
//    void on_Tri_categorie_currentTextChanged(const QString &arg1);

int countType(const QString &category);

    void on_pdf_button_clicked();

    void on_rechercher_button_affichage_clicked();

    void on_trier_button_clicked();

    void on_Tri_comboBox_currentTextChanged(const QString &arg1);

    void on_Statistique_button_clicked();

private:
    Ui::Evenement1 *ui;
    Entite_evenment ev;
   Map *mapEvent = nullptr;
//   Map *mapWidget;
signals:
    void setCenterPosition(QVariant,QVariant);
    void setLocationMarking(QVariant,QVariant);
};

#endif // EVENEMENT1_H
