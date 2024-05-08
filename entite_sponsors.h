#ifndef ENTITE_SPONSORS_H
#define ENTITE_SPONSORS_H
#include <QString>
#include <QMessageBox>
#include <QDate>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QtCharts/QChart>

class Entite_sponsors
{
public:
    Entite_sponsors();
    Entite_sponsors(int,int,QString,QString,QString);
    int getID_SPONSOR();
    int getNUM_CONTRAT();
    QString getCATEGORY();
    QString getDURE_CONTRAT();
    QString getNOM();
    void setID_SPONSOR(int);
    void setNUM_CONTRAT(int);
    void setCATEGORY(QString);
    void setDURE_CONTRAT(QString);
    void setNOM(QString);
    bool ajouter();
    QSqlQueryModel* afficher();
    bool supprimer(int);
    bool modifier(int ID_SPONSOR, int newNumContrat, const QString& newCategory, const QString& newDureContrat, const QString& newNom);
    Entite_sponsors getSponsorByID(int ID_SPONSOR);
    QSqlQueryModel* rankingByNumContrat();
    QSqlQueryModel* rankingBycat();
    QtCharts::QChart *getChart() const { return m_chart; }

    static void createColorfulCircleChart();
    static void createQuestionStatsCharts(); // New function declaration
    static int countType(const QString& category);
    bool addQuestions(const QString& ques1, const QString& ques2, const QString& ques3, const QString& ques4, const QString& ques5);
    int retrieveCount(const QString &questionName, const QString &option);
    QVector<int> getAllQuestionsStats();
    void createStatsChart(const QString &questionName);
    void drawCircle();
    void paintEvent(QPaintEvent *event);


private:
    int ID_SPONSOR, NUM_CONTRAT ;
    QString CATEGORY, DURE_CONTRAT, NOM;
    QtCharts::QChart *m_chart;

};

#endif // ENTITE_SPONSORS_H
