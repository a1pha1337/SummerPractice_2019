#include "postgresqlhandle.h"
#include <QCryptographicHash>
#include <QVariant>
#include <QSqlError>
#include <QList>

bool PostgreSQLHandle::addUser(QString username, QString password)
{   

    if (username.length() > 12)
    {
        this->lastError = "Имя пользователя не должно превышать 12 символов!";
        return false;
    }
    else if (username.length() < 3)
    {
        this->lastError = "Имя пользователя не должно быть меньше 3 символов!";
        return false;
    }
    else if (password.length() > 16)
    {
        this->lastError = "Пароль не должен превыашть 16 символов!";
        return false;
    }
    else if (password.length() < 6)
    {
        this->lastError = "Пароль не должен быть меньше 6 символов!";
        return false;
    }

    for (int i = 0; i < username.length(); i++)
    {
        bool checkLetters = username[i] >= 'a' && username[i] <= 'z';
        bool checkDigits = username[i] >= '0' && username[i] <= '9';
        if (!(checkLetters || checkDigits))
        {
            this->lastError = "Логин должен содержать только цифры и латинские буквы!";
            return false;
        }
    }

    QString cmd = "INSERT INTO Accounts(name, password) VALUES ('" + username + "', '"
            + QCryptographicHash::hash(password.toUtf8(), QCryptographicHash::Sha256).toHex() + "')";

    QSqlQuery query(this->db);
    bool isSuccesfull = query.exec(cmd);

    QString addPersonalTable = "CREATE TABLE " + username + "Timers("
                                    "timerName VARCHAR(20) NOT NULL,"
                                    "dateOfStart VARCHAR(20) NOT NULL,"
                                    "dateOfEnd VARCHAR(20)"
                               ")";

    isSuccesfull &= query.exec(addPersonalTable);

    if (!isSuccesfull)
    {
        switch (query.lastError().number())
        {
            case 1:
                this->lastError = "Ошибка подключения к серверу!";
                break;

            case 3:
                this->lastError = "Невозможно добавить аккаунт!";
                break;

            default:
                this->lastError = "Такой пользователь уже существует";
                break;
        }
    }

    return isSuccesfull;
}

bool PostgreSQLHandle::checkLogin(QString username, QString password)
{
    if (username.length() == 0 || password.length() == 0)
    {
        this->lastError = "Поля не должны быть пустыми!";
        return false;
    }

    QString cmd = "SELECT name, password FROM Accounts";
    QString hash = QCryptographicHash::hash(password.toUtf8(), QCryptographicHash::Sha256).toHex();
    QSqlQuery query(this->db);
    query.exec(cmd);

    while (query.next())
    {
        QString uname = query.value(0).toString();

        if (uname == username)
        {
            QString pass = query.value(1).toString();

            if (pass == hash)
                return true;
            else
            {
                this->lastError = "Неверный имя пользователя или пароль!";
                return false;
            }
        }
    }

    this->lastError = "Неверный имя пользователя или пароль!";
    return false;
}

void PostgreSQLHandle::pauseTimer(QString username, QString currentTime)
{
    QString cmd = "UPDATE " + username + "Timers SET dateofend = '" + currentTime + "' WHERE dateofend IS NULL";
    QSqlQuery query(this->db);

    query.exec(cmd);

}

void PostgreSQLHandle::startTimer(QString username, QString currentTime, QString newTimerName)
{
    QString cmd = "INSERT INTO " + username + "Timers VALUES ('" + newTimerName + "', '" + currentTime + "')";
    QSqlQuery query(this->db);

    query.exec(cmd);
}

QList<TimePeriod>* PostgreSQLHandle::getTimers(QString username)
{
    QList<TimePeriod>* timersList = new QList<TimePeriod>();

    QString event;
    QString start;
    QString end;
    bool isWorking;

    QString cmd = "SELECT * FROM " + username + "Timers";
    QSqlQuery query(this->db);

    query.exec(cmd);

    while (query.next())
    {
        event = query.value(0).toString();
        start = query.value(2).toString();
        end = query.value(3).toString();

        if (end == "")
        {
            isWorking = true;
            end = "-";
        }
        else
            isWorking = false;

        timersList->append(TimePeriod(event, start, end, isWorking));
    }

    return timersList;
}

void PostgreSQLHandle::deleteAllTimers(QString username)
{
    QString cmd = "DELETE FROM " + username + "Timers";
    QSqlQuery query(this->db);

    query.exec(cmd);
}

QString PostgreSQLHandle::getLastError()
{
    return this->lastError;
}

