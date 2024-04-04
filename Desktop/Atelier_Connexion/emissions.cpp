#include "emissions.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <QtCharts>
Emissions::Emissions()
{
      id_emission=0;
      titre="";
      categorie="";
      realisateur="";
      duree="";
      date_emission= QDate();
      description="";
}
Emissions::Emissions(int id_emission,QString titre,QString categorie,QString realisateur,QString duree,QDate date_emission,QString description)
{
  this->id_emission=id_emission;
  this->titre=titre;
  this->categorie=categorie;
  this->realisateur=realisateur;
  this->duree=duree;
  this->date_emission=date_emission;
  this->description=description;
}
int Emissions::getID(){return id_emission;}
QString Emissions::getTitre(){return titre;}
QString Emissions::getCategorie(){return categorie;}
QString Emissions::getRealisateur(){return realisateur;}
QString Emissions::getDuree(){return duree;}
QDate Emissions::getDate_emission(){return date_emission;}
QString Emissions::getDescription(){return description;}


void Emissions::setID(int id_emission){this->id_emission=id_emission;}
void Emissions::setTitre(QString t){titre=t;}
void Emissions::setCategorie(QString c){categorie=c;}
void Emissions::setRealisateur(QString r){realisateur=r;}
void Emissions::setDuree(QString du){duree=du;}
void Emissions::setDate_emission(QDate da){date_emission=da;}
void Emissions::setDescription(QString de){description=de;}

bool Emissions::ajouter()
{
    QSqlQuery query;
    QString res = QString::number(id_emission);

    query.prepare("insert into emissions (id_emission, titre, categorie, realisateur, duree, date_emission, description) "
                  "values (:id_emission, :titre, :categorie, :realisateur, :duree, :date_emission, :description)");

    query.bindValue(":id_emission", res);
    query.bindValue(":titre", titre);
    query.bindValue(":categorie", categorie);
    query.bindValue(":realisateur", realisateur);
    query.bindValue(":duree", duree);
    query.bindValue(":date_emission", date_emission);
    query.bindValue(":description", description);

    return query.exec();
}

bool Emissions::supprimer(int id)
{
    QSqlQuery query;
   // QString res = QString::number(id_emission);

    query.prepare("delete from emissions where id_emission = :id");

    query.bindValue(":id", id);
    return query.exec();
}

QSqlQueryModel * Emissions::afficher()
{
    QSqlQueryModel * model = new QSqlQueryModel();
    model->setQuery("select * from emissions");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("IdEmission"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Titre"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("Categorie"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("Realisateur"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("DateEmission"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("Duree"));
    model->setHeaderData(6, Qt::Horizontal, QObject::tr("Description"));

    return model;
}

bool Emissions::modifier(int id_emission, QString titre, QString categorie, QString realisateur, QString duree, QDate date_emission, QString description)
{
    QSqlQuery query;

    query.prepare("UPDATE emissions SET titre = :titre, categorie = :categorie, realisateur = :realisateur, duree = :duree, date_emission = :date_emission, description = :description WHERE id_emission = :id_emission");
    query.bindValue(":id_emission", id_emission);
    query.bindValue(":titre", titre);
    query.bindValue(":categorie", categorie);
    query.bindValue(":realisateur", realisateur);
    query.bindValue(":duree", duree);
    query.bindValue(":date_emission", date_emission);
    query.bindValue(":description", description);

    if(query.exec())
        return true;
    else
        return false;
}

Emissions Emissions::rechercherEmission(int id_emission)
{
    QSqlQuery query;
    query.prepare("SELECT * FROM emissions WHERE id_emission = :id_emission");
    query.bindValue(":id_emission", id_emission);
    query.exec();

    if (query.next()) {
        QString titre = query.value(1).toString();
        QString categorie = query.value(2).toString();
        QString realisateur = query.value(3).toString();
        QString duree = query.value(5).toString();
        QDate date_emission = query.value(5).toDate();
        QString description = query.value(6).toString();

        Emissions E(id_emission, titre, categorie, realisateur, duree, date_emission, description);
        return E;
    }

    // Si aucune émission n'est trouvée, retourner un objet Emissions vide
    return Emissions();
}


bool Emissions::supprimerTout()
{
    QSqlQuery query;
    return query.exec("DELETE FROM emissions");
}

bool Emissions::existeId(int id_emission)
{
    QSqlQuery query;
    query.prepare("SELECT COUNT(*) FROM emissions WHERE id_emission = :id");
    query.bindValue(":id", id_emission);
    if (query.exec() && query.next()) {
        int count = query.value(0).toInt();
        return count > 0;
    }
    return false;
}

bool Emissions::existeTitre(QString titre)
{
    QSqlQuery query;
    query.prepare("SELECT COUNT(*) FROM emissions WHERE titre = :titre");
    query.bindValue(":titre", titre);
    if (query.exec() && query.next()) {
        int count = query.value(0).toInt();
        return count > 0;
    }
    return false;
}


QSqlQueryModel * Emissions::trierPar(QString colonne, QString ordre)
{
    QSqlQueryModel * model = new QSqlQueryModel();
    QSqlQuery query;
    query.prepare("SELECT * FROM emissions ORDER BY " + colonne + " " + ordre);
    query.exec();
    model->setQuery(query);

    model->setHeaderData(0, Qt::Horizontal, QObject::tr("IdEmission"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Titre"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("Categorie"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("Realisateur"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("DateEmission"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("Duree"));
    model->setHeaderData(6, Qt::Horizontal, QObject::tr("Description"));

    return model;
}

void Emissions::statistiquesParCategorie()
{
    QSqlQuery query("SELECT categorie, COUNT(*) FROM emissions GROUP BY categorie");
        QtCharts::QBarSeries *series = new QtCharts::QBarSeries();

        while (query.next())
        {
            QString categorie = query.value(0).toString();
            int count = query.value(1).toInt();

            QtCharts::QBarSet *set = new QtCharts::QBarSet(categorie); // Utilisez la catégorie comme libellé
            *set << count;

            series->append(set);
        }

        QtCharts::QChart *chart = new QtCharts::QChart();
        chart->addSeries(series);
        chart->setTitle("Nombre d'émissions par catégorie");
        chart->setAnimationOptions(QtCharts::QChart::SeriesAnimations);

        QStringList categories;
        categories << "Catégories"; // Ajoutez les noms de vos catégories ici

        QtCharts::QBarCategoryAxis *axis = new QtCharts::QBarCategoryAxis();
        axis->append(categories);
        chart->createDefaultAxes();
        chart->setAxisX(axis, series);
        chart->legend()->setVisible(true);

        QtCharts::QChartView *chartView = new QtCharts::QChartView(chart);
        chartView->resize(900, 600);
        chartView->show();
}

QSqlQueryModel * Emissions::rechercherParid_emission(int id_emission)
{
    QSqlQueryModel *model = new QSqlQueryModel();

        // Vérifiez si l'id_emission est valide (différent de zéro)
        if(id_emission != 0)
        {
            // Utilisez des paramètres liés pour éviter les injections SQL
            QSqlQuery query;
            query.prepare("SELECT * FROM emissions WHERE id_emission = :id");
            query.bindValue(":id", id_emission);

            if(!query.exec())
            {
                // Gérer les erreurs d'exécution de la requête
                qDebug() << "Erreur lors de l'exécution de la requête :" << query.lastError().text();
            }
            else
            {
                // Définir la requête sur le modèle
                model->setQuery(query);
            }
        }
        else
        {
            // Si l'id_emission est vide, récupérez toutes les émissions
            model->setQuery("SELECT * FROM emissions");
        }

        return model;
}
QSqlQueryModel * Emissions::rechercherParTitre(QString titre)
{
    QSqlQueryModel *model = new QSqlQueryModel();
        if(titre.isEmpty()){
            model->setQuery("SELECT * FROM emissions");
        }
        else{
            model->setQuery("SELECT * FROM emissions WHERE titre='" + titre + "'");
        }
        return model;
}
QSqlQueryModel * Emissions::rechercherParCategorie(QString categorie)
{
    QSqlQueryModel *model = new QSqlQueryModel();
        if(categorie.isEmpty()){
            model->setQuery("SELECT * FROM emissions");
        }
        else{
            model->setQuery("SELECT * FROM emissions WHERE categorie='" + categorie + "'");
        }
        return model;
}

QSqlQueryModel * Emissions::rechercherParrealisateur(QString realisateur)
{
    QSqlQueryModel *model = new QSqlQueryModel();
        if(realisateur.isEmpty()){
            model->setQuery("SELECT * FROM emissions");
        }
        else{
            model->setQuery("SELECT * FROM emissions WHERE realisateur='" + realisateur + "'");
        }
        return model;
}
QSqlQueryModel * Emissions::rechercherParduree(QString duree)
{
    QSqlQueryModel *model = new QSqlQueryModel();
        if(duree.isEmpty()){
            model->setQuery("SELECT * FROM emissions");
        }
        else{
            model->setQuery("SELECT * FROM emissions WHERE duree='" + duree + "'");
        }
        return model;
}
QSqlQueryModel * Emissions::rechercherPardate_emission(QDate date_emission)
{
    QSqlQueryModel *model = new QSqlQueryModel();
        QSqlQuery query;

        if (!date_emission.isValid()) {
            query.prepare("SELECT * FROM emissions");
        } else {
            query.prepare("SELECT * FROM emissions WHERE date_emission = :date");
            query.bindValue(":date", date_emission);
        }

        if (!query.exec()) {
            qDebug() << "Erreur lors de l'exécution de la requête :" << query.lastError().text();
        } else {
            model->setQuery(query);
        }

        return model;
}
