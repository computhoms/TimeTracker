#include "generalworkperiod.h"

GeneralWorkPeriod::GeneralWorkPeriod():
    start       (DateTime(0)),
    end         (DateTime(0))
{

}

GeneralWorkPeriod::GeneralWorkPeriod(DateTime s, DateTime e):
    start   (s),
    end     (e)
{

}

GeneralWorkPeriod::~GeneralWorkPeriod()
{

}
DateTime GeneralWorkPeriod::getStart() const
{
    return start;
}

void GeneralWorkPeriod::setStart(const DateTime &value)
{
    start = value;
}
DateTime GeneralWorkPeriod::getEnd() const
{
    return end;
}

void GeneralWorkPeriod::setEnd(const DateTime &value)
{
    end = value;
}

DateTime GeneralWorkPeriod::getDuration() const
{
    return end.distanceTo(start);
}




