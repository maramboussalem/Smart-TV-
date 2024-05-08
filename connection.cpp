#include "connection.h"
Connection::Connection(){}
bool Connection::createconnection()
{
    db = QSqlDatabase::addDatabase("QODBC");
    bool test = false ;
<<<<<<< HEAD
    db.setDatabaseName("Smart_TV");
    db.setUserName("system");//inserer nom de l'utilisateur
    db.setPassword("123");//inserer mot de passe de cet utilisateur
=======
    db.setDatabaseName("test_db");
    db.setUserName("alaa");
    db.setPassword("alaa");
>>>>>>> 18d955075ebf7e49d498a0f477c7a42083282ca3
    if (db.open())
    {
        test = true;
    }
    return test;
}
void Connection::closeConnection(){db.close();}
<<<<<<< HEAD



=======
>>>>>>> 18d955075ebf7e49d498a0f477c7a42083282ca3
