//===========================================================================//
//  Nathan Lucas
//  2015
//===========================================================================//

#include "utl_test.hpp"       // utl_test::test_label
#include "chrono_test.hpp"

#include "utl/chrono.hpp"     // utl::chrono::clock_precision

#include <iostream>     // std::cout, std::endl
#include <string>       // std::string

namespace {   //-------------------------------------------------------------

template<typename T>
void
clock_info()
{
  std::cout << "  precision: " << utl::chrono::clock_precision<T>() << "\n"
            << "  is_steady: " << (T::is_steady ? "true" : "false")
            << "\n" << std::endl;

  //-----------------------------------------------------------------

  std::size_t const N = 1000000;
  clock_t t = clock();  // start time
  for (std::size_t i = 0; i != N; ++i)
  {
    T::now();
  }
  t = clock() - t;      // end time

  std::cout << "  It took " << t << " clicks ("
      << ((float)t)/CLOCKS_PER_SEC << " seconds)\n"
      << "  to call now() " << N << " times,\n  or "
      << ((1000000.0 * (float)t)/CLOCKS_PER_SEC) / (float)N
      << " microseconds per call\n"
      << std::endl;
}

} // anonymous ---------------------------------------------------------------


namespace utl_test {


void
test_clock(int& n)
{
  utl_test::test_label(n, "system_clock");
  clock_info<std::chrono::system_clock>();

  utl_test::test_label(n, "steady_clock");
  clock_info<std::chrono::steady_clock>();

  utl_test::test_label(n, "high_resolution_clock");
  clock_info<std::chrono::high_resolution_clock>();
}


} // utl_test
//===========================================================================//
