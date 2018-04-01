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

