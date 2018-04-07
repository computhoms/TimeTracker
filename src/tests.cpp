#define CATCH_CONFIG_MAIN
#include "../../libs/catch/catch.hpp"
#include "workday.h"
#include "timetracker.h"
#include "timeplanner.h"

TEST_CASE("Duration::operator/")
{
    Duration d(0, TimeOfDay(10, 0, 0));
    REQUIRE((d/10).getTotalHours() == 1.0);
}

TEST_CASE("Duration::operator*")
{
    Duration d(0, TimeOfDay(10, 0, 0));
    REQUIRE((d*10).getTotalHours() == 100.0);
}

TEST_CASE("Duration::operator+")
{
    Duration d1(0, TimeOfDay(10, 0, 0));
    Duration d2(0, TimeOfDay(5, 0, 0));
    REQUIRE((d1 + d2).getTotalHours() == 15.0);
}

TEST_CASE("Duration::operator+=")
{
    Duration d1(0, TimeOfDay(10, 0, 0));
    Duration d2(0, TimeOfDay(5, 0, 0));
    d1 += d2;
    REQUIRE(d1.getTotalHours() == 15.0);
}

TEST_CASE("Duration::operator-")
{
    Duration d1(0, TimeOfDay(10, 0, 0));
    Duration d2(0, TimeOfDay(5, 0, 0));
    REQUIRE((d1 - d2).getTotalHours() == 5.0);
}

TEST_CASE("Duration::rearrange")
{
    int seconds = 12 + 3 * 60 + 2 * 3600 + 2 * 24 * 3600;
    REQUIRE(seconds == 180192);
    Duration d(0, TimeOfDay(0, 0, seconds));
    d.rearange();
    REQUIRE(d.getDays() == 2);
    REQUIRE(d.getHours() == 2);
    REQUIRE(d.getMinutes() == 3);
    REQUIRE(d.getSeconds() == 12);
}

TEST_CASE("getDiffTime")
{
    DateTime d1(Date(2018, 01, 01), TimeOfDay(10, 0, 0));
    DateTime d2(Date(2018, 01, 01), TimeOfDay(10, 0, 12));

    REQUIRE(getDiffTime(d1, d2) == 12);
}

TEST_CASE("DateTime::distanceTo")
{
    DateTime dt1(Date(2018, 01, 02), TimeOfDay(10, 0, 0));
    DateTime dt2(Date(2018, 01, 04), TimeOfDay(12, 3, 12));

    REQUIRE(getDiffTime(dt1, dt2) == 12 + 3 * 60 + 2 * 3600 + 2 * 3600 * 24);

    Duration dist = dt1.distanceTo(dt2);
    REQUIRE(dist.getDays() == 2);
    REQUIRE(dist.getHours() == 2);
    REQUIRE(dist.getMinutes() == 3);
    REQUIRE(dist.getSeconds() == 12);
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

    REQUIRE(d.getWorkTime().getTotalHours() == 5);
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

    REQUIRE(tt.getWorkingDurationOfToday().getTotalHours() == 2);
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
              .getTotalHours() == 7);

}

TEST_CASE("TimePlanner::getRemainingTimeForWeek")
{
    TimePlanner pl(Duration(0, TimeOfDay(42, 0, 0)));
    Duration worked(0, TimeOfDay(18, 0, 0));
    REQUIRE(pl.getRemainingTimeForWeek(worked).getSeconds() == 0.0);
    REQUIRE(pl.getRemainingTimeForWeek(worked).getMinutes() == 0.0);
    REQUIRE(pl.getRemainingTimeForWeek(worked).getHours() == 0.0);
    REQUIRE(pl.getRemainingTimeForWeek(worked).getDays() == 1.0);
    REQUIRE(pl.getRemainingTimeForWeek(worked).getTotalHours() == 24.0);
}

TEST_CASE("TimePlanner::getTotalExtraTime")
{
    TimePlanner pl(Duration(0, TimeOfDay(42, 0, 0)));
    Duration worked(0, TimeOfDay(45, 0, 0));
    REQUIRE(pl.getTotalExtraTime(worked, 5).getHours() == 3.0);
}
