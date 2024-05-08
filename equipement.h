#ifndef EQUIPEMENT_H
#define EQUIPEMENT_H
#include "entite_equipement.h"
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


private slots:
    void on_pushButton_ajouter_clicked();

    void on_pushButton_14_clicked();

    void on_pushButton_clicked();



    void on_pushButton_ajouter_2_clicked();

    void on_pushButton_actu_clicked();

    void on_tric_clicked();

    void on_tric_2_clicked();

    void on_tric_3_clicked();

    void on_stat_clicked();


    void on_SelectImage_clicked();

    void on_selectimage_clicked();

    void on_pushButton_3_clicked();

private:
    Ui::Equipement *ui;
    entite_equipement Etmp;
};

#endif // EQUIPEMENT_H
