#pragma once

#include <QList>
#include "timeperiod.h"
#include <QStandardItemModel>

/*Данный класс содержит все таймеры пользователя*/
class Stats
{
public:
    Stats();
    Stats(QList<TimePeriod> timeList);

    /*Метод для установки таймеров*/
    void SetTimers(QList<TimePeriod> timeList);

    /*Возвращает таймер по индексу*/
    TimePeriod GetTimerAtIndex(int index);

    /*Возвращает все таймеры*/
    QList<TimePeriod> GetTimers();

    /*Возвращает таймер по названию*/
    QList<TimePeriod> GetTimersByTitle(QString title);

    /*Возвращает суммарное время работы таймера*/
    QList<int> GetTimersInterval(QString title);

    /*Возвращает кол-во таймеров*/
    int Count();

    /*Возвращает кол-во таймеров по имени*/
    int Count(QString title);

    /*Добавляет новый таймер*/
    void Add(TimePeriod timePeriod);

    /*Обновляет таблицу с таймерами*/
    void ShowTable(QStandardItemModel* tableModel, QList<TimePeriod> newTimers);
private:
    /*Список таймеров*/
    QList<TimePeriod> timelist_;
};
