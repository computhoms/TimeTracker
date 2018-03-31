#ifndef DATETIME_H
#define DATETIME_H

#include <ctime>

class DateTime
{
public:
    DateTime();
    DateTime(double refValue);
    ~DateTime();

    DateTime distanceTo(DateTime a) const;

    double getReference() const;
    static DateTime now();
private:
    time_t thisTime;
};

#endif // DATETIME_H
