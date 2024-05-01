#include "connection.h"
#include <QSqlDatabase>
connection::connection()
{

}
bool connection::createconnect()
{
    bool test=false;
    QSqlDatabase db = QSqlDatabase::addDatabase("QODBC");
    db.setDatabaseName("SMARTTV");
    db.setUserName("system");//inserer nom de l'utilisateur
    db.setPassword("eya2003");//inserer mot de passe de cet utilisateur

    if (db.open())

    test=true;

    return  test;
}
void connection::closeConnection()
{
    db.close();
}
