#include "timeplanner.h"

TimePlanner::TimePlanner(Duration weeklyWorkDuration):
    _weeklyWorkDuration (weeklyWorkDuration)
{

}

TimePlanner::~TimePlanner()
{

}

Duration TimePlanner::getDailyWorkDuration() const
{
    return _weeklyWorkDuration / 5;
}

Duration TimePlanner::getWeeklyWorkDuration() const
{
    return _weeklyWorkDuration;
}

Duration TimePlanner::getRemainingTimeForWeek(Duration timeWorked) const
{
    Duration weeklyDuration = getWeeklyWorkDuration();
    return weeklyDuration - timeWorked;
}

