//===========================================================================//
//  Nathan Lucas
//  2015
//===========================================================================//

#include "chrono_test.hpp"

#include "utl_test.hpp"  // utl_test::test_label

int
main(int argc, char* argv[])
{
  int n = 0;  // test number

  // time_test_time.cpp
  utl_test::test_timepoint(n);    // epoch, current time
  utl_test::test_segment(n);      // combine and segment time

  // time_test_clock.cpp
  utl_test::test_clock(n);        // <chrono> clocks

  // time_test_datetime.cpp
  utl_test::test_datetime(n);     // extract components from time structure

  // time_test_timer.cpp
  utl_test::test_timer(n);            // utl::timer
  utl_test::test_timer_chrono(n);     // <chrono> timer
  utl_test::test_timer_ctime(n);      // <ctime> timer

  // time_test_timestamp.cpp
  utl_test::test_timestamp(n);    // utl::timestamp::date, datetime, time
}

//===========================================================================//
