#ifndef SPONSORS_H
#define SPONSORS_H
#include "entite_sponsors.h"
#include <QDialog>
#include "arduino.h"
namespace Ui {
class Sponsors;
}

class Sponsors : public QDialog
{
    Q_OBJECT

public:
    explicit Sponsors(QWidget *parent = nullptr);
    ~Sponsors();
private slots:
    void update_label();
    void on_button_ajouter_clicked();

    void on_pushButton_2_clicked();

    void on_deleteBut_clicked();

    void on_modifyButton_clicked();

    void on_showButton_clicked();


    void on_Reset_clicked();

    void on_Reset_2_clicked();



    void on_ranking_clicked();

    void on_comboBox_ID_SPONSOR_activated(const QString &arg1);

    void on_ranking_2_clicked();
    void on_colorfulCircleButton_clicked();

    void on_showColorfulStatsButton_clicked();

    void on_stats_clicked();

    void on_label_9_linkActivated(const QString &link);

    void on_stats_2_clicked();

    void on_ok_clicked();

    void on_ok_2_clicked();

    void on_stats2_clicked();
    //void displayQuestionStats(const QString &questionName, const QString &option1, const QString &option2, const QString &option3, const QString &option4);
    void createQuestionStatsChart(const QString &questionName, const QString &option1, const QString &option2, const QString &option3, const QString &option4);

   // void on_cell_clicked(int row, int column); // Declare the function here
   // int countSelectedRadioButton(const QString &question, const QString &answer); // Declaration of countSelectedRadioButton
   // int countSelectedAnswers(const QString &selectedAnswer);

    //void on_cell_clicked();

    void on_stats2_2_clicked();

    void on_stats2_3_clicked();

    void on_stats2_4_clicked();

    void on_stats2_5_clicked();

    void on_logo1_clicked();

    void on_logo1_2_clicked();

    void on_logo2_clicked();

    void on_logo2_3_clicked();

    void on_logo2_2_clicked();


    void on_reset_clicked();
    void askChatbotAboutServices();

    void on_reset_2_clicked();

    void on_recherche_activated(const QString &arg1);
     void recherche(const QString& searchText);
     void on_find_clicked();

     void on_reset_search_clicked();

     void on_pushButton_clicked();

     void on_pushButton_4_clicked();
private:
    Ui::Sponsors *ui;
    QWidget *statsWidget;

    Entite_sponsors S;
    QByteArray data; // variable contenant les données reçues

    Arduino A;

    int countType(const QString &category);
       void createColorfulCircleChart();
};

#endif // SPONSORS_H
