#pragma once

#include "mainwork/timeperiod.h"
#include "postrgresqlconnection.h"

/*Singletone-класс необходимый для управления БД PostgreSQL*/
class PostgreSQLHandle : public PostgreSQLConnection
{
public:

    /*Метод получения ссылки на текущий объект*/
    static PostgreSQLHandle& Instance()
    {
        static PostgreSQLHandle s;
        return s;
    }

    /*Добавление пользователя в БД*/
    bool addUser(QString username, QString password);

    /*Авторизация*/
    bool checkLogin(QString username, QString password);

    /*Остановка таймера в БД*/
    void pauseTimer(QString username, QString currentTime);

    /*Запуск таймера в БД*/
    void startTimer(QString username, QString currentTime, QString newTimerName);

    /*Получение всех таймеров пользователя username*/
    QList<TimePeriod>* getTimers(QString username);

    /*Удаления всех таймеров пользователя username*/
    void deleteAllTimers(QString username);

    /*Последняя ошибка*/
    QString getLastError();

private:
    PostgreSQLHandle(QString host, int port, QString DBName, QString username, QString password) :
        PostgreSQLConnection(host, port, DBName, username, password){}
    PostgreSQLHandle(){}

    PostgreSQLHandle(PostgreSQLHandle const&) = delete;
    PostgreSQLHandle& operator= (PostgreSQLHandle const&) = delete;

    /*Содержит в себе инормацию о последней ошибке*/
    QString lastError;
};
