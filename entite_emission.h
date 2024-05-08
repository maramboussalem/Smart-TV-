#ifndef ENTITE_EMISSION_H
#define ENTITE_EMISSION_H
<<<<<<< HEAD
#include <QDate>
#include <QString>
#include <QSqlQuery>
#include <QMessageBox>
#include <QSqlQueryModel>
#include <QtCharts>
#include <QSqlQuery>

#include "arduino.h"
class Entite_emission
{
    int id_emission;
    QDate date_emission;
    QString titre,categorie,realisateur,duree,description,video,soustitrage;

public:
    Entite_emission();
    Entite_emission(int,QString,QString,QString,QString,QDate,QString,QString,QString);

    int getID();
    QString getTitre();
    QString getCategorie();
    QString getRealisateur();
    QString getDuree();
    QDate getDate_emission();
    QString getDescription();
    QString getvideo();
    QString getsoustitrage();

    void setID(int id_emission);
    void setTitre(QString t);
    void setCategorie(QString c);
    void setRealisateur(QString r);
    void setDuree(QString du);
    void setDate_emission(QDate da);
    void setDescription(QString de);
    void setvideo(QString v);
    void setsoustitrage(QString s);

    // CRUD functionality
    bool ajouter();
    QSqlQueryModel * afficher();
    bool supprimer(int);
    bool modifier(int,QString,QString,QString,QString,QDate,QString,QString,QString);
    void setTotalTime(QTime duree, QString mVideoFilePath);
    QTime getTotalTime(QString mVideoFilePath);

    QSqlQueryModel * rechercher(int);
    Entite_emission rechercherEmission(int);
    QSqlQueryModel * rechercherParid_emission(int);
    QSqlQueryModel * rechercherParCategorie(QString);
    QSqlQueryModel * rechercherParTitre(QString);
    QSqlQueryModel * rechercherParrealisateur(QString);
    QSqlQueryModel * rechercherParduree(QString );
    QSqlQueryModel * rechercherPardate_emission(QDate);

    bool supprimerTout();

    bool existeId(int);
    bool existeTitre(QString);

    QSqlQueryModel * trierPar(QString,QString);

=======
#include <QString>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QDate>

class Entite_emission
{
private:
    int id;
    QString titre, category, duree, realisateur, date, description, horraire;

public:
    Entite_emission();
    Entite_emission(int,QString,QString,QString,QString,QString,QString, QString);
    // Getters
//    QString getTitre() const { return titre; }
//    QString getCategory() const { return category; }
//    QString getDuree() const { return duree; }
//    QString getLangue() const { return langue; }
//    QString getRealisateur() const { return realisateur; }
//    QString getDate() const { return date; }
//    int getId() const { return id; }

//    // Setters
//    void setTitre( QString t) { this->titre = t; }
//    void setCategory(QString c) {this->category = c; }
//    void setDuree( QString d) { this->duree = d; }
//    void setLangue(QString l) { this->langue = l; }
//    void setRealisateur( QString &r) { this->realisateur = r; }
//    void setDate(const QString d) { this->date = d; }
    // CRUD functionality
    bool ajouter();
    bool supprimer(int);
    QSqlQueryModel *afficher();
    bool modifier ();
>>>>>>> 18d955075ebf7e49d498a0f477c7a42083282ca3
};
#endif
