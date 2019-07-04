#include "postrgresqlconnection.h"

PostgreSQLConnection::PostgreSQLConnection(){}

PostgreSQLConnection::PostgreSQLConnection(QString host, int port, QString DBName, QString username, QString password) :
    SqlConnection(host, port, DBName, username, password)
{
    this->db = QSqlDatabase::addDatabase("QPSQL", "conn");
}

bool PostgreSQLConnection::open()
{
    this->db = QSqlDatabase::addDatabase("QPSQL", "conn");

    if (db.isOpen())
        return false;

    this->db.setHostName(this->host_);
    this->db.setPort(this->port_);
    this->db.setDatabaseName(this->DBName_);
    this->db.setUserName(this->username_);
    this->db.setPassword(this->password_);

    this->isOpen = db.open();

    return this->isOpen;
}

void PostgreSQLConnection::close()
{
    this->db.close();
    this->isOpen = db.isOpen();
    QSqlDatabase::removeDatabase("conn");
}
