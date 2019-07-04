#ifndef REGISTRATIONWINDOW_H
#define REGISTRATIONWINDOW_H

#include <QDialog>
#include <sql/postgresqlhandle.h>

namespace Ui {
class registrationWindow;
}

class registrationWindow : public QDialog
{
    Q_OBJECT

public:
    explicit registrationWindow(QWidget *parent = nullptr);
    PostgreSQLHandle& handler = PostgreSQLHandle::Instance();
    ~registrationWindow();

private slots:
    void on_registrationButton_clicked();

private:
    Ui::registrationWindow *ui;
};

#endif // REGISTRATIONWINDOW_H
