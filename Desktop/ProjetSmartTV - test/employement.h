#ifndef EMPLOYEMENT_H
#define EMPLOYEMENT_H
#include "employes.h"
#include <QDialog>
#include "smtp.h"
#include "arduino.h"
namespace Ui {
class employement;
}

class employement : public QDialog
{
    Q_OBJECT

public:
    explicit employement(QWidget *parent = nullptr);
    ~employement();

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

    void on_pushButton_Afficher_clicked();

    void on_pushButton_pasdaffichage_clicked();

     void update_label();// slot permettant la mise à jour du label état de la lampe 1,
     // ce slot est lancé à chaque réception d'un message de Arduino

private:
    Ui::employement *ui;
    employes etmp;
    Smtp *smtp;
    QByteArray data; // variable contenant les données reçues

    arduino a; // objet temporaire
};

#endif // EMPLOYEMENT_H
