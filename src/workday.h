#ifndef WORKDAY_H
#define WORKDAY_H

#include <vector>
#include "journalentry.h"
#include "generalworkperiod.h"

/**
 * @brief The WorkDay class represents a working day with the time worked and a summary of the job done (journal).
 */
class WorkDay
{
public:
    WorkDay();
    WorkDay(Date d);
    ~WorkDay();

    bool isNull();

    double getWorkTime() const;

    void addWorkPeriod(GeneralWorkPeriod p);
    void addJournalEntry(JournalEntry entry);

    DateTime getTime() const;
    GeneralWorkPeriod *getCurrentWorkPeriod() const;

private:
    std::vector<GeneralWorkPeriod> _workPeriods;
    std::vector<JournalEntry> _journalEntries;
    Date _day;

    GeneralWorkPeriod *_currentWorkPeriod;
};

#endif // WORKDAY_H
