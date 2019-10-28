//===========================================================================//
//  Nathan Lucas
//  2015
//===========================================================================//

#include <iostream>     // std::cout, std::endl
#include <sstream>      // std::ostringstream
#include <string>       // std::string
#include <chrono>       // std::chrono::milliseconds
                        // std::chrono::system_clock::now, time_point

#include "utl/chrono.hpp"   // util::chrono::date
                            // util::chrono::datetime
                            // util::chrono::time

#include "utl_test.hpp"        // utl_test::test_label
#include "chrono_test.hpp"

namespace utl_test {


void
test_timestamp(int& n)
{
  utl_test::test_label(n, "utl::chrono date/timestamp");

  // [x]  timestamp      basic               extended
  //      ---------      -----               --------
  //      date           YYYYMMDD            YYYY-MM-DD
  //      time           hhmmss              hh:mm:ss
  //      datetime       YYYYMMDDThhmmss     YYYY-MM-DDThh:mm:ss
  //      filename       YYYYMMDD_hhmmss
  std::ostringstream oss;
  oss << "  timestamp\tbasic\t\t\textended\n"
      << "  ---------\t-----\t\t\t--------\n"
      << "  date\t\t"    << utl::chrono::date("")             << "\t\t"
                         << utl::chrono::date()               << "\n"
      << "  time\t\t"    << utl::chrono::time("")             << "\t\t\t"
                         << utl::chrono::time()               << "\n"
      << "  datetime\t"  << utl::chrono::datetime("T","","")  << "\t\t"
                         << utl::chrono::datetime()           << "\n";

  std::string filename = "log_";
  filename += (utl::chrono::datetime("_","","") + ".txt");
  oss << "  filename\t" << filename << std::endl;

  std::cout << oss.str() << std::endl;

  //-----------------------------------------------------------------

  std::size_t const N = 1000000;
  clock_t t = clock();  // start time
  for (std::size_t i = 0; i != N; ++i)
  {
    utl::chrono::time("");
  }
  t = clock() - t;      // end time

  std::cout << "  It took " << t << " clicks ("
      << ((float)t)/CLOCKS_PER_SEC << " seconds)\n"
      << "  to call utl::chrono::time() " << N << " times,\n  or "
      << ((1000000.0 * (float)t)/CLOCKS_PER_SEC) / (float)N
      << " microseconds per call\n" << std::endl;
}


} // utl_test
//===========================================================================//
