#pragma once

#include <QString>

/*Класс, который содержит в себе событие текущего таймера*/
class Event
{
public:
    Event();
    Event(QString title);

    /*Установить событие таймера*/
    void setTitle(QString title);

    /*Получить событие таймера*/
    QString getTitle();

private:
    /*Название события*/
    QString title_;
};
