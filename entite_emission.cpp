#include "entite_emission.h"
<<<<<<< HEAD
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <QtCharts>

Entite_emission::Entite_emission()
{
    id_emission=0;
    titre="";
    categorie="";
    realisateur="";
    duree="";
    date_emission= QDate();
    description="";
    video="";
    soustitrage="";
}
Entite_emission::Entite_emission(int id_emission,QString titre,QString categorie,QString realisateur,QString duree,QDate date_emission,QString description,QString video,QString soustitrage)
{
    this->id_emission=id_emission;
    this->titre=titre;
    this->categorie=categorie;
    this->realisateur=realisateur;
    this->duree=duree;
    this->date_emission=date_emission;
    this->description=description;
    this->video=video;
    this->soustitrage=soustitrage;
}

int Entite_emission::getID(){return id_emission;}
QString Entite_emission::getTitre(){return titre;}
QString Entite_emission::getCategorie(){return categorie;}
QString Entite_emission::getRealisateur(){return realisateur;}
QString Entite_emission::getDuree(){return duree;}
QDate Entite_emission::getDate_emission(){return date_emission;}
QString Entite_emission::getDescription(){return description;}
QString Entite_emission::getvideo(){return video;}
QString Entite_emission::getsoustitrage(){return soustitrage;}

void Entite_emission::setID(int id_emission){this->id_emission=id_emission;}
void Entite_emission::setTitre(QString t){titre=t;}
void Entite_emission::setCategorie(QString c){categorie=c;}
void Entite_emission::setRealisateur(QString r){realisateur=r;}
void Entite_emission::setDuree(QString du){duree=du;}
void Entite_emission::setDate_emission(QDate da){date_emission=da;}
void Entite_emission::setDescription(QString de){description=de;}
void Entite_emission::setvideo(QString v){video=v;}
void Entite_emission::setsoustitrage(QString s){soustitrage=s;}

bool Entite_emission::ajouter()
{
    QSqlQuery query;
    QString res = QString::number(id_emission);

    query.prepare("insert into Entite_emission (id_emission, titre, categorie, realisateur, duree, date_emission, description, video ,soustitrage) "
                  "values (:id_emission, :titre, :categorie, :realisateur, :duree, :date_emission, :description, :video, :soustitrage)");

    query.bindValue(":id_emission", res);
    query.bindValue(":titre", titre);
    query.bindValue(":categorie", categorie);
    query.bindValue(":realisateur", realisateur);
    query.bindValue(":duree", duree);
    query.bindValue(":date_emission", date_emission);
    query.bindValue(":description", description);
    query.bindValue(":video", video);
    query.bindValue(":soustitrage", soustitrage);

    return query.exec();
}

bool Entite_emission::supprimer(int id)
{
    QSqlQuery query;

    query.prepare("delete from Entite_emission where id_emission = :id");

    query.bindValue(":id", id);
    return query.exec();
}

QSqlQueryModel * Entite_emission::afficher()
{
    QSqlQueryModel * model = new QSqlQueryModel();
    model->setQuery("select * from Entite_emission");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("IdEmission"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Titre"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("Categorie"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("Realisateur"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("DateEmission"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("Duree"));
    model->setHeaderData(6, Qt::Horizontal, QObject::tr("Description"));
    model->setHeaderData(7, Qt::Horizontal, QObject::tr("video"));
    model->setHeaderData(8, Qt::Horizontal, QObject::tr("soustitrage"));
    return model;
}

bool Entite_emission::modifier(int id_emission, QString titre, QString categorie, QString realisateur, QString duree, QDate date_emission, QString description, QString video, QString soustitrage)
{
    QSqlQuery query;

    query.prepare("UPDATE Entite_emission SET titre = :titre, categorie = :categorie, realisateur = :realisateur, duree = :duree, date_emission = :date_emission, description = :description , video = :video, soustitrage =:soustitrage WHERE id_emission = :id_emission");
    query.bindValue(":id_emission", id_emission);
    query.bindValue(":titre", titre);
    query.bindValue(":categorie", categorie);
    query.bindValue(":realisateur", realisateur);
    query.bindValue(":duree", duree);
    query.bindValue(":date_emission", date_emission);
    query.bindValue(":description", description);
    query.bindValue(":video", video);
    query.bindValue(":soustitrage", soustitrage);

    if(query.exec())
        return true;
    else
        return false;
}

Entite_emission Entite_emission::rechercherEmission(int id_emission)
{
    QSqlQuery query;
    query.prepare("SELECT * FROM Entite_emission WHERE id_emission = :id_emission");
    query.bindValue(":id_emission", id_emission);
    query.exec();

    if (query.next())
    {
        QString titre = query.value(1).toString();
        QString categorie = query.value(2).toString();
        QString realisateur = query.value(3).toString();
        QString duree = query.value(5).toString();
        QDate date_emission = query.value(5).toDate();
        QString description = query.value(6).toString();
        QString video = query.value(6).toString();
        QString soustitrage = query.value(6).toString();

        Entite_emission E(id_emission, titre, categorie, realisateur, duree, date_emission, description,video,soustitrage);
        return E;
    }

    // Si aucune émission n'est trouvée, retourner un objet Emissions vide
    return Entite_emission();
}


bool Entite_emission::supprimerTout()
{
    QSqlQuery query;
    return query.exec("DELETE FROM Entite_emission");
}

bool Entite_emission::existeId(int id_emission)
{
    QSqlQuery query;
    query.prepare("SELECT COUNT(*) FROM Entite_emission WHERE id_emission = :id");
    query.bindValue(":id", id_emission);
    if (query.exec() && query.next())
    {
        int count = query.value(0).toInt();
        return count > 0;
    }
    return false;
}

bool Entite_emission::existeTitre(QString titre)
{
    QSqlQuery query;
    query.prepare("SELECT COUNT(*) FROM Entite_emission WHERE titre = :titre");
    query.bindValue(":titre", titre);
    if (query.exec() && query.next())
    {
        int count = query.value(0).toInt();
        return count > 0;
    }
    return false;
}

QSqlQueryModel * Entite_emission::trierPar(QString colonne, QString ordre)
{
    QSqlQueryModel * model = new QSqlQueryModel();
    QSqlQuery query;
    query.prepare("SELECT * FROM Entite_emission ORDER BY " + colonne + " " + ordre);
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
QSqlQueryModel * Entite_emission::rechercherParid_emission(int id_emission)
{
    QSqlQueryModel *model = new QSqlQueryModel();

        // Vérifiez si l'id_emission est valide (différent de zéro)
        if(id_emission != 0)
        {
            // Utilisez des paramètres liés pour éviter les injections SQL
            QSqlQuery query;
            query.prepare("SELECT * FROM  Entite_emission WHERE id_emission = :id");
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
            model->setQuery("SELECT * FROM  Entite_emission");
        }

        return model;
}
QSqlQueryModel *  Entite_emission::rechercherParTitre(QString titre)
{
    QSqlQueryModel *model = new QSqlQueryModel();
        if(titre.isEmpty()){
            model->setQuery("SELECT * FROM Entite_emission");
        }
        else{
            model->setQuery("SELECT * FROM Entite_emission WHERE titre='" + titre + "'");
        }
        return model;
}
QSqlQueryModel *  Entite_emission::rechercherParCategorie(QString categorie)
{
    QSqlQueryModel *model = new QSqlQueryModel();
        if(categorie.isEmpty()){
            model->setQuery("SELECT * FROM Entite_emission");
        }
        else{
            model->setQuery("SELECT * FROM Entite_emission WHERE categorie='" + categorie + "'");
        }
        return model;
}

QSqlQueryModel * Entite_emission::rechercherParrealisateur(QString realisateur)
{
    QSqlQueryModel *model = new QSqlQueryModel();
        if(realisateur.isEmpty()){
            model->setQuery("SELECT * FROM  Entite_emission");
        }
        else{
            model->setQuery("SELECT * FROM  Entite_emission WHERE realisateur='" + realisateur + "'");
        }
        return model;
}
QSqlQueryModel * Entite_emission::rechercherParduree(QString duree)
{
    QSqlQueryModel *model = new QSqlQueryModel();
        if(duree.isEmpty()){
            model->setQuery("SELECT * FROM  Entite_emission");
        }
        else{
            model->setQuery("SELECT * FROM  Entite_emission WHERE duree='" + duree + "'");
        }
        return model;
}
QSqlQueryModel *  Entite_emission::rechercherPardate_emission(QDate date_emission)
{
    QSqlQueryModel *model = new QSqlQueryModel();
        QSqlQuery query;

        if (!date_emission.isValid()) {
            query.prepare("SELECT * FROM  Entite_emission");
        } else {
            query.prepare("SELECT * FROM  Entite_emission WHERE date_emission = :date");
            query.bindValue(":date", date_emission);
        }

        if (!query.exec()) {
            qDebug() << "Erreur lors de l'exécution de la requête :" << query.lastError().text();
        } else {
            model->setQuery(query);
        }

        return model;
}

void Entite_emission::setTotalTime(QTime duree, QString mVideoFilePath)
{
    // Convert QTime to string in the format "hh:mm:ss"
    QString durationString = duree.toString("hh:mm:ss");

    QSqlQuery query;
    query.prepare("UPDATE ENTITE_EMISSION SET DUREE = :duration WHERE VIDEO = :videoFilePath");
    query.bindValue(":duration", durationString); // Bind the string representation of QTime
    query.bindValue(":videoFilePath", mVideoFilePath);

    // Execute the query
    if (query.exec())
    {
        qDebug() << "DUREE attribute updated successfully for video file: " << mVideoFilePath;
    }
    else
    {
        qDebug() << "Failed to update DUREE attribute for video file: " << mVideoFilePath;
        qDebug() << "Error:" << query.lastError().text();
    }
}

QTime Entite_emission::getTotalTime(QString mVideoFilePath)
{
    QSqlQuery query;
    query.prepare("SELECT DUREE FROM ENTITE_EMISSION WHERE VIDEO = :videoFilePath");
    query.bindValue(":videoFilePath", mVideoFilePath);

    if (query.exec() && query.next())
    {
        // Retrieve the duration string from the query result
        QString durationString = query.value(0).toString();

        // Convert the duration string to QTime format
        QTime totalTime = QTime::fromString(durationString, "hh:mm:ss");

        // Check if the conversion was successful
        if (totalTime.isValid())
        {
            return totalTime;
        }
        else
        {
            qDebug() << "Failed to convert DUREE string to QTime for video file: " << mVideoFilePath;
            // Return an invalid QTime to indicate failure
            return QTime();
        }
    }
    else
    {
        qDebug() << "Failed to retrieve DUREE attribute for video file: " << mVideoFilePath;
        qDebug() << "Error:" << query.lastError().text();
        // Return an invalid QTime to indicate failure
        return QTime();
    }
}

=======
#include<QDate>

Entite_emission::Entite_emission(int id,QString titre , QString category,QString realisateur,QString date,QString duree,QString description ,QString horraire)
{
  this->id = id;
  this->titre = titre;
  this->category = category;
  this->realisateur = realisateur;
   // this->langue = langue;
    this->date = date;
    this->duree = duree;
    this->description = description ;
    this->horraire = horraire ;
};
bool Entite_emission::ajouter(){
    // todo
    QSqlQuery query ;
    QString res = QString::number(id);
    query.prepare("insert into EMISSIONS (ID_EMISSION,TITRE,CATEGORIE,DURE,REALISATEUR,DESCRIPTION) values (:id,:titre,:category,:duree,:realisateur,:description)");
    query.bindValue(":id",res);
   // query.bindValue(":date",QDate(date));
    query.bindValue(":titre",titre);
   // query.bindValue(":langue",langue);
    query.bindValue(":realisateur",realisateur);
    query.bindValue(":category",category);
    query.bindValue(":description",description);
  //  query.bindValue(":horraire",horraire);

    return query.exec();
};
bool Entite_emission::supprimer(int id){
    // todo
    QSqlQuery query ;
    QString res = QString::number(id);
    query.prepare("DELETE from EMISSIONS WHERE ID_EMISSION =:id");
    query.bindValue(":id",res);
    return query.exec();

};
QSqlQueryModel * Entite_emission::afficher()
{
    // todo
    QSqlQueryModel * model = new QSqlQueryModel;
    model->setQuery("SELECT * FROM EMISSIONS");
    model->setHeaderData(0,Qt::Horizontal,QObject::tr("ID"));
    model->setHeaderData(1,Qt::Horizontal,QObject::tr("DATE"));
    model->setHeaderData(2,Qt::Horizontal,QObject::tr("TITRE"));
    model->setHeaderData(3,Qt::Horizontal,QObject::tr("CATEGORY"));
    model->setHeaderData(4,Qt::Horizontal,QObject::tr("DURE"));
    model->setHeaderData(5,Qt::Horizontal,QObject::tr("REALISATEUR"));
    model->setHeaderData(6,Qt::Horizontal,QObject::tr("DESCRIPTION"));
    return model ;
};
bool Entite_emission::modifier(){
    // todo
    QSqlQuery query ;
    QString res = QString::number(id);
   query.prepare("UPDATE EMISSIONS SET TITRE = :titre, CATEGORIE = :category, DURE = :duree, REALISATEUR = :realisateur, DESCRIPTION = :description WHERE ID_EMISSION = :id");
    query.bindValue(":id",res);
   // query.bindValue(":date",QDate(date));
    query.bindValue(":titre",titre);
   // query.bindValue(":langue",langue);
    query.bindValue(":realisateur",realisateur);
    query.bindValue(":category",category);
    query.bindValue(":description",description);
  //  query.bindValue(":horraire",horraire);

    return query.exec();
};
>>>>>>> 18d955075ebf7e49d498a0f477c7a42083282ca3
