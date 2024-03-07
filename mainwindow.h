#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "equipements.h"
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
    void on_pushButton_ajouter_clicked();

    void on_pushButton_14_clicked();

    void on_pushButton_clicked();



    void on_pushButton_ajouter_2_clicked();

private:
    Ui::MainWindow *ui;
    equipements Etmp;
};

#endif // MAINWINDOW_H
