#ifndef TIMEPLANNER_H
#define TIMEPLANNER_H

#include "duration.h"

/**
 * @brief The TimePlanner class represents an entity that plans and handles
 * the expected work time vs. actual worked time and gives
 * stats with respected to planned / actually done work.
 */
class TimePlanner
{
public:
    TimePlanner(Duration weeklyWorkDuration);
    ~TimePlanner();

    Duration getDailyWorkDuration();
    Duration getWeeklyWorkDuration();

private:
    Duration _weeklyWorkDuration;
};

#endif // TIMEPLANNER_H
