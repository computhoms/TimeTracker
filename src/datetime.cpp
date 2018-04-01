#include "datetime.h"


DateTime::DateTime()
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

DateTime DateTime::distanceTo(DateTime a) const
{
    Date d(a.getDate().year - _date.year,
           a.getDate().month - _date.month,
           a.getDate().dayOfMonth - _date.dayOfMonth);

    TimeOfDay t(a.getTimeOfDay().hours - _time.hours,
                a.getTimeOfDay().minutes - _time.minutes,
                a.getTimeOfDay().seconds - _time.seconds);

    return DateTime(d, t);
}

double DateTime::totalHours() const
{
    return 0.0;
}

double DateTime::getTotalHoursOf(TimeOfDay t)
{
    return t.hours + (t.minutes / 60.0) + (t.seconds / 3600.0);
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
    struct tm dtm1 = {0};
    dtm1.tm_year = d1.getDate().year - 1900;
    dtm1.tm_mon = d1.getDate().month;
    dtm1.tm_mday = d1.getDate().dayOfMonth;
    dtm1.tm_hour = d1.getTimeOfDay().hours;
    dtm1.tm_min = d1.getTimeOfDay().minutes;
    dtm1.tm_sec = d1.getTimeOfDay().seconds;

    struct tm dtm2 = {0};
    dtm2.tm_year = d2.getDate().year - 1900;
    dtm2.tm_mon = d2.getDate().month;
    dtm2.tm_mday = d2.getDate().dayOfMonth;
    dtm2.tm_hour = d2.getTimeOfDay().hours;
    dtm2.tm_min = d2.getTimeOfDay().minutes;
    dtm2.tm_sec = d2.getTimeOfDay().seconds;

    time_t t1 = mktime(&dtm1);
    time_t t2 = mktime(&dtm2);
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
