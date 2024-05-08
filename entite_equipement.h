#ifndef ENTITE_EQUIPEMENT_H
#define ENTITE_EQUIPEMENT_H
#include <QString>
#include <QSqlQuery>
#include <QMessageBox>
#include <QSqlQueryModel>

class ImageQueryModel : public QSqlQueryModel {
public:

    QVariant data(const QModelIndex &index, int role) const
    {
        if (!index.isValid())
            return QVariant();

        if (role == Qt::DecorationRole && index.column() == 4) { // Supposant que la colonne 4 contient les chemins d'accès aux images
            QString imagePath = QSqlQueryModel::data(index, Qt::DisplayRole).toString();
            QPixmap image(imagePath);

            // Redimensionner l'image selon vos besoins
            QSize imageSize(100, 100); // Par exemple, redimensionner à 100x100 pixels
            image = image.scaled(imageSize, Qt::KeepAspectRatio);

            return QVariant(image);
        }

        return QSqlQueryModel::data(index, role);
    }
};

class entite_equipement
{
    int id_equipement;
     QString type,quantite,prix, image;
public:
    entite_equipement();

    //Constructeur Parametre
    entite_equipement(int,QString,QString,QString,QString);

    //Getters Pour récupérer la valeur
        int getID_equipement();
        QString getType();
        QString getQuantite();
        QString getPrix();
        QString getImage();

        //Setters Pour definir la valeur
         void setID_equipement(int);
         void setType(QString);
         void setQuantite(QString);
         void setPrix(QString);
         void setImage(QString);



         bool ajouter();
 ImageQueryModel* afficher();
         bool supprimer(int);
   bool modifier(int, QString, QString, QString, QString);
        entite_equipement rechercherEquipement(int);
       QSqlQueryModel * search(const QString &) ;
       QSqlQueryModel * rechercherPartype(QString );
       QSqlQueryModel * trierParPrix();
       QSqlQueryModel * trierParPrixd();
       void  statistiquesParQuantite();




};

#endif // ENTITE_EQUIPEMENT_H
