#include "timeperiod.h"
#include <QStringList>
#include <QDateTime>

TimePeriod::TimePeriod(){}

TimePeriod::TimePeriod(const TimePeriod& object)
{
    this->event_ = object.event_;
    this->start_ = object.start_;
    this->end_ = object.end_;
    this->isWorking_ = object.isWorking_;
}

TimePeriod::TimePeriod(QString event, QString start, QString end, bool isWorking)
{
    this->event_.setTitle(event);
    this->start_ = start;
    this->end_ = end;
    this->isWorking_ = isWorking;
}

QList<int> TimePeriod::getTimeInterval()
{
    //Берем начальную дату
    QDateTime startTime;
    startTime = QDateTime::fromString(this->start_, "dd.MM.yyyy hh:mm:ss");

    //Берем конечную дату
    QDateTime endTime;
    if (this->end_ == "-")
        endTime = QDateTime::currentDateTime();
    else
        endTime = QDateTime::fromString(this->end_, "dd.MM.yyyy hh:mm:ss");

    //Находим интеравал между датами в секундах
    qint64 secsInterval = startTime.secsTo(endTime);

    qint64 hours = 0;
    qint64 minutes = 0;
    qint64 seconds = 0;

    //Находим кол-во часов
    hours = secsInterval / 3600;
    secsInterval -= hours * 3600;

    //Находим кол-во минут
    minutes = secsInterval / 60;
    secsInterval -= minutes * 60;

    //Находим кол-во секунд
    seconds = secsInterval;
    secsInterval -= seconds;

    //Интервал времени хранится в списке
    QList<int> timeInterval;
    timeInterval.append(static_cast<int>(hours));
    timeInterval.append(static_cast<int>(minutes));
    timeInterval.append(static_cast<int>(seconds));

    return timeInterval;
}


QString TimePeriod::getStartTime()
{
    return this->start_;
}

QString TimePeriod::getEndTime()
{
    return this->end_;
}

QString TimePeriod::getEventName()
{
    return this->event_.getTitle();
}

QString TimePeriod::getState()
{
    if (this->isWorking_)
        return "Работает";
    else
        return "Не работает";
}

bool TimePeriod::getBoolState()
{
    return this->isWorking_;
}

Event TimePeriod::getEvent()
{
    return this->event_;
}

bool operator== (TimePeriod& first, TimePeriod& second)
{
    return (first.getEventName() == second.getEventName() && first.getStartTime() == second.getStartTime()
            && first.getEndTime() == second.getEndTime() && first.getBoolState() == second.getBoolState());
}
