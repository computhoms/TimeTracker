#include "workday.h"

WorkDay::WorkDay()
{

}

WorkDay::~WorkDay()
{

}

double WorkDay::getWorkTime() const
{
    double totalWorkTime(0);
    for (size_t i(0); i < workPeriods.size(); ++i)
        totalWorkTime += workPeriods[i].getDuration().getReference();
    return totalWorkTime;
}

void WorkDay::addWorkPeriod(GeneralWorkPeriod p)
{
    workPeriods.push_back(p);
}

