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

    double getWorkTime() const;

    void addWorkPeriod(GeneralWorkPeriod p);

    Date getDay() const;

private:
    std::vector<GeneralWorkPeriod> workPeriods;
    std::vector<JournalEntry> journalEntries;
    Date day;

};

#endif // WORKDAY_H
