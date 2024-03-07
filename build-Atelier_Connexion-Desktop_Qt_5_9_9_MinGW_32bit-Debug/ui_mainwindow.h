/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.9.9
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QScrollBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTableView>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QTabWidget *tabWidget;
    QWidget *tab_2;
    QScrollBar *verticalScrollBar;
    QLabel *label_15;
    QTableView *tableViewafficherEquipement;
    QLineEdit *pushButton_2;
    QPushButton *pushButton;
    QWidget *tab;
    QLineEdit *lineEdit_quant;
    QLineEdit *lineEdit_prix;
    QLabel *label_4;
    QLabel *label_6;
    QLabel *label_7;
    QLabel *label_9;
    QLineEdit *lineEdit_ref;
    QLineEdit *lineEdit_idequipement;
    QPushButton *pushButton_8;
    QPushButton *pushButton_ajouter;
    QLabel *label_11;
    QLineEdit *lineEdit_type;
    QWidget *tab_3;
    QPushButton *pushButton_11;
    QLineEdit *lineEdit_7;
    QLineEdit *lineEdit_9;
    QLabel *label_8;
    QLineEdit *lineEdit_5;
    QLineEdit *lineEdit_10;
    QLineEdit *lineEdit_8;
    QLabel *label_10;
    QLabel *label_12;
    QLabel *label_13;
    QLabel *label_5;
    QPushButton *pushButton_ajouter_2;
    QWidget *tab_4;
    QLabel *label_39;
    QLineEdit *lineEdit_14;
    QPushButton *pushButton_14;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(923, 698);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        tabWidget = new QTabWidget(centralWidget);
        tabWidget->setObjectName(QStringLiteral("tabWidget"));
        tabWidget->setGeometry(QRect(0, 10, 861, 601));
        tabWidget->setStyleSheet(QLatin1String("background-color: rgb(227, 227, 227);\n"
"font: 9pt \"Sitka\";"));
        tab_2 = new QWidget();
        tab_2->setObjectName(QStringLiteral("tab_2"));
        verticalScrollBar = new QScrollBar(tab_2);
        verticalScrollBar->setObjectName(QStringLiteral("verticalScrollBar"));
        verticalScrollBar->setGeometry(QRect(890, 90, 20, 441));
        verticalScrollBar->setOrientation(Qt::Vertical);
        label_15 = new QLabel(tab_2);
        label_15->setObjectName(QStringLiteral("label_15"));
        label_15->setGeometry(QRect(770, 30, 41, 31));
        label_15->setStyleSheet(QStringLiteral("image: url(:/new/prefix1/Tri.png);"));
        tableViewafficherEquipement = new QTableView(tab_2);
        tableViewafficherEquipement->setObjectName(QStringLiteral("tableViewafficherEquipement"));
        tableViewafficherEquipement->setGeometry(QRect(140, 180, 621, 331));
        pushButton_2 = new QLineEdit(tab_2);
        pushButton_2->setObjectName(QStringLiteral("pushButton_2"));
        pushButton_2->setGeometry(QRect(300, 80, 191, 41));
        pushButton_2->setStyleSheet(QStringLiteral("background-color: rgb(255, 255, 255);"));
        pushButton = new QPushButton(tab_2);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setGeometry(QRect(510, 80, 71, 41));
        tabWidget->addTab(tab_2, QString());
        tab = new QWidget();
        tab->setObjectName(QStringLiteral("tab"));
        lineEdit_quant = new QLineEdit(tab);
        lineEdit_quant->setObjectName(QStringLiteral("lineEdit_quant"));
        lineEdit_quant->setGeometry(QRect(410, 260, 161, 20));
        lineEdit_quant->setStyleSheet(QStringLiteral("background-color: rgb(255, 255, 255);"));
        lineEdit_prix = new QLineEdit(tab);
        lineEdit_prix->setObjectName(QStringLiteral("lineEdit_prix"));
        lineEdit_prix->setGeometry(QRect(410, 340, 161, 20));
        lineEdit_prix->setStyleSheet(QStringLiteral("background-color: rgb(255, 255, 255);"));
        label_4 = new QLabel(tab);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setGeometry(QRect(270, 180, 121, 16));
        label_4->setStyleSheet(QStringLiteral("background-color: rgb(227, 227, 227);"));
        label_6 = new QLabel(tab);
        label_6->setObjectName(QStringLiteral("label_6"));
        label_6->setGeometry(QRect(270, 220, 81, 16));
        label_7 = new QLabel(tab);
        label_7->setObjectName(QStringLiteral("label_7"));
        label_7->setGeometry(QRect(270, 340, 91, 16));
        label_9 = new QLabel(tab);
        label_9->setObjectName(QStringLiteral("label_9"));
        label_9->setGeometry(QRect(270, 300, 101, 20));
        lineEdit_ref = new QLineEdit(tab);
        lineEdit_ref->setObjectName(QStringLiteral("lineEdit_ref"));
        lineEdit_ref->setGeometry(QRect(410, 220, 161, 20));
        lineEdit_ref->setStyleSheet(QStringLiteral("background-color: rgb(255, 255, 255);"));
        lineEdit_idequipement = new QLineEdit(tab);
        lineEdit_idequipement->setObjectName(QStringLiteral("lineEdit_idequipement"));
        lineEdit_idequipement->setGeometry(QRect(410, 180, 161, 20));
        lineEdit_idequipement->setStyleSheet(QStringLiteral("background-color: rgb(255, 255, 255);"));
        pushButton_8 = new QPushButton(tab);
        pushButton_8->setObjectName(QStringLiteral("pushButton_8"));
        pushButton_8->setGeometry(QRect(450, 410, 111, 31));
        pushButton_8->setStyleSheet(QLatin1String("background-color: rgb(170, 0, 0);\n"
"border :1px solid rgb(255, 255, 255);\n"
"border-radius :10px;\n"
"color: #FFF;\n"
"padding-left: 20px;\n"
"padding-right:20px;\n"
""));
        pushButton_ajouter = new QPushButton(tab);
        pushButton_ajouter->setObjectName(QStringLiteral("pushButton_ajouter"));
        pushButton_ajouter->setGeometry(QRect(320, 410, 111, 31));
        pushButton_ajouter->setStyleSheet(QLatin1String("background-color: rgb(170, 0, 0);\n"
"border :1px solid rgb(255, 255, 255);\n"
"border-radius :10px;\n"
"color: #FFF;\n"
"padding-left: 20px;\n"
"padding-right:20px;\n"
""));
        label_11 = new QLabel(tab);
        label_11->setObjectName(QStringLiteral("label_11"));
        label_11->setGeometry(QRect(270, 260, 101, 16));
        lineEdit_type = new QLineEdit(tab);
        lineEdit_type->setObjectName(QStringLiteral("lineEdit_type"));
        lineEdit_type->setGeometry(QRect(410, 300, 161, 20));
        lineEdit_type->setStyleSheet(QStringLiteral("background-color: rgb(255, 255, 255);"));
        tabWidget->addTab(tab, QString());
        tab_3 = new QWidget();
        tab_3->setObjectName(QStringLiteral("tab_3"));
        pushButton_11 = new QPushButton(tab_3);
        pushButton_11->setObjectName(QStringLiteral("pushButton_11"));
        pushButton_11->setGeometry(QRect(450, 420, 111, 31));
        pushButton_11->setStyleSheet(QLatin1String("background-color: rgb(170, 0, 0);\n"
"border :1px solid rgb(255, 255, 255);\n"
"border-radius :10px;\n"
"color: #FFF;\n"
"padding-left: 20px;\n"
"padding-right:20px;\n"
""));
        lineEdit_7 = new QLineEdit(tab_3);
        lineEdit_7->setObjectName(QStringLiteral("lineEdit_7"));
        lineEdit_7->setGeometry(QRect(420, 180, 161, 20));
        lineEdit_7->setStyleSheet(QStringLiteral("background-color: rgb(255, 255, 255);"));
        lineEdit_9 = new QLineEdit(tab_3);
        lineEdit_9->setObjectName(QStringLiteral("lineEdit_9"));
        lineEdit_9->setGeometry(QRect(420, 220, 161, 20));
        lineEdit_9->setStyleSheet(QStringLiteral("background-color: rgb(255, 255, 255);"));
        label_8 = new QLabel(tab_3);
        label_8->setObjectName(QStringLiteral("label_8"));
        label_8->setGeometry(QRect(280, 340, 91, 16));
        lineEdit_5 = new QLineEdit(tab_3);
        lineEdit_5->setObjectName(QStringLiteral("lineEdit_5"));
        lineEdit_5->setGeometry(QRect(420, 340, 161, 20));
        lineEdit_5->setStyleSheet(QStringLiteral("background-color: rgb(255, 255, 255);"));
        lineEdit_10 = new QLineEdit(tab_3);
        lineEdit_10->setObjectName(QStringLiteral("lineEdit_10"));
        lineEdit_10->setGeometry(QRect(420, 300, 161, 20));
        lineEdit_10->setStyleSheet(QStringLiteral("background-color: rgb(255, 255, 255);"));
        lineEdit_8 = new QLineEdit(tab_3);
        lineEdit_8->setObjectName(QStringLiteral("lineEdit_8"));
        lineEdit_8->setGeometry(QRect(410, 260, 161, 20));
        lineEdit_8->setStyleSheet(QStringLiteral("background-color: rgb(255, 255, 255);"));
        label_10 = new QLabel(tab_3);
        label_10->setObjectName(QStringLiteral("label_10"));
        label_10->setGeometry(QRect(280, 300, 101, 20));
        label_12 = new QLabel(tab_3);
        label_12->setObjectName(QStringLiteral("label_12"));
        label_12->setGeometry(QRect(280, 220, 81, 16));
        label_13 = new QLabel(tab_3);
        label_13->setObjectName(QStringLiteral("label_13"));
        label_13->setGeometry(QRect(280, 260, 101, 16));
        label_5 = new QLabel(tab_3);
        label_5->setObjectName(QStringLiteral("label_5"));
        label_5->setGeometry(QRect(280, 180, 121, 16));
        label_5->setStyleSheet(QStringLiteral("background-color: rgb(227, 227, 227);"));
        pushButton_ajouter_2 = new QPushButton(tab_3);
        pushButton_ajouter_2->setObjectName(QStringLiteral("pushButton_ajouter_2"));
        pushButton_ajouter_2->setGeometry(QRect(310, 420, 111, 31));
        pushButton_ajouter_2->setStyleSheet(QLatin1String("background-color: rgb(170, 0, 0);\n"
"border :1px solid rgb(255, 255, 255);\n"
"border-radius :10px;\n"
"color: #FFF;\n"
"padding-left: 20px;\n"
"padding-right:20px;\n"
""));
        tabWidget->addTab(tab_3, QString());
        tab_4 = new QWidget();
        tab_4->setObjectName(QStringLiteral("tab_4"));
        label_39 = new QLabel(tab_4);
        label_39->setObjectName(QStringLiteral("label_39"));
        label_39->setGeometry(QRect(230, 260, 131, 31));
        label_39->setStyleSheet(QStringLiteral("background-color: rgb(227, 227, 227);"));
        lineEdit_14 = new QLineEdit(tab_4);
        lineEdit_14->setObjectName(QStringLiteral("lineEdit_14"));
        lineEdit_14->setGeometry(QRect(360, 260, 191, 31));
        lineEdit_14->setStyleSheet(QStringLiteral("background-color: rgb(255, 255, 255);"));
        pushButton_14 = new QPushButton(tab_4);
        pushButton_14->setObjectName(QStringLiteral("pushButton_14"));
        pushButton_14->setGeometry(QRect(320, 370, 201, 41));
        pushButton_14->setStyleSheet(QLatin1String("background-color: rgb(170, 0, 0);\n"
"border :1px solid rgb(255, 255, 255);\n"
"border-radius :10px;\n"
"color: #FFF;\n"
"padding-left: 20px;\n"
"padding-right:20px;\n"
""));
        tabWidget->addTab(tab_4, QString());
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 923, 26));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);

        retranslateUi(MainWindow);

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "Gestion des Clients", Q_NULLPTR));
        label_15->setText(QString());
        pushButton_2->setText(QApplication::translate("MainWindow", "7", Q_NULLPTR));
        pushButton->setText(QApplication::translate("MainWindow", "seach", Q_NULLPTR));
        tabWidget->setTabText(tabWidget->indexOf(tab_2), QApplication::translate("MainWindow", "Afficher", Q_NULLPTR));
        label_4->setText(QApplication::translate("MainWindow", "Id Equipement :", Q_NULLPTR));
        label_6->setText(QApplication::translate("MainWindow", "R\303\251f\303\251rence :", Q_NULLPTR));
        label_7->setText(QApplication::translate("MainWindow", "Prix :", Q_NULLPTR));
        label_9->setText(QApplication::translate("MainWindow", "Type :", Q_NULLPTR));
        pushButton_8->setText(QApplication::translate("MainWindow", "Quitter", Q_NULLPTR));
        pushButton_ajouter->setText(QApplication::translate("MainWindow", "Valider", Q_NULLPTR));
        label_11->setText(QApplication::translate("MainWindow", "Quantit\303\251:", Q_NULLPTR));
        tabWidget->setTabText(tabWidget->indexOf(tab), QApplication::translate("MainWindow", "Ajouter", Q_NULLPTR));
        pushButton_11->setText(QApplication::translate("MainWindow", "Quitter", Q_NULLPTR));
        label_8->setText(QApplication::translate("MainWindow", "Prix :", Q_NULLPTR));
        label_10->setText(QApplication::translate("MainWindow", "Type :", Q_NULLPTR));
        label_12->setText(QApplication::translate("MainWindow", "R\303\251f\303\251rence :", Q_NULLPTR));
        label_13->setText(QApplication::translate("MainWindow", "Quantit\303\251:", Q_NULLPTR));
        label_5->setText(QApplication::translate("MainWindow", "Id Equipement :", Q_NULLPTR));
        pushButton_ajouter_2->setText(QApplication::translate("MainWindow", "update", Q_NULLPTR));
        tabWidget->setTabText(tabWidget->indexOf(tab_3), QApplication::translate("MainWindow", "Modifier", Q_NULLPTR));
        label_39->setText(QApplication::translate("MainWindow", "Id Equipement :", Q_NULLPTR));
        pushButton_14->setText(QApplication::translate("MainWindow", "Supprimer", Q_NULLPTR));
        tabWidget->setTabText(tabWidget->indexOf(tab_4), QApplication::translate("MainWindow", "Supprimer", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
