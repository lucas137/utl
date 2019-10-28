//===========================================================================//
//  Nathan Lucas
//  2017
//===========================================================================//

#include "utl/chrono/chrono_datetime.hpp"

#include "utl/chrono/chrono_clock.hpp"    // utl::chrono::now_tm
#include "utl_test.hpp"                   // utl_test::test_label
#include "chrono_test.hpp"

#include <ctime>        // std::tm
#include <iostream>     // std::cout
#include <string>       // std::string, std::to_string

namespace utl_test {

void
test_datetime(int& n)
{
  namespace C = utl::chrono;

  utl_test::test_label(n, "utl::chrono date and time components");

  std::tm now = C::now_tm();

  std::string ns = "utl::chrono::";   // namespace

  std::cout << ns << "day         : " << std::to_string(C::day(now))
    << '\n' << ns << "dayweek     : " << std::to_string(C::dayweek(now))
    << '\n' << ns << "dayweek_str : " <<                C::dayweek_str(now)
    << '\n' << ns << "month       : " << std::to_string(C::month(now))
    << '\n' << ns << "month_str   : " <<                C::month_str(now)
    << '\n' << ns << "mon_str     : " <<                C::mon_str(now)
    << '\n' << ns << "year        : " << std::to_string(C::year(now))
    << '\n' << ns << "yyyymmdd    : " << std::to_string(C::yyyymmdd(now))
    << '\n' << ns << "hour        : " << std::to_string(C::hour(now))
    << '\n' << ns << "min         : " << std::to_string(C::min(now))
    << '\n' << ns << "sec         : " << std::to_string(C::sec(now))
    << '\n' << ns << "is_dst      : " << (C::is_dst(now) ? "true" : "false")
    << '\n' << '\n';
}

} // utl_test
//===========================================================================//
