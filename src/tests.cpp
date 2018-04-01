#define CATCH_CONFIG_MAIN
#include "../../libs/catch/catch.hpp"
#include "workday.h"
#include "timetracker.h"


TEST_CASE("DateTime constructor with refTime argument")
{
    DateTime dt(1);
    REQUIRE(dt.getReference() == 1);
}

TEST_CASE("DateTime::distanceTo")
{
    DateTime dt1(1);
    DateTime dt2(2);

    DateTime dist = dt1.distanceTo(dt2);
    REQUIRE(dist.getReference() == -1.0);
}

TEST_CASE("DateTime::IsSameDayAs")
{
    DateTime dt1(DateTime::now());
    DateTime dt2(DateTime::now());
    REQUIRE(dt1.getDate().equals(dt2.getDate()));
}

TEST_CASE("GeneralWorkPeriod getDuration")
{
    GeneralWorkPeriod wp;
    wp.setStart(DateTime(1));
    wp.setEnd(DateTime(2));

    DateTime d = wp.getDuration();
    REQUIRE(d.getReference() == 1.0);
}

TEST_CASE("WorkDay::getWorkTime")
{
    WorkDay d;
    GeneralWorkPeriod p1(DateTime(1), DateTime(2));
    d.addWorkPeriod(p1);
    GeneralWorkPeriod p2(DateTime(1), DateTime(5));
    d.addWorkPeriod(p2);

    REQUIRE(d.getWorkTime() == 5);
}

TEST_CASE("TimeTracker::getWorkDay returns 'Null' workday if nothing exists")
{
    TimeTracker tt;
    WorkDay wd = tt.getWorkDay(Date());
    REQUIRE(wd.getDay().equals(Date(0, 0, 0)));
}

TEST_CASE("TimeTracker::getWorkDay returns write workday if exists")
{
    WorkDay existingWd(Date(2018, 01, 01));
    WorkDay testingWd(Date(2018, 01, 01));

    TimeTracker tt;
    tt.addWorkDay(existingWd);

    REQUIRE(tt.getWorkDay(testingWd.getDay()).getDay().equals(existingWd.getDay()));
}

TEST_CASE("TimeTracker::startWorking adds a workDay")
{
    TimeTracker tt;
    REQUIRE(tt.getWorkDay(Date::today()).getDay().equals(Date(0, 0, 0)));
    tt.startWorking();
    REQUIRE(tt.getWorkDay(Date::today()).getDay().equals(Date(0, 0, 0)) == false);
}
