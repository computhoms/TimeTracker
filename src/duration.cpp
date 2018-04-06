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
    double totalSeconds = getTotalHours() * 3600.0;
    double oneMinuteInSeconds = 60.0;
    double oneHourInSeconds = 60.0 * oneMinuteInSeconds;
    double oneDayInSeconds = 24.0 * oneHourInSeconds;


    _days = std::floor(totalSeconds / oneDayInSeconds);
    int daysInSeconds = _days * oneDayInSeconds;

    _time.hours = std::floor((totalSeconds - daysInSeconds) / oneHourInSeconds);
    int hoursInSeconds = _time.hours * oneHourInSeconds;

    _time.minutes = std::floor((totalSeconds - daysInSeconds - hoursInSeconds) / oneMinuteInSeconds);
    int minutesInSeconds = _time.minutes * oneMinuteInSeconds;

    _time.seconds = std::floor(
                (totalSeconds - daysInSeconds - hoursInSeconds - minutesInSeconds));
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
