#include "timetracker.h"

TimeTracker::TimeTracker()
{

}

TimeTracker::~TimeTracker()
{

}

void TimeTracker::startWorking()
{
    WorkDay existing = getWorkDay(DateTime::today().getDate());
    if (existing.isNull())
    {
        existing = WorkDay(DateTime::today().getDate());
        workDays.push_back(existing);
    }
    existing.addWorkPeriod(GeneralWorkPeriod(DateTime::now()));
}

void TimeTracker::stopWorking()
{
    WorkDay existing = getWorkDay(DateTime::today().getDate());
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
    WorkDay existing = getWorkDay(DateTime::today().getDate());
    if (!existing.isNull())
    {
        return DateTime(Date(), TimeOfDay(existing.getWorkTime(), 0, 0));
    }
    return DateTime(Date(0, 0, 0), TimeOfDay(0, 0, 0));
}

DateTime TimeTracker::getWorkingDurationBetween(DateTime from, DateTime to) const
{
    double workDimeAsHours = 0;
    for (size_t i(0); i < workDays.size(); ++i)
    {
        WorkDay d = workDays[i];
        if (d.getTime() >= from && d.getTime() <= to)
            workDimeAsHours += d.getWorkTime();
    }
    return DateTime(Date(), TimeOfDay(workDimeAsHours, 0, 0));
}

WorkDay TimeTracker::getWorkDay(Date day) const
{
    for (size_t i(0); i < workDays.size(); ++i)
        if (workDays[i].getTime().isSameDayAs(DateTime(day, TimeOfDay())))
            return workDays[i];
    return WorkDay(Date(0, 0, 0));
}

