#ifndef TIMEOFDAY_H
#define TIMEOFDAY_H


class TimeOfDay
{
public:
    TimeOfDay();
    TimeOfDay(int hour, int minutes, int seconds);
    ~TimeOfDay();

    TimeOfDay distanceTo(TimeOfDay t) const;

    int getHour() const;
    int getMinutes() const;
    int getSeconds() const;

    double getTotalHours() const;

private:
    int _hour;
    int _minutes;
    int _seconds;
};

#endif // TIMEOFDAY_H
