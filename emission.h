#ifndef EMISSION_H
#define EMISSION_H
#include "entite_emission.h"
#include <QDialog>
#include <QMainWindow>

#include <QtMultimediaWidgets>
#include <QtMultimedia>
#include <QtCore>
#include <QtGui>
#include <QFileDialog>
#include <QMediaPlayer>
#include <QVideoWidget>

#include <QString>
#include <QComboBox>
#include <QRadioButton>
#include <QPushButton>
#include <QVBoxLayout>
#include <QMessageBox>
#include "arduino.h"

namespace Ui {
class Emission;
}

class Emission : public QDialog
{
    Q_OBJECT
public:
    explicit Emission(QWidget *parent = nullptr);
    ~Emission();

private slots:

    void update_label();

    void on_pushButton_Ajouter_clicked();

    void on_pushButton_supprimer_clicked();

    void on_pushButtonsuptout_clicked();

    void on_pushButtonRechID_clicked();

    void on_pushButton_valider_clicked();

    void on_pushButton_AnnulerModifier_clicked();

    void on_pushButton_AnnulerAjouter_clicked();

    void on_pushButtonTri_clicked();

    void on_pushButtonPdf_clicked();

    void on_pushButtonstat_clicked();

    void on_comboBoxTri_activated(int index);

    void on_radioButtonCroissant_toggled(bool checked);

    void on_pushButtonValidier_recherche_clicked();

    void on_pushButtonCSV_clicked();

    void on_pushButtonregarder_clicked();

    void on_pushButtonImprimer_clicked();

    void on_pushButton_clicked();

    void on_pushButton_insertVideo_clicked();

    void on_pushButton_soustitrage_clicked();

    void on_pushButton_insertVideo_2_clicked();

    void on_pushButton_soustitrage_2_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::Emission *ui;
    Entite_emission  Etmp;

    QVBoxLayout *mainLayout;
    QComboBox *comboBoxTri;
    QRadioButton *radioButtonCroissant;
    QRadioButton *radioButtonDecroissant;
    QPushButton *pushButtonTri;
    float countType(QString);
    void setupUI();

    QByteArray data; // variable contenant les données reçues
    Arduino A; // objet temporaire
};

#endif // EMISSION_H
