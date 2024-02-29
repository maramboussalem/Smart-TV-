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
      date_emission= QDate();;
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

bool Emissions::supprimer(int id_emission)
{
    QSqlQuery query;
    QString res = QString::number(id_emission);

    query.prepare("delete from emissions where id_emission = :id_emission");

    query.bindValue(":id_emission", res);
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
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("Duree"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("DateEmission"));
    model->setHeaderData(6, Qt::Horizontal, QObject::tr("Description"));
    return model;
}

bool Emissions::modifier(int id_emission,QString titre,QString categorie,QString realisateur,QString duree,QDate date_emission,QString description)
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


