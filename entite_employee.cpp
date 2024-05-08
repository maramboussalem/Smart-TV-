#include "entite_employee.h"
#include <QtSql/QSqlQuery>
#include <QDate>
#include <QSqlError>
#include <QDebug>
#include<QMessageBox>
#include <QtCharts>
#include <QPainter>
#include <QRegularExpression>
#include <QStringList>
#include <QMessageBox>
#include <QtNetwork/QDnsMailExchangeRecord>
#include <QRegularExpression>
#include <QSqlDatabase>
entite_employee::entite_employee()
{
    id_E = 0;
    nom = "";
    prenom = "";
    email = "";
    date_naissance = QDate();
    password = "";
    adresse = "";
}
entite_employee::entite_employee(int id_E, QString nom, QString prenom, QString email, QDate date_naissance, QString password, QString adresse)
{
    this->id_E = id_E;
    this->nom = nom;
    this->prenom = prenom;
    this->email = email;
    this->date_naissance = date_naissance;
    this->password = password;
    this->adresse = adresse;
}
int entite_employee::getid_E(){return id_E;}
QString entite_employee::getNom() { return nom; }
QString entite_employee::getPrenom() { return prenom;}
QString entite_employee::getEmail() { return email;}
QDate entite_employee::getDate_naissance(){return date_naissance;}
QString entite_employee::getTelephonne (){return password;}
QString entite_employee::getAdresse(){return adresse;}
//Setters
void entite_employee::setid_E(int id_E) { this->id_E = id_E; }
void entite_employee::setNom(QString n) { nom = n; }
void entite_employee::setPrenom(QString p) { prenom = p; }
void entite_employee::setEmail(QString e) { email = e; }
void entite_employee::setDate_Naissance(QDate d) { date_naissance = d; }
void entite_employee::setTelephonne(QString t) { password = t; }
void entite_employee::setAdresse(QString a) { adresse = a; }

bool entite_employee::ajouter()
{
    QSqlQuery query;
            QString res1 = QString::number(id_E);

            query.prepare("INSERT INTO employes (id_E, nom, prenom, email, date_naissance, password, adresse) "
                          "VALUES (:id_E, :nom, :prenom, :email, :date_naissance, :password, :adresse)");

            // Convert QDate to string before binding.
            query.bindValue(":id_E", res1);
            query.bindValue(":nom", nom);
            query.bindValue(":prenom", prenom);
            query.bindValue(":email", email);
            query.bindValue(":date_naissance", date_naissance);
            query.bindValue(":password", password);
            query.bindValue(":adresse", adresse);

            return query.exec();
}

QSqlQueryModel * entite_employee::afficher()
{
    QSqlQueryModel * model = new QSqlQueryModel();
    model->setQuery("SELECT * FROM employes");

    model->setHeaderData(0, Qt::Horizontal, QObject::tr("Id_E"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Nom"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("Prénom"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("Email"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("Date de naissance"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("Password"));
    model->setHeaderData(6, Qt::Horizontal, QObject::tr("Adresse"));

    return model;
}

bool entite_employee::supprimer(int id_E)
{
    QSqlQuery query;
    QString res = QString::number(id_E);
    query.prepare("DELETE FROM EMPLOYES WHERE id_E = :id_E");
    query.bindValue(":id_E", res);

    return query.exec();
}
bool entite_employee::modifier(int id_E, QString nom, QString prenom, QString email, QDate date_naissance, QString password, QString adresse)
{
    QSqlQuery query;
    QString res1 = QString::number(id_E);

    // Corrected the SQL query to use "UPDATE" instead of "Update INTO"
    query.prepare("UPDATE employes SET nom = :nom, prenom = :prenom, email = :email, date_naissance = :date_naissance, password = :password, adresse = :adresse WHERE id_E = :id_E");

    // Convert QDate to string before binding.
    query.bindValue(":id_E", res1);
    query.bindValue(":nom", nom);
    query.bindValue(":prenom", prenom);
    query.bindValue(":email", email);
    query.bindValue(":date_naissance", date_naissance);
    query.bindValue(":password", password);
    query.bindValue(":adresse", adresse);

    if(query.exec())
        return true;
    else
        return false;
}
void entite_employee::Recherche(int id_E)
{
    QSqlQuery query;
    query.prepare("SELECT * FROM employes WHERE id_E = :id_E");
    query.bindValue(":id_E", id_E);

    // Exécute la requête
    if (query.exec() && query.next()) {
        // Récupère les données de la requête
        int id = query.value(0).toInt();
        QString nom = query.value(1).toString();
        QString prenom = query.value(2).toString();
        QString email = query.value(3).toString();
        QDate date_naissance = query.value(4).toDate();
        QString password = query.value(5).toString();
        QString adresse = query.value(6).toString();

        // Affiche les coordonnées de l'employé dans une boîte de message
        QMessageBox::information(nullptr, "Coordonnées de l'employé",
                                 "ID : " + QString::number(id) + "\n"
                                 "Nom : " + nom + "\n"
                                 "Prénom : " + prenom + "\n"
                                 "Email : " + email + "\n"
                                 "Date de naissance : " + date_naissance.toString("yyyy-MM-dd") + "\n"
                                 "password : " + password + "\n"
                                 "Adresse : " + adresse, QMessageBox::Ok);
    } else {
        // Affiche un message si l'employé n'est pas trouvé ou s'il y a une erreur
        QMessageBox::warning(nullptr, "Erreur", "L'employé avec l'ID spécifié n'existe pas ou une erreur s'est produite lors de la recherche.", QMessageBox::Ok);
    }

}
void entite_employee::Statistique()
{
    QSqlQuery query("SELECT adresse, COUNT(*) FROM employes GROUP BY adresse");
        QtCharts::QBarSeries *series = new QtCharts::QBarSeries();

        while (query.next())
        {
            QString adresse = query.value(0).toString();
            int count = query.value(1).toInt();

            QtCharts::QBarSet *set = new QtCharts::QBarSet(adresse); // Utilisez l'adresse comme libellé
            *set << count;

            series->append(set);
        }

        QtCharts::QChart *chart = new QtCharts::QChart();
        chart->addSeries(series);
        chart->setTitle("Nombre d'employés par adresse");
        chart->setAnimationOptions(QtCharts::QChart::SeriesAnimations);

        QStringList adresses;
        // Ajoutez les noms de vos adresses ici si vous ne les avez pas déjà dans la base de données

        QtCharts::QBarCategoryAxis *axis = new QtCharts::QBarCategoryAxis();
        axis->append(adresses);
        chart->createDefaultAxes();
        chart->setAxisX(axis, series);
        chart->legend()->setVisible(true);

        QtCharts::QChartView *chartView = new QtCharts::QChartView(chart);
        chartView->resize(900, 600);
        chartView->show();
}
void entite_employee::trie()
{
    QSqlQueryModel *model = new QSqlQueryModel();
        model->setQuery("SELECT * FROM employes ORDER BY date_naissance");

        // Met à jour les en-têtes du modèle avec des noms significatifs
        model->setHeaderData(0, Qt::Horizontal, QObject::tr("Id_E"));
        model->setHeaderData(1, Qt::Horizontal, QObject::tr("Nom"));
        model->setHeaderData(2, Qt::Horizontal, QObject::tr("Prénom"));
        model->setHeaderData(3, Qt::Horizontal, QObject::tr("Email"));
        model->setHeaderData(4, Qt::Horizontal, QObject::tr("Date de naissance"));
        model->setHeaderData(5, Qt::Horizontal, QObject::tr("password"));
        model->setHeaderData(6, Qt::Horizontal, QObject::tr("Adresse"));

        // Affiche le modèle trié
        QTableView *tableView = new QTableView;
        tableView->setModel(model);
        tableView->show();
}
void entite_employee::Email(const QString &email)
{
    // Vérifier si l'e-mail est au format "nom@gmail.com"
        QRegularExpression emailRegex("[a-zA-Z0-9._%+-]+@gmail.com");
        if (!emailRegex.match(email).hasMatch()) {
            qDebug() << "Adresse e-mail invalide : " << email;
            return;
        }

        // Adresses e-mails valides pour l'envoi
        QStringList validEmails = {"emission@gmail.com", "employes@gmail.com", "publicite@gmail.com", "equippement@gmail.com", "sponsore@gmail.com", "evennnement@gmail.com"};

        // Vérifier si l'e-mail est dans la liste des adresses valides
        if (validEmails.contains(email)) {
            // Code pour envoyer un e-mail
            qDebug() << "Valide : " << email;
            // Vous devez écrire le code pour envoyer un e-mail ici
        } else {
            qDebug() << "Non valide : " << email;
        }
}
void entite_employee::pdf()
{
    QPdfWriter pdf("C:/Users/Mega-PC/Bureau/Atelier_ConnexionEya/employes.pdf");
        QPainter painter(&pdf);

        if (painter.begin(&pdf))
        {
            // Début de la peinture sur le PDF
            // Styles
            QFont titleFont("Times New Roman", 30);
            QFont headerFont("Times New Roman", 8); // Augmenter la taille de la police pour les en-têtes
            QFont dataFont("Arial", 6); // Augmenter la taille de la police pour les données

            // Dessiner le titre
            painter.setFont(titleFont);
            painter.drawText(3000, 1400, "Liste des Employés");

            // Dessiner les bordures
            painter.setPen(Qt::black);

            // Dessiner les en-têtes de colonne
            QStringList headers = {"Id_E", "Nom", "Prénom", "Email", "Date de naissance", "password", "Adresse"};
            painter.setFont(headerFont);
            int x = 300; // Position horizontale initiale
            int y = 3300; // Position verticale
            int columnWidth = 1300; // Largeur de chaque colonne

            for (int col = 0; col < headers.size(); ++col)
            {
                // Dessiner le rectangle autour de l'en-tête
                painter.drawRect(x, y, columnWidth, 150); // Augmenter la hauteur de l'en-tête

                // Dessiner le texte centré dans la colonne
                painter.drawText(x, y, columnWidth, 150, Qt::AlignCenter, headers[col]);

                // Déplacer la position horizontale pour la prochaine colonne
                x += columnWidth;
            }

            painter.end(); // Fin de la peinture sur le PDF
        } else {
            qDebug() << "Erreur : Impossible de commencer la peinture sur le PDF.";
        }
}
QSqlQueryModel * entite_employee::rechercher_M(QString adresse)
{
    QSqlQueryModel *model = new QSqlQueryModel();
    if(adresse.isEmpty()) {
        model->setQuery("SELECT * FROM employes");
    } else {
        model->setQuery("SELECT * FROM employes WHERE adresse='" + adresse + "'");
    }
    return model;
}
