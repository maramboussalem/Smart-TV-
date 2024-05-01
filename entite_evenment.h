#ifndef ENTITE_EVENMENT_H
#define ENTITE_EVENMENT_H
#include <QString>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QDate>
class Entite_evenment
{
private:
    int id;
    QString titre, description, category,location;
    QDateTime date ;
public:
    Entite_evenment();
    Entite_evenment(int,QString,QString,QDateTime,QString,QString);
    // Getters
      QString getTitre() const { return titre; }
      QString getCategory() const { return category; }
      QString getLocation() const { return location; }
      QString getDescription() const { return description; }
      QDateTime getDate() const { return date; }
      int getId() const { return id; }

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
    QSqlQueryModel *afficher_selon_titre(QString title);
    QSqlQueryModel *afficher_Tri(QString title);
    QSqlQueryModel *afficher_Selon_Date(QDate date);

    QSqlQueryModel *afficher_Selon_Asc();
    QSqlQueryModel *afficher_Selon_Desc();
    bool modifier ();
    void statistique();
    QString locationById(int id);


    Entite_evenment rechercher(int);
};

#endif // ENTITE_EVENMENT_H
