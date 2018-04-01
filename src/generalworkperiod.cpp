#include "generalworkperiod.h"

GeneralWorkPeriod::GeneralWorkPeriod():
    _start       (DateTime()),
    _end         (DateTime())
{

}

GeneralWorkPeriod::GeneralWorkPeriod(DateTime start):
    _start       (start),
    _end         (DateTime())
{

}

GeneralWorkPeriod::GeneralWorkPeriod(DateTime start, DateTime end):
    _start   (start),
    _end     (end)
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




