#pragma once

#include <QString>

/*Класс, который содержит в себе информацию пользователя*/
class User
{
public:
    User(QString username);

    /*Возвращает имя пользователя*/
    QString getUserName();

private:
    /*Имя пользователя*/
    QString username_;
};
