#include "currenttimer.h"
#include <QDateTime>

CurrentTimer::CurrentTimer(){}

 CurrentTimer::CurrentTimer(TimePeriod obj)
 {
     this->event_ = obj.getEvent();
     this->start_ = obj.getStartTime();
     this->end_ = obj.getEndTime();
     this->isWorking_ = obj.getBoolState();
 }

bool CurrentTimer::Start(QString username, QString newTimerName)
{
    //Подключаемся к БД
    PostgreSQLHandle& handler = PostgreSQLHandle::Instance();
    handler.open();

    //Берем текущую дату
    QDateTime dateTime = QDateTime::currentDateTime();
    QString currentDateTimeStr = dateTime.toString("dd.MM.yyyy hh:mm:ss");

    //Запускаем таймер и закрываем подключение
    handler.startTimer(username, currentDateTimeStr, newTimerName);
    handler.close();
}

bool CurrentTimer::Pause(QString username)
{
    if (this->isWorking_)
    {
        //Подключаемся к БД
        PostgreSQLHandle& handler = PostgreSQLHandle::Instance();
        handler.open();

        //Берем текущую дату
        QDateTime dateTime = QDateTime::currentDateTime();
        QString currentDateTimeStr = dateTime.toString("dd.MM.yyyy hh:mm:ss");
        this->end_ = currentDateTimeStr;

        //Останавливаем таймер
        handler.pauseTimer(username, currentDateTimeStr);

        this->isWorking_ = false;

        //Закрываем подключение
        handler.close();

        return true;
    }
    else
        return false;
}
