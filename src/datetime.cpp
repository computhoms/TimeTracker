#include "datetime.h"
#include "duration.h"
#include <cmath>


DateTime::DateTime()
{

}

DateTime::DateTime(Date date):
    _date   (date)
{

}

DateTime::DateTime(Date date, TimeOfDay timeOfDay):
    _date   (date),
    _time   (timeOfDay)
{

}

DateTime::~DateTime()
{

}

Duration DateTime::distanceTo(DateTime a) const
{
    double diffSeconds = getDiffTime(*this, a);
    int days = std::floor(diffSeconds / (3600.0 * 24.0));
    int daysInSeconds = days * 24.0 * 3600.0;
    int hours = std::floor((diffSeconds - daysInSeconds) / 3600.0);
    int hoursInSeconds = hours * 3600.0;
    int minutes = std::floor((diffSeconds - daysInSeconds - hoursInSeconds) / 60.0);
    int minutesInSeconds = minutes * 60.0;
    int seconds = std::floor(diffSeconds - daysInSeconds - hoursInSeconds - minutesInSeconds);

    TimeOfDay t(hours, minutes, seconds);
    return Duration(days, t);
}

time_t DateTime::toLocalTime() const
{
    struct tm dtm1;
    dtm1.tm_year = _date.year - 1900;
    dtm1.tm_mon = _date.month;
    dtm1.tm_mday = _date.dayOfMonth;
    dtm1.tm_hour = _time.hours;
    dtm1.tm_min = _time.minutes;
    dtm1.tm_sec = _time.seconds;
    dtm1.tm_wday = 0;
    dtm1.tm_yday = 0;
    dtm1.tm_isdst = -1;

    return mktime(&dtm1);
}

DateTime DateTime::now()
{
    time_t ttime = time(NULL);
    struct tm lt = (*localtime(&ttime));

    Date d;
    d.year = lt.tm_year + 1900;
    d.month = lt.tm_mon;
    d.dayOfMonth = lt.tm_mday;
    TimeOfDay t;
    t.hours = lt.tm_hour;
    t.minutes = lt.tm_min;
    t.seconds = lt.tm_sec;
    return DateTime(d, t);
}

DateTime DateTime::today()
{
    time_t t = time(NULL);
    struct tm lt = (*localtime(&t));
    Date d;
    d.year = lt.tm_year + 1900;
    d.month = lt.tm_mon;
    d.dayOfMonth = lt.tm_mday;
    return DateTime(d, TimeOfDay());
}

bool DateTime::isSameDayAs(DateTime d) const
{
    Date dDate = d.getDate();
    return _date.year == dDate.year && _date.month == dDate.month && _date.dayOfMonth == dDate.dayOfMonth;
}

bool DateTime::areDatesEqual(Date d1, Date d2)
{
    return d1.year == d2.year && d1.month == d2.month && d1.dayOfMonth == d2.dayOfMonth;
}

Date DateTime::getDate() const
{
    return _date;
}

TimeOfDay DateTime::getTimeOfDay() const
{
    return _time;
}

bool operator<(const DateTime &d1, const DateTime &d2)
{
    return getDiffTime(d1, d2) > 0;
}

bool operator<=(const DateTime &d1, const DateTime &d2)
{
    return getDiffTime(d1, d2) >= 0;
}

double getDiffTime(const DateTime &d1, const DateTime &d2)
{
    time_t t1 = d1.toLocalTime();
    time_t t2 = d2.toLocalTime();
    return difftime(t2, t1);
}


bool operator>(const DateTime &d1, const DateTime &d2)
{
    return getDiffTime(d1, d2) < 0;
}


bool operator>=(const DateTime &d1, const DateTime &d2)
{
    return getDiffTime(d1, d2) <= 0;
}
