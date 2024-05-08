#include "emissions.h"
#include "ui_emissions.h"
#include "qsubtitles.h"
#include "entite_emission.h"
#include <QApplication>
#include <QMessageBox>
#include <QString>
#include <QPrinter>
#include <QPrintDialog>
#include <QPdfWriter>
#include <QPainter>
#include <QtCharts>
#include <QVBoxLayout>
#include <QComboBox>
#include <QRadioButton>
#include <QPushButton>
#include <QWidget>
#include <QMainWindow>
#include <QPieSeries>
#include <QPieSlice>

Emissions::Emissions(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Emissions)
{
    ui->setupUi(this);
    ui->table_AfficherEmission->setModel(Etmp.afficher());
    on_pushButtonstat_clicked();


    // Initialisation du lecteur vidéo
    Player = new QMediaPlayer();

    ui->pushButton_Play_Pause->setIcon(style()->standardIcon(QStyle::SP_MediaPlay));
    ui->pushButton_Stop->setIcon(style()->standardIcon(QStyle::SP_MediaStop));
    ui->pushButton_Seek_Backward->setIcon(style()->standardIcon(QStyle::SP_MediaSeekBackward));
    ui->pushButton_Seek_Forward->setIcon(style()->standardIcon(QStyle::SP_MediaSeekForward));
    ui->pushButton_Volume->setIcon(style()->standardIcon(QStyle::SP_MediaVolume));
    ui->horizontalSlider_Volume->setMinimum(0);
    ui->horizontalSlider_Volume->setMaximum(100);
    ui->horizontalSlider_Volume->setValue(30);

    Player->setVolume(ui->horizontalSlider_Volume->value());

    connect(Player, &QMediaPlayer::durationChanged, this, &Emissions::durationChanged);
    connect(Player, &QMediaPlayer::positionChanged, this, &Emissions::positionChanged);

    ui->horizontalSlider_Duration->setRange(0, Player->duration() / 1000);

    IS_Pause = false;
    IS_Muted = false;

    //Arduino
    int ret = A.connect_arduino();

    switch(ret)
    {
    case(0):
        qDebug()<< "arduino is available and connected to : "<< A.getarduino_port_name();
        break;
    case(1):
        qDebug()<< "arduino is available but not connected to :" <<A.getarduino_port_name();
        break;
    case(-1):
        qDebug()<< "arduino is not available";
    }
    QObject::connect(A.getserial(),SIGNAL(readyRead()),this,SLOT(update_label()));
}

Emissions::~Emissions()
{
    delete ui;
}
void Emissions::update_label()
{
    data = A.read_from_arduino();

    // Vérifier si les données reçues sont un chiffre de 0 à 9
    if (data >= "0" && data <= "9"){
        QString valeur = ui->lineEditRechercheTableau->text() + data;
        ui->lineEditRechercheTableau->setText(valeur);
    }
    if (data == "UP"){
        int id_emission = ui->lineEditRechercheTableau->text().toInt();
        Entite_emission Etmp;
        QSqlQueryModel *model = Etmp.rechercherParid_emission(id_emission);
        if (model->rowCount() > 0){
            // Si un enregistrement existe, déclencher la fonction pour regarder l'émission
            on_pushButton_2_clicked();
            //A.write_to_arduino("a");
        }
        else{
            //A.write_to_arduino("n");
            QMessageBox::warning(nullptr, QObject::tr("Erreur"),
                                 QObject::tr("L'ID d'émission spécifié n'existe pas dans la base de données. Veuillez vérifier l'ID et réessayer."),QMessageBox::Cancel);
        }
        delete model;
    }
    if (data == "OK"){
        on_pushButton_Play_Pause_clicked();
    }else if (data == "LEFT"){
       // on_pushButton_Seek_Backward_clicked();
        ui->lineEditRechercheTableau->clear();
    }else if (data == "RIGHT"){
        on_pushButton_Seek_Forward_clicked();
    }else if (data == "DOWN"){
        on_pushButton_Volume_clicked();
    }else if (data == "*"){
        on_pushButtonSousTitrage_clicked();
    }else if (data == "#"){
        on_pushButton_3_clicked();
    }else{
        qDebug() << "Unknown button pressed. Data:" << data;
    }

}
void Emissions::updateDuration(qint64 Duration)
{
    Entite_emission Etmp;

    if (Duration || mDuration)
    {
        QTime currentTime((Duration / 3600) % 60, (Duration / 60) % 60, Duration % 60, (Duration * 1000) % 1000);
        QTime totalTime((mDuration / 3600) % 60, (mDuration / 60) % 60, mDuration % 60, (mDuration * 1000) % 1000);

        // Set total time in the database
        Etmp.setTotalTime(totalTime, mVideoFilePath);
        //get the time
        QTime time = Etmp.getTotalTime(mVideoFilePath);
        // Calculate the difference between total time and current time
        int totalTimeInSeconds = time.hour() * 3600 + time.minute() * 60 + time.second();
        int currentTimeInSeconds = currentTime.hour() * 3600 + currentTime.minute() * 60 + currentTime.second();
        int timeDifferenceInSeconds = totalTimeInSeconds - currentTimeInSeconds;

        // Convert time difference back to QTime
        QTime timeDifference = QTime(0, 0).addSecs(timeDifferenceInSeconds);

        // Format the time difference as desired
        QString formattedDifference = timeDifference.toString("hh:mm:ss");

        // Send the formatted time difference to Arduino
        QByteArray dataToSend = formattedDifference.toUtf8();
        qDebug() << "data to send: " << dataToSend;
        A.write_to_arduino(dataToSend);

        // Update UI with current and total time
        QString format = (mDuration > 3600) ? "hh:mm:ss" : "mm:ss";
        ui->label_current_Time->setText(currentTime.toString(format));
        ui->label_Total_Time->setText(totalTime.toString(format));
    }


}
void Emissions::on_pushButton_Ajouter_clicked()
{
    QString id_emission_str = ui->lineEdit_IdEmission->text();
    QString titre=ui->lineEdit_Titre->text();
    QString categorie=ui->comboBoxCategorie->currentText();
    QString realisateur=ui->lineEdit_Realisateur->text();
    QString duree=ui->lineEdit_Duree->text();
    QDate date_emission=ui->dateEdit->date();
    QString description=ui->lineEdit_Description->text();
    QString video=ui->video->text();
    QString soustitrage=ui->soustitrage->text();
    int id_emission = id_emission_str.toInt();

    if (!id_emission_str.isEmpty() && id_emission == 0)
    {
        QMessageBox::warning(nullptr, QObject::tr("Erreur de saisie"),
                             QObject::tr("Veuillez saisir un ID valide (Entier)."),QMessageBox::Cancel);
        return;
    }
    else if (id_emission_str.isEmpty())
    {
        QMessageBox::warning(nullptr, QObject::tr("Champ obligatoire"),
                             QObject::tr("Veuillez saisir un ID"),QMessageBox::Cancel);
        return;
    }
    Entite_emission Etmp;
    if (Etmp.existeId(id_emission))
    {
        QMessageBox::warning(nullptr, QObject::tr("ID existant"),
                             QObject::tr("L'ID de l'émission existe déjà."),QMessageBox::Cancel);
        return;
    }
    if (Etmp.existeTitre(titre))
    {
        QMessageBox::warning(nullptr, QObject::tr("Titre existant"),
                             QObject::tr("Le titre de l'émission existe déjà."),QMessageBox::Cancel);
        return;
    }
    if(titre.isEmpty())
    {
        QMessageBox::warning(nullptr, QObject::tr("Champ obligatoire"),
                             QObject::tr("Veuillez saisir un titre."),QMessageBox::Cancel);
        return;
    }
    if(categorie.isEmpty())
    {
        QMessageBox::warning(nullptr, QObject::tr("Champ obligatoire"),
                             QObject::tr("Veuillez saisir une catégorie."),QMessageBox::Cancel);
        return;
    }
    if(realisateur.isEmpty())
    {
        QMessageBox::warning(nullptr, QObject::tr("Champ obligatoire"),
                             QObject::tr("Veuillez saisir un réalisateur."),QMessageBox::Cancel);
        return;
    }
    if(duree.isEmpty() || !duree.toInt() )
    {
        QMessageBox::warning(nullptr, QObject::tr("Erreur de saisie"),
                             QObject::tr("Veuillez saisir une durée valide(Entier)."),QMessageBox::Cancel);
        return;
    }
    if(description.isEmpty())
    {
        QMessageBox::warning(nullptr, QObject::tr("Champ obligatoire"),
                             QObject::tr("Veuillez saisir une description."),QMessageBox::Cancel);
        return;
    }
    if (date_emission < QDate::currentDate())
    {
        QMessageBox::warning(nullptr, QObject::tr("Date invalide"),
                             QObject::tr("La date que vous avez saisie est antérieure à la date actuelle."),QMessageBox::Cancel);
        return;
    }

    Entite_emission E(id_emission,titre,categorie,realisateur,duree,date_emission,description,video,soustitrage);
    bool test=E.ajouter();

    if(test)
    {
        ui->table_AfficherEmission->setModel(Etmp.afficher());
        QMessageBox::information(nullptr, QObject::tr("Ajout réussi"),
                                 QObject::tr("L'émission a été ajoutée avec succès.\n"), QMessageBox::Cancel);

        // Réinitialiser les champs après l'ajout
        ui->lineEdit_IdEmission->clear();
        ui->lineEdit_Titre->clear();
        ui->lineEdit_Realisateur->clear();
        ui->lineEdit_Duree->clear();
        ui->dateEdit->setDate(QDate::currentDate());
        ui->lineEdit_Description->clear();
        ui->video->clear();
        ui->soustitrage->clear();

        on_pushButtonstat_clicked();

    }
    else
        QMessageBox::critical(nullptr, QObject::tr("Échec de l'ajout"),
                              QObject::tr("L'ajout de l'émission a échoué.\n""Veuillez vérifier les données et réessayer."), QMessageBox::Cancel);
}

void Emissions::on_pushButton_supprimer_clicked()
{
    QString id_emission_str = ui->lineEdit_RechercheIdSup->text();

    bool ok;
    int id_emission = id_emission_str.toInt(&ok);

    if (!ok)
    {
        QMessageBox::warning(nullptr, QObject::tr("ID invalide"),
                             QObject::tr("Veuillez saisir un ID valide (Entier)."),QMessageBox::Cancel);
        return;
    }
    if(id_emission_str.isEmpty())
    {
        QMessageBox::warning(nullptr, QObject::tr("Champ obligatoiret"),
                             QObject::tr("Veuillez saisir un ID pour supprimer une émission."),QMessageBox::Cancel);
        return;
    }

    Entite_emission Etmp;
    if (!Etmp.existeId(id_emission))
    {
        QMessageBox::warning(nullptr, QObject::tr("ID inexistant"),
                             QObject::tr("L'ID de l'émission n'existe pas."),QMessageBox::Cancel);
        return;
    }

    bool test=Etmp.supprimer(id_emission);
    if(test)
    {
        ui->table_AfficherEmission->setModel(Etmp.afficher());
        ui->lineEdit_RechercheIdSup->clear();
        on_pushButtonstat_clicked();
        QMessageBox::information(nullptr, QObject::tr("Suppression réussie"),
                                 QObject::tr("La suppression a été effectuée avec succès."), QMessageBox::Cancel);
    }
    else
        QMessageBox::critical(nullptr, QObject::tr("Échec de la suppression"),
                              QObject::tr("La suppression n'a pas pu être effectuée."), QMessageBox::Cancel);

}

void Emissions::on_pushButtonsuptout_clicked()
{
    Entite_emission E;
    bool isTableEmpty = ui->table_AfficherEmission->model()->rowCount() == 0;
    if (isTableEmpty)
    {
        QMessageBox::warning(nullptr, QObject::tr("Erreur de suppression"),
                             QObject::tr("Le tableau est vide. Aucune émission à supprimer."),QMessageBox::Cancel);
        return;
    }
    bool success = E.supprimerTout();
    if (success)
    {
        ui->table_AfficherEmission->setModel(Etmp.afficher());
        on_pushButtonstat_clicked();
        QMessageBox::information(nullptr, QObject::tr("Suppression réussie"),
                                 QObject::tr("Toutes les émissions ont été supprimées."), QMessageBox::Cancel);
    }
    else
    {
        QMessageBox::critical(nullptr, QObject::tr("Échec de la suppression"),
                              QObject::tr("Une erreur s'est produite lors de la suppression des émissions."), QMessageBox::Cancel);
    }
}

void Emissions::on_pushButtonRechID_clicked()//Modifier
{
    QString id_emission_str = ui->lineEdit_recherID->text();
    if (id_emission_str.isEmpty())
    {
        QMessageBox::warning(nullptr, QObject::tr("Champ obligatoire"),
                             QObject::tr("Veuillez saisir un ID pour rechercher une émission."),QMessageBox::Cancel);
        return;
    }
    bool ok;
    int id_emission = id_emission_str.toInt(&ok);
    if (!ok)
    {
        QMessageBox::warning(nullptr, QObject::tr("Erreur"),
                             QObject::tr("Veuillez saisir un ID valide (Entier)."),QMessageBox::Cancel);
        return;
    }

    Entite_emission Etmp;
    if (!Etmp.existeId(id_emission))
    {
        QMessageBox::warning(nullptr, QObject::tr("ID inexistant"),
                             QObject::tr("L'ID de l'émission n'existe pas."), QMessageBox::Cancel);
        return;
    }
    Entite_emission emission = Etmp.rechercherEmission(id_emission);

    ui->lineEdit_Titre_M->setText(emission.getTitre());
    ui->comboBox_M_2->setCurrentText(emission.getCategorie());
    ui->lineEdit_Realisateur_M->setText(emission.getRealisateur());
    ui->lineEdit_Duree_M->setText(emission.getDuree());
    ui->dateEdit_M->setDate(emission.getDate_emission());
    ui->lineEdit_Description_M->setText(emission.getDescription());
    ui->video_M->setText(emission.getvideo());
    ui->soustitrage_M->setText(emission.getsoustitrage());

    ui->table_AfficherEmission->setModel(Etmp.afficher());

}

void Emissions::on_pushButton_valider_clicked()
{
    QString id_emission_str = ui->lineEdit_recherID->text();
    if(id_emission_str.isEmpty())
    {
        QMessageBox::warning(nullptr, QObject::tr("Champ obligatoire"),
                             QObject::tr("Veuillez saisir un ID pour effectuer la modification."),QMessageBox::Cancel);
        return;
    }

    QString titre=ui->lineEdit_Titre_M->text();
    QString categorie = ui->comboBox_M_2->currentText();
    QString realisateur=ui->lineEdit_Realisateur_M->text();
    QString duree=ui->lineEdit_Duree_M->text();
    QDate date_emission=ui->dateEdit_M->date();
    QString description=ui->lineEdit_Description_M->text();
    QString video=ui->video_M->text();
    QString soustitrage=ui->soustitrage_M->text();

    int id_emission = id_emission_str.toInt();

    if (!id_emission_str.isEmpty() && id_emission == 0)
    {
        QMessageBox::warning(nullptr, QObject::tr("Erreur de saisie"),
                             QObject::tr("Veuillez saisir un ID valide (Entier)."),QMessageBox::Cancel);
        return;
    }
    else if (id_emission_str.isEmpty())
    {
        QMessageBox::warning(nullptr, QObject::tr("Champ obligatoire"),
                             QObject::tr("Veuillez saisir un ID."),QMessageBox::Cancel);
        return;
    }
    if(titre.isEmpty())
    {
        QMessageBox::warning(nullptr, QObject::tr("Champ obligatoire"),
                             QObject::tr("Veuillez saisir un titre."),QMessageBox::Cancel);
        return;
    }
    if(categorie.isEmpty())
    {
        QMessageBox::warning(nullptr, QObject::tr("Champ obligatoire"),
                             QObject::tr("Veuillez saisir une catégorie."),QMessageBox::Cancel);
        return;
    }
    if(realisateur.isEmpty())
    {
        QMessageBox::warning(nullptr, QObject::tr("Champ obligatoire"),
                             QObject::tr("Veuillez saisir un réalisateur."),QMessageBox::Cancel);
        return;
    }
    if(duree.isEmpty() || !duree.toInt() )
    {
        QMessageBox::warning(nullptr, QObject::tr("Champ obligatoire"),
                             QObject::tr("Veuillez saisir une durée valide (Entier)."),QMessageBox::Cancel);
        return;
    }
    if(description.isEmpty())
    {
        QMessageBox::warning(nullptr, QObject::tr("Champ obligatoire"),
                             QObject::tr("Veuillez saisir une description."),QMessageBox::Cancel);
        return;
    }

    Entite_emission Etmp;
    // Modifier l'émission dans la base de données ou dans la classe Emissions
    bool success = Etmp.modifier(id_emission, titre, categorie, realisateur, duree, date_emission, description, video, soustitrage);

    if (success)
    {
        ui->table_AfficherEmission->setModel(Etmp.afficher());
        on_pushButtonstat_clicked();
        QMessageBox::information(nullptr, QObject::tr("Modification réussie"),
                                 QObject::tr("La modification a été effectuée avec succès."), QMessageBox::Cancel);

        ui->lineEdit_recherID->clear();
        ui->lineEdit_Titre_M->clear();
        ui->lineEdit_Realisateur_M->clear();
        ui->lineEdit_Duree_M->clear();
        ui->dateEdit_M->setDate(QDate::currentDate());
        ui->lineEdit_Description_M->clear();
        ui->video_M->clear();
        ui->soustitrage_M->clear();
    }
    else
    {
        QMessageBox::critical(nullptr, QObject::tr("Modification échouée"),
                              QObject::tr("La modification n'a pas pu être effectuée."), QMessageBox::Cancel);
    }
}

void Emissions::on_pushButton_AnnulerModifier_clicked()
{
    if (!ui->lineEdit_recherID->text().isEmpty() ||
            !ui->lineEdit_Titre_M->text().isEmpty() ||
            !ui->lineEdit_Realisateur_M->text().isEmpty() ||
            !ui->lineEdit_Duree_M->text().isEmpty() ||
            !ui->lineEdit_Description_M->text().isEmpty() ||
            !ui->video_M->text().isEmpty()||
            !ui->soustitrage_M->text().isEmpty())
    {
        QMessageBox::StandardButton reply;
        reply = QMessageBox::question(this, "Confirmation", "Êtes-vous sûr de vouloir quitter sans enregistrer?",
                                      QMessageBox::Yes | QMessageBox::No);
        if (reply == QMessageBox::Yes)
        {
            ui->lineEdit_recherID->clear();
            ui->lineEdit_Titre_M->clear();
            ui->lineEdit_Realisateur_M->clear();
            ui->lineEdit_Duree_M->clear();
            ui->dateEdit_M->setDate(QDate::currentDate());
            ui->lineEdit_Description_M->clear();
            ui->video_M->clear();
            ui->soustitrage_M->clear();
        }
    }
}

void Emissions::on_pushButton_AnnulerAjouter_clicked()
{
    if (!ui->lineEdit_IdEmission->text().isEmpty() ||
            !ui->lineEdit_Titre->text().isEmpty() ||
            !ui->lineEdit_Realisateur->text().isEmpty() ||
            !ui->lineEdit_Duree->text().isEmpty() ||
            !ui->lineEdit_Description->text().isEmpty()||
            !ui->video->text().isEmpty()||
            !ui->soustitrage->text().isEmpty())
    {

        QMessageBox::StandardButton reply;
        reply = QMessageBox::question(this, "Confirmation", "Êtes-vous sûr de vouloir quitter sans enregistrer?",
                                      QMessageBox::Yes | QMessageBox::No);
        if (reply == QMessageBox::Yes)
        {
            ui->lineEdit_IdEmission->clear();
            ui->lineEdit_Titre->clear();
            ui->lineEdit_Realisateur->clear();
            ui->lineEdit_Duree->clear();
            ui->dateEdit->setDate(QDate::currentDate());
            ui->lineEdit_Description->clear();
            ui->video->clear();
            ui->soustitrage->clear();
        }
    }
}

void Emissions::on_pushButtonTri_clicked()
{
    QSortFilterProxyModel *proxyModel = new QSortFilterProxyModel(this);
    proxyModel->setSourceModel(ui->table_AfficherEmission->model());

    // Récupérer le critère de tri sélectionné
    QString critereTri = ui->comboBoxTri->currentText();

    // Déterminer l'ordre de tri (croissant ou décroissant)
    Qt::SortOrder ordreTri = (ui->radioButtonCroissant->isChecked()) ? Qt::AscendingOrder : Qt::DescendingOrder;

    // Définir le numéro de colonne à trier
    int columnToSort = -1; // Colonne à trier (-1 par défaut)

    if (critereTri == "ID")
    {
        columnToSort = 0; // Colonne ID
    }
    else if (critereTri == "Date")
    {
        columnToSort = 1; // Colonne Date
    }
    else if (critereTri == "Categorie")
    {
        columnToSort = 2; // Colonne Catégorie
    }
    else if (critereTri == "Duree")
    {
        columnToSort = 3; // Colonne Durée
    }

    // Appliquer le tri sur le proxy model
    if (columnToSort != -1)
    {
        proxyModel->sort(columnToSort, ordreTri);
    }

    // Appliquer le proxy model à la table view
    ui->table_AfficherEmission->setModel(proxyModel);
}

void Emissions::on_pushButtonPdf_clicked()
{
    QPrinter printer;
    QPrintDialog dialog(&printer, this);

    QPdfWriter pdf("C:/Users/user/Desktop/SmartTV/Emissions.pdf");
    QPainter painter(&pdf);

    // Styles
    QFont titleFont("Times New Roman", 30);
    QFont headerFont("Times New Roman", 10); // Augmenter la taille de la police pour les en-têtes
    QFont dataFont("Arial", 7); // Augmenter la taille de la police pour les données

    // Dessiner le logo
    QPixmap logo("C:/Users/user/Desktop/SmartTV/Logo.png");
    painter.drawPixmap(20, 20, logo);

    // Dessiner le titre
    painter.setFont(titleFont);
    painter.setPen(Qt::black); // Couleur du texte
    painter.drawText(400, 400, "STREAMFLIX"); // Remplacez par le nom de votre application
    painter.drawText(2900, 1800, "LISTE DES EMISSIONS");

    // Dessiner les bordures
    painter.setPen(Qt::black); // Couleur des bordures

    // Dessiner les en-têtes de colonne
    QStringList headers = {"IdEmission", "Titre", "Catégorie", "Réalisateur", "Date Emission", "Durée", "Description"};
    painter.setFont(headerFont);
    int x = 300; // Position horizontale initiale
    int y = 3300; // Position verticale
    int columnWidth = 1300; // Largeur de chaque colonne

    for (int col = 0; col < headers.size(); ++col)
    {
        // Dessiner le rectangle autour de l'en-tête
        painter.drawRect(x, y, columnWidth, 150); // Augmenter la hauteur de l'en-tête

        // Dessiner le texte centré dans la colonne
        painter.drawText(x, y, columnWidth, 150, Qt::AlignCenter, headers[col]);

        // Déplacer la position horizontale pour la prochaine colonne
        x += columnWidth;
    }

    // Dessiner les données de la table
    painter.setFont(dataFont);
    x = 300; // Réinitialiser la position horizontale
    y = 3450; // Définir la position verticale pour les données

    Entite_emission Etmp;
    QSqlQueryModel *model = Etmp.afficher(); // Récupérer le modèle de données
    for (int row = 0; row < model->rowCount(); ++row)
    {
        x = 300; // Réinitialiser la position horizontale pour chaque ligne
        for (int col = 0; col < model->columnCount(); ++col)
        {
            // Dessiner le rectangle autour de la cellule
            painter.drawRect(x, y, columnWidth, 300); // Augmenter la hauteur de la cellule

            // Récupérer les données de la cellule
            QModelIndex index = model->index(row, col);
            QString data = model->data(index).toString();

            // Dessiner le texte centré dans la cellule
            painter.drawText(x, y, columnWidth, 150, Qt::AlignCenter, data);

            // Déplacer la position horizontale pour la prochaine cellule
            x += columnWidth;
        }
        // Déplacer la position verticale pour la prochaine ligne
        y += 160; // Augmenter l'espacement entre les lignes
    }

    QMessageBox::information(this, tr("PDF Enregistré!"), tr("PDF Enregistré!.\n" "Click Ok to exit."), QMessageBox::Ok);
}
float Emissions::countType(QString ch)
{
    QSqlQueryModel* searchModel = new QSqlQueryModel();
    searchModel->setQuery("SELECT * FROM Entite_emission WHERE categorie LIKE '%" + ch + "%'");

    return searchModel->rowCount() ;
}
void Emissions::on_pushButtonstat_clicked()
{
    // Effacer le contenu précédent du QLabel
    QList<QWidget*> childWidgets = ui->label_statistiques->findChildren<QWidget*>();
    for (QWidget* childWidget : childWidgets)
    {
        childWidget->deleteLater();
    }
    ui->label_statistiques->clear();
    ui->label_statistiques->hide();

    // Initialiser les variables pour les statistiques
    float s0 = 0, s1 = 0, s2 = 0, s3 = 0, s4 = 0, s5 = 0, s6 = 0, s7 = 0;

    // Calculer les statistiques pour chaque catégorie sélectionnée
    s0 = countType("Documentaire");
    s1 = countType("Action");
    s2 = countType("Drame");
    s3 = countType("Comedie");
    s4 = countType("Divertissement");
    s5 = countType("Information");
    s6 = countType("Sport");
    s7 = countType("Voyage");

    // Calculer le total des émissions
    float stat = s0 + s1 + s2 + s3 + s4 + s5 + s6 + s7;

    // Calculer les pourcentages
    float x = (stat != 0) ? (s0 * 100) / stat : 0.0;
    float y = (stat != 0) ? (s1 * 100) / stat : 0.0;
    float z = (stat != 0) ? (s2 * 100) / stat : 0.0;
    float d = (stat != 0) ? (s3 * 100) / stat : 0.0;
    float e = (stat != 0) ? (s4 * 100) / stat : 0.0;
    float f = (stat != 0) ? (s5 * 100) / stat : 0.0;
    float g = (stat != 0) ? (s6 * 100) / stat : 0.0;
    float h = (stat != 0) ? (s7 * 100) / stat : 0.0;

    // Construire les labels des parts du graphique
    QString ch1 = QString("Documentaire %1%").arg(x);
    QString ch2 = QString("Action %1%").arg(y);
    QString ch3 = QString("Drame %1%").arg(z);
    QString ch4 = QString("Comedie %1%").arg(d);
    QString ch5 = QString("Divertissement %1%").arg(e);
    QString ch6 = QString("Information %1%").arg(f);
    QString ch7 = QString("Sport %1%").arg(g);
    QString ch8 = QString("Voyage %1%").arg(h);

    // Créer la série pour le graphique
    QPieSeries *series = new QPieSeries();
    series->setHoleSize(0.35);

    // Ajouter les parts au graphique
    if (x > 0)
    {
        QPieSlice *slice = series->append(ch1, x);
        slice->setLabelVisible();
        slice->setLabelColor(QColor(Qt::black));
        slice->setBrush(QColor(85, 170, 0));
    }
    if (y > 0)
    {
        QPieSlice *slice1 = series->append(ch2, y);
        slice1->setLabelVisible();
        slice1->setLabelColor(QColor(Qt::black));
        slice1->setBrush(QColor(68, 137, 206));
    }
    if (z > 0)
    {
        QPieSlice *slice2 = series->append(ch3, z);
        slice2->setLabelVisible();
        slice2->setLabelColor(QColor(Qt::black));
        slice2->setBrush(QColor(255, 236, 26));
    }
    if (d > 0)
    {
        QPieSlice *slice3 = series->append(ch4, d);
        slice3->setLabelVisible();
        slice3->setLabelColor(QColor(Qt::black));
        slice3->setBrush(QColor(0, 108, 158));
    }
    if (e > 0)
    {
        QPieSlice *slice4 = series->append(ch5, e);
        slice4->setLabelVisible();
        slice4->setLabelColor(QColor(Qt::black));
        slice4->setBrush(QColor(170, 0, 127)); // Divertissement
    }
    if (f > 0)
    {
        QPieSlice *slice5 = series->append(ch6, f);
        slice5->setLabelVisible();
        slice5->setLabelColor(QColor(Qt::black));
        slice5->setBrush(QColor(0, 0, 221)); // Information
    }
    if (g > 0)
    {
        QPieSlice *slice6 = series->append(ch7, g);
        slice6->setLabelVisible();
        slice6->setLabelColor(QColor(Qt::black));
        slice6->setBrush(QColor(0, 180, 208)); // Sport
    }
    if (h > 0)
    {
        QPieSlice *slice7 = series->append(ch8, h);
        slice7->setLabelVisible();
        slice7->setLabelColor(QColor(Qt::black));
        slice7->setBrush(QColor(229, 153, 0)); // Voyage
    }

    // Créer le graphique
    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->setAnimationOptions(QChart::SeriesAnimations);
    QBrush backgroundBrush(QColor(187, 93, 87, 0));
    chart->setBackgroundBrush(backgroundBrush);

    // Créer la vue du graphique
    QChartView *chartview = new QChartView(chart);
    chartview->setRenderHint(QPainter::Antialiasing);
    chartview->setFixedSize(ui->label_statistiques->size());
    chartview->setParent(ui->label_statistiques);
    ui->label_statistiques->setStyleSheet("background:transparent; color:white; ");
    ui->label_statistiques->show();

}
void Emissions::setupUI()
{
    mainLayout = new QVBoxLayout(this); // Use this as the parent widget

    comboBoxTri = new QComboBox;
    comboBoxTri->addItem("ID");
    comboBoxTri->addItem("Date");
    comboBoxTri->addItem("Categorie");
    comboBoxTri->addItem("Duree");

    radioButtonCroissant = new QRadioButton("Croissant");
    radioButtonDecroissant = new QRadioButton("Décroissant");
    radioButtonCroissant->setChecked(true);

    pushButtonTri = new QPushButton("Trier");

    mainLayout->addWidget(comboBoxTri);
    mainLayout->addWidget(radioButtonCroissant);
    mainLayout->addWidget(radioButtonDecroissant);
    mainLayout->addWidget(pushButtonTri);

    // No need to set central widget since Emission is not a QMainWindow

    connect(pushButtonTri, &QPushButton::clicked, this, &Emissions::on_pushButtonTri_clicked);
    connect(comboBoxTri, QOverload<int>::of(&QComboBox::activated), this, &Emissions::on_comboBoxTri_activated);
    connect(radioButtonCroissant, &QRadioButton::toggled, this, &Emissions::on_radioButtonCroissant_toggled);
    connect(radioButtonDecroissant, &QRadioButton::toggled, this, &Emissions::on_radioButtonCroissant_toggled);
}
void Emissions::on_comboBoxTri_activated(int index)
{
    Q_UNUSED(index);
    // Mettre à jour le critère de tri sélectionné
}

void Emissions::on_radioButtonCroissant_toggled(bool checked)
{
    Q_UNUSED(checked);
    // Mettre à jour l'ordre de tri sélectionné
}

void Emissions::on_pushButtonValidier_recherche_clicked()
{
    Entite_emission Etmp;
    QString critere = ui->comboBoxRecherche->currentText();
    QString valeur = ui->lineEditRechercheTableau->text();

    QSqlQueryModel *model = new QSqlQueryModel();

    if (critere == "Id_Emission")
    {
        // Convertir la valeur en entier
        int id_emission = valeur.toInt();
        model = Etmp.rechercherParid_emission(id_emission);
    }
    else if (critere == "Titre")
    {
        model = Etmp.rechercherParTitre(valeur);
    }
    else if (critere == "Categorie")
    {
        model = Etmp.rechercherParCategorie(valeur);
    }
    else if (critere == "Realisateur")
    {
        model = Etmp.rechercherParrealisateur(valeur);
    }
    else if (critere == "Duree")
    {
        // Convertir la valeur en entier
        int duree = valeur.toInt();
        model = Etmp.rechercherParduree(QString::number(duree));

    }
    else if (critere == "Date_emission")
    {
        // Convertir la date saisie par l'utilisateur en objet QDate
        QDate date = QDate::fromString(valeur, "dd-MM-yyyy");
        if (date.isValid())
        {
            // Exécuter la recherche par date
            model = Etmp.rechercherPardate_emission(date);
        }
        else
        {
            QMessageBox::warning(this, "Format de date invalide", "Veuillez entrer une date valide dans le format DD-MM-YYYY.");
            return; // Arrêter l'exécution de la fonction en cas de date invalide
        }
    }

    if (model->rowCount() > 0)
    {
        ui->table_AfficherEmission->setModel(model);
    }
    else
    {
        QMessageBox::information(this, "Résultat de la recherche", "Aucun résultat trouvé.");
        // Utilisez simplement la fonction d'affichage pour réinitialiser la table
        ui->table_AfficherEmission->setModel(Etmp.afficher());
    }
}

void Emissions::on_pushButtonCSV_clicked()
{
    QString fileName = QFileDialog::getSaveFileName(this, tr("Save File"),
                       "emissions.csv",
                       tr("CSV (.csv);;All Files ()"));
    if (fileName.isEmpty())
        return;

    QFile file(fileName);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        QMessageBox::warning(this, tr("Unable to open file"),
                             file.errorString());
        return;
    }
    QTextStream out(&file);
    out << "IdEmission" << ";" << "Titre" << ";" << "Categorie" << ";" << "Realisateur" << ";" << "DateEmission" << ";" << "Duree" << ";" << "Description" << "\n";
    QSqlQuery query("SELECT * FROM Entite_emission");
    while (query.next())
    {
        out << query.value("IdEmission").toString() << ";"
            << query.value("Titre").toString() << ";"
            << query.value("Categorie").toString() << ";"
            << query.value("Realisateur").toString() << ";"
            << query.value("DateEmission").toDate().toString("dd-MM-yyyy") << ";"
            << query.value("Duree").toString() << ";"
            << query.value("Description").toString() << "\n";
    }
    file.close();

}
void Emissions::on_pushButtonImprimer_clicked()
{
    QPrinter printer;
    printer.setPrinterName ("Le Nom De l'imprimante");
    QPrintDialog dialog(&printer,this);
    if (dialog.exec()== QDialog::Rejected)return;
    ui->table_AfficherEmission->render(&printer);
}

void Emissions::on_pushButton_clicked() //actualiser
{
    ui->table_AfficherEmission->setModel(Etmp.afficher());
    ui->lineEditRechercheTableau->clear();
}

void Emissions::on_pushButton_insertVideo_clicked()
{
    QString filePath = QFileDialog::getOpenFileName(this, tr("Select Video File"),"", tr("Video Files (*.mp4 *.avi);;All Files (*)"));
    if (!filePath.isEmpty())
    {
        ui->video->setText(filePath);
    }
}
void Emissions::on_pushButton_soustitrage_clicked()
{
    QString filePath = QFileDialog::getOpenFileName(this, tr("Select Subtitle File"), "", tr("Subtitle Files (*.srt);;All Files (*)"));
    if (!filePath.isEmpty())
    {
        ui->soustitrage->setText(filePath);
    }
}
void Emissions::on_pushButton_insertVideo_2_clicked()
{
    QString filePath = QFileDialog::getOpenFileName(this, tr("Select Video File"),"", tr("Video Files (*.mp4 *.avi);;All Files (*)"));
    if (!filePath.isEmpty())
    {
        ui->video_M->setText(filePath);
    }
}
void Emissions::on_pushButton_soustitrage_2_clicked()
{
    QString filePath = QFileDialog::getOpenFileName(this, tr("Select Subtitle File"), "", tr("Subtitle Files (*.srt);;All Files (*)"));
    if (!filePath.isEmpty())
    {
        ui->soustitrage_M->setText(filePath);
    }
}

void Emissions::on_pushButton_2_clicked()
{
    // Remplacez 5 par l'index de votre onglet "Lecteur Video"
    ui->tabWidget_->setCurrentIndex(5);
}

void Emissions::durationChanged(qint64 duration)
{
    mDuration = duration / 1000;
    ui->horizontalSlider_Duration->setMaximum(mDuration);
}
void Emissions::positionChanged(qint64 duration)
{
    static qint64 lastPosition = 0;
    static QTime lastCallTime = QTime::currentTime();

    qint64 currentPosition = duration / 1000;
    QTime currentTime = QTime::currentTime();

    // Vérifier si un certain temps s'est écoulé depuis le dernier appel
    int elapsedMilliseconds = lastCallTime.msecsTo(currentTime);
    if (elapsedMilliseconds < 500)   // Limiter la fréquence des appels à 500 millisecondes
    {
        return;
    }
    qDebug() << "positionChanged called";

    // Votre logique de mise à jour de l'interface utilisateur ici...
    lastPosition = currentPosition;
    lastCallTime = currentTime;

    //To Do
    /*if (!ui->horizontalSlider_Duration->isSliderDown())
      {
           ui->horizontalSlider_Duration->setValue(duration / 1000);
      }*/
    updateDuration(duration / 1000);
}


void Emissions::on_pushButton_Seek_Backward_clicked()
{
    if (ui->horizontalSlider_Duration->value() > 20)
    {
        ui->horizontalSlider_Duration->setValue(ui->horizontalSlider_Duration->value() - 20);
        Player->setPosition(ui->horizontalSlider_Duration->value() * 1000);
    }
}
void Emissions::on_pushButton_Play_Pause_clicked()
{
    if (IS_Pause == true)
    {
        IS_Pause = false;
        Player->play();
        ui->pushButton_Play_Pause->setIcon(style()->standardIcon(QStyle::SP_MediaPause));
    }
    else
    {
        IS_Pause = true;
        Player->pause();
        ui->pushButton_Play_Pause->setIcon(style()->standardIcon(QStyle::SP_MediaPlay));
    }
}
void Emissions::on_pushButton_Stop_clicked()
{
    Player->stop();
}
void Emissions::on_pushButton_Seek_Forward_clicked()
{
    if (ui->horizontalSlider_Duration->value() + 20 < ui->horizontalSlider_Duration->maximum())
    {
        ui->horizontalSlider_Duration->setValue(ui->horizontalSlider_Duration->value() + 20);
        Player->setPosition(ui->horizontalSlider_Duration->value() * 1000);
    }
}
void Emissions::on_pushButtonSousTitrage_clicked()
{
    ui->labelSousTitre->setVisible(!ui->labelSousTitre->isVisible());
}
void Emissions::on_pushButton_Volume_clicked()
{
    if (IS_Muted == false)
    {
        IS_Muted = true;
        ui->pushButton_Volume->setIcon(style()->standardIcon(QStyle::SP_MediaVolumeMuted));
        Player->setMuted(true);
    }
    else
    {
        IS_Muted = false;
        ui->pushButton_Volume->setIcon(style()->standardIcon(QStyle::SP_MediaVolume));
        Player->setMuted(false);
    }
}
void Emissions::on_horizontalSlider_Duration_valueChanged(int value)
{
    Player->setPosition(value * 1000);
}
void Emissions::on_horizontalSlider_Volume_valueChanged(int value)
{
    Player->setVolume(value);
}
void Emissions::on_pushButton_3_clicked() //open
{
    QString FileName = QFileDialog::getOpenFileName(this, tr("Select Video File"), "", tr("Video Files (*.mp4 *.avi);;All Files (*)"));
    if (!FileName.isEmpty())
    {
        QString subtitleFileName = QFileDialog::getOpenFileName(this, tr("Select Subtitle File"), "", tr("Subtitle Files (*.srt);;All Files (*)"));
        if (!subtitleFileName.isEmpty())
        {
            mVideoFilePath = FileName;
            QDir appDir = QCoreApplication::applicationDirPath();
            QString videoFilePath = appDir.absoluteFilePath(FileName);
            QString subtitleFilePath = appDir.absoluteFilePath(subtitleFileName);

            Video = new QVideoWidget();
            Video->setGeometry(5, 5, ui->groupBox_video->width() - 10, ui->groupBox_video->height() - 10);
            Video->setParent(ui->groupBox_video);
            Player->setVideoOutput(Video);

            // Charger le fichier vidéo
            Player->setMedia(QUrl::fromLocalFile(videoFilePath));

            // Charger les sous-titres
            QSubtitles* subtitles = new QSubtitles(subtitleFilePath);
            connect(Player, &QMediaPlayer::positionChanged, subtitles, &QSubtitles::updatePosition);

            // Afficher les sous-titres dans labelSousTitre
            connect(subtitles, &QSubtitles::subtitleChanged, ui->labelSousTitre, &QLabel::setText);

            ui->labelSousTitre->setStyleSheet("QLabel { background-color : rgba(0, 0, 0, 100); color : white; padding: 5px; }");
            ui->labelSousTitre->setAlignment(Qt::AlignCenter);

            Video->setVisible(true);
            Video->show();

            // Ajout de la fonctionnalité de sous-titrage via un bouton
            QPushButton *pushButton_Subtitle = new QPushButton("Toggle Subtitles", this);
            pushButton_Subtitle->setGeometry(10, 10, 120, 30);
            connect(pushButton_Subtitle, &QPushButton::clicked, this, &Emissions::on_pushButtonSousTitrage_clicked);
        }
    }
}
