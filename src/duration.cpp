#include "duration.h"

Duration::Duration()
{

}

Duration::Duration(Date d, TimeOfDay t):
    _dateTime   (d, t)
{

}

Duration::~Duration()
{

}

int Duration::getDays() const
{
    return _dateTime.getDate().dayOfMonth;
}

int Duration::getHours() const
{
    return _dateTime.getTimeOfDay().hours;
}

int Duration::getMinutes() const
{
    return _dateTime.getTimeOfDay().minutes;
}

int Duration::getSeconds() const
{
    return _dateTime.getTimeOfDay().seconds;
}

double Duration::getTotalHours() const
{
    TimeOfDay t = _dateTime.getTimeOfDay();
    // TODO compute with number of days, month, years...
    return t.hours + (t.minutes / 60.0) + (t.seconds / 3600.0);
}

