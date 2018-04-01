#ifndef TIMEOFDAY_H
#define TIMEOFDAY_H


class TimeOfDay
{
public:
    TimeOfDay();
    TimeOfDay(int hour, int minutes, int seconds);
    ~TimeOfDay();

private:
    int _hour;
    int _minutes;
    int _seconds;
};

#endif // TIMEOFDAY_H
