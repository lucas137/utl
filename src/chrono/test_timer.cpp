//===========================================================================//
//  Nathan Lucas
//  2015
//===========================================================================//

#include <iostream>     // std::cout, endl
#include <sstream>      // std::ostringstream
#include <string>       // std::string
#include <math.h>       // sqrt
#include <chrono>       // std::chrono::
                        //    duration, duration_cast, milliseconds,
                        //    microseconds, nanoseconds, steady_clock
#include <ctime>        // clock_t, clock, CLOCKS_PER_SEC

#include "utl/chrono.hpp"   //  utl::timer

#include "utl_test.hpp"      // utl_test::test_label
#include "chrono_test.hpp"

namespace {   //-------------------------------------------------------------

const int PRIME_LIMIT = 1000000;
const int PRIME_MAX = (PRIME_LIMIT - 1);

int
frequency_of_primes(int n)
{
  int freq = n-1;
  for (int i=2; i<=n; ++i)
  {
    for (int j=sqrt(i); j>1; --j) {
        if (i%j == 0) { --freq; break; }
    }
  }
  return freq;
}

} // anonymous --------------------------------------------------------------


namespace utl_test {


// Steady Clock Timer
void
test_timer(int& n)
{
  utl_test::test_label(n, "utl::timer");

  utl::chrono::timer tmr;

  int f = frequency_of_primes(PRIME_MAX);

  std::ostringstream oss;
  oss << "  The number of primes lower than "
      << PRIME_LIMIT << " is: " << f << "\n\n"
      << "  Computation time:\n\n  "
      << tmr.elapsed<utl::chrono::timer::s>().count() << " seconds, or\n  "
      << tmr.elapsed<utl::chrono::timer::ms>().count() << " milliseconds, or\n  "
      << tmr.elapsed<utl::chrono::timer::us>().count() << " microseconds, or\n  "
      << tmr.elapsed<utl::chrono::timer::ns>().count() << " nanoseconds"
      << std::endl;
  std::cout << oss.str() << std::endl;
}


void
test_timer_chrono(int& n)
{
  utl_test::test_label(n, "<chrono> Timer");

  using std::chrono::duration_cast;
  using std::chrono::steady_clock;

  steady_clock::time_point t1 = steady_clock::now();  // start time
  int f = frequency_of_primes(PRIME_MAX);
  steady_clock::time_point t2 = steady_clock::now();  // end time

  std::ostringstream oss;
  oss << "  The number of primes lower than "
      << PRIME_LIMIT << " is: " << f << "\n\n"
      << "  Computation time:\n\n  ";
  auto duration_s = duration_cast<std::chrono::duration<double>>(t2 - t1);
  auto duration_ms = duration_cast<std::chrono::milliseconds>(t2 - t1);
  auto duration_us = duration_cast<std::chrono::microseconds>(t2 - t1);
  auto duration_ns = duration_cast<std::chrono::nanoseconds>(t2 - t1);
  oss << duration_s.count() << " seconds, or\n  "
      << duration_ms.count() << " milliseconds, or\n  "
      << duration_us.count() << " microseconds, or\n  "
      << duration_ns.count() << " nanoseconds" << std::endl;
  std::cout << oss.str() <<std::endl;
}


void
test_timer_ctime(int& n)
{
  utl_test::test_label(n, "<ctime> Timer");

  clock_t t = clock();  // start time
  int f = frequency_of_primes(PRIME_MAX);
  t = clock() - t;      // end time

  std::ostringstream oss;
  oss << "  The number of primes lower than "
      << PRIME_LIMIT << " is: " << f << "\n\n"
      << "  Computation took " << t << " clicks ("
      << ((float)t)/CLOCKS_PER_SEC << " seconds)" << std::endl;
  std::cout << oss.str() <<std::endl;
}


} // utl_test
//===========================================================================//
