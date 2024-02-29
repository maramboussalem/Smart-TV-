#ifndef EMISSIONS_H
#define EMISSIONS_H
#include <QDate>
#include <QString>
#include <QSqlQuery>
#include <QMessageBox>
#include <QSqlQueryModel>

class Emissions
{
    int id_emission;
    QDate date_emission;
    QString titre,categorie,realisateur,duree,description;

public:
    //Constructeur Par Défaut
    Emissions();
    //Constructeur Parametre
    Emissions(int,QString,QString,QString,QString,QDate,QString);

    //Getters Pour récupérer la valeur
    int getID();
    QString getTitre();
    QString getCategorie();
    QString getRealisateur();
    QString getDuree();
    QDate getDate_emission();
    QString getDescription();

    //Setters Pour definir la valeur
    void setID(int id_emission);
    void setTitre(QString t);
    void setCategorie(QString c);
    void setRealisateur(QString r);
    void setDuree(QString du);
    void setDate_emission(QDate da);
    void setDescription(QString de);

    bool ajouter();
    QSqlQueryModel * afficher();
    bool supprimer(int);
    bool modifier(int,QString,QString,QString,QString,QDate,QString);
    QSqlQueryModel * rechercher(int);

};

#endif // EMISSIONS_H
