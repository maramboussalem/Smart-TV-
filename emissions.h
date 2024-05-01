#ifndef EMISSIONS_H
#define EMISSIONS_H

#include <QMainWindow>

#include "entite_emission.h"
#include "arduino.h"

#include <QDialog>
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
#include <QtWidgets>

namespace Ui {
class Emissions;
}

class Emissions : public QMainWindow
{
    Q_OBJECT

public:
    explicit Emissions(QWidget *parent = nullptr);
    ~Emissions();
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


    void durationChanged(qint64 duration);

    void positionChanged(qint64 duration);

    void on_actionOpen_triggered();

    void on_pushButton_Seek_Backward_clicked();

    void on_pushButton_Play_Pause_clicked();

    void on_pushButton_Stop_clicked();

    void on_pushButton_Seek_Forward_clicked();

    void on_pushButtonSousTitrage_clicked();

    void on_pushButton_Volume_clicked();

    void on_horizontalSlider_Duration_valueChanged(int value);

    void on_horizontalSlider_Volume_valueChanged(int value);

    void on_pushButton_3_clicked();

private:
    Ui::Emissions *ui;
    Entite_emission  Etmp;
    QString mVideoFilePath;

    QVBoxLayout *mainLayout;
    QComboBox *comboBoxTri;
    QRadioButton *radioButtonCroissant;
    QRadioButton *radioButtonDecroissant;
    QPushButton *pushButtonTri;
    float countType(QString);
    void setupUI();

    QMediaPlayer *Player;
    QVideoWidget *Video;
    qint64 mDuration;
    bool IS_Pause = true;
    bool IS_Muted = false;
    bool subtitlesEnabled = false;
    void updateDuration(qint64 Duration);

    QByteArray data; // variable contenant les données reçues
    Arduino A; // objet temporaire
};

#endif // EMISSIONS_H


