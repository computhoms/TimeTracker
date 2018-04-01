#include "date.h"
#include <ctime>

Date::Date()
{
    time_t t = time(NULL);
    struct tm lt = (*localtime(&t));
    _year = lt.tm_year + 1900;
    _month = lt.tm_mon;
    _day = lt.tm_mday;
}

/**
 * @brief Date::Date
 * @param year Date's year
 * @param month Month from 1 to 12
 * @param day Day from 1 to 31
 */
Date::Date(int year, int month, int day):
    _year   (year),
    _month  (month),
    _day    (day)
{

}

Date::~Date()
{

}

Date Date::today()
{
    return Date();
}

Date Date::null()
{
    return Date(0, 0, 0);
}

bool Date::equals(Date d) const
{
    return _year == d.getYear() && _month == d.getMonth() && _day == d.getDay();
}

Date Date::distanceTo(Date d) const
{
    return Date(d.getYear() - _year, d.getMonth() - _month, d.getDay() - _day);
}

int Date::getYear() const
{
    return _year;
}

int Date::getMonth() const
{
    return _month;
}

int Date::getDay() const
{
    return _day;
}




