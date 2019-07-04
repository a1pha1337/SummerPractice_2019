#include <mainwork/event.h>

Event::Event()
{
    this->title_ = "";
}

Event::Event(QString title)
{
    this->title_ = title;
}

void Event::setTitle(QString title)
{
    this->title_ = title;
}

QString Event::getTitle()
{
    return this->title_;
}
