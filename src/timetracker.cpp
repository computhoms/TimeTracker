#include "timetracker.h"

TimeTracker::TimeTracker()
{

}

TimeTracker::~TimeTracker()
{

}

void TimeTracker::startWorking()
{

}

void TimeTracker::stopWorking()
{

}

void TimeTracker::addWorkDay(WorkDay wd)
{
    workDays.push_back(wd);
}

DateTime TimeTracker::getWorkingDurationOfToday() const
{
    return DateTime();
}

DateTime TimeTracker::getWorkingDurationBetween(DateTime from, DateTime to) const
{
    return DateTime();
}

WorkDay TimeTracker::getWorkDay(Date day) const
{
    for (size_t i(0); i < workDays.size(); ++i)
        if (workDays[i].getDay().equals(day))
            return workDays[i];
    return WorkDay(day);
}

