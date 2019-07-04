#pragma once

#include <QThread>
#include "sql/postgresqlhandle.h"
#include "mainwork/stats.h"
#include "user.h"

/*Класс унаследованный от класса QThread. Необходим для постоянного обновления
таблицы с базы данных*/
class FormUpdater : public QThread
{
public:
    /*В конструктор передаем указатель на стастику, таблицу и пользователя*/
    FormUpdater(Stats* stats, QStandardItemModel* table, User* user);

protected:
    /*Переопределенный метод run,
      небходим для выполнения действий на новом потоке*/
    void run() override;

private:
    Stats* stats_;
    QStandardItemModel* table_;
    User* user_;
};
