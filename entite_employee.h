#ifndef ENTITE_EMPLOYEE_H
#define ENTITE_EMPLOYEE_H
#include <QDate>
#include <QString>
#include <QSqlQuery>
#include <QMessageBox>
#include <QSqlQueryModel>
#include <QtCharts>
#include <QPainter>
#include <QSqlDatabase>
class entite_employee
{
    QString nom, prenom, email, adresse,password;
    int id_E;
    QDate date_naissance;
public:
    entite_employee();
    entite_employee(int, QString, QString, QString, QDate, QString, QString);

    int getid_E();
    QString getNom() ;
    QString getPrenom() ;
    QString getEmail() ;
    QDate getDate_naissance();
    QString getTelephonne ();
    QString getAdresse();
    //Setters
    void setid_E(int ) ;
    void setNom(QString );
    void setPrenom(QString );
    void setEmail(QString);
    void setDate_Naissance(QDate ) ;
    void setTelephonne(QString) ;
    void setAdresse(QString ) ;
    // Fonctionnalités de Base relatives à l'entite employee
    bool ajouter();
    QSqlQueryModel * afficher();
    bool supprimer (int);
    bool modifier(int, QString, QString, QString, QDate, QString, QString);
    QSqlQueryModel *rechercher(int id_E);
    void Recherche(int id_E);
    void trie();
    void pdf();
    void Statistique();
    void Email(const QString &email);
    QSqlQueryModel *rechercher_M(QString adresse);
    void Recherche_M(QString adresse);
    void email_envoie();
};

#endif // ENTITE_EMPLOYEE_H
