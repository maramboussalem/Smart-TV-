#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "emissions.h"
#include <QApplication>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_Ajouter_clicked()
{
    QString id_emission_str = ui->lineEdit_IdEmission->text();
    QString titre=ui->lineEdit_Titre->text();
    QString categorie=ui->lineEdit_Categorie->text();
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
        ui->lineEdit_Categorie->clear();
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
    ui->lineEdit_Categorie_M->setText(emission.getCategorie());
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
    QString categorie=ui->lineEdit_Categorie_M->text();
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
        ui->lineEdit_Categorie_M->clear();
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
    /*QString fileName = QFileDialog::getOpenFileName(this, tr("Select Video File"),"", tr("MP4 Files (*.mp4)"));
    if(fileName.isEmpty())
    {
        return;
    }

    QMediaPlayer *player = new QMediaPlayer();
    QVideoWidget *video = new QVideoWidget(this);
    video->setGeometry(200, 200, 640, 480);
    player->setVideoOutput(video);
    player->setMedia(QUrl::fromLocalFile(fileName));
    video->show();
    player->play();*/

}

void MainWindow::on_pushButton_QuitterAjouter_clicked()
{
    if (!ui->lineEdit_IdEmission->text().isEmpty() ||
        !ui->lineEdit_Titre->text().isEmpty() ||
        !ui->lineEdit_Categorie->text().isEmpty() ||
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
            ui->lineEdit_Categorie->clear();
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
        !ui->lineEdit_Categorie_M->text().isEmpty() ||
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
            ui->lineEdit_Categorie_M->clear();
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
    Emissions Etmp;
        QSqlQueryModel *model = Etmp.trierParDate();
        ui->table_AfficherEmission->setModel(model);
}
