#ifndef DATETIME_H
#define DATETIME_H

#include <ctime>

/**
 * @brief The Date struct represents a single day in a year
 */
struct Date
{
    Date()
    {
        year = 0;
        month = 0;
        dayOfMonth = 0;
    }

    Date(int y, int m, int d)
    {
        year = y;
        month = m;
        dayOfMonth = d;
    }

    int year;
    int month;
    int dayOfMonth;
};

/**
 * @brief The TimeOfDay struct represents a time in a day.
 */
struct TimeOfDay
{
    TimeOfDay()
    {
        hours = 0;
        minutes = 0;
        seconds = 0;
    }

    TimeOfDay(int h, int m, int s)
    {
        hours = h;
        minutes = m;
        seconds = s;
    }

    int hours;
    int minutes;
    int seconds;
};

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
    static DateTime today();
    // static WeekNumber => DateTime.weekNumber

    bool isSameDayAs(DateTime d) const;
    static bool areDatesEqual(Date d1, Date d2);

    Date getDate() const;
    TimeOfDay getTimeOfDay() const;

    DateTime distanceTo(DateTime a) const;

    double totalHours() const;
    static double getTotalHoursOf(TimeOfDay t);

private:
    Date _date;
    TimeOfDay _time;

    time_t createLocalTime(double reference) const;
};

#endif // DATETIME_H
