#include "registrationwindow.h"
#include "ui_registrationwindow.h"
#include <QMessageBox>
#include <QDebug>

registrationWindow::registrationWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::registrationWindow)
{
    ui->setupUi(this);
}

registrationWindow::~registrationWindow()
{
    delete ui;
}

/*Нажатие на кнопку регистрации*/
void registrationWindow::on_registrationButton_clicked()
{
    /*Проверка подключения к БД*/
    bool successOpen = true;

    if (!(handler.isOpen))
        successOpen = handler.open();

    if (!successOpen)
    {
        QMessageBox::information(this, "Ошибка!", "Ошибка подключения к базе данных!");
        handler.close();
        return;
    }

    QString login = ui->loginEdit->text();
    QString password = ui->passwordEdit->text();
    QString repeatedPassword = ui->repeatPasswordEdit->text();

    /*Проверка правильности ввода логина и пароля*/
    if (password != repeatedPassword)
    {
        QMessageBox::information(this, "Ошибка", "Неверно повторен пароль!");
        return;
    }

    bool check = handler.addUser(login, password);
    if (!check)
    {
        QMessageBox::information(this, "Ошибка", handler.getLastError());
    }
    else
    {
        QMessageBox::information(this, "Готово", "Вы успешно зарегистрировались!");
    }

    /*Закрытие подключения к БД*/
    handler.close();
    this->destroy(false, true);
}
