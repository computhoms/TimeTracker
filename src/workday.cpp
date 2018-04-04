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
    for (size_t i(0); i < _workPeriods.size(); ++i)
    {
        Duration duration = _workPeriods[i].getDuration();
        double durationInHours = duration.getTotalHours();
        // TODO get duraiton days
        totalWorkTime += durationInHours;
    }
    return totalWorkTime;
}

void WorkDay::addWorkPeriod(GeneralWorkPeriod p)
{
    _workPeriods.push_back(p);
    _currentWorkPeriod = &_workPeriods.back();
}

void WorkDay::addJournalEntry(JournalEntry entry)
{
    _journalEntries.push_back(entry);
}


DateTime WorkDay::getTime() const
{
    return DateTime(_day, TimeOfDay());
}

GeneralWorkPeriod *WorkDay::getCurrentWorkPeriod() const
{
    return _currentWorkPeriod;
}


