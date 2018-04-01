#define CATCH_CONFIG_MAIN
#include "../../libs/catch/catch.hpp"
#include "workday.h"
#include "timetracker.h"

TEST_CASE("Date::distanceTo")
{
    Date d1(2018, 01, 02);
    Date d2(2018, 01, 30);

    Date dist = d1.distanceTo(d2);
    REQUIRE(dist.getYear() == 0);
    REQUIRE(dist.getMonth() == 0);
    REQUIRE(dist.getDay() == 28);
}

TEST_CASE("Date::distanceTo2")
{
    Date d1(2018, 01, 02);
    Date d2(2021, 04, 02);

    Date dist = d1.distanceTo(d2);
    REQUIRE(dist.getYear() == 3);
    REQUIRE(dist.getMonth() == 3);
    REQUIRE(dist.getDay() == 0);
}

TEST_CASE("TimeOfDay::distanceTo")
{
    TimeOfDay td1(10, 23, 40);
    TimeOfDay td2(12, 18, 23);

    TimeOfDay dist = td1.distanceTo(td2);
    REQUIRE(dist.getHour() == 2);
    REQUIRE(dist.getMinutes() == -5);
    REQUIRE(dist.getSeconds() == -17);
}

TEST_CASE("DateTime::distanceTo")
{
    DateTime dt1(Date(2018, 01, 01), TimeOfDay(10, 0, 0));
    DateTime dt2(Date(2018, 01, 03), TimeOfDay(12, 0, 0));


    DateTime dist = dt1.distanceTo(dt2);
    REQUIRE(dist.getDate().getYear() == 0);
    REQUIRE(dist.getDate().getMonth() == 0);
    REQUIRE(dist.getDate().getDay() == 2);
    REQUIRE(dist.getTimeOfDay().getHour() == 2);
    REQUIRE(dist.getTimeOfDay().getMinutes() == 0);
    REQUIRE(dist.getTimeOfDay().getSeconds() == 0);
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
    wp.setStart(DateTime(Date(2018, 01, 01), TimeOfDay(10, 0, 0)));
    wp.setEnd(DateTime(Date(2018, 01, 01), TimeOfDay(10, 10, 10)));

    DateTime d = wp.getDuration();
    REQUIRE(d.getDate().equals(Date(0, 0, 0)));
    REQUIRE(d.getTimeOfDay().getHour() == 0);
    REQUIRE(d.getTimeOfDay().getMinutes() == 10);
    REQUIRE(d.getTimeOfDay().getSeconds() == 10);
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

TEST_CASE("TimeTracker::getWorkingDurationOfToday")
{
    TimeTracker tt;
    WorkDay wd(Date::today());
    wd.addWorkPeriod(GeneralWorkPeriod(
                         DateTime(Date(2018, 1, 1), TimeOfDay(10, 0, 0)),
                         DateTime(Date(2018, 1, 1), TimeOfDay(12, 0, 0))));
    tt.addWorkDay(wd);

    REQUIRE(tt.getWorkingDurationOfToday().getTimeOfDay().getHour() == 2);
}

// TODO
// - Refactor dates to add a "Duration" class?
// - Refactor dates to convert Date and TimeOfDay into structs and group functions in DateTime class
// - Finish implementing TimeTracker class
