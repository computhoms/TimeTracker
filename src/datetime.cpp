#include "datetime.h"


DateTime::DateTime():
    thisTime    (time(NULL))
{

}

DateTime::DateTime(double refValue)
{
    struct tm timeTm = {0};
    timeTm.tm_hour = 0;
    timeTm.tm_year = 100;
    timeTm.tm_min = 0;
    timeTm.tm_mon = 0;
    timeTm.tm_sec = refValue;
    timeTm.tm_mday = 1;
    thisTime = mktime(&timeTm);
}

DateTime::~DateTime()
{

}

DateTime DateTime::distanceTo(DateTime a) const
{
    DateTime dist(getReference() - a.getReference());
    return dist;
}

double DateTime::getReference() const
{
    struct tm refTime = {0};
    refTime.tm_hour = 0;
    refTime.tm_year = 100;
    refTime.tm_min = 0;
    refTime.tm_mon = 0;
    refTime.tm_sec = 0;
    refTime.tm_mday = 1;
    return difftime(thisTime, mktime(&refTime));
}

DateTime DateTime::now()
{
    return DateTime();
}

