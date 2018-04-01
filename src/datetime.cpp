#include "datetime.h"


DateTime::DateTime():
    thisTime    (time(NULL)),
    _date   (Date()),
    _time   (TimeOfDay())
{

}

DateTime::DateTime(double refValue)
{
    thisTime = createLocalTime(refValue);
    struct tm lt = (*localtime(&thisTime));
    _date = Date(lt.tm_year, lt.tm_mon, lt.tm_mday);
    _time = TimeOfDay(lt.tm_hour, lt.tm_min, lt.tm_sec);
}

DateTime::~DateTime()
{

}

DateTime DateTime::distanceTo(DateTime a) const
{
    DateTime dist(getReference() - a.getReference());
    return dist;
}

double DateTime::getReference() const
{
    struct tm refTime = {0};
    refTime.tm_hour = 0;
    refTime.tm_year = 100;
    refTime.tm_min = 0;
    refTime.tm_mon = 0;
    refTime.tm_sec = 0;
    refTime.tm_mday = 1;
    return difftime(thisTime, mktime(&refTime));
}

time_t DateTime::createLocalTime(double reference) const
{
    struct tm drefTime = {0};
    drefTime.tm_hour = 0;
    drefTime.tm_year = 100;
    drefTime.tm_min = 0;
    drefTime.tm_mon = 0;
    drefTime.tm_sec = reference;
    drefTime.tm_mday = 1;
    return mktime(&drefTime);
}

DateTime DateTime::now()
{
    return DateTime();
}

Date DateTime::getDate() const
{
    return _date;
}

TimeOfDay DateTime::getTimeOfDay() const
{
    return _time;
}

