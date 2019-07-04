#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStandardItemModel>
#include "mainwork/user.h"
#include <sql/postgresqlhandle.h>
#include <mainwork/stats.h>
#include "mainwork/currenttimer.h"
#include "mainwork/formupdater.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr, User* username = nullptr);
    ~MainWindow();

private slots:
    void on_addTimerButton_clicked();

    void on_stopTimerButton_clicked();

    void on_tableViewTimers_clicked(const QModelIndex &index);

    void on_deleteAllAction_triggered();

    void on_showTimerStatsAction_triggered();

private:
    Ui::MainWindow *ui;
    /*Модель таблицы*/
    QStandardItemModel* tableModel;
    /*Объект управления БД*/
    PostgreSQLHandle& handler = PostgreSQLHandle::Instance();
    /*Информация о пользователе*/
    User* user;
    /*Статистика пользователя*/
    Stats* stats;
    /*Обновление таблицы*/
    FormUpdater* formUpdater;
};

#endif // MAINWINDOW_H
