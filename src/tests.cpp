#define CATCH_CONFIG_MAIN
#include "../../libs/catch/catch.hpp"
#include "workday.h"
#include "timetracker.h"

TEST_CASE("DateTime::distanceTo")
{
    DateTime dt1(Date(2018, 01, 01), TimeOfDay(10, 0, 0));
    DateTime dt2(Date(2018, 01, 03), TimeOfDay(12, 0, 0));


    DateTime dist = dt1.distanceTo(dt2);
    REQUIRE(dist.getDate().year == 0);
    REQUIRE(dist.getDate().month == 0);
    REQUIRE(dist.getDate().dayOfMonth == 2);
    REQUIRE(dist.getTimeOfDay().hours == 2);
    REQUIRE(dist.getTimeOfDay().minutes == 0);
    REQUIRE(dist.getTimeOfDay().seconds == 0);
}

TEST_CASE("DateTime::IsSameDayAs")
{
    DateTime dt1(DateTime::now());
    DateTime dt2(DateTime::now());
    REQUIRE(DateTime::areDatesEqual(dt1.getDate(), dt2.getDate()));
}

TEST_CASE("GeneralWorkPeriod getDuration")
{
    GeneralWorkPeriod wp;
    wp.setStart(DateTime(Date(2018, 01, 01), TimeOfDay(10, 0, 0)));
    wp.setEnd(DateTime(Date(2018, 01, 01), TimeOfDay(10, 10, 10)));

    DateTime d = wp.getDuration();
    REQUIRE(d.isSameDayAs(DateTime()));

    REQUIRE(d.getTimeOfDay().hours == 0);
    REQUIRE(d.getTimeOfDay().minutes == 10);
    REQUIRE(d.getTimeOfDay().seconds == 10);
}

TEST_CASE("WorkDay::getWorkTime")
{
    WorkDay d;
    GeneralWorkPeriod p1(DateTime(Date(2018, 01, 01), TimeOfDay(10, 00, 00)),
                         DateTime(Date(2018, 01, 01), TimeOfDay(11, 00, 00)));
    d.addWorkPeriod(p1);

    GeneralWorkPeriod p2(DateTime(Date(2018, 01, 01), TimeOfDay(10, 00, 00)),
                         DateTime(Date(2018, 01, 01), TimeOfDay(14, 00, 00)));
    d.addWorkPeriod(p2);

    REQUIRE(d.getWorkTime() == 5);
}

TEST_CASE("TimeTracker::getWorkDay returns 'Null' workday if nothing exists")
{
    TimeTracker tt;
    WorkDay wd = tt.getWorkDay(Date());
    REQUIRE(wd.getDay().year == 0);
    REQUIRE(wd.getDay().month == 0);
    REQUIRE(wd.getDay().dayOfMonth == 0);
}

TEST_CASE("TimeTracker::getWorkDay returns write workday if exists")
{
    WorkDay existingWd(Date(2018, 01, 01));
    WorkDay testingWd(Date(2018, 01, 01));

    TimeTracker tt;
    tt.addWorkDay(existingWd);

    REQUIRE(tt.getWorkDay(testingWd.getDay()).getDay().year == existingWd.getDay().year);
    REQUIRE(tt.getWorkDay(testingWd.getDay()).getDay().month == existingWd.getDay().month);
    REQUIRE(tt.getWorkDay(testingWd.getDay()).getDay().dayOfMonth == existingWd.getDay().dayOfMonth);
}

TEST_CASE("TimeTracker::startWorking adds a workDay")
{
    TimeTracker tt;
    WorkDay emptyWordDay = tt.getWorkDay((DateTime::today().getDate()));
    REQUIRE(DateTime::areDatesEqual(emptyWordDay.getDay(), Date()));
    tt.startWorking();
    WorkDay wd = tt.getWorkDay(DateTime::today().getDate());
    REQUIRE(DateTime::areDatesEqual(wd.getDay(), Date()) == false);
}

TEST_CASE("TimeTracker::getWorkingDurationOfToday")
{
    TimeTracker tt;
    WorkDay wd(DateTime::today().getDate());
    wd.addWorkPeriod(GeneralWorkPeriod(
                         DateTime(Date(2018, 1, 1), TimeOfDay(10, 0, 0)),
                         DateTime(Date(2018, 1, 1), TimeOfDay(12, 0, 0))));
    tt.addWorkDay(wd);

    REQUIRE(tt.getWorkingDurationOfToday().getTimeOfDay().hours == 2);
}

// TODO
// - Refactor dates to add a "Duration" class?
// - Finish implementing TimeTracker class
