#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include "emissions.h"
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

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_Ajouter_clicked();

    void on_pushButton_supprimer_clicked();

    void on_pushButton_Modifier_clicked();

    void on_pushButtonRecherche_clicked();

    void on_pushButtonRech_clicked();

    void on_pushButtonsuptout_clicked();

    void on_pushButton_rechercher_Id_clicked();

    void on_pushButtonRechID_clicked();

    void on_pushButton_valider_clicked();

    void on_pushButton_regarder_clicked();

    void on_pushButton_QuitterAjouter_clicked();

    void on_pushButton_QuitterModifier_clicked();

    void on_pushButtonRef_clicked();

    void on_pushButtonTri_clicked();

    void on_pushButtonPdf_clicked();

    void on_pushButtonExcel_clicked();

    void on_pushButtonstat_clicked();

    void on_pushButton_rechCat_clicked();

    void on_comboBoxTri_activated(int index);

    void on_radioButtonC_toggled(bool checked);

    void on_pushButtonValidier_recherche_clicked();

    void on_pushButtonTelecharger_clicked();

    void on_pushButtonImprimer_clicked();

    void on_pushButtoneee_clicked();

private:
    Ui::MainWindow *ui;
    Emissions Etmp;

        QVBoxLayout *mainLayout;
        QComboBox *comboBoxTri;
        QRadioButton *radioButtonCroissant;
        QRadioButton *radioButtonDecroissant;
        QPushButton *pushButtonTri;

        void setupUI();
};

#endif // MAINWINDOW_H
