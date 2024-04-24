#include "connection.h"

connection::connection()
{

}
bool connection::createconnect()
{bool test=false;
    QSqlDatabase db = QSqlDatabase::addDatabase("QODBC");
    db.setDatabaseName("test-bd");
    db.setUserName("system");
    db.setPassword("Rached19");
    if (db.open())
       test=true;


    return test;
}
