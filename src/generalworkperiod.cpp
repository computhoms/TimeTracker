#include "generalworkperiod.h"

GeneralWorkPeriod::GeneralWorkPeriod():
    _start       (DateTime(Date::null(), TimeOfDay(0, 0, 0))),
    _end         (DateTime(Date::null(), TimeOfDay(0, 0, 0)))
{

}

GeneralWorkPeriod::GeneralWorkPeriod(DateTime start):
    _start       (start),
    _end         (DateTime(Date::null(), TimeOfDay(0, 0, 0)))
{

}

GeneralWorkPeriod::GeneralWorkPeriod(DateTime s, DateTime e):
    _start   (s),
    _end     (e)
{

}

GeneralWorkPeriod::~GeneralWorkPeriod()
{

}
DateTime GeneralWorkPeriod::getStart() const
{
    return _start;
}

void GeneralWorkPeriod::setStart(const DateTime &value)
{
    _start = value;
}
DateTime GeneralWorkPeriod::getEnd() const
{
    return _end;
}

void GeneralWorkPeriod::setEnd(const DateTime &value)
{
    _end = value;
}

DateTime GeneralWorkPeriod::getDuration() const
{
    return _start.distanceTo(_end);
}




