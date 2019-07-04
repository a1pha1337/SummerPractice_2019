#pragma once

#include "timeperiod.h"
#include "sql/postgresqlhandle.h"

/*Данный класс необходим для запуска или остановки некоторого таймера*/
class CurrentTimer : public TimePeriod
{
public:
    CurrentTimer();
    CurrentTimer(const TimePeriod obj);

    /*Запускает таймер для пользователся username под названием newTimerName*/
    static bool Start(QString username, QString newTimerName);

    /*Останавливает текущий таймер*/
    bool Pause(QString username);
};
