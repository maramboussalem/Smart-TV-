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

private:
    Ui::MainWindow *ui;
    Emissions Etmp;
};

#endif // MAINWINDOW_H
