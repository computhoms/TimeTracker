#include "workday.h"

WorkDay::WorkDay():
    day (Date::today())
{

}

WorkDay::WorkDay(Date d):
    day (d)
{

}

WorkDay::~WorkDay()
{

}

bool WorkDay::isNull()
{
    return day.equals(Date::null());
}

double WorkDay::getWorkTime() const
{
    double totalWorkTime(0);
    for (size_t i(0); i < workPeriods.size(); ++i)
        totalWorkTime += workPeriods[i].getDuration().getReference();
    return totalWorkTime;
}

void WorkDay::addWorkPeriod(GeneralWorkPeriod p)
{
    workPeriods.push_back(p);
}


Date WorkDay::getDay() const
{
    return day;
}


