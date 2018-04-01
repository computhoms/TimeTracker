#include "timetracker.h"

TimeTracker::TimeTracker()
{

}

TimeTracker::~TimeTracker()
{

}

void TimeTracker::startWorking()
{
    WorkDay existing = getWorkDay(Date::today());
    if (existing.isNull())
    {
        existing = WorkDay(Date::today());
        workDays.push_back(existing);
    }
    existing.addWorkPeriod(GeneralWorkPeriod(DateTime::now()));
}

void TimeTracker::stopWorking()
{
    WorkDay existing = getWorkDay(Date::today());
    if (!existing.isNull() && existing.getCurrentWorkPeriod() != NULL)
    {
        existing.getCurrentWorkPeriod()->setEnd(DateTime::now());
    }
}

void TimeTracker::addWorkDay(WorkDay wd)
{
    workDays.push_back(wd);
}

DateTime TimeTracker::getWorkingDurationOfToday() const
{
    WorkDay existing = getWorkDay(Date::today());
    if (!existing.isNull())
    {
        return DateTime(Date::today(), TimeOfDay(existing.getWorkTime(), 0, 0));
    }
    return DateTime(Date(0, 0, 0), TimeOfDay(0, 0, 0));
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
    return WorkDay(Date(0, 0, 0));
}

