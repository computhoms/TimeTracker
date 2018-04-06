#include "duration.h"
#include <cmath>

Duration::Duration():
    _days   (0)
{

}

Duration::Duration(int days, TimeOfDay t):
    _time   (t),
    _days   (days)
{

}

Duration::~Duration()
{

}

int Duration::getDays() const
{
    return _days;
}

int Duration::getHours() const
{
    return _time.hours;
}

int Duration::getMinutes() const
{
    return _time.minutes;
}

int Duration::getSeconds() const
{
    return _time.seconds;
}

double Duration::getTotalHours() const
{
    TimeOfDay t = _time;
    return _days * 24 + t.hours + (t.minutes / 60.0) + (t.seconds / 3600.0);
}

/**
 * @brief Rearranges the duration in days, months, years, hours, minutes, seconds...
 * @param dur
 */
void Duration::rearange()
{
    double hours = getTotalHours();
    _days = std::floor(hours / 24);
    _time.hours = std::floor((hours - _days * 24));
    _time.minutes = std::floor((hours - _days * 24 - _time.hours) * 60);
    _time.seconds = std::floor((hours - _days * 24 - _time.hours - _time.minutes * 60) * 3600);
}

Duration &Duration::operator+=(const Duration &dur)
{
    *this = (*this + dur);
    return *this;
}



Duration operator/(const Duration &dur, const double &divid)
{
    double totalHours = dur.getTotalHours();
    totalHours /= divid;
    Duration d(0, TimeOfDay(totalHours, 0, 0));
    d.rearange();
    return d;
}


Duration operator*(const Duration &dur, const double &mul)
{
    double totalHours = dur.getTotalHours();
    totalHours *= mul;
    Duration d(0, TimeOfDay(totalHours, 0, 0));
    d.rearange();
    return d;
}


Duration operator+(const Duration &dur1, const Duration &dur2)
{
    double totalHours = dur1.getTotalHours() + dur2.getTotalHours();
    Duration d(0, TimeOfDay(totalHours, 0, 0));
    d.rearange();
    return d;
}


Duration operator-(const Duration &dur1, const Duration &dur2)
{
    double totalHours = dur1.getTotalHours() - dur2.getTotalHours();
    Duration d(0, TimeOfDay(totalHours, 0, 0));
    d.rearange();
    return d;
}
