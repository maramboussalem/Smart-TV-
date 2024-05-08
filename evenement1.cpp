#include "evenement1.h"
#include "ui_evenement1.h"
#include <QMessageBox>
#include "entite_evenment.h"
#include "map.h"
#include <QFileDialog>
#include <QPrinter>
#include <QChart>
#include <QPainter>
#include <QtCharts>
#include <QtCharts/QChartView>
#include <QtCharts/QPieSeries>
#include <QtCharts/QChart>
Evenement1::Evenement1(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Evenement1)
{
    ui->setupUi(this);
    ui->tableView->setModel(ev.afficher());
    ui->titre_modif->setEnabled(false);
    ui->date_modif->setEnabled(false);
    ui->description_modif->setEnabled(false);
    ui->category_modif->setEnabled(false);
    ui->longtitude_modif->setEnabled(false);
    ui->latitude_modif->setEnabled(false);
}

Evenement1::~Evenement1()
{
    delete ui;
}



void Evenement1::on_Location_clicked()
{
    int id = ui->id_location->text().toInt();
        Map * mapEvent = new Map(this);
    //    mapEvent->show();
    //    std::pair<double, double> coordinates = getLocationCoordinatesById(id);
         int latitude = ev.getLatitudeById(id);
         int longititude = ev.getLongititudeById(id);

           // Assuming you have a pointer to the map widget
    //       mapEvent->setCenterPosition(coordinates.first, coordinates.second);
    //       mapEvent->setLocationMarking(coordinates.first, coordinates.second);
        mapEvent->setCenterPosition(latitude, longititude);
        mapEvent->setLocationMarking (latitude, longititude);
        mapEvent->show();

}

void Evenement1::on_ajouter_button_clicked()
{
    //int id = ui->id->text().toInt();

    int id =NULL;
    float latitude = ui->latitude->text().toFloat();
    float  longtitude= ui->longtitude->text().toFloat();
    QString titre = ui->titre->text();
    QString category = ui->category->currentText();
    QString description = ui->description->toPlainText();
    QDateTime date = ui->date->dateTime();
    QDateTime currentDateTime = QDateTime::currentDateTime();
    QString specialChars = "@#$%&'()*+,-./=<>\±×÷€£¥$@§©®™°^_~₽₹฿";

    if(titre.isEmpty() && category.isEmpty())
    {
        QMessageBox::warning(nullptr, QObject::tr("Champs obligatoires"),
                             QObject::tr("Veuillez saisir un titre et une category."),QMessageBox::Cancel);
        return;
    }
    bool containsSpecialChars = false;

    for (const QChar& ch : titre) {
        if (specialChars.contains(ch)) {
            containsSpecialChars = true;
            break;
        }
    }
    if(containsSpecialChars)
    {
        QMessageBox::warning(nullptr, QObject::tr("Champ non valid"),
                             QObject::tr("veuillez saisir un titre qui ne contient pas des characteres speciaux"),QMessageBox::Cancel);
        return;
    }
    if(titre.isEmpty())
    {
        QMessageBox::warning(nullptr, QObject::tr("Champ obligatoire"),
                             QObject::tr("Veuillez saisir un titre."),QMessageBox::Cancel);
        return;
    }
    if(category.isEmpty())
    {
        QMessageBox::warning(nullptr, QObject::tr("Champ obligatoire"),
                             QObject::tr("Veuillez saisir une category."),QMessageBox::Cancel);
        return;
    }
    if (date < currentDateTime) {
        QMessageBox::warning(nullptr, QObject::tr("Champ invalid"),
                             QObject::tr("La date que vous avez saisir est revolue"),QMessageBox::Cancel);
        return;
     }
    Entite_evenment ev (id, titre, category,date, description,latitude,longtitude);
    bool test = ev.ajouter();
    if(test) {
       // ui->id->clear();
        ui->titre->clear();
        ui->description->clear();
        ui->category->clear();
        ui->date->clear();
        ui->tableView->setModel(ev.afficher());
        QMessageBox::information(nullptr,QObject::tr("insertion"),
                               QObject::tr("insertion avec success.\n"),QMessageBox::Cancel);
    }
    else {
        QMessageBox::critical(nullptr,QObject::tr("insertion"),
                               QObject::tr("insertion echoue.\n"),QMessageBox::Cancel);
    }
}
// supprimer
void Evenement1::on_supprimer_button_clicked()
{
    int id = ui->id_supprime->text().toInt();
       Entite_evenment ev;  // Declare the object
       ev = ev.rechercher(id);
        if (ev.getId()==-1){
            QMessageBox::critical(nullptr,QObject::tr("delete"),
                                   QObject::tr("delete failed : you must use a an exist id.\n"),QMessageBox::Cancel);
        }
        else {
              bool test = ev.supprimer(id);

                if(test) {
                     ui->tableView->setModel(ev.afficher());
                    QMessageBox::information(nullptr,QObject::tr("suppression"),
                                       QObject::tr("delete succesful.\n"),QMessageBox::Cancel);
                         }
                else {
                        QMessageBox::critical(nullptr,QObject::tr("delete"),
                                       QObject::tr("delete failed.\n"),QMessageBox::Cancel);
                }
        }

}
 //modifier
void Evenement1::on_modifier_button_clicked()
{
    int id = ui->id_modif->text().toInt();
    float latitude = ui->latitude_modif->text().toFloat();
    float longtitude = ui->longtitude_modif->text().toFloat();
    QString titre = ui->titre_modif->text();
    QString category = ui->category_modif->currentText();
    QDateTime date = ui->date_modif->dateTime();
    QString description = ui->description_modif->toPlainText();

    Entite_evenment em (id, titre, category,date,description,latitude,longtitude);
    QDateTime currentDateTime = QDateTime::currentDateTime();
    QString specialChars = "@#$%&'()*+,-./=<>\±×÷€£¥$@§©®™°^_~₽₹฿";
     bool containsSpecialChars = false;
    // controle de saisie
    if(titre.isEmpty() && category.isEmpty())
    {
        QMessageBox::warning(nullptr, QObject::tr("Champs obligatoires"),
                             QObject::tr("Veuillez saisir un titre et une category."),QMessageBox::Cancel);
        return;
    }
    if(titre.isEmpty())
    {
        QMessageBox::warning(nullptr, QObject::tr("Champ obligatoire"),
                             QObject::tr("Veuillez saisir un titre."),QMessageBox::Cancel);
        return;
    }


    for (const QChar& ch : titre) {
        if (specialChars.contains(ch)) {
            containsSpecialChars = true;
            break;
        }
    }
    if(containsSpecialChars)
    {
        QMessageBox::warning(nullptr, QObject::tr("Champ non valid"),
                             QObject::tr("veuillez saisir un titre qui ne contient pas des characteres speciaux"),QMessageBox::Cancel);
        return;
    }
    if(category.isEmpty())
    {
        QMessageBox::warning(nullptr, QObject::tr("Champ obligatoire"),
                             QObject::tr("Veuillez saisir une category."),QMessageBox::Cancel);
        return;
    }
    if (date < currentDateTime) {
        QMessageBox::warning(nullptr, QObject::tr("Champ invalid"),
                             QObject::tr("La date que vous avez saisir est revolue"),QMessageBox::Cancel);
        return;
     }
    bool test = em.modifier();
    if(test) {
        ui->tableView->setModel(ev.afficher());
        //ce block du code pour update affichage ui
        ui->id_modif->setEnabled(true);
        ui->titre_modif->setEnabled(false);
        ui->category_modif->setEnabled(false);
        ui->date_modif->setEnabled(false);
        ui->description_modif->setEnabled(false);
        ui->latitude_modif->setEnabled(false);
         ui->longtitude_modif->setEnabled(false);
        //fin du code update l affichage ui
        //code pour vider les champs saisie
        ui->id_modif->clear();
        ui->titre_modif->clear();
        ui->description_modif->clear();
        ui->category_modif->clear();
        ui->date_modif->clear();
        ui->latitude_modif->clear();
        ui->longtitude_modif->clear();
        // fin du code de vider les champs
        QMessageBox::information(nullptr,QObject::tr("insertion"),
                               QObject::tr("modification avec success.\n"),QMessageBox::Cancel);

    }
    else {
        QMessageBox::critical(nullptr,QObject::tr("insertion"),
                               QObject::tr("modification echoue.\n"),QMessageBox::Cancel);
    }
}

void Evenement1::on_Rechercher_button_clicked()
{
    int id = ui->id_modif->text().toInt();
    Entite_evenment ev ;
    ev = ev.rechercher(id);
    if(ev.getId()==-1)
    {
        // handle error
        QMessageBox::critical(nullptr,QObject::tr("Error"),
                               QObject::tr("Vous devez inserer un id existant.\n"),QMessageBox::Cancel);
    }
    else {
        // i will enable the inputs
        ui->titre_modif->setEnabled(true);
        ui->date_modif->setEnabled(true);
        ui->description_modif->setEnabled(true);
        ui->category_modif->setEnabled(true);
        ui->latitude_modif->setEnabled(true);
        ui->longtitude_modif->setEnabled(true);
        // update the inputs with the data getted from the database
        ui->id_modif->setEnabled(false);
        ui->titre_modif->setText(ev.getTitre());
        ui->date_modif->setDateTime(ev.getDate());
        ui->description_modif->setText(ev.getDescription());
        ui->latitude_modif->setText(QString::number(ev.getLatitude()));
        ui->longtitude_modif->setText(QString::number(ev.getLongtitude()));

        //ui->category_modif->currentText(ev.getCategory());//(ev.getCategory());

    }

}


void Evenement1::on_calendarWidget_clicked(const QDate &date)
{
    qDebug()<<date;
      ui->tableView->setModel(ev.afficher_Selon_Date(date));

}

void Evenement1::on_pdf_button_clicked()
{
        QString fileName = QFileDialog::getSaveFileName(this, "Export to PDF", "", "PDF Files (*.pdf)");
        if (fileName.isEmpty())
            return;

        QPrinter printer(QPrinter::PrinterResolution);
        printer.setOutputFormat(QPrinter::PdfFormat);
        printer.setPaperSize(QPrinter::A4);
        printer.setOutputFileName(fileName);

        QPainter painter;
        painter.begin(&printer);

        // Logo
        QPixmap logo(":/new/prefix1/Logo.png");
        QRect logoRect(50, 50, 100, 100); // Adjust position and size as needed
        painter.drawPixmap(logoRect, logo);

        // Current date
        QString currentDate = QDate::currentDate().toString("yyyy-MM-dd");
        QFont dateFont;
        dateFont.setPointSize(16); // Adjust the font size as needed
        painter.setFont(dateFont);
        QRect dateRect(printer.pageRect().width() - 200, 50, 150, 30); // Adjust position as needed
        painter.drawText(dateRect, Qt::AlignRight, currentDate);

        // Scale and render table
        double xscale = (printer.pageRect().width() - 100) / double(ui->tableView->width()); // Adjust scale and position
        double yscale = (printer.pageRect().height() - 200) / double(ui->tableView->height()); // Adjust scale and position
        double scale = qMin(xscale, yscale);

        painter.translate(50, 200); // Adjust position
        painter.scale(scale, scale);
        ui->tableView->render(&painter);
        painter.end();
}

void Evenement1::on_rechercher_button_affichage_clicked()
{
    QString title = ui->rechercher->text();
     ui->tableView->setModel(ev.afficher_selon_titre(title));
}


void Evenement1::on_Tri_comboBox_currentTextChanged(const QString &arg1)
{
    if(arg1 == ""){
         ui->tableView->setModel(ev.afficher());
    }
   else if(arg1 == "Asc"){
        //here i will update the the view based on date
        ui->tableView->setModel(ev.afficher_Selon_Asc());
     }
    else
     {
        ui->tableView->setModel(ev.afficher_Selon_Desc());

      }
    }
void Evenement1::on_Statistique_button_clicked() {
    Entite_evenment ev ;
    // Effacer le contenu précédent du QLabel
    ui->label_stat->clear();

    // Créer la série pour le graphique
    QtCharts::QPieSeries *series = new QtCharts::QPieSeries();
    series->setHoleSize(0.35);

    // Ajouter les parts au graphique en utilisant la fonction countType
    QStringList categories = {"Sports", "Comedy", "Drama", "Festival", "Concert"};
    foreach (const QString &category, categories) {
        int count = ev.countType(category);
        if (count > 0) {
            series->append(category, count);
        }
    }

    // Créer le graphique
    QtCharts::QChart *chart = new QtCharts::QChart();
    chart->addSeries(series);
    chart->setTitle("Statistiques des événements par catégorie");

    // Créer la vue pour le graphique
    QtCharts::QChartView *chartView = new QtCharts::QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);

    // Convertir la vue en pixmap
    QPixmap pixmap = chartView->grab();

    // Afficher l'image sur le QLabel
    ui->label_stat->setPixmap(pixmap);
}
