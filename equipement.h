#ifndef EQUIPEMENT_H
#define EQUIPEMENT_H
<<<<<<< HEAD
#include "entite_equipement.h"
#include <QDialog>

=======

#include <QDialog>
>>>>>>> 18d955075ebf7e49d498a0f477c7a42083282ca3

namespace Ui {
class Equipement;
}

class Equipement : public QDialog
{
    Q_OBJECT

public:
    explicit Equipement(QWidget *parent = nullptr);
    ~Equipement();

<<<<<<< HEAD

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
=======
private:
    Ui::Equipement *ui;
>>>>>>> 18d955075ebf7e49d498a0f477c7a42083282ca3
};

#endif // EQUIPEMENT_H
