#ifndef EMPLOYES_H
#define EMPLOYES_H
#include <QDate>
#include <QString>
#include <QSqlQuery>
#include <QMessageBox>
#include <QSqlQueryModel>

class employes
{
    QString nom, prenom, email, adresse,telephonne;
    int id_E;
    QDate date_naissance;
public:
    // Constructors
    employes();
    employes(int, QString, QString, QString, QDate, QString, QString);

    int getid_E();
    QString getNom() ;
    QString getPrenom() ;
    QString getEmail() ;
    QDate getDate_de_naissance();
    QString getTelephonne ();
    QString getAdresse();
    //Setters
    void setid_E(int ) ;
    void setNom(QString );
    void setPrenom(QString );
    void setEmail(QString);
    void setDateDeNaissance(QDate ) ;
    void setTelephonne(QString) ;
    void setAdresse(QString ) ;
    // Fonctionnalités de Base relatives à l'entite employee
    bool ajouter();
    QSqlQueryModel * afficher();
    bool supprimer (int);
   bool modifier(int, QString, QString, QString, QDate, QString, QString);
   QSqlQueryModel * rechercher(int);
};
#endif // EMPLOYEE_H
