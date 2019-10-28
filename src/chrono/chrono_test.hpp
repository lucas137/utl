//===========================================================================//
//  Nathan Lucas
//  2015
//===========================================================================//
#ifndef UTL_TIME_TEST_HPP
#define UTL_TIME_TEST_HPP

#include "utl_test.hpp"

namespace utl_test {

// test_time.cpp
void test_timepoint(int& n);    // epoch, current time
void test_segment(int& n);      // combine and segment time

// test_clock.cpp
void test_clock(int& n);        // <chrono> clocks

// time_test_datetime.cpp
void test_datetime(int& n);     // extract components from time structure

// test_timer.cpp
void test_timer(int& n);            // utl::Timer
void test_timer_chrono(int& n);     // <chrono> timer
void test_timer_ctime(int& n);      // <ctime> timer

// test_timestamp.cpp
void test_timestamp(int& n);        // utl::timestamp::date, datetime, time

} // utl_test

#endif // UTL_TIME_TEST_HPP
//===========================================================================//
