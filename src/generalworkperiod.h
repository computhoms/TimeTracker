#ifndef GENERALWORKPERIOD_H
#define GENERALWORKPERIOD_H

#include "datetime.h"

class GeneralWorkPeriod
{
public:
    GeneralWorkPeriod();
    GeneralWorkPeriod(DateTime start, DateTime end);
    ~GeneralWorkPeriod();

    DateTime getStart() const;
    void setStart(const DateTime &value);

    DateTime getEnd() const;
    void setEnd(const DateTime &value);

    DateTime getDuration() const;

private:
    DateTime start;
    DateTime end;
};

#endif // GENERALWORKPERIOD_H
