#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "emissions.h"
#include <QApplication>
#include <QMessageBox>
#include <QString>
#include <QPrinter>
#include <QPrintDialog>
#include <QPdfWriter>
#include <QPainter>



MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    on_pushButtonRef_clicked();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_Ajouter_clicked()
{
    QString id_emission_str = ui->lineEdit_IdEmission->text();
    QString titre=ui->lineEdit_Titre->text();
    QString categorie=ui->comboBoxCategorie->currentText();
   // QString categorie=ui->lineEdit_Categorie->text();

    QString realisateur=ui->lineEdit_Realisateur->text();
    QString duree=ui->lineEdit_Duree->text();
    QDate date_emission=ui->dateEdit->date();
    QString description=ui->lineEdit_Description->text();

    int id_emission = id_emission_str.toInt();

    // Vérifier si l'ID de l'émission est un entier
    if (!id_emission_str.isEmpty() && id_emission == 0)
    {
        QMessageBox::warning(nullptr, QObject::tr("Erreur de saisie"),
                             QObject::tr("Veuillez saisir un ID valide (Entier)."),QMessageBox::Cancel);
        return;
    }
    // Vérifier si l'ID de l'émission est vide
    else if (id_emission_str.isEmpty())
    {
        QMessageBox::warning(nullptr, QObject::tr("Champ obligatoire"),
                             QObject::tr("Veuillez saisir un ID"),QMessageBox::Cancel);
        return;
    }

    // Vérifier si l'ID ou le titre de l'émission existe déjà
    Emissions Etmp;
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

    // Vérifier si le titre est vide
    if(titre.isEmpty())
    {
        QMessageBox::warning(nullptr, QObject::tr("Champ obligatoire"),
                             QObject::tr("Veuillez saisir un titre."),QMessageBox::Cancel);
        return;
    }

    // Vérifier si la catégorie est vide
    if(categorie.isEmpty())
    {
        QMessageBox::warning(nullptr, QObject::tr("Champ obligatoire"),
                             QObject::tr("Veuillez saisir une catégorie."),QMessageBox::Cancel);
        return;
    }

    // Vérifier si le réalisateur est vide
    if(realisateur.isEmpty())
    {
        QMessageBox::warning(nullptr, QObject::tr("Champ obligatoire"),
                             QObject::tr("Veuillez saisir un réalisateur."),QMessageBox::Cancel);
        return;
    }

    // Vérifier si la durée est vide ou non un entier
    if(duree.isEmpty() || !duree.toInt() )
    {
        QMessageBox::warning(nullptr, QObject::tr("Erreur de saisie"),
                             QObject::tr("Veuillez saisir une durée valide(Entier)."),QMessageBox::Cancel);
        return;
    }

    // Vérifier si la description est vide
    if(description.isEmpty())
    {
        QMessageBox::warning(nullptr, QObject::tr("Champ obligatoire"),
                             QObject::tr("Veuillez saisir une description."),QMessageBox::Cancel);
        return;
    }
    // Vérifier si la date est antérieure à la date actuelle
    if (date_emission < QDate::currentDate())
    {
        QMessageBox::warning(nullptr, QObject::tr("Date invalide"),
                             QObject::tr("La date que vous avez saisie est antérieure à la date actuelle."),QMessageBox::Cancel);
        return;
    }

    Emissions E(id_emission,titre,categorie,realisateur,duree,date_emission,description);
    bool test=E.ajouter();

    if(test)
    {
        ui->table_AfficherEmission->setModel(Etmp.afficher());
        QMessageBox::information(nullptr, QObject::tr("Ajout réussi"),
                                 QObject::tr("L'émission a été ajoutée avec succès.\n"), QMessageBox::Cancel);

        // Réinitialiser les champs après l'ajout
        ui->lineEdit_IdEmission->clear();
        ui->lineEdit_Titre->clear();
        //ui->lineEdit_Categorie->clear();
        ui->lineEdit_Realisateur->clear();
        ui->lineEdit_Duree->clear();
        ui->dateEdit->setDate(QDate::currentDate());
        ui->lineEdit_Description->clear();

    }
    else
        QMessageBox::critical(nullptr, QObject::tr("Échec de l'ajout"),
                              QObject::tr("L'ajout de l'émission a échoué.\n"
                                          "Veuillez vérifier les données et réessayer."), QMessageBox::Cancel);
}

void MainWindow::on_pushButton_supprimer_clicked()
{
    QString id_emission_str = ui->lineEdit_RechercheIdSup->text();
    bool ok;
    int id_emission = id_emission_str.toInt(&ok);

    // Vérifier si l'ID est un entier
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

    // int id_emission=ui->lineEdit_RechercheIdSup->text().toInt();
    Emissions Etmp;

    // Vérifier si l'ID de l'émission existe
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
        QMessageBox::information(nullptr, QObject::tr("Suppression réussie"),
                                 QObject::tr("La suppression a été effectuée avec succès."), QMessageBox::Cancel);

    }
    else
        QMessageBox::critical(nullptr, QObject::tr("Échec de la suppression"),
                              QObject::tr("La suppression n'a pas pu être effectuée."), QMessageBox::Cancel);

}

void MainWindow::on_pushButton_Modifier_clicked()
{
}


void MainWindow::on_pushButtonRecherche_clicked()
{

}

void MainWindow::on_pushButtonRech_clicked()
{

}

void MainWindow::on_pushButtonsuptout_clicked()
{
    Emissions E;
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
        QMessageBox::information(nullptr, QObject::tr("Suppression réussie"),
                                 QObject::tr("Toutes les émissions ont été supprimées."), QMessageBox::Cancel);
    }
    else
    {
        QMessageBox::critical(nullptr, QObject::tr("Échec de la suppression"),
                              QObject::tr("Une erreur s'est produite lors de la suppression des émissions."), QMessageBox::Cancel);
    }
}

void MainWindow::on_pushButton_rechercher_Id_clicked()
{

}

void MainWindow::on_pushButtonRechID_clicked()
{
    // int id_emission = ui->lineEdit_recherID->text().toInt();
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
    // Créer une instance de la classe Emissions
    Emissions Etmp;
    if (!Etmp.existeId(id_emission))
    {
        QMessageBox::warning(nullptr, QObject::tr("ID inexistant"),
                             QObject::tr("L'ID de l'émission n'existe pas."), QMessageBox::Cancel);
        return;
    }

    // Utiliser la fonction rechercherEmission pour obtenir les détails de l'émission
    Emissions emission = Etmp.rechercherEmission(id_emission);

    // Mettre à jour les champs de l'interface graphique avec les détails de l'émission trouvée
    ui->lineEdit_Titre_M->setText(emission.getTitre());
    //ui->lineEdit_Categorie_M->setText(emission.getCategorie());
    ui->comboBox_M_2->setCurrentText(emission.getCategorie());
    ui->lineEdit_Realisateur_M->setText(emission.getRealisateur());
    ui->lineEdit_Duree_M->setText(emission.getDuree());
    ui->dateEdit_M->setDate(emission.getDate_emission());
    ui->lineEdit_Description_M->setText(emission.getDescription());

    // Mettre à jour le tableau affichant les émissions
    ui->table_AfficherEmission->setModel(Etmp.afficher());

}

void MainWindow::on_pushButton_valider_clicked()
{
    QString id_emission_str = ui->lineEdit_recherID->text();
        if(id_emission_str.isEmpty())
        {
            QMessageBox::warning(nullptr, QObject::tr("Champ obligatoire"),
                                 QObject::tr("Veuillez saisir un ID pour effectuer la modification."),QMessageBox::Cancel);
            return;
        }
    //QString id_emission_str = ui->lineEdit_recherID->text();
    QString titre=ui->lineEdit_Titre_M->text();
    QString categorie = ui->comboBox_M_2->currentText();
    QString realisateur=ui->lineEdit_Realisateur_M->text();
    QString duree=ui->lineEdit_Duree_M->text();
    QDate date_emission=ui->dateEdit_M->date();
    QString description=ui->lineEdit_Description_M->text();

    int id_emission = id_emission_str.toInt();

    // Vérifier si l'ID de l'émission est un entier
    if (!id_emission_str.isEmpty() && id_emission == 0)
    {
        QMessageBox::warning(nullptr, QObject::tr("Erreur de saisie"),
                             QObject::tr("Veuillez saisir un ID valide (Entier)."),QMessageBox::Cancel);
        return;
    }
    // Vérifier si l'ID de l'émission est vide
    else if (id_emission_str.isEmpty())
    {
        QMessageBox::warning(nullptr, QObject::tr("Champ obligatoire"),
                             QObject::tr("Veuillez saisir un ID."),QMessageBox::Cancel);
        return;
    }

    // Vérifier si le titre est vide
    if(titre.isEmpty())
    {
        QMessageBox::warning(nullptr, QObject::tr("Champ obligatoire"),
                             QObject::tr("Veuillez saisir un titre."),QMessageBox::Cancel);
        return;
    }

    // Vérifier si la catégorie est vide
    if(categorie.isEmpty())
    {
        QMessageBox::warning(nullptr, QObject::tr("Champ obligatoire"),
                             QObject::tr("Veuillez saisir une catégorie."),QMessageBox::Cancel);
        return;
    }

    // Vérifier si le réalisateur est vide
    if(realisateur.isEmpty())
    {
        QMessageBox::warning(nullptr, QObject::tr("Champ obligatoire"),
                             QObject::tr("Veuillez saisir un réalisateur."),QMessageBox::Cancel);
        return;
    }

    // Vérifier si la durée est vide ou non un entier
    if(duree.isEmpty() || !duree.toInt() )
    {
        QMessageBox::warning(nullptr, QObject::tr("Champ obligatoire"),
                             QObject::tr("Veuillez saisir une durée valide (Entier)."),QMessageBox::Cancel);
        return;
    }

    // Vérifier si la description est vide
    if(description.isEmpty())
    {
        QMessageBox::warning(nullptr, QObject::tr("Champ obligatoire"),
                             QObject::tr("Veuillez saisir une description."),QMessageBox::Cancel);
        return;
    }

    // Créer une instance de la classe Emissions
    Emissions Etmp;

    // Modifier l'émission dans la base de données ou dans la classe Emissions
    bool success = Etmp.modifier(id_emission, titre, categorie, realisateur, duree, date_emission, description);

    if (success)
    {
        // Mettre à jour le tableau affichant les émissions
        ui->table_AfficherEmission->setModel(Etmp.afficher());

        QMessageBox::information(nullptr, QObject::tr("Modification réussie"),
                                 QObject::tr("La modification a été effectuée avec succès."), QMessageBox::Cancel);

        // Réinitialiser les champs après la modification
        ui->lineEdit_recherID->clear();
        ui->lineEdit_Titre_M->clear();
        //ui->lineEdit_Categorie_M->clear();
        ui->lineEdit_Realisateur_M->clear();
        ui->lineEdit_Duree_M->clear();
        ui->dateEdit_M->setDate(QDate::currentDate());
        ui->lineEdit_Description_M->clear();
    }
    else
    {
        QMessageBox::critical(nullptr, QObject::tr("Modification échouée"),
                              QObject::tr("La modification n'a pas pu être effectuée."), QMessageBox::Cancel);
    }
}



void MainWindow::on_pushButton_regarder_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this,tr("Select Video File"),"",tr("AVI Files (*.avi)"));

    QMediaPlayer *player = new QMediaPlayer();
    QVideoWidget *video = new QVideoWidget();

    video->setGeometry(20, 20, 640, 480);

    player->setVideoOutput(video);
    player->setMedia(QUrl::fromLocalFile(fileName));

    video->show();
    player->play();

}

void MainWindow::on_pushButton_QuitterAjouter_clicked()
{
    if (!ui->lineEdit_IdEmission->text().isEmpty() ||
        !ui->lineEdit_Titre->text().isEmpty() ||
        !ui->lineEdit_Realisateur->text().isEmpty() ||
        !ui->lineEdit_Duree->text().isEmpty() ||
        !ui->lineEdit_Description->text().isEmpty())
    {

        QMessageBox::StandardButton reply;
        reply = QMessageBox::question(this, "Confirmation", "Êtes-vous sûr de vouloir quitter sans enregistrer?",
                                      QMessageBox::Yes | QMessageBox::No);
        if (reply == QMessageBox::Yes)
        {
            ui->lineEdit_IdEmission->clear();
            ui->lineEdit_Titre->clear();
            //ui->lineEdit_Categorie->clear();
            ui->lineEdit_Realisateur->clear();
            ui->lineEdit_Duree->clear();
            ui->dateEdit->setDate(QDate::currentDate());
            ui->lineEdit_Description->clear();
        }
    }
}

void MainWindow::on_pushButton_QuitterModifier_clicked()
{
    if (!ui->lineEdit_recherID->text().isEmpty() ||
        !ui->lineEdit_Titre_M->text().isEmpty() ||      
        !ui->lineEdit_Realisateur_M->text().isEmpty() ||
        !ui->lineEdit_Duree_M->text().isEmpty() ||
        !ui->lineEdit_Description_M->text().isEmpty())
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
        }
    }
}

void MainWindow::on_pushButtonRef_clicked()
{
       ui->table_AfficherEmission->setModel(Etmp.afficher());
}

void MainWindow::on_pushButtonTri_clicked()
{
    /*Emissions Etmp;
        QSqlQueryModel *model = Etmp.trierParDate();
        ui->table_AfficherEmission->setModel(model);*/
    // Créer un proxy model pour la table view
        QSortFilterProxyModel *proxyModel = new QSortFilterProxyModel(this);
        proxyModel->setSourceModel(ui->table_AfficherEmission->model()); // Utiliser le modèle source de la table view

        // Récupérer le critère de tri sélectionné
        QString critereTri = ui->comboBoxTri->currentText();

        // Déterminer l'ordre de tri (croissant ou décroissant)
        Qt::SortOrder ordreTri = (ui->radioButtonCroissant->isChecked()) ? Qt::AscendingOrder : Qt::DescendingOrder;

        // Définir le numéro de colonne à trier
        int columnToSort = -1; // Colonne à trier (-1 par défaut)

        if (critereTri == "ID") {
            columnToSort = 0; // Colonne ID
        } else if (critereTri == "Date") {
            columnToSort = 1; // Colonne Date
        } else if (critereTri == "Catégorie") {
            columnToSort = 2; // Colonne Catégorie
        } else if (critereTri == "Durée") {
            columnToSort = 3; // Colonne Durée
        }

        // Appliquer le tri sur le proxy model
        if (columnToSort != -1) {
            proxyModel->sort(columnToSort, ordreTri);
        }

        // Appliquer le proxy model à la table view
        ui->table_AfficherEmission->setModel(proxyModel);
}

void MainWindow::on_pushButtonPdf_clicked()
{
    QPrinter printer;
           QPrintDialog dialog(&printer, this);

    QPdfWriter pdf("C:/Users/user/Desktop/Atelier_Connexion/Emissions.pdf");
        QPainter painter(&pdf);

        // Styles
        QFont titleFont("Times New Roman", 30);
        QFont headerFont("Times New Roman", 10); // Augmenter la taille de la police pour les en-têtes
        QFont dataFont("Arial", 7); // Augmenter la taille de la police pour les données

        // Dessiner le logo
        QPixmap logo("C:/Users/user/Desktop/Atelier_Connexion/Logo.png");
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

                        Emissions Etmp;
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
void MainWindow::on_pushButtonExcel_clicked()
{

}

void MainWindow::on_pushButtonstat_clicked()
{
    Emissions Etmp;
    Etmp.statistiquesParCategorie();
}

void MainWindow::setupUI()
{
    mainLayout = new QVBoxLayout;
    comboBoxTri = new QComboBox;
    comboBoxTri->addItem("ID");
    comboBoxTri->addItem("Date");
    comboBoxTri->addItem("Catégorie");
    comboBoxTri->addItem("Durée");

    radioButtonCroissant = new QRadioButton("Croissant");
    radioButtonDecroissant = new QRadioButton("Décroissant");
    radioButtonCroissant->setChecked(true);

    pushButtonTri = new QPushButton("Trier");

    mainLayout->addWidget(comboBoxTri);
    mainLayout->addWidget(radioButtonCroissant);
    mainLayout->addWidget(radioButtonDecroissant);
    mainLayout->addWidget(pushButtonTri);

    QWidget *centralWidget = new QWidget(this);
    centralWidget->setLayout(mainLayout);
    setCentralWidget(centralWidget);

    connect(pushButtonTri, &QPushButton::clicked, this, &MainWindow::on_pushButtonTri_clicked);
    connect(comboBoxTri, QOverload<int>::of(&QComboBox::activated), this, &MainWindow::on_comboBoxTri_activated);
    connect(radioButtonCroissant, &QRadioButton::toggled, this, &MainWindow::on_radioButtonC_toggled);
    connect(radioButtonDecroissant, &QRadioButton::toggled, this, &MainWindow::on_radioButtonC_toggled);
}
void MainWindow::on_comboBoxTri_activated(int index)
{
    Q_UNUSED(index);
        // Mettre à jour le critère de tri sélectionné
}

void MainWindow::on_radioButtonC_toggled(bool checked)
{
    Q_UNUSED(checked);
       // Mettre à jour l'ordre de tri sélectionné
}

void MainWindow::on_pushButtonValidier_recherche_clicked()
{
    Emissions Etmp;
        QString critere = ui->comboBoxRecherche->currentText();
        QString valeur = ui->lineEditRechercheTableau->text();

        QSqlQueryModel *model = new QSqlQueryModel();

        if (critere == "Id_Emission") {
            // Convertir la valeur en entier
            int id_emission = valeur.toInt();
            model = Etmp.rechercherParid_emission(id_emission);
        } else if (critere == "Titre") {
            model = Etmp.rechercherParTitre(valeur);
        } else if (critere == "Categorie") {
            model = Etmp.rechercherParCategorie(valeur);
        } else if (critere == "Realisateur") {
            model = Etmp.rechercherParrealisateur(valeur);
        } else if (critere == "Duree") {
            // Convertir la valeur en entier
            int duree = valeur.toInt();
            model = Etmp.rechercherParduree(QString::number(duree));

        } else if (critere == "Date_emission") {
                // Convertir la date saisie par l'utilisateur en objet QDate
                QDate date = QDate::fromString(valeur, "dd-MM-yyyy");
                if (date.isValid()) {
                    // Exécuter la recherche par date
                    model = Etmp.rechercherPardate_emission(date);
                } else {
                    QMessageBox::warning(this, "Format de date invalide", "Veuillez entrer une date valide dans le format DD-MM-YYYY.");
                    return; // Arrêter l'exécution de la fonction en cas de date invalide
                }
            }

        if (model->rowCount() > 0) {
            ui->table_AfficherEmission->setModel(model);
        } else {
            QMessageBox::information(this, "Résultat de la recherche", "Aucun résultat trouvé.");
            // Utilisez simplement la fonction d'affichage pour réinitialiser la table
            ui->table_AfficherEmission->setModel(Etmp.afficher());
}
}

void MainWindow::on_pushButtonTelecharger_clicked()
{
    QString filePath = "C:/Users/user/Desktop/Atelier_Connexion/Emissions.pdf"; // Chemin vers le fichier PDF à télécharger

        QFile file(filePath);
        if (!file.exists()) {
            QMessageBox::warning(this, tr("Erreur"), tr("Le fichier PDF n'existe pas."));
            return;
        }

        QDesktopServices::openUrl(QUrl::fromLocalFile(filePath));
}

void MainWindow::on_pushButtonImprimer_clicked()
{
    /*

    // Jouer le son
        QMediaPlayer *player = new QMediaPlayer;
        player->setMedia(QUrl::fromLocalFile("C:/Users/user/Desktop/Atelier_Connexion"));
        player->setVolume(2000);
        player->play();

        // Sélectionner un fichier image à imprimer
        QString filename = QFileDialog::getOpenFileName(this, tr("Choisir une image"), "", tr("Images (*.png *.jpeg *.jpg *.bmp *.gif)"));
        if (!filename.isEmpty())
        {
            // Charger l'image
            QImage image;
            bool valid = image.load(filename);
            if (valid)
            {
                // Créer une boîte de dialogue d'impression
                QPrinter printer;
                QPrintDialog dialog(&printer, this);
                dialog.setWindowTitle(tr("Imprimer l'image"));

                // Si l'utilisateur clique sur "OK" dans la boîte de dialogue, imprimer l'image
                if (dialog.exec() == QDialog::Accepted)
                {
                    QPainter painter(&printer);
                    QRect rect = painter.viewport();
                    QSize size = image.size();
                    size.scale(rect.size(), Qt::KeepAspectRatio);
                    painter.setViewport(rect.x(), rect.y(), size.width(), size.height());
                    painter.setWindow(image.rect());
                    painter.drawImage(0, 0, image);
                }
            }
            else
            {
                // Gérer les erreurs de chargement de l'image
                QMessageBox::warning(this, tr("Erreur"), tr("Impossible de charger l'image. Veuillez sélectionner une image valide."));
            }
        }*/

    // Jouer le son
       /* QMediaPlayer *player = new QMediaPlayer;
        player->setMedia(QUrl::fromLocalFile("C:/Users/user/Desktop/Atelier_Connexion"));
        player->setVolume(2000);
        player->play();

        // Capturer l'écran principal
        QScreen *screen = QGuiApplication::primaryScreen();
        if (!screen) {
            QMessageBox::warning(this, tr("Erreur"), tr("Impossible de récupérer l'écran principal."));
            return;
        }

        // Obtenir la capture d'écran
        QPixmap screenshot = screen->grabWindow(0);

        // Vérifier si la capture d'écran est valide
        if (screenshot.isNull()) {
            QMessageBox::warning(this, tr("Erreur"), tr("Impossible de capturer l'écran."));
            return;
        }

        // Créer une boîte de dialogue d'impression
        QPrinter printer;
        QPrintDialog dialog(&printer, this);
        dialog.setWindowTitle(tr("Imprimer l'écran"));

        // Si l'utilisateur clique sur "OK" dans la boîte de dialogue, imprimer l'image
        if (dialog.exec() == QDialog::Accepted)
        {
            QPainter painter(&printer);
            QRect rect = painter.viewport();
            QSize size = screenshot.size();
            size.scale(rect.size(), Qt::KeepAspectRatio);
            painter.setViewport(rect.x(), rect.y(), size.width(), size.height());
            painter.setWindow(screenshot.rect());
            painter.drawPixmap(0, 0, screenshot);
        }*/
    // Créer une boîte de dialogue d'impression
        QPrinter printer;
        QPrintDialog dialog(&printer, this);
        dialog.setWindowTitle(tr("Imprimer l'écran"));

        // Si l'utilisateur clique sur "OK" dans la boîte de dialogue, imprimer l'image
        if (dialog.exec() == QDialog::Accepted)
        {
            QPainter painter(&printer);

            // Dessiner les bordures
            painter.setPen(Qt::black); // Couleur des bordures

            // Dessiner les en-têtes de colonne
            QStringList headers = {"IdEmission", "Titre", "Catégorie", "Réalisateur", "Date Emission", "Durée", "Description"};
            QFont headerFont("Times New Roman", 10); // Augmenter la taille de la police pour les en-têtes
            painter.setFont(headerFont);
            int x = 300; // Position horizontale initiale
            int y = 300; // Position verticale
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
            QFont dataFont("Arial", 7); // Augmenter la taille de la police pour les données
            painter.setFont(dataFont);
            x = 300; // Réinitialiser la position horizontale
            y = 450; // Définir la position verticale pour les données

            Emissions Etmp;
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

            // Informer que l'impression est terminée
            QMessageBox::information(this, tr("Impression terminée"), tr("L'impression a été effectuée avec succès!"));
        }



}

void MainWindow::on_pushButtoneee_clicked()
{
    QString fileName = QFileDialog::getSaveFileName(this, tr("Save File"),
                                          "emissions.csv",
                                          tr("CSV (.csv);;All Files ()"));
    if (fileName.isEmpty())
        return;

    QFile file(fileName);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QMessageBox::warning(this, tr("Unable to open file"),
        file.errorString());
        return;
    }
    QTextStream out(&file);
    out << "IdEmission" << ";" << "Titre" << ";" << "Categorie" << ";" << "Realisateur" << ";" << "DateEmission" << ";" << "Duree" << ";" << "Description" << "\n";
    QSqlQuery query("SELECT * FROM emissions");
    while (query.next()) {
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
