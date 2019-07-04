#ifndef LOGINWINDOW_H
#define LOGINWINDOW_H

#include <QMainWindow>
#include <sql/postgresqlhandle.h>
#include "gui/mainwindow.h"
#include "gui/registrationwindow.h"

namespace Ui {
class LoginWindow;
}

class LoginWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit LoginWindow(QWidget *parent = nullptr);
    /*Объект управления базой данных*/
    PostgreSQLHandle& handler = PostgreSQLHandle::Instance();
    ~LoginWindow();

private slots:

    void on_loginButton_clicked();

    void on_registrationButton_clicked();

private:
    Ui::LoginWindow *ui;
};

#endif // LOGINWINDOW_H
