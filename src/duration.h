#ifndef DURATION_H
#define DURATION_H

#include "datetime.h"

class Duration
{
public:
    Duration();
    Duration(Date d, TimeOfDay t);
    ~Duration();

    int getDays() const;
    int getHours() const;
    int getMinutes() const;
    int getSeconds() const;

    double getTotalHours() const;

private:
    DateTime _dateTime;
};

#endif // DURATION_H
