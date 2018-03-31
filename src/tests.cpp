#define CATCH_CONFIG_MAIN
#include "../../libs/catch/catch.hpp"
#include "workday.h"


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
