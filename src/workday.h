#ifndef WORKDAY_H
#define WORKDAY_H

#include <vector>
#include "journalentry.h"
#include "generalworkperiod.h"

class WorkDay
{
public:
    WorkDay();
    ~WorkDay();

    double getWorkTime() const;

    void addWorkPeriod(GeneralWorkPeriod p);
private:
    std::vector<GeneralWorkPeriod> workPeriods;
    std::vector<JournalEntry> journalEntries;

};

#endif // WORKDAY_H
