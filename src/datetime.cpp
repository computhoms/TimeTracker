#include "datetime.h"


DateTime::DateTime():
    _date   (Date()),
    _time   (TimeOfDay())
{

}

DateTime::DateTime(Date date, TimeOfDay timeOfDay):
    _date   (date),
    _time   (timeOfDay)
{

}

DateTime::~DateTime()
{

}

DateTime DateTime::distanceTo(DateTime a) const
{
    Date dateDist = _date.distanceTo(a.getDate());
    TimeOfDay timeDist = _time.distanceTo(a.getTimeOfDay());

    return DateTime(dateDist, timeDist);
}

//time_t DateTime::createLocalTime(double reference) const
//{
//    struct tm drefTime = {0};
//    drefTime.tm_hour = 0;
//    drefTime.tm_year = 100;
//    drefTime.tm_min = 0;
//    drefTime.tm_mon = 0;
//    drefTime.tm_sec = reference;
//    drefTime.tm_mday = 1;
//    return mktime(&drefTime);
//}

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

