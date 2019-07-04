#include "formupdater.h"
#include <QException>
#include "mainwork/user.h"

FormUpdater::FormUpdater(Stats* stats, QStandardItemModel* table, User* user)
{
    this->stats_ = stats;
    this->table_ = table;
    this->user_ = user;
}

void FormUpdater::run()
{
    //Открываем БД
    QSqlDatabase db_ = QSqlDatabase::addDatabase("QPSQL", "formUpdater");

    db_.setHostName("13.59.61.33");
    db_.setPort(5432);
    db_.setDatabaseName("Practice");
    db_.setUserName("postgres");
    db_.setPassword("QdfGh12Q");

    db_.open();

    //Содержит все таймеры с БД
    QList<TimePeriod> timersList;

    QString event;
    QString start;
    QString end;
    bool isWorking;

    while (true)
    {
        timersList.clear();

        //Выполняем запрос
        QString cmd = "SELECT * FROM " + this->user_->getUserName() + "Timers";
        QSqlQuery query(db_);

        query.exec(cmd);

        while (query.next())
        {
            event = query.value(0).toString();
            start = query.value(1).toString();
            end = query.value(2).toString();

            if (end == "")
            {
                isWorking = true;
                end = "-";
            }
            else
                isWorking = false;

            timersList.append(TimePeriod(event, start, end, isWorking));
        }

        //Передаем таймеры и указатель на модель таблицы для обновления данных
        this->stats_->ShowTable(table_, timersList);

        QThread::msleep(500);
    }
}
