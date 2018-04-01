#include "timeofday.h"
#include <ctime>

TimeOfDay::TimeOfDay()
{
    time_t t = time(NULL);
    struct tm lt = (*localtime(&t));
    _hour = lt.tm_hour;
    _minutes = lt.tm_min;
    _seconds = lt.tm_sec;
}

TimeOfDay::TimeOfDay(int hour, int minutes, int seconds):
    _hour       (hour),
    _minutes    (minutes),
    _seconds    (seconds)
{

}

TimeOfDay::~TimeOfDay()
{

}

TimeOfDay TimeOfDay::distanceTo(TimeOfDay t) const
{
    return TimeOfDay(t.getHour() - _hour, t.getMinutes() - _minutes, t.getSeconds() - _seconds);
}

int TimeOfDay::getHour() const
{
    return _hour;
}

int TimeOfDay::getMinutes() const
{
    return _minutes;
}

int TimeOfDay::getSeconds() const
{
    return _seconds;
}

double TimeOfDay::getTotalHours() const
{
    return _hour + (_minutes / 60.0) + (_seconds / 3600.0);
}


