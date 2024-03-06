#include "emissions.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>

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

QSqlQueryModel * Emissions::trierParDate()
{
    QSqlQueryModel * model = new QSqlQueryModel();
    model->setQuery("SELECT * FROM emissions ORDER BY id_emission ASC");

    model->setHeaderData(0, Qt::Horizontal, QObject::tr("IdEmission"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Titre"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("Categorie"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("Realisateur"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("DateEmission"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("Duree"));
    model->setHeaderData(6, Qt::Horizontal, QObject::tr("Description"));

  return model;
}
