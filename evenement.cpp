#include "evenement.h"
#include "ui_evenement.h"
#include <QMessageBox>
<<<<<<< HEAD
#include <entite_evenment.h>
=======
#include <QDateTime>
#include <QDebug>
#include <entite_evenment.h>
#include <QRegularExpression>
#include <QFileDialog>
#include <QPrinter>
#include <QPainter>
#include <localisation.h>
#include <QUrl>
#include <QDesktopServices>


>>>>>>> 18d955075ebf7e49d498a0f477c7a42083282ca3
//Entite_evenment::Entite_evenment(){}
Evenement::Evenement(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Evenement)
{
    ui->setupUi(this);
    ui->tableView->setModel(ev.afficher());
    ui->titre_modif->setEnabled(false);
    ui->date_modif->setEnabled(false);
    ui->description_modif->setEnabled(false);
    ui->category_modif->setEnabled(false);
}

Evenement::~Evenement()
{
    delete ui;
}
// ajouter
void Evenement::on_ajouter_button_clicked()
{
<<<<<<< HEAD
    int id = ui->id->text().toInt();
    QString titre = ui->titre->text();
    QString category = ui->category->text();
    QString description = ui->description->toPlainText();
    QDateTime date = ui->date->dateTime();
    Entite_evenment ev (id, titre, category,date, description);
    bool test = ev.ajouter();
    if(test) {
        ui->id->clear();
        ui->titre->clear();
        ui->description->clear();
        ui->category->clear();
=======
    //int id = ui->id->text().toInt();

    int id =NULL;
    QString titre = ui->titre->text();
    QString category = ui->category->currentText();
    QString description = ui->description->toPlainText();
    QDateTime date = ui->date->dateTime();
    QDateTime currentDateTime = QDateTime::currentDateTime();
    QString location = ui->location->text();
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
    Entite_evenment ev (id, titre, category,date, description,location);
    bool test = ev.ajouter();
    if(test) {
       // ui->id->clear();
        ui->titre->clear();
        ui->description->clear();
     //   ui->category->cle;
>>>>>>> 18d955075ebf7e49d498a0f477c7a42083282ca3
        ui->date->clear();
        ui->tableView->setModel(ev.afficher());
        QMessageBox::information(nullptr,QObject::tr("insertion"),
                               QObject::tr("insertion avec success.\n"),QMessageBox::Cancel);
<<<<<<< HEAD


=======
>>>>>>> 18d955075ebf7e49d498a0f477c7a42083282ca3
    }
    else {
        QMessageBox::critical(nullptr,QObject::tr("insertion"),
                               QObject::tr("insertion echoue.\n"),QMessageBox::Cancel);
    }
}
// supprimer
void Evenement::on_supprimer_button_clicked()
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
void Evenement::on_modifier_button_clicked()
{
    int id = ui->id_modif->text().toInt();
    QString titre = ui->titre_modif->text();
<<<<<<< HEAD
    QString category = ui->category_modif->text();
    QDateTime date = ui->date_modif->dateTime();
    QString description = ui->description_modif->toPlainText();
    Entite_evenment em (id, titre, category,date,description);
    bool test = em.modifier();
    if(test) {
        ui->tableView->setModel(ev.afficher());
=======
    QString category = ui->category_modif->currentText();
    QDateTime date = ui->date_modif->dateTime();
    QString description = ui->description_modif->toPlainText();
    Entite_evenment em (id, titre, category,date,description,"");
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
        //fin du code update l affichage ui
        //code pour vider les champs saisie
        ui->id_modif->clear();
        ui->titre_modif->clear();
        ui->description_modif->clear();
        ui->category_modif->clearEditText();
        ui->date_modif->clear();
        // fin du code de vider les champs
>>>>>>> 18d955075ebf7e49d498a0f477c7a42083282ca3
        QMessageBox::information(nullptr,QObject::tr("insertion"),
                               QObject::tr("modification avec success.\n"),QMessageBox::Cancel);

    }
    else {
        QMessageBox::critical(nullptr,QObject::tr("insertion"),
                               QObject::tr("modification echoue.\n"),QMessageBox::Cancel);
    }
}

void Evenement::on_Rechercher_button_clicked()
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
        // update the inputs with the data getted from the database
        ui->id_modif->setEnabled(false);
        ui->titre_modif->setText(ev.getTitre());
        ui->date_modif->setDateTime(ev.getDate());
        ui->description_modif->setText(ev.getDescription());
<<<<<<< HEAD
        ui->category_modif->setText(ev.getCategory());
=======
        ui->category_modif->setEditText(ev.getCategory());
>>>>>>> 18d955075ebf7e49d498a0f477c7a42083282ca3

    }

}
<<<<<<< HEAD
=======

void Evenement::on_rechercher_button_affichage_clicked()
{
    QString title = ui->rechercher->text();
     ui->tableView->setModel(ev.afficher_selon_titre(title));
}

void Evenement::on_pdf_button_clicked()
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




//void Evenement::on_comboBox_3_currentTextChanged(const QString &arg1)
//{

//}

void Evenement::on_Tri_categorie_currentTextChanged(const QString &arg1)
{
    // here i will call the tri function
    qDebug()<<arg1 ;
    if(arg1 == "")
        ui->tableView->setModel(ev.afficher());
    else
        ui->tableView->setModel(ev.afficher_Tri(arg1));
}

void Evenement::on_calendarWidget_clicked(const QDate &date)
{
    qDebug()<<date;
    ui->tableView->setModel(ev.afficher_Selon_Date(date));
}

void Evenement::on_localisation_button_clicked()
{  Entite_evenment ev;
   int id = ui->localisation_input->text().toInt();
   ev = ev.rechercher(id);
    if (ev.getId()==-1){
        QMessageBox::critical(nullptr,QObject::tr("Location"),
                               QObject::tr("localisation failed : you must use a an exist id.\n"),QMessageBox::Cancel);
    }
    else{
        QString address = ev.locationById(id);
        if(address != "")
        {
         QString googleMapsUrl = QString("https://www.google.com/maps/search/?api=1&query=%1").arg(address);
         QDesktopServices::openUrl(QUrl(googleMapsUrl));
        }
        else{
            QMessageBox::critical(nullptr,QObject::tr("Location"),
                                   QObject::tr("localisation failed : this event dont have direct access, will be only streamed.\n"),QMessageBox::Cancel);
        }
    }

}
>>>>>>> 18d955075ebf7e49d498a0f477c7a42083282ca3
