#include "timeplanner.h"

TimePlanner::TimePlanner(Duration weeklyWorkDuration):
    _weeklyWorkDuration (weeklyWorkDuration)
{

}

TimePlanner::~TimePlanner()
{

}

Duration TimePlanner::getDailyWorkDuration()
{
    return _weeklyWorkDuration / 5;
}

Duration TimePlanner::getWeeklyWorkDuration()
{
    return _weeklyWorkDuration;
}

