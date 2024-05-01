#include "connection.h"
Connection::Connection(){}
bool Connection::createconnection()
{
    db = QSqlDatabase::addDatabase("QODBC");
    bool test = false ;
    db.setDatabaseName("Smart_TV");
    db.setUserName("system");//inserer nom de l'utilisateur
    db.setPassword("123");//inserer mot de passe de cet utilisateur
    if (db.open())
    {
        test = true;
    }
    return test;
}
void Connection::closeConnection(){db.close();}



