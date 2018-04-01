#ifndef GENERALWORKPERIOD_H
#define GENERALWORKPERIOD_H

#include "datetime.h"

/**
 * @brief The GeneralWorkPeriod class represents a working period with start and end time.
 */
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
