#ifndef DATETIME_H
#define DATETIME_H

#include <ctime>
#include "date.h"
#include "timeofday.h"

/**
 * @brief The DateTime class represents either a given moment in time or a time duration.
 */
class DateTime
{
public:
    DateTime();
    DateTime(Date date, TimeOfDay timeOfDay);
    ~DateTime();

    static DateTime now();

    Date getDate() const;
    TimeOfDay getTimeOfDay() const;

    DateTime distanceTo(DateTime a) const;
//    double getReference() const;

private:
    Date _date;
    TimeOfDay _time;

    time_t createLocalTime(double reference) const;
};

#endif // DATETIME_H
