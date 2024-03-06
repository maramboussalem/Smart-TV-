#include "employes.h"
#include <QtSql/QSqlQuery>
#include <QDate>
#include <QSqlError>
#include <QDebug>
employes::employes()
{
    id_E = 0;
    nom = "";
    prenom = "";
    email = "";
    date_naissance = QDate();
    telephonne = "";
    adresse = "";
}
employes::employes(int id_E, QString nom, QString prenom, QString email, QDate date_naissance, QString telephonne, QString adresse)
{
    this->id_E = id_E;
    this->nom = nom;
    this->prenom = prenom;
    this->email = email;
    this->date_naissance = date_naissance;
    this->telephonne = telephonne;
    this->adresse = adresse;
}
int employes::getid_E(){return id_E;}
QString employes::getNom() { return nom; }
QString employes::getPrenom() { return prenom;}
QString employes::getEmail() { return email;}
QDate employes::getDate_de_naissance(){return date_naissance;}
QString employes::getTelephonne (){return telephonne;}
QString employes::getAdresse(){return adresse;}
//Setters
void employes::setid_E(int id_E) { this->id_E = id_E; }
void employes::setNom(QString n) { nom = n; }
void employes::setPrenom(QString p) { prenom = p; }
void employes::setEmail(QString e) { email = e; }
void employes::setDateDeNaissance(QDate d) { date_naissance = d; }
void employes::setTelephonne(QString t) { telephonne = t; }
void employes::setAdresse(QString a) { adresse = a; }

bool employes::ajouter()
{
    QSqlQuery query;
        QString res1 = QString::number(id_E);

        query.prepare("INSERT INTO employes (id_E, nom, prenom, email, date_naissance, telephonne, adresse) "
                      "VALUES (:id_E, :nom, :prenom, :email, :date_naissance, :telephonne, :adresse)");

        // Convert QDate to string before binding.
        query.bindValue(":id_E", res1);
        query.bindValue(":nom", nom);
        query.bindValue(":prenom", prenom);
        query.bindValue(":email", email);
        query.bindValue(":date_naissance", date_naissance);
        query.bindValue(":telephonne", telephonne);
        query.bindValue(":adresse", adresse);

        return query.exec();
}

QSqlQueryModel * employes::afficher()
{
    QSqlQueryModel * model = new QSqlQueryModel();
    model->setQuery("SELECT * FROM employes");

    model->setHeaderData(0, Qt::Horizontal, QObject::tr("Id_E"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Nom"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("Prénom"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("Email"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("Date de naissance"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("Telephonne"));
    model->setHeaderData(6, Qt::Horizontal, QObject::tr("Adresse"));

    return model;
}

bool employes::supprimer(int id_E)
{
    QSqlQuery query;
    QString res = QString::number(id_E);
    query.prepare("DELETE FROM EMPLOYES WHERE id_E = :id_E");
    query.bindValue(":id_E", res);

    return query.exec();
}
bool employes::modifier(int id_E, QString nom, QString prenom, QString email, QDate date_naissance, QString telephonne, QString adresse)
{
    QSqlQuery query;
    QString res1 = QString::number(id_E);

    // Corrected the SQL query to use "UPDATE" instead of "Update INTO"
    query.prepare("UPDATE employes SET nom = :nom, prenom = :prenom, email = :email, date_naissance = :date_naissance, "
                  "telephonne = :telephonne, adresse = :adresse WHERE id_E = :id_E");

    // Convert QDate to string before binding.
    query.bindValue(":id_E", res1);
    query.bindValue(":nom", nom);
    query.bindValue(":prenom", prenom);
    query.bindValue(":email", email);
    query.bindValue(":date_naissance", date_naissance);
    query.bindValue(":telephonne", telephonne);
    query.bindValue(":adresse", adresse);

    if(query.exec())
        return true;
    else
        return false;
}

