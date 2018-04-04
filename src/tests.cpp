#define CATCH_CONFIG_MAIN
#include "../../libs/catch/catch.hpp"
#include "workday.h"
#include "timetracker.h"

TEST_CASE("DateTime::distanceTo")
{
    DateTime dt1(Date(2018, 01, 01), TimeOfDay(10, 0, 0));
    DateTime dt2(Date(2018, 01, 03), TimeOfDay(12, 0, 0));


    Duration dist = dt1.distanceTo(dt2);
    REQUIRE(dist.getDays() == 2);
    REQUIRE(dist.getHours() == 2);
}

TEST_CASE("DateTime::IsSameDayAs")
{
    DateTime dt1(DateTime::now());
    DateTime dt2(DateTime::now());
    REQUIRE(DateTime::areDatesEqual(dt1.getDate(), dt2.getDate()));
}

TEST_CASE("DateTime::operator<")
{
    DateTime dt1(Date(2018, 01, 01), TimeOfDay());
    DateTime dt2(Date(2018, 01, 02), TimeOfDay());

    REQUIRE(dt1 < dt2);
}

TEST_CASE("GeneralWorkPeriod getDuration")
{
    GeneralWorkPeriod wp;
    wp.setStart(DateTime(Date(2018, 01, 01), TimeOfDay(10, 0, 0)));
    wp.setEnd(DateTime(Date(2018, 01, 01), TimeOfDay(10, 10, 10)));

    Duration d = wp.getDuration();
    REQUIRE(d.getTotalHours() == ((10/60.0) + (10 / 3600.0)));

    REQUIRE(d.getHours() == 0);
    REQUIRE(d.getMinutes() == 10);
    REQUIRE(d.getSeconds() == 10);
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
    REQUIRE(wd.getTime().getDate().year == 0);
    REQUIRE(wd.getTime().getDate().month == 0);
    REQUIRE(wd.getTime().getDate().dayOfMonth == 0);
}

TEST_CASE("TimeTracker::getWorkDay returns write workday if exists")
{
    WorkDay existingWd(Date(2018, 01, 01));
    WorkDay testingWd(Date(2018, 01, 01));

    TimeTracker tt;
    tt.addWorkDay(existingWd);

    REQUIRE(tt.getWorkDay(testingWd.getTime().getDate()).getTime().getDate().year == existingWd.getTime().getDate().year);
    REQUIRE(tt.getWorkDay(testingWd.getTime().getDate()).getTime().getDate().month == existingWd.getTime().getDate().month);
    REQUIRE(tt.getWorkDay(testingWd.getTime().getDate()).getTime().getDate().dayOfMonth == existingWd.getTime().getDate().dayOfMonth);
}

TEST_CASE("TimeTracker::startWorking adds a workDay")
{
    TimeTracker tt;
    WorkDay emptyWordDay = tt.getWorkDay((DateTime::today().getDate()));
    REQUIRE(DateTime::areDatesEqual(emptyWordDay.getTime().getDate(), Date()));
    tt.startWorking();
    WorkDay wd = tt.getWorkDay(DateTime::today().getDate());
    REQUIRE(DateTime::areDatesEqual(wd.getTime().getDate(), Date()) == false);
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

TEST_CASE("TimeTracker::getTimeDurationBetween")
{
    GeneralWorkPeriod wd1(DateTime(Date(2018, 1, 1), TimeOfDay(10, 0, 0)),
                DateTime(Date(2018, 1, 1), TimeOfDay(12, 0, 0)));
    GeneralWorkPeriod wd2(DateTime(Date(2018, 1, 2), TimeOfDay(10, 0, 0)),
                DateTime(Date(2018, 1, 2), TimeOfDay(13, 0, 0)));
    GeneralWorkPeriod wd3(DateTime(Date(2018, 1, 3), TimeOfDay(10, 0, 0)),
                DateTime(Date(2018, 1, 3), TimeOfDay(14, 0, 0)));
    GeneralWorkPeriod wd4(DateTime(Date(2018, 1, 4), TimeOfDay(10, 0, 0)),
                DateTime(Date(2018, 1, 4), TimeOfDay(15, 0, 0)));

    WorkDay w1(Date(2018, 1, 1));
    WorkDay w2(Date(2018, 1, 2));
    WorkDay w3(Date(2018, 1, 3));
    WorkDay w4(Date(2018, 1, 4));
    w1.addWorkPeriod(wd1);
    w2.addWorkPeriod(wd2);
    w3.addWorkPeriod(wd3);
    w4.addWorkPeriod(wd4);

    TimeTracker tt;
    tt.addWorkDay(w1);
    tt.addWorkDay(w2);
    tt.addWorkDay(w3);
    tt.addWorkDay(w4);

    REQUIRE(tt.getWorkingDurationBetween(DateTime(Date(2018, 1, 2)),
                                         DateTime(Date(2018, 1, 3)))
              .getTimeOfDay().hours == 7);

}

// TODO
// - Refactor dates to add a "Duration" class?
// - Finish implementing TimeTracker class
