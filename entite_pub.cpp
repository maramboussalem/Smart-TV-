#include "entite_pub.h"
#include <QString>
#include <QDebug>
#include <QSqlError>
#include "publicite.h"

Entite_pub::Entite_pub()
{
     idpublicite =0;
    QString ObjectifdeLaCompagne ="";
    QString Duree ="";
    QString Frequences="";
}
Entite_pub::Entite_pub(int idpublicite, QString ObjectifdeLaCompagne, QString Duree, QString Frequences)
{
    this->idpublicite = idpublicite;
    this->ObjectifdeLaCompagne = ObjectifdeLaCompagne;
    this->Duree = Duree;
    this->Frequences = Frequences;
}
QString Entite_pub::getObjectifdeLaCompagne(){return  ObjectifdeLaCompagne;}
QString Entite_pub::getDuree(){return Duree;}
QString Entite_pub::getFrequences(){return Frequences;}
int Entite_pub::getIdPublicite(){return idpublicite;}
void Entite_pub::setObjectifdeLaCompagne(QString o){ObjectifdeLaCompagne=o;}
void Entite_pub::setDuree(QString d){Duree=d;}
void Entite_pub::setFrequences(QString f){ Frequences=f;}
void Entite_pub::setIdPublicite(int id){this->idpublicite=id;}

bool Entite_pub::ajouter()
{
    QSqlQuery query;
    QString res = QString::number(idpublicite);
    query.prepare("INSERT INTO publicite (IdPublicite, ObjectifdeLaCompagne, Duree, Frequences , VIDEOPATH) "
                  "VALUES (:IdPublicite, :ObjectifdeLaCompagne, :Duree, :Frequences , :VIDEOPATH)");
    query.bindValue(":IdPublicite", res);
    query.bindValue(":ObjectifdeLaCompagne", ObjectifdeLaCompagne);
    query.bindValue(":Duree", Duree);
    query.bindValue(":Frequences", Frequences);
    query.bindValue(":VIDEOPATH" , VIDEOPATH);
    return query.exec();
}

QSqlQueryModel* Entite_pub::afficher()
{
    QSqlQueryModel* model = new QSqlQueryModel();
    model->setQuery("SELECT * FROM publicite");
    return model;
}

bool Entite_pub::supprimer(int idpublicite)
{
    QSqlQuery query;
    QString res = QString::number(idpublicite);
    query.prepare("DELETE FROM publicite WHERE idpublicite = :id");
    query.bindValue(":id", res);
    return query.exec();
}
bool Entite_pub::modifier(int idpublicite, QString ObjectifdeLaCompagne, QString Duree, QString Frequences)
{
    QSqlQuery query;
    QString res = QString::number(idpublicite);
    query.prepare("UPDATE publicite SET OBJECTIFDELACOMPAGNE = :ObjectifdeLaCompagne, DUREE = :Duree, FREQUENCES = :Frequences WHERE IDPUBLICITE = :IdPublicite");
    query.bindValue(":IdPublicite", idpublicite);
    query.bindValue(":ObjectifdeLaCompagne", ObjectifdeLaCompagne);
    query.bindValue(":Duree", Duree);
    query.bindValue(":Frequences", Frequences);

    if (query.exec()) {
        return true;
    } else {
        return false;
    }
}

Entite_pub Entite_pub::rechercherpub(int idpublicite)
{
    QSqlQuery query;
    query.prepare("SELECT * FROM publicite WHERE idpublicite = :idpublicite");
    query.bindValue(":idpublicite", idpublicite);
    query.exec();

    if (query.next())
    {
        int id = query.value(0).toInt();
        QString ObjectifdeLaCompagne = query.value(1).toString();
        QString Duree = query.value(2).toString();
        QString Frequences = query.value(3).toString();

        Entite_pub p(id, ObjectifdeLaCompagne, Duree, Frequences);
        return p;
    }

    return Entite_pub();
}
QSqlQueryModel * Entite_pub::triPUB(QString attribut)
{
    QSqlQueryModel* model =new QSqlQueryModel() ;
    if(attribut == "DUREE") model->setQuery("select * from publicite order by DUREE ASC");
    else if( attribut == "FREQUENCES") model->setQuery("select * from publicite order by FREQUENCES ASC");
    else  model->setQuery("select * from publicite order by OBJECTIFDELACOMPAGNE ASC");
    return  model ;
}
bool Entite_pub::id_existe(int IdPublicite)
{
    QSqlQuery query;
    query.prepare("SELECT *  FROM publicite where idpublicite=:id") ;
    query.bindValue(":id" , IdPublicite);
    if(query.exec() && query.next())
    {
        if (query.size()!=0)
            return true ;
        else
            return false ;
    }
    else return false;
}
QSqlQueryModel * Entite_pub::rechercherid(int idpublicite)
{
    QSqlQueryModel *model = new QSqlQueryModel();
    if (idpublicite == 0) {
        model->setQuery("SELECT * FROM Publicite");
    } else {
        QString queryStr = QString("SELECT * FROM publicite WHERE idpublicite = %1").arg(idpublicite);
        model->setQuery(queryStr);
    }
    return model;
}
