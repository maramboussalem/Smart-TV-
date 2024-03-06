#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "employes.h"
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

    //void on_pushButtonRecherche_clicked();

private:
    Ui::MainWindow *ui;

    employes etmp;
};

#endif // MAINWINDOW_H
