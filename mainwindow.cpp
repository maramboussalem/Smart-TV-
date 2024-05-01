#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "menu.h"
#include <QMessageBox>
#include "evenement1.h"
#include "map.h"
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_Connecter_clicked()
{
    Menu menuDialog;
    menuDialog.exec();

   // Map * mapEvent = new Map(this);
    //mapEvent->show();


   // Evenement1 *event = new Evenement1(this); // Create an instance
    //event->show(); // Show the instance
}
