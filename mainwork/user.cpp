#include <mainwork/user.h>

User::User(QString username)
{
    this->username_ = username;
}

QString User::getUserName()
{
    return this->username_;
}
