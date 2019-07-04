#pragma once

#include <QString>
#include "event.h"

/*Класс, который содержит в себе всю информацию о таймере*/
class TimePeriod
{
public:
    TimePeriod();
    TimePeriod(const TimePeriod& object);
    TimePeriod(QString event, QString start, QString end, bool isWorking);

    /*Возвращает интервал времени между запуском и отключение таймера*/
    QList<int> getTimeInterval();

    /*Возвращает дату старта таймера*/
    QString getStartTime();

    /*Возвращает дату конца таймера*/
    QString getEndTime();

    /*Возвращает событие таймера*/
    QString getEventName();

    /*Возвращает состояние таймера*/
    QString getState();

    /*Возвращает состояние таймера*/
    bool getBoolState();

    /*Возвращает событие таймера*/
    Event getEvent();

    friend bool operator== (TimePeriod& first, TimePeriod& second);
protected:
    /*Дата старта таймера*/
    QString start_;
    /*Дата окончания таймера*/
    QString end_;
    /*Событие таймера*/
    Event event_;
    /*Состояние таймера*/
    bool isWorking_;
};
