#ifndef DATE_H
#define DATE_H

/**
 * @brief The Date class represents a date as year/month/day
 *
 */
class Date
{
public:
    Date();
    Date(int getYear, int month, int day);
    ~Date();

    static Date today();
    static Date null();

    bool equals(Date d) const;
    Date distanceTo(Date d) const;

    int getYear() const;
    int getMonth() const;
    int getDay() const;

private:
    int _year;
    int _month;
    int _day;
};

#endif // DATE_H
