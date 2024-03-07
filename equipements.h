#ifndef EQUIPEMENTS_H
#define EQUIPEMENTS_H

#include <QString>
#include <QSqlQuery>
#include <QMessageBox>
#include <QSqlQueryModel>

class equipements
{
      int id_equipement;
       QString reference,type,quantite,prix;
public:
     //Constructeur Par Défaut
      equipements();

    //Constructeur Parametre
      equipements(int,QString,QString,QString,QString);

     //Getters Pour récupérer la valeur
        int getID_equipement();
        QString getRefrence();
        QString getType();
        QString getQuantite();
        QString getPrix();


        //Setters Pour definir la valeur
         void setID_equipement(int);
         void setRefrence(QString);
         void setType(QString);
         void setQuantite(QString);
         void setPrix(QString);


         bool ajouter();
         QSqlQueryModel * afficher();
         bool supprimer(int);
       bool modifier(int,QString,QString ,QString,QString );
        equipements rechercherEquipement(int);




};

#endif // EQUIPEMENTS_H


