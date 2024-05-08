#include "entite_equipement.h"
#include <QSqlError>
#include <QDebug>
#include <QtPrintSupport/QPrinter>
#include <QFileDialog>
#include <QPainter>
#include <QPdfWriter>
#include <QPieSeries>
#include <QPieSlice>
#include <QtCharts>
#include <QChartView>
#include <QSqlQuery>

entite_equipement::entite_equipement()
{
    id_equipement = 0;
    type = "";
    quantite = "";
    prix = "";
    image = "";
}
entite_equipement::entite_equipement(int id_equipement, QString type, QString quantite, QString prix, QString image)
{
    this->id_equipement = id_equipement;
    this->type = type;
    this->quantite = quantite;
    this->prix = prix;
    this->image =image;
}
//get
int entite_equipement::getID_equipement(){return id_equipement;}
QString entite_equipement::getType(){return type;}
QString entite_equipement::getQuantite(){return quantite;}
QString entite_equipement::getPrix(){return prix;}
QString entite_equipement::getImage(){return image;}

//set
void entite_equipement::setID_equipement(int id){id_equipement=id;}
void entite_equipement::setType(QString tp){type=tp;}
void entite_equipement::setQuantite(QString quant){quantite=quant;}
void entite_equipement::setPrix(QString pr){prix=pr;}
void entite_equipement::setImage(QString im){image=im;}

bool entite_equipement::ajouter()
{
    if ( type.isEmpty() || quantite.isEmpty() || prix.isEmpty() || image.isEmpty()) {
            qDebug() << "Erreur : Tous les champs doivent être renseignés.";
            return false;
        }

        QSqlQuery query;
        query.prepare("INSERT INTO equipements (id_equipement, type, quantite, prix, image) "
                      "VALUES (:id_equipement, :type, :quantite, :prix, :image)");

        query.bindValue(":id_equipement", id_equipement);
        query.bindValue(":type", type);
        query.bindValue(":quantite", quantite);
        query.bindValue(":prix", prix);
        query.bindValue(":image", image);

        return query.exec();
}

bool entite_equipement::supprimer(int id_equipement)
{
        QSqlQuery query;
        QString res = QString::number(id_equipement);

        query.prepare("delete from equipements where id_equipement = :id_equipement");

        query.bindValue(":id_equipement", res);  // Corrected the parameter name

        return query.exec();
}

ImageQueryModel* entite_equipement::afficher()
{
    // Créer un modèle personnalisé pour gérer l'affichage des images
    ImageQueryModel* model = new ImageQueryModel();

    // Récupérer les données de la base de données
    QSqlQuery query("SELECT * FROM equipements");

    // Définir les en-têtes des colonnes
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("Reference"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Type"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("Quantite"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("Prix"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("Image"));

    // Remplir le modèle avec les données de la requête
    model->setQuery(query);

    return model;
}




bool entite_equipement::modifier(int id_equipement, QString type, QString quantite, QString prix, QString image)
{
    // Vérification des champs obligatoires
    if ( type.isEmpty() || quantite.isEmpty() || prix.isEmpty() || image.isEmpty()) {
        qDebug() << "Erreur : Tous les champs doivent être renseignés.";
        return false;
    }

    QSqlQuery query;
    query.prepare("UPDATE equipements SET type = :type, quantite = :quantite, prix = :prix, image = :image WHERE id_equipement = :id_equipement");
    query.bindValue(":id_equipement", id_equipement);
    query.bindValue(":type", type);
    query.bindValue(":quantite", quantite);
    query.bindValue(":prix", prix);
    query.bindValue(":image", image);

    if (query.exec()) {
        return true;
    } else {
        qDebug() << "Erreur lors de la modification :" << query.lastError().text();
        return false;
    }
}



QSqlQueryModel * entite_equipement::rechercherPartype(QString type)
{
    QSqlQueryModel *model = new QSqlQueryModel();
        if(type.isEmpty()){
            model->setQuery("SELECT * FROM equipements");
        }
        else{
            model->setQuery("SELECT * FROM equipements WHERE type ='" + type + "'");
        }
        return model;
}
QSqlQueryModel * entite_equipement::trierParPrix()
{
    QSqlQueryModel * model = new QSqlQueryModel();
    model->setQuery("SELECT * FROM equipements ORDER BY prix ASC");

    model->setHeaderData(0, Qt::Horizontal, QObject::tr("id_equipement"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("type"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("quantite"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("prix"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("image"));

  return model;
}
QSqlQueryModel * entite_equipement::trierParPrixd()
{
    QSqlQueryModel * model = new QSqlQueryModel();
    model->setQuery("SELECT * FROM equipements ORDER BY prix DESC");

    model->setHeaderData(0, Qt::Horizontal, QObject::tr("id_equipement"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("type"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("quantite"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("prix"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("image"));

  return model;
}

void entite_equipement::statistiquesParQuantite()
{
    QSqlQuery query("SELECT quantite, COUNT(*) FROM  equipements GROUP BY quantite");
        QtCharts::QBarSeries *series = new QtCharts::QBarSeries();

        while (query.next())
        {
            QString quantite = query.value(0).toString();
            int count = query.value(1).toInt();

            QtCharts::QBarSet *set = new QtCharts::QBarSet(quantite); // Utilisez la catégorie comme libellé
            *set << count;

            series->append(set);
        }

        QtCharts::QChart *chart = new QtCharts::QChart();
        chart->addSeries(series);
        chart->setTitle("Nombre d'equipement par prix");
        chart->setAnimationOptions(QtCharts::QChart::SeriesAnimations);

        QStringList quantites;
        quantites << "quantites"; // Ajoutez les noms de vos catégories ici

        QtCharts::QBarCategoryAxis *axis = new QtCharts::QBarCategoryAxis();
        axis->append(quantites);
        chart->createDefaultAxes();
        chart->setAxisX(axis, series);
        chart->legend()->setVisible(true);

        QtCharts::QChartView *chartView = new QtCharts::QChartView(chart);
        chartView->resize(900, 600);
        chartView->show();
}

