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

