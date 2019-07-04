#include "sqlconnection.h"

SqlConnection::SqlConnection(){}

SqlConnection::SqlConnection(QString host, int port, QString DBName, QString username, QString password)
{
    this->host_ = host;
    this->port_ = port;
    this->DBName_ = DBName;
    this->username_ = username;
    this->password_ = password;
}

void SqlConnection::setHost(QString host)
{
    this->host_ = host;
}

void SqlConnection::setPort(int port)
{
    this->port_ = port;
}

void SqlConnection::setDBName(QString DBName)
{
    this->DBName_ = DBName;
}

void SqlConnection::setUserName(QString username)
{
    this->username_ = username;
}

void SqlConnection::setPassword(QString password)
{
    this->password_ = password;
}

SqlConnection::~SqlConnection() {};
