#include "stats.h"

Stats::Stats(){}

Stats::Stats(QList<TimePeriod> timeList)
{
    this->timelist_ = timeList;
}

void Stats::SetTimers(QList<TimePeriod> timeList)
{
    this->timelist_ = timeList;
}

QList<TimePeriod> Stats::GetTimers()
{
    return this->timelist_;
}

TimePeriod Stats::GetTimerAtIndex(int index)
{
    return this->timelist_.at(index);
}

QList<TimePeriod> Stats::GetTimersByTitle(QString title)
{
    QList<TimePeriod> timers;

    foreach (TimePeriod i, this->timelist_)
    {
        if (i.getEvent().getTitle() == title)
            timers.append(i);
    }

    return timers;
}

QList<int> Stats::GetTimersInterval(QString title)
{
    QList<TimePeriod> timers = this->GetTimersByTitle(title);

    int hours = 0;
    int minutes = 0;
    int seconds = 0;

    //У каждого таймера находим его время работы
    foreach (TimePeriod i, timers)
    {
        QList<int> timeInterval;

        timeInterval = i.getTimeInterval();

        hours += timeInterval[0];
        minutes += timeInterval[1];
        seconds += timeInterval[2];
    }

    if (seconds >= 60)
    {
        int sMinutes = seconds / 60;
        minutes += sMinutes;
        seconds -= sMinutes * 60;
    }

    if (minutes >= 60)
    {
        int sHours = minutes / 60;
        hours += sHours;
        minutes -= sHours * 60;
    }

    QList<int> timeInterval;
    timeInterval.append(hours);
    timeInterval.append(minutes);
    timeInterval.append(seconds);

    return timeInterval;
}

int Stats::Count()
{
    return this->timelist_.count();
}

int Stats::Count(QString title)
{
    return this->GetTimersByTitle(title).count();
}

void Stats::ShowTable(QStandardItemModel *tableModel, QList<TimePeriod> newTimers)
{
    //Необходим для добавления строк в таблицу
    QList<QStandardItem *> items;

    //Кол-во итераций одного из циклов
    int times;

    //Если кол-во таймеров в БД больше или равно, чем в таблице
    if (newTimers.count() >= this->timelist_.count())
    {
        times = newTimers.count();
        for (int i = 0; i < times; i++)
        {
            //Если в таблице еще есть значения
            if (this->timelist_.count() > i)
            {
                if (this->timelist_[i] == newTimers[i])
                    continue;
                else
                {
                    this->timelist_.removeAt(i);
                    this->timelist_.append(newTimers[i]);

                    tableModel->removeRows(i, 1);

                    items.clear();

                    items.append(new QStandardItem(newTimers[i].getEventName()));
                    items.append(new QStandardItem(newTimers[i].getStartTime()));
                    items.append(new QStandardItem(newTimers[i].getEndTime()));
                    items.append(new QStandardItem(newTimers[i].getState()));

                    tableModel->appendRow(items);
                }
            }
            else //Если в таблице закончились значения
            {
                //Добавляем новый таймер из БД в список
                this->Add(newTimers[i]);

                items.clear();

                //Добавляем новый таймер непосредственно в таблицу
                items.append(new QStandardItem(newTimers[i].getEventName()));
                items.append(new QStandardItem(newTimers[i].getStartTime()));
                items.append(new QStandardItem(newTimers[i].getEndTime()));
                items.append(new QStandardItem(newTimers[i].getState()));

                tableModel->appendRow(items);
            }
        }
    }
    else    //Если же в таблице больше таймеров, чем в таблице
    {
        times = this->timelist_.count();
        for (int i = 0; i < times; i++)
        {
            //Если в БД еще есть таймеры
            if (newTimers.count() > i)
            {
                //Если таймеры равны, то пропускаем итерацию
                if (this->timelist_[i] == newTimers[i])
                    continue;
                else    //Если таймеры не равны
                {
                    //Исправляем значения в таблице
                    this->timelist_.removeAt(i);
                    this->timelist_.append(newTimers[i]);

                    tableModel->removeRows(i, 1);

                    items.clear();

                    items.append(new QStandardItem(newTimers[i].getEventName()));
                    items.append(new QStandardItem(newTimers[i].getStartTime()));
                    items.append(new QStandardItem(newTimers[i].getEndTime()));
                    items.append(new QStandardItem(newTimers[i].getState()));

                    tableModel->appendRow(items);
                }
            }
            else    //Если в БД больше нет таймеров
            {
                //Удаляем лишние таймеры
                this->timelist_.removeAt(i);
                tableModel->removeRows(i, 1);
            }
        }
    }
}

void Stats::Add(TimePeriod timePeriod)
{
    this->timelist_.append(timePeriod);
}
