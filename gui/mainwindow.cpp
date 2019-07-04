#include <QInputDialog>
#include <QDebug>
#include <QException>
#include <QMessageBox>
#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent, User* username) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->user = username;

    //Создание модели таблицы
    tableModel = new QStandardItemModel(0, 4, this);
    ui->tableViewTimers->setModel(tableModel);
    ui->tableViewTimers->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    //Выставление названий каждого столбца таблицы
    tableModel->setHeaderData(0, Qt::Horizontal, "Название таймера");
    tableModel->setHeaderData(1, Qt::Horizontal, "Дата запуска таймера");
    tableModel->setHeaderData(2, Qt::Horizontal, "Дата завершения таймера");
    tableModel->setHeaderData(3, Qt::Horizontal, "Таймер работает");

    //Создаем статистику
    stats = new Stats();

    formUpdater = new FormUpdater(stats, tableModel, username);

    //Запускаемя formUpdater на другом потоке
    formUpdater->start();
}

MainWindow::~MainWindow()
{
    handler.close();
    delete formUpdater;
    delete stats;
    delete ui;
}

/*Нажатие на кнопку создания нового таймера*/
void MainWindow::on_addTimerButton_clicked()
{
    bool bOk;
    QString newTimerName = QInputDialog::getText(this, "Название таймера", "", QLineEdit::Normal, QString(), &bOk);

    if (newTimerName.count() == 0)
    {
        QMessageBox::information(this, "Добавление таймера", "Название таймера не может быть пустым!");
        return;
    }

    //Пользователь нажал "ОК"
    if (bOk)
    {
        //Берем все таймеры
        QList<TimePeriod> timers = stats->GetTimers();

        for (int i = 0; i < timers.count(); i++)
        {
            //Приводим таймеры к типу CurrentTimer
            CurrentTimer ct(timers[i]);

            if (ct.getBoolState())
            {
                //Останавливаем работающий таймер
                ct.Pause(user->getUserName());
            }
        }

        //Запускаем новый таймер
        CurrentTimer::Start(user->getUserName(), newTimerName);
    }
}

/*Нажатие на остановку текущего таймера*/
void MainWindow::on_stopTimerButton_clicked()
{
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Остановка", "Вы точно хотите остановить таймер?");

    //Если пользователь нажал на кнопку "Yes"
    if (reply == QMessageBox::Yes)
    {
        //Берем все таймеры
        QList<TimePeriod> timers = stats->GetTimers();

        for (int i = 0; i < timers.count(); i++)
        {
            CurrentTimer ct(timers[i]);

            if (ct.getBoolState())
            {
                //Останавливаем таймер
                ct.Pause(user->getUserName());
            }
        }
    }
}

/*Нажатие на строку в таблице*/
void MainWindow::on_tableViewTimers_clicked(const QModelIndex &index)
{
   QList<int> timeInterval = stats->GetTimerAtIndex(index.row()).getTimeInterval();

   QString information = "Прошло ";

   if (timeInterval[0] != 0)
   {
       information += QString::number(timeInterval[0]) + " часов, ";
   }

   if (timeInterval[1] != 0)
   {
       information += QString::number(timeInterval[1]) + " минут, ";
   }

   if (timeInterval[2] != 0)
   {
       information += QString::number(timeInterval[2]) + " секунд.";
   }

   QMessageBox::information(this, "Информация о таймере", information);
}

/*Нажатие на удаление всей статистика*/
void MainWindow::on_deleteAllAction_triggered()
{
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Удаление статистики!", "Вы точно хотите удалить всю статистику?");

    if (reply == QMessageBox::Yes)
    {
        handler.open();
        tableModel->setRowCount(0);
        handler.deleteAllTimers(user->getUserName());
        handler.close();
    }
}

/*Нажатие на показ статистики таймера*/
void MainWindow::on_showTimerStatsAction_triggered()
{
    bool bOk;
    QString title = QInputDialog::getText(this, "Название таймера", "", QLineEdit::Normal, QString(), &bOk);

    //Пользователь нажал "ОК"
    if (bOk)
    {
        //Кол-во таймеров
        int count = stats->Count(title);

        if (count == 0)
        {
            QMessageBox::information(this, "Статистика", "Такого таймера не существует!");
            return;
        }

        QString timeInformation;

        QList<int> timeInterval = stats->GetTimersInterval(title);

        //Приводим информацию к более красивому виду
        if (timeInterval[0] != 0)
        {
            timeInformation += QString::number(timeInterval[0]) + " часов, ";
        }

        if (timeInterval[1] != 0)
        {
            timeInformation += QString::number(timeInterval[1]) + " минут, ";
        }

        if (timeInterval[2] != 0)
        {
            timeInformation += QString::number(timeInterval[2]) + " секунд.";
        }

        QString information = "Вы запускали таймер \"" + title + "\" " + QString::number(count) + " раз и потратили суммарно " + timeInformation;
        QMessageBox::information(this, "Статистика", information);
    }
}
