//===========================================================================//
//  Nathan Lucas
//  2015
//===========================================================================//

#include <iostream>     //  std::cout, std::endl
#include <string>       //  std::string
//#include <chrono>       //  std::chrono::milliseconds
//                        //  std::chrono::system_clock::now, time_point

#include "utl/chrono.hpp"   //  utl::chrono::combine
                            //  utl::chrono::segment
                            //  utl::chrono::time_since_epoch
                            //  utl::chrono::to_string

#include "utl_test.hpp"  // utl_test::test_label
#include "chrono_test.hpp"

namespace utl_test {


//  C++11 chrono library timepoint test.
//
//  Timepoint           Given by
//  ---------           --------
//  epoch               default constructor of class time_point for each clock
//  current time        function now() of each clock
//  minimum timepoint   function min() of class time_point for each clock
//  maximum timepoint   function max() of class time_point for each clock
//----------------------------------------------------------------------------
void
test_timepoint(int& n)
{
  utl_test::test_label(n, "Timepoints");

  std::chrono::system_clock::time_point tp;   // epoch of system clock
  std::cout << "  epoch:  " << utl::chrono::to_string(tp) << std::endl;

  tp = std::chrono::system_clock::now();      // current time
  std::cout << "  now:    " << utl::chrono::to_string(tp) << std::endl;

  auto time_ms = utl::chrono::time_since_epoch<std::chrono::milliseconds>();
  std::cout << "  milliseconds since epoch = " << time_ms.count()
            << "\n" << std::endl;

  std::cout << "  now_yyyymmdd = " << utl::chrono::now_yyyymmdd()
            << "\n" << std::endl;
}


void
test_segment(int& n)
{
  utl_test::test_label(n, "Time Segments");

  int t_hour = 1;
  int t_min = 23;
  int t_sec = 45;
  int t_ms = 678;
  int t = (1000*(60*(60*t_hour + t_min) + t_sec) + t_ms);

  auto ms = utl::chrono::combine(t_hour, t_min, t_sec, t_ms);

  std::cout << "  " << t << " milliseconds = "
            << utl::chrono::segment(ms) << " [hh:mm:ss.sss]\n" << std::endl;
}


} // utl_test
//===========================================================================//
