#include "timetracker.h"
#include "duration.h"

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
        _workDays.push_back(existing);
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
    _workDays.push_back(wd);
}

Duration TimeTracker::getWorkingDurationOfToday() const
{
    WorkDay existing = getWorkDay(DateTime::today().getDate());
    if (!existing.isNull())
        return existing.getWorkTime();

    return Duration();
}

Duration TimeTracker::getWorkingDurationBetween(DateTime from, DateTime to) const
{
    Duration workDuration;
    for (size_t i(0); i < _workDays.size(); ++i)
    {
        WorkDay d = _workDays[i];
        if (d.getTime() >= from && d.getTime() <= to)
            workDuration += d.getWorkTime();
    }
    return workDuration;
}

WorkDay TimeTracker::getWorkDay(Date day) const
{
    for (size_t i(0); i < _workDays.size(); ++i)
        if (_workDays[i].getTime().isSameDayAs(DateTime(day, TimeOfDay())))
            return _workDays[i];
    return WorkDay(Date(0, 0, 0));
}

