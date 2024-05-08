#ifndef ENTITE_PUB_H
#define ENTITE_PUB_H
#include <QString>
#include <QSqlQuery>
#include <QDate>
#include <QSqlQueryModel>
#include <QMessageBox>
#include <QDate>
#include <QTableView>

class Entite_pub
{
public:
    QString ObjectifdeLaCompagne ,Duree,  Frequences ;
      int idpublicite;
      QString VIDEOPATH;

public:
      Entite_pub();
      Entite_pub(int,QString,QString,QString);
      QString getObjectifdeLaCompagne();
      QString getDuree();
      QString getFrequences();
      int getIdPublicite();
      void setObjectifdeLaCompagne(QString );
      void setDuree(QString );
      void setFrequences(QString );
      void setIdPublicite(int );
      bool ajouter();
      bool modifier(int,QString,QString,QString);
      QSqlQueryModel * afficher();
      QSqlQueryModel * triPUB(QString attribut);
        bool supprimer(int);
      bool id_existe(int IdPublicite);
      QSqlQueryModel * rechercherid(int);


  Entite_pub rechercherpub(int);
};

#endif // ENTITE_PUB_H
