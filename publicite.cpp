#include "publicite.h"
#include "ui_publicite.h"
#include "entite_pub.h"
#include <QDate>
#include <QString>
#include <QMessageBox>
#include <QLineEdit>
#include <QSqlQueryModel>
#include <QTextDocument>
#include <QFileDialog>
#include<QtCharts>
#include<QChartView>
#include<QPieSeries>
#include <QPrinter>
#include <QDebug>
#include<QVideoWidget>

Publicite::Publicite(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Publicite)
{

    ui->setupUi(this);
    ui->tableView_publicite->setModel(p.afficher());
    int ret=A.connect_arduino(); // lancer la connexion à arduino
    switch(ret){
    case(0):qDebug()<< "arduino is available and connected to : "<< A.getarduino_port_name();
        break;
    case(1):qDebug() << "arduino is available but not connected to :" <<A.getarduino_port_name();
       break;
    case(-1):qDebug() << "arduino is not available";
    }
     QObject::connect(A.getserial(),SIGNAL(readyRead()),this,SLOT(update_label())); // permet de lancer
     //le slot update_label suite à la reception du signal readyRead (reception des données).
}

Publicite::~Publicite()
{
    delete ui;
}

void Publicite::on_pushButton_2_clicked() {
    int idpublicite = ui->lineEditrech->text().toInt();

    Entite_pub publiciteObject;

    if (publiciteObject.id_existe(idpublicite)) {
        Entite_pub p = publiciteObject.rechercherpub(idpublicite);

        ui->comboBox_2_bj_M->setCurrentText(p.getObjectifdeLaCompagne());
        ui->timeEdit_2_duree_M->setTime(QTime::fromString(p.getDuree(), "hh:mm:ss"));
        ui->spinBox_2_fq_M->setValue(p.getFrequences().toInt());
        ui->tableView_publicite->setModel(publiciteObject.afficher());

        A.write_to_arduino("1");

        if (p.getFrequences().toInt() > 8) {
            QMessageBox::warning(this, "Attention", "La fréquence est supérieure à 80 !");
            A.write_to_arduino("2");
        }


    } else {
        QMessageBox::critical(this, "Erreur", "L'ID n'existe pas !");
        A.write_to_arduino("3");
    }
}

void Publicite::on_pushButton_9_clicked() // ajouter
{
    int IdPublicite = ui->lineEdit_6->text().toInt();
    QString ObjectifdeLaCompagne = ui->comboBox->currentText();
    QString Duree = ui->timeEdit->time().toString("hh:mm:ss");
    QString Frequences = ui->spinBox->text();

    Entite_pub publiciteObject(IdPublicite, ObjectifdeLaCompagne, Duree, Frequences);
    publiciteObject.VIDEOPATH=filePath;

    if (ui->lineEdit_6->text()!="")
    {
        if(!publiciteObject.ajouter())
         {

            QMessageBox::critical(nullptr, QObject::tr("Erreur"),
                                  QObject::tr("ajout non effectuer.\nCliquez sur Annuler pour quitter."),
                                  QMessageBox::Cancel);
        }
           else
        {
            ui->tableView_publicite->setModel(publiciteObject.afficher());
            QMessageBox::information(nullptr, QObject::tr("ok"),
                                     QObject::tr("Ajout effectué\nCliquez sur Annuler pour quitter."),
                                     QMessageBox::Cancel);
            QString message = "publicité" +  QString::number(IdPublicite) +  "added : \n"
                                          "ObjectifdeLaCompagne : " + ObjectifdeLaCompagne + "\n"
                                          "Duree : " + Duree + "\n"
                                          "FREQUENCES : " + Frequences + "\n";

               // Logs l;
                //l.writeLogToFile(message);
        }
    }
    else
    {
        QMessageBox::critical(nullptr, QObject::tr("Erreur"),
                              QObject::tr("remplir tous les chams.\nCliquez sur Annuler pour quitter."),
                              QMessageBox::Cancel);
    }
    filePath="";
}

void Publicite::on_pushButton_14_clicked()   //supp
{
    QString IdPubliciteString = ui->lineEdit_14->text();
    int IdPublicite = IdPubliciteString.toInt();


    if (p.id_existe(IdPublicite))
    {
        QSqlQuery query;
                query.prepare("SELECT * FROM publicite WHERE idpublicite = :IdPublicite");
                query.bindValue(":IdPublicite", IdPublicite);

                if (query.exec() && query.next()) {
                    QString ObjectifdeLaCompagne = query.value("ObjectifdeLaCompagne").toString();
                    QString Duree = query.value("Duree").toString();
                    QString Frequences = query.value("Frequences").toString();
                    QString temp = QDate::currentDate().toString("dd/MM/yyyy");
                    QSqlQuery insertQuery;
                    insertQuery.prepare("INSERT INTO publicitesupprimer (IdPublicite, ObjectifdeLaCompagne, Duree, Frequences, TEMP) "
                                        "VALUES (:IdPublicite, :ObjectifdeLaCompagne, :Duree, :Frequences, :temp)");
                    insertQuery.bindValue(":IdPublicite", IdPublicite);
                    insertQuery.bindValue(":ObjectifdeLaCompagne", ObjectifdeLaCompagne);
                    insertQuery.bindValue(":Duree", Duree);
                    insertQuery.bindValue(":Frequences", Frequences);
                    insertQuery.bindValue(":temp", temp);




                   insertQuery.exec();
                }

        if(p.supprimer(IdPublicite))
        {
            ui->tableView_publicite->setModel(p.afficher());
            QMessageBox::information(nullptr, QObject::tr("ok"),
                                     QObject::tr("Suppression effectuée\nCliquez sur Annuler pour quitter."),
                                     QMessageBox::Cancel);
        }
        else
        {
            QMessageBox::critical(nullptr, QObject::tr("Erreur"),
                                  QObject::tr("Suppression non effectuée.\nCliquez sur Annuler pour quitter."),
                                  QMessageBox::Cancel);
        }
    }
    else
    {
        QMessageBox::critical(nullptr, QObject::tr("Erreur"),
                              QObject::tr("id non exsite.\nCliquez sur Annuler pour quitter."),
                              QMessageBox::Cancel);
    }

}






void Publicite::on_Modifier_clicked()
{

    int IdPublicite = ui->lineEditrech->text().toInt();
    QString ObjectifdeLaCompagne = ui->comboBox_2_bj_M->currentText();
    QString Duree = ui->timeEdit_2_duree_M->time().toString("hh:mm:ss");
    QString Frequences = ui->spinBox_2_fq_M->text();
    QString temp = QDate::currentDate().toString("dd/MM/yyyy");

    Entite_pub publiciteObject;


    QSqlQuery insertQuery;
    insertQuery.prepare("INSERT INTO publicitesupprimer (IdPublicite, ObjectifdeLaCompagne, Duree, Frequences, TEMP) "
                        "VALUES (:IdPublicite, :ObjectifdeLaCompagne, :Duree, :Frequences, :temp)");
    insertQuery.bindValue(":IdPublicite", IdPublicite);
    insertQuery.bindValue(":ObjectifdeLaCompagne", ObjectifdeLaCompagne);
    insertQuery.bindValue(":Duree", Duree);
    insertQuery.bindValue(":Frequences", Frequences);
    insertQuery.bindValue(":temp", temp);

    insertQuery.exec();


    bool test = publiciteObject.modifier(IdPublicite, ObjectifdeLaCompagne, Duree, Frequences);

    if (test)
    {
        ui->tableView_publicite->setModel(publiciteObject.afficher());  // Utilisez directement afficher() ici
        insertQuery.prepare("UPDATE publicitesupprimer SET OBJECTIFDELACOMPAGNE = :ObjectifdeLaCompagne, DUREE = :Duree, FREQUENCES = :Frequences, TEMP= :temp WHERE IDPUBLICITE = :IdPublicite");
        insertQuery.bindValue(":IdPublicite", IdPublicite);
        insertQuery.bindValue(":ObjectifdeLaCompagne", ObjectifdeLaCompagne);
        insertQuery.bindValue(":Duree", Duree);
        insertQuery.bindValue(":Frequences", Frequences);
        insertQuery.bindValue(":temp", temp);

        insertQuery.exec();

        QMessageBox::information(nullptr, QObject::tr("OK"),
                                 QObject::tr("Modification effectuée.\n"
                                             "Click Cancel to exit."), QMessageBox::Cancel);
        QString message = "publicité" +  QString::number(IdPublicite) +  "updated : \n"
                                      "ObjectifdeLaCompagne : " + ObjectifdeLaCompagne + "\n"
                                      "Duree : " + Duree + "\n"
                                      "FREQUENCES : " + Frequences + "\n";

            //Logs l;
            //l.writeLogToFile(message);
    }
    else
    {
        QMessageBox::critical(nullptr, QObject::tr("Not OK"),
                              QObject::tr("Modification non effectuée.\n"
                                          "Click Cancel to exit."), QMessageBox::Cancel);
    }
}




void Publicite::on_pushButtontri_clicked()  //tri
{
    Entite_pub p;
           ui->tableView_publicite->setModel(p.triPUB(ui->comboBox_2->currentText()));
}

void Publicite::on_pushButton_18_clicked()     // pdf
{
    QPrinter printer(QPrinter::PrinterResolution);
    printer.setOutputFormat(QPrinter::PdfFormat);
    QString filePath = QFileDialog::getSaveFileName(this, "Enregistrer le PDF", "liste_Pub.pdf", "Fichiers PDF (*.pdf)");
    if(filePath.isEmpty()) {
        return;
    }
    printer.setOutputFileName(filePath);
    QPainter painter(&printer);

    // Créer un document texte pour contenir la liste des produits
    QTextDocument doc;
    QTextCursor cursor(&doc);

    // Insérer le titre dans le document PDF
    QTextBlockFormat titleFormat;
    titleFormat.setAlignment(Qt::AlignCenter);
    QTextCharFormat titleCharFormat;
    titleCharFormat.setFontWeight(QFont::Bold);
    titleCharFormat.setFontPointSize(14);
    cursor.setBlockFormat(titleFormat);
    cursor.setCharFormat(titleCharFormat);
    cursor.insertText("Liste des Pub\n\n");

    // Insérer un tableau pour afficher les données des produits
    QTextTableFormat tableFormat;
    tableFormat.setAlignment(Qt::AlignLeft);
    tableFormat.setBorder(1);
    QTextTable *table = cursor.insertTable(ui->tableView_publicite->model()->rowCount() + 1, ui->tableView_publicite->model()->columnCount(), tableFormat);

    // Remplir le tableau avec les en-têtes de colonnes
    for(int col = 0; col < ui->tableView_publicite->model()->columnCount(); ++col) {
        QString header = ui->tableView_publicite->model()->headerData(col, Qt::Horizontal).toString();
        QTextCursor cellCursor = table->cellAt(0, col).firstCursorPosition();
        cellCursor.insertText(header);
    }

    // Remplir le tableau avec les données des produits
    for(int row = 0; row < ui->tableView_publicite->model()->rowCount(); ++row) {
        for(int col = 0; col < ui->tableView_publicite->model()->columnCount(); ++col) {
            QString data = ui->tableView_publicite->model()->data(ui->tableView_publicite->model()->index(row, col)).toString();
            QTextCursor cellCursor = table->cellAt(row + 1, col).firstCursorPosition();
            cellCursor.insertText(data);
        }
    }

    // Dessiner le document PDF
    doc.drawContents(&painter);

    // Terminer l'impression
    painter.end();

    // Afficher un message de confirmation
    QMessageBox::information(this, "Succès", "Le fichier PDF a été généré avec succès !");
}
float countType(QString ch)
{
    QSqlQueryModel* searchModel = new QSqlQueryModel();
    searchModel->setQuery("SELECT * FROM publicite WHERE OBJECTIFDELACOMPAGNE LIKE '%" + ch + "%'");

    return searchModel->rowCount() ;
}
void Publicite::on_pushButton_16_clicked()
{
    QList<QWidget*> childWidgets = ui->label->findChildren<QWidget*>();
        for (QWidget* childWidget : childWidgets) {
            childWidget->deleteLater();

        }
        ui->label->clear();
        ui->label->hide();

    float s0, s1, s2 , s3 ,s4 ;
    s0 = countType("Pas de pauvrete");
    s1 = countType("Industrie, innovation et infrastructure");
    s2 = countType("Travail decent et croissance economique");
    s3 = countType("Education de qualite");
    s4 = countType("Bonne sante et bien-etre");

    qDebug () << s0 ;
    float stat = s0 + s1 + s2 +s3 ;
    float x = (stat != 0) ? (s0 * 100) / stat : 0.0;
    float y = (stat != 0) ? (s1 * 100) / stat : 0.0;
    float z = (stat != 0) ? (s2 * 100) / stat : 0.0;
    float d = (stat != 0) ? (s3 * 100) / stat : 0.0;
    float a = (stat != 0) ? (s4 * 100) / stat : 0.0;

    QString ch1 = QString("Pas de pauvrete %1%").arg(x);
    QString ch2 = QString("Industrie, innovation et infrastructure %1%").arg(y);
    QString ch3 = QString("Travail decent et croissance economique %1%").arg(z);
    QString ch4 = QString("Education de qualite %1%").arg(z);
    QString ch5 = QString("Bonne sante et bien-etre %1%").arg(z);

        QPieSeries *series=new QPieSeries();
        series->setHoleSize(0.35);



        QPieSlice *slice= series->append(ch1,x);
        slice->setLabelVisible();
        slice->setLabelColor(QColor(Qt::black));
        slice->setBrush(QColor(189, 76, 224, 1));

        QPieSlice *slice1= series->append(ch2,y);
        slice1->setLabelVisible();
        slice1->setLabelColor(QColor(Qt::black));
        slice1->setBrush(QColor(Qt::yellow));

        QPieSlice *slice2= series->append(ch3,z);
        slice2->setLabelVisible();
        slice2->setLabelColor(QColor(Qt::black));
        slice2->setBrush(QColor(Qt::green));

        QPieSlice *slice3= series->append(ch4,d);
        slice3->setLabelVisible();
        slice3->setLabelColor(QColor(Qt::black));
        slice3->setBrush(QColor(Qt::red));

        QPieSlice *slice4= series->append(ch5,a);
        slice4->setLabelVisible();
        slice4->setLabelColor(QColor(Qt::black));
        slice4->setBrush(QColor(Qt::blue));

        QChart *chart=new QChart();
        chart->addSeries(series);
        chart->setAnimationOptions(QChart::SeriesAnimations);
        QBrush backgroundBrush(QColor(187,93,87,0));
        chart->setBackgroundBrush(backgroundBrush);
        QChartView *chartview=new QChartView(chart);
        chartview->setRenderHint(QPainter::Antialiasing);
        chartview->setFixedSize(ui->label->size());
        chartview->setParent(ui->label);
        ui->label->setStyleSheet("background:transparent; color:white; ");
        ui->label->show();
}


void Publicite::on_pushButton_rechid_clicked()
{
    int IdPublicite = ui->lineEditrechid->text().toInt(); // Récupérer l'identifiant de la publicité à partir du champ de texte

        Entite_pub publiciteObject; // Utilisation de la classe Publicite

        QSqlQueryModel *model = publiciteObject.rechercherid(IdPublicite); // Recherche par identifiant

        if (model->rowCount() == 0)
        {
            QMessageBox::information(this, "Aucune publicité trouvée", "Aucune publicité trouvée pour cet identifiant.");
        }
        else
        {
            ui->tableView_publicite->setModel(model);
        }

}




void Publicite::on_pushButton_3_clicked() //his
{
    //ui->tableView->setCurrentIndex(4);

    QSqlQueryModel* model = new QSqlQueryModel();
    model->setQuery("SELECT * FROM publicitesupprimer");
     ui->tableView_publicite_2->setModel(model);
}

void Publicite::on_tableView_currentChanged(int index)
{
    if(index!=4){ui->tableView_publicite_2->setModel(NULL);}
}

void Publicite::on_pushButton_play_clicked()
{
    VideoPlayer  * videoPlayer = new VideoPlayer();
    videoPlayer->setPath(filePath);
    videoPlayer->show();
}

void Publicite::on_pushButton_addvideo_clicked()
{
    filePath = QFileDialog::getOpenFileName(nullptr, "Select Video", "", "*.AVI");
}

void Publicite::on_tableView_publicite_clicked(const QModelIndex &index)
{

    QAbstractItemModel *model = ui->tableView_publicite->model();
    QModelIndex urlIndex = model->index(index.row(), 5);
    filePath = model->data(urlIndex, Qt::DisplayRole).toString();
    qDebug() << filePath ;

}

void Publicite::on_pushButton_on_clicked()
{
    //A.write_to_arduino("1"); //envoyer 1 à arduino

}

void Publicite::on_pushButton_off_clicked()
{
   // A.write_to_arduino("0");  //envoyer 0 à arduino

}

void Publicite::on_pushButton_plus_clicked()
{
   // A.write_to_arduino("2");   //envoyer 2 à arduino

}

void Publicite::on_pushButton_clicked()
{
    //A.write_to_arduino("3");  //envoyer 3 à arduino

}
