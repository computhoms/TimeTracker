#include "workday.h"

WorkDay::WorkDay():
    _day                 (DateTime::today().getDate()),
    _currentWorkPeriod   (NULL)
{

}

WorkDay::WorkDay(Date d):
    _day (d),
    _currentWorkPeriod  (NULL)
{

}

WorkDay::~WorkDay()
{

}

bool WorkDay::isNull()
{
    return DateTime::areDatesEqual(_day, Date());
}

double WorkDay::getWorkTime() const
{
    double totalWorkTime(0);
    for (size_t i(0); i < workPeriods.size(); ++i)
    {
        DateTime duration = workPeriods[i].getDuration();
        double durationInHours = DateTime::getTotalHoursOf(duration.getTimeOfDay());
        // TODO get duraiton days
        totalWorkTime += durationInHours;
    }
    return totalWorkTime;
}

void WorkDay::addWorkPeriod(GeneralWorkPeriod p)
{
    workPeriods.push_back(p);
    _currentWorkPeriod = &workPeriods.back();
}


Date WorkDay::getDay() const
{
    return _day;
}

GeneralWorkPeriod *WorkDay::getCurrentWorkPeriod() const
{
    return _currentWorkPeriod;
}


