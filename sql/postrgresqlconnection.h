#pragma once

#include "sqlconnection.h"

/*Класс необходимый для подключения к БД PostgreSQL*/
class PostgreSQLConnection : public SqlConnection
{
public:
    PostgreSQLConnection();
    PostgreSQLConnection(QString host, int port, QString DBName, QString username, QString password);

    /*Метод открытия БД*/
    virtual bool open() override;
    /*Метод закрытия БД*/
    virtual void close() override;
};
