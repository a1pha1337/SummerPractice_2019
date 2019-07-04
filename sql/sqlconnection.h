#pragma once

#include <QString>
#include <QSqlDatabase>
#include <QSqlQuery>

/*Абстрактный класс, который отвечает за подключение к базе данных SQL*/
class SqlConnection
{
public:
    SqlConnection();
    SqlConnection(QString host, int port, QString DBName, QString username, QString password);

    /*Необходим для открытия базы данных*/
    virtual bool open() = 0;
    /*Необходим для закрытия базы данных*/
    virtual void close() = 0;


    /*Устанавливает текущее значение host*/
    void setHost(QString host);
    /*Устанавливает порт БД*/
    void setPort(int port);
    /*Устанавливает название БД*/
    void setDBName(QString DBName);
    /*Устанавливает пользователя БД*/
    void setUserName(QString username);
    /*Устанавливает пароль от БД*/
    void setPassword(QString password);

    virtual ~SqlConnection() = 0;

    /*Переменная (открыта ли БД)*/
    bool isOpen;
protected:
    QString host_;
    int port_;
    QString DBName_;
    QString username_;
    QString password_;

    QSqlDatabase db;
};
