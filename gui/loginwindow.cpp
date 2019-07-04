#include "loginwindow.h"
#include "ui_loginwindow.h"
#include <QDebug>
#include <QMessageBox>
#include <QThread>

LoginWindow::LoginWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::LoginWindow)
{
    ui->setupUi(this);

    /*Установка значение для подключения к БД*/
    handler.setHost("13.59.61.33");
    handler.setPort(5432);
    handler.setDBName("Practice");
    handler.setPassword("QdfGh12Q");
    handler.setUserName("postgres");
}


LoginWindow::~LoginWindow()
{
    delete ui;
}

/*Нажатие на кнопку Логин*/
void LoginWindow::on_loginButton_clicked()
{
    //Пытаемся открыть БД
    bool successOpen = handler.open();

    //Если БД не открылось сообщаем пользователя
    if (!successOpen)
    {
        QMessageBox::information(this, "Ошибка!", "Отсутсвует подключение к базе данных!");
        handler.close();
        return;
    }

    //Проверся правильность ввода логина и пароля
    bool successLogin = handler.checkLogin(ui->loginEdit->text(), ui->passwordEdit->text());
    if (successLogin)
    {
        handler.close();

        User* user = new User(ui->loginEdit->text());

        MainWindow* mainWindow = new MainWindow(nullptr, user);
        mainWindow->show();

        close();
    }
    else
        QMessageBox::information(this, "Ошибка!", handler.getLastError());

    handler.close();
}

/*Нажатие на кнопку регистрации*/
void LoginWindow::on_registrationButton_clicked()
{   
    registrationWindow window(this);
    window.setModal(true);
    window.exec();
}
