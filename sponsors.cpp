#include "sponsors.h"
#include <QSqlQuery>
#include <QtDebug>
#include <QObject>
#include <QSqlError>
#include <QColor>
#include <QtCharts/QPieSeries>
#include <QtCharts/QChart>
#include <QtCharts/QChartView>
#include <QPainter>
#include <QtCharts/QBarCategoryAxis>
#include <QtCharts/QValueAxis>
#include <QtCharts/QBarSeries>
#include <QtCharts/QBarSet>
#include <QPainter>
#include <QPaintEvent>
Sponsors::Sponsors()
{
    ID_SPONSOR = 0;
    NUM_CONTRAT = 0;
    CATEGORY = "";
    DURE_CONTRAT = "";
    NOM = "";
}

Sponsors::Sponsors(int ID_SPONSOR, int NUM_CONTRAT, QString CATEGORY, QString DURE_CONTRAT, QString NOM)
{
    this->ID_SPONSOR = ID_SPONSOR;
    this->NUM_CONTRAT = NUM_CONTRAT;
    this->CATEGORY = CATEGORY;
    this->DURE_CONTRAT = DURE_CONTRAT;
    this->NOM = NOM;
}

int Sponsors::getID_SPONSOR() { return ID_SPONSOR; }
int Sponsors::getNUM_CONTRAT() { return NUM_CONTRAT; }
QString Sponsors::getCATEGORY() { return CATEGORY; }
QString Sponsors::getDURE_CONTRAT() { return DURE_CONTRAT; }
QString Sponsors::getNOM() { return NOM; }
void Sponsors::setID_SPONSOR(int ID_SPONSOR) { this->ID_SPONSOR = ID_SPONSOR; }
void Sponsors::setNUM_CONTRAT(int NUM_CONTRAT) { this->NUM_CONTRAT = NUM_CONTRAT; }
void Sponsors::setCATEGORY(QString CATEGORY) { this->CATEGORY = CATEGORY; }
void Sponsors::setDURE_CONTRAT(QString DURE_CONTRAT) { this->DURE_CONTRAT = DURE_CONTRAT; }
void Sponsors::setNOM(QString NOM) { this->NOM = NOM; }

bool Sponsors::ajouter()
{
    QSqlQuery query;
    // Check if ID exists
    query.prepare("SELECT ID_SPONSOR FROM Sponsors WHERE ID_SPONSOR = :id_sponsor");
    query.bindValue(":id_sponsor", ID_SPONSOR);
    if (query.exec() && query.next())
    {
        // ID already exists
        int existingID = query.value(0).toInt();
        QMessageBox::warning(nullptr, "Duplicate ID", "The ID " + QString::number(existingID) + " already exists in the table.");
        return false;
    }

    // Check if NUM_CONTRAT exists
    query.prepare("SELECT NUM_CONTRAT FROM Sponsors WHERE NUM_CONTRAT = :num_contrat");
    query.bindValue(":num_contrat", NUM_CONTRAT);
    if (query.exec() && query.next())
    {
        // NUM_CONTRAT already exists
        int existingNumContrat = query.value(0).toInt();
        QMessageBox::warning(nullptr, "Duplicate NUM_CONTRAT", "The NUM_CONTRAT " + QString::number(existingNumContrat) + " already exists in the table.");
        return false;
    }

    // Neither ID nor NUM_CONTRAT exists, proceed with insertion
    query.prepare("INSERT INTO Sponsors (ID_SPONSOR, NUM_CONTRAT, CATEGORY, DURE_CONTRAT, NOM) "
                  "VALUES (:id_sponsor, :num_contrat, :category, :dure_contrat, :nom)");
    query.bindValue(":id_sponsor", ID_SPONSOR);
    query.bindValue(":num_contrat", NUM_CONTRAT);
    query.bindValue(":category", CATEGORY);
    query.bindValue(":dure_contrat", DURE_CONTRAT);
    query.bindValue(":nom", NOM);

    return query.exec();
}

QSqlQueryModel *Sponsors::afficher()
{
    QSqlQueryModel *model = new QSqlQueryModel();
    model->setQuery("SELECT * FROM SPONSORS");

    model->setHeaderData(0, Qt::Horizontal, QObject::tr("IDSPONSOR"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("NUMCONTRAT"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("CATEGORY"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("DURECONTRAT"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("NOM"));

    return model;
}

bool Sponsors::supprimer(int ID_SPONSOR)
{
    QSqlQuery query;
    query.prepare("SELECT ID_SPONSOR FROM SPONSORS WHERE ID_SPONSOR = :ID_SPONSOR");
    query.bindValue(":ID_SPONSOR", ID_SPONSOR);
    if (!query.exec())
    {
        qDebug() << "Error executing query:" << query.lastError().text();
        return false;
    }
    if (!query.next())
    {
        qDebug() << "ID_SPONSOR not found in the table";
        return false;
    }

    query.prepare("DELETE FROM SPONSORS WHERE ID_SPONSOR = :ID_SPONSOR");
    query.bindValue(":ID_SPONSOR", ID_SPONSOR);
    if (!query.exec())
    {
        qDebug() << "Error deleting entry:" << query.lastError().text();
        return false;
    }

    return true;
}

bool Sponsors::modifier(int ID_SPONSOR, int newNumContrat, const QString &newCategory, const QString &newDureContrat, const QString &newNom)
{
    QSqlQuery query;
    query.prepare("SELECT ID_SPONSOR FROM Sponsors WHERE ID_SPONSOR = :id_sponsor");
    query.bindValue(":id_sponsor", ID_SPONSOR);
    if (query.exec() && query.next())
    {
        // ID_SPONSOR exists, proceed with modification
        query.prepare("UPDATE Sponsors SET  NUM_CONTRAT = :new_num_contrat, CATEGORY = :category, DURE_CONTRAT = :dure_contrat, NOM = :nom WHERE ID_SPONSOR = :id_sponsor");
        query.bindValue(":new_num_contrat", newNumContrat);
        query.bindValue(":category", newCategory);
        query.bindValue(":dure_contrat", newDureContrat);
        query.bindValue(":nom", newNom);
        query.bindValue(":id_sponsor", ID_SPONSOR);
        return query.exec();
    }
    else
    {
        // ID_SPONSOR doesn't exist
        return false;
    }
}

Sponsors Sponsors::getSponsorByID(int ID_SPONSOR)
{
    QSqlQuery query;
    query.prepare("SELECT * FROM SPONSORS WHERE ID_SPONSOR = :ID_SPONSOR");
    query.bindValue(":ID_SPONSOR", ID_SPONSOR);
    query.exec();

    Sponsors sponsor;
    if (query.next())
    {
        sponsor.setID_SPONSOR(query.value(0).toInt());
        sponsor.setNUM_CONTRAT(query.value(1).toInt());
        sponsor.setCATEGORY(query.value(2).toString());
        sponsor.setDURE_CONTRAT(query.value(3).toString());
        sponsor.setNOM(query.value(4).toString());
    }
    return sponsor;
}

QSqlQueryModel *Sponsors::rankingByNumContrat()
{
    QSqlQueryModel *model = new QSqlQueryModel();
    model->setQuery("SELECT * FROM Sponsors ORDER BY NUM_CONTRAT");
    return model;
}


QSqlQueryModel *Sponsors::rankingBycat()
{
    QSqlQueryModel *model = new QSqlQueryModel();
    model->setQuery("SELECT * FROM Sponsors ORDER BY CATEGORY");
    return model;
}


int Sponsors::countType(const QString &category)
{
    QSqlQuery query;
    query.prepare("SELECT COUNT(*) FROM Sponsors WHERE CATEGORY = ?");
    query.addBindValue(category);
    if (query.exec() && query.next())
    {
        return query.value(0).toInt();
    }
    return 0; // Error occurred or no records found
}

void Sponsors::createColorfulCircleChart()
{
    // Define colors for each category
    QColor goldColor(255, 215, 0);        // Gold color
    QColor silverColor(192, 192, 192);    // Silver color
    QColor platinumColor(37, 101, 121);   // Platinum color
    QColor bronzeColor(165, 42, 42);      // Bronze color

    // Calculate the count of each category
    int goldCount = countType("Gold");
    int silverCount = countType("Silver");
    int platinumCount = countType("Plat");
    int bronzeCount = countType("Bronze");

    // Create a pie series
    QtCharts::QPieSeries *series = new QtCharts::QPieSeries();

    // Create slices for each category and set their colors
    QtCharts::QPieSlice *goldSlice = series->append("Gold", goldCount);
    goldSlice->setColor(goldColor);

    QtCharts::QPieSlice *silverSlice = series->append("Silver", silverCount);
    silverSlice->setColor(silverColor);

    QtCharts::QPieSlice *platinumSlice = series->append("Plat", platinumCount);
    platinumSlice->setColor(platinumColor);

    QtCharts::QPieSlice *bronzeSlice = series->append("Bronze", bronzeCount);
    bronzeSlice->setColor(bronzeColor);

    // Create a chart and set the series
    QtCharts::QChart *chart = new QtCharts::QChart();
    chart->addSeries(series);
    chart->setTitle("Category Statistics");

    // Enable animations
    chart->setAnimationOptions(QtCharts::QChart::SeriesAnimations);

    // Create a chart view and set the chart
    QtCharts::QChartView *chartView = new QtCharts::QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);

    // Set the size and style
    chartView->setFixedSize(500, 500);
    chartView->setStyleSheet("background-color: #ADD8E6;");

    // Show the chart
    chartView->show();
}

bool Sponsors::addQuestions(const QString &ques1, const QString &ques2, const QString &ques3, const QString &ques4, const QString &ques5)
{



    QSqlQuery query;

    // Prepare the query to insert questions into the QUEST table
    query.prepare("INSERT INTO QUEST (QUES1, QUES2, QUES3, QUES4, QUES5) "
                  "VALUES (:ques1, :ques2, :ques3, :ques4, :ques5)");
    query.bindValue(":ques1", ques1);
    query.bindValue(":ques2", ques2);
    query.bindValue(":ques3", ques3);
    query.bindValue(":ques4", ques4);
    query.bindValue(":ques5", ques5);

    // Execute the query
    return query.exec();
}

int Sponsors::retrieveCount(const QString &questionName, const QString &option)
{
    QSqlQuery query;
    query.prepare("SELECT COUNT(*) FROM QUEST WHERE " + questionName + " = ?");
    query.addBindValue(option);
    if (query.exec() && query.next())
    {
        return query.value(0).toInt();
    }
    return 0; // Error occurred or no records found
}

void Sponsors::createStatsChart(const QString &questionName)
{
    // Create a bar series for the chart
    QtCharts::QBarSeries *series = new QtCharts::QBarSeries();

    // Set the title of the chart based on the question
    QString chartTitle;
    if (questionName == "ques1")
        chartTitle = "Question 1: Technologie, Alimentation, Mode, Autre";
    else if (questionName == "ques2")
        chartTitle = "Question 2: Durée du contrat";
    else if (questionName == "ques3")
        chartTitle = "Question 3: Budget";
    else if (questionName == "ques4")
        chartTitle = "Question 4: Tranche d'âge";
    else if (questionName == "ques5")
        chartTitle = "Question 5: Objectif";

    // Count the occurrences of each option for the specified question
    if (questionName == "ques1") {
        int countTechnologie = retrieveCount(questionName, "Technologie");
        int countAlimentation = retrieveCount(questionName, "Alimentation");
        int countMode = retrieveCount(questionName, "Mode");
        int countAutre = retrieveCount(questionName, "Autre");

        // Append data to the series based on the question
        QtCharts::QBarSet *barSet = new QtCharts::QBarSet("Options");
        *barSet << countTechnologie << countAlimentation << countMode << countAutre;
        series->append(barSet);
    } else if (questionName == "ques2") {
        int count3Mois = retrieveCount(questionName, "3 mois (bronze)");
        int count6Mois = retrieveCount(questionName, "6 mois (silver)");
        int count1An = retrieveCount(questionName, "1 an(gold)");

        // Append data to the series based on the question
        QtCharts::QBarSet *barSet = new QtCharts::QBarSet("Options");
        *barSet << count3Mois << count6Mois << count1An;
        series->append(barSet);
    } else if (questionName == "ques3") {
        int countMoins5000 = retrieveCount(questionName, "Moins de 5 000 $ (bronze)");
        int count5000_10000 = retrieveCount(questionName, "Entre 5 000 $ et 10 000 $ (silver)");
        int count10000_20000 = retrieveCount(questionName, "Entre 10 000 $ et 20 000 $(Gold)");
        int countPlus20000 = retrieveCount(questionName, "Plus de 20 000 $ (plat)");

        // Append data to the series based on the question
        QtCharts::QBarSet *barSet = new QtCharts::QBarSet("Options");
        *barSet << countMoins5000 << count5000_10000 << count10000_20000 << countPlus20000;
        series->append(barSet);
    } else if (questionName == "ques4") {
        int count1824 = retrieveCount(questionName, " 18-24 ans");
        int count2534 = retrieveCount(questionName, "25-34 ans");
        int count3544 = retrieveCount(questionName, "35-44 ans");
        int count45plus = retrieveCount(questionName, "45 ans et plus");

        // Append data to the series based on the question
        QtCharts::QBarSet *barSet = new QtCharts::QBarSet("Options");
        *barSet << count1824 << count2534 << count3544 << count45plus;
        series->append(barSet);
    } else if (questionName == "ques5") {
        int countAugmentationVentes = retrieveCount(questionName, " Augmentation des ventes");
        int countTauxEngagement = retrieveCount(questionName, "Taux d'engagement");
        int countNotorieteMarque = retrieveCount(questionName, "Notoriété de la marque");
        int countAutre = retrieveCount(questionName, "Autre");

        // Append data to the series based on the question
        QtCharts::QBarSet *barSet = new QtCharts::QBarSet("Options");
        *barSet << countAugmentationVentes << countTauxEngagement << countNotorieteMarque << countAutre;
        series->append(barSet);
    }

    // Create a chart and set the series
    QtCharts::QChart *chart = new QtCharts::QChart();
    chart->addSeries(series);
    chart->setTitle(chartTitle);

    // Create categories for the x-axis based on the question
    QStringList categories;
    if (questionName == "ques1")
        categories << "Technologie" << "Alimentation" << "Mode" << "Autre";
    else if (questionName == "ques2")
        categories << "3 mois (bronze)" << "6 mois (silver)" << "1 an(gold)";
    else if (questionName == "ques3")
        categories << "Moins de 5 000 $ (bronze)" << "Entre 5 000 $ et 10 000 $ (silver)"
                   << "Entre 10 000 $ et 20 000 $(Gold)" << "Plus de 20 000 $ (plat)";
    else if (questionName == "ques4")
        categories << " 18-24 ans" << "25-34 ans" << "35-44 ans" << "45 ans et plus";
    else if (questionName == "ques5")
        categories << " Augmentation des ventes" << "Taux d'engagement"
                   << "Notoriété de la marque" << "Autre";

    // Create the x-axis and set categories
    QtCharts::QBarCategoryAxis *axisX = new QtCharts::QBarCategoryAxis();
    axisX->append(categories);
    chart->addAxis(axisX, Qt::AlignBottom);
    series->attachAxis(axisX);

    // Create the y-axis
    QtCharts::QValueAxis *axisY = new QtCharts::QValueAxis();
    chart->addAxis(axisY, Qt::AlignLeft);
    series->attachAxis(axisY);

    // Enable animations
    chart->setAnimationOptions(QtCharts::QChart::SeriesAnimations);

    // Create a chart view and set the chart
    QtCharts::QChartView *chartView = new QtCharts::QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);

    // Set the size and style
    chartView->setFixedSize(800, 500);
    chartView->setStyleSheet("background-color: #ADD8E6;");

    // Show the chart
    chartView->show();
}


/*
void Sponsors::paintEvent(QPaintEvent *event)
{
    // Call the base class implementation of paintEvent
    QWidget::paintEvent(event);

    // Create a QPainter object to draw on this widget
    QPainter painter(this);

    // Set the color and size of the pen used for drawing
    QPen pen(Qt::blue);
    pen.setWidth(2);
    painter.setPen(pen);

    // Draw a circle at position (100, 100) with radius 50
    painter.drawEllipse(100, 100, 50, 50);
}

void Sponsors::drawCircle()
{
    // Trigger a repaint request, which will indirectly call paintEvent
    update();
}
*/
