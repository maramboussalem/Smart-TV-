#ifndef EMPLOYEE_H
#define EMPLOYEE_H

#include <QMainWindow>
#include "employes.h"
#include "smtp.h"

namespace Ui {
class employee;
}

class employee : public QMainWindow
{
    Q_OBJECT

public:
    explicit employee(QWidget *parent = nullptr);
    ~employee();

private slots:
    void on_pushButton_Ajouter_clicked();

    void on_pushButton_Modifier_clicked();

    void on_pushButton_supprimer_clicked();

    void on_pushButton_Statistique_clicked();

    void on_pushButton_Trie_clicked();

    void on_pushButton_Recherche_clicked();

    void on_pushButton_Email_clicked();

    void on_pushButton_Email_Envoie_clicked();

    void on_pushButton_PDF_clicked();

    void on_pushButton_Recherche_M_clicked();

private:
    Ui::employee *ui;
    employes etmp;
    Smtp *smtp;
};

#endif // EMPLOYEE_H
