#ifndef EMPLOYEE_H
#define EMPLOYEE_H

#include <QDialog>
<<<<<<< HEAD
#include <QMainWindow>
#include "entite_employee.h"
#include "smtp.h"
=======

>>>>>>> 18d955075ebf7e49d498a0f477c7a42083282ca3
namespace Ui {
class Employee;
}

class Employee : public QDialog
{
    Q_OBJECT

public:
    explicit Employee(QWidget *parent = nullptr);
    ~Employee();

<<<<<<< HEAD
private slots:
    void on_pushButton_Ajouter_clicked();

    void on_pushButton_supprimer_clicked();

    void on_pushButton_Modifier_clicked();

    void on_pushButton_Recherche_clicked();

    void on_pushButton_Trie_clicked();

    void on_pushButton_Statistique_clicked();

    void on_pushButton_Email_clicked();

    void on_pushButton_PDF_clicked();

    void on_pushButton_Recherche_M_clicked();

    void on_pushButton_Email_Envoie_clicked();

    void on_pushButton_clicked();

    void on_pushButton_Ajouter_2_clicked();

    void on_pushButton_Recherche_M_2_clicked();

    void on_pushButton_Email_2_clicked();

    void on_pushButton_Email_Envoie_2_clicked();

    void on_pushButton_Trie_2_clicked();

    void on_pushButton_Recherche_2_clicked();

    void on_pushButton_Statistique_2_clicked();

    void on_pushButton_supprimer_2_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::Employee *ui;
    Smtp *smtp;
    entite_employee etmp;
=======
private:
    Ui::Employee *ui;
>>>>>>> 18d955075ebf7e49d498a0f477c7a42083282ca3
};

#endif // EMPLOYEE_H
