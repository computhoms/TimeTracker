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

TEST_CASE("Duration::getTotalHours")
{
    Duration d(1, TimeOfDay(2, 7, 2));
    REQUIRE(d.getTotalHours() == 24 + 2 + (7.0 / 60.0) + (2.0 / 3600.0));

    Duration d2(0, TimeOfDay(0, 10, 10));
    REQUIRE(d2.getDays() == 0);
    REQUIRE(d2.getHours() == 0);
    REQUIRE(d2.getMinutes() == 10);
    REQUIRE(d2.getSeconds() == 10);
    REQUIRE(d2.getTotalHours() == (10.0 / 60.0) + (10.0 / 3600.0));
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
    wp.setStart(TimeOfDay(10, 0, 0));
    wp.setEnd(TimeOfDay(10, 10, 10));

    Duration d = wp.getDuration();
    REQUIRE(d.getDays() == 0);
    REQUIRE(d.getHours() == 0);
    REQUIRE(d.getMinutes() == 10);
    REQUIRE(d.getSeconds() == 10);

    REQUIRE(d.getTotalHours() == ((10.0 / 60.0) + (10.0 / 3600.0)));
}

TEST_CASE("WorkDay::getWorkTime")
{
    WorkDay d;
    GeneralWorkPeriod p1(TimeOfDay(10, 00, 00),
                         TimeOfDay(11, 00, 00));
    d.addWorkPeriod(p1);

    GeneralWorkPeriod p2(TimeOfDay(10, 00, 00),
                         TimeOfDay(14, 00, 00));
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
                         TimeOfDay(10, 0, 0),
                         TimeOfDay(12, 0, 0)));
    tt.addWorkDay(wd);

    REQUIRE(tt.getWorkingDurationOfToday().getTotalHours() == 2);
}

TEST_CASE("TimeTracker::getTimeDurationBetween")
{
    GeneralWorkPeriod wd1(TimeOfDay(10, 0, 0),
                TimeOfDay(12, 0, 0));
    GeneralWorkPeriod wd2(TimeOfDay(10, 0, 0),
                TimeOfDay(13, 0, 0));
    GeneralWorkPeriod wd3(TimeOfDay(10, 0, 0),
                TimeOfDay(14, 0, 0));
    GeneralWorkPeriod wd4(TimeOfDay(10, 0, 0),
                TimeOfDay(15, 0, 0));

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

TEST_CASE("TimePlanner::getTotalExtraTime")
{
    TimePlanner pl(Duration(0, TimeOfDay(42, 0, 0)));
    Duration worked(0, TimeOfDay(45, 0, 0));
    REQUIRE(pl.getExtraTime(worked, 5).getHours() == 3.0);
}

TEST_CASE("WorkDayCollectionWriter::writeToString")
{
    std::vector<WorkDay> days;
    WorkDay d1(Date(2018, 1, 1));
    d1.addWorkPeriod(GeneralWorkPeriod(TimeOfDay(10, 0, 0),
                                       TimeOfDay(12, 0, 0)));
}





