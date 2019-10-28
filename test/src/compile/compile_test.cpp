//===========================================================================//
//  Nathan Lucas
//  2017
//===========================================================================//

#include "utl/compile.hpp"

#include "test/test/utl_test.hpp"  // utl_test::test_label

#include <iostream>   // std::cout
#include <string>     // std::string


namespace {   //-------------------------------------------------------------

void
test_compile()
{
  namespace uc = utl::compile;
  std::cout
    <<'\n'<< "compilation date and time"
    <<'\n'
    <<'\n'<< "  __DATE__                "       << __DATE__
    <<'\n'<< "  date_yyyymmdd_str(\":\")  "     << uc::date_yyyymmdd_str(":")
    <<'\n'<< "  date_yyyymmdd_str()     "       << uc::date_yyyymmdd_str()
    <<'\n'<< "  date_yyyymmdd()         "       << uc::date_yyyymmdd()
    <<'\n'<< "  date_yyyy_str()         "       << uc::date_yyyy_str()
    <<'\n'<< "  date_yyyy()             "       << uc::date_yyyy()
    <<'\n'<< "  date_yy_str()             "     << uc::date_yy_str()
    <<'\n'<< "  date_yy()                 "     << uc::date_yy()
    <<'\n'<< "  date_mmm_str()              "   << uc::date_mmm_str()
    <<'\n'<< "  date_mm_str()               "   << uc::date_mm_str()
    <<'\n'<< "  date_m_str()                "   << uc::date_m_str()
    <<'\n'<< "  date_m()                    "   << uc::date_m()
    <<'\n'<< "  date_dd_str()                 " << uc::date_dd_str()
    <<'\n'<< "  date_d_str()                  " << uc::date_d_str()
    <<'\n'<< "  date_d()                      " << uc::date_d()
    <<'\n'
    <<'\n'<< "  __TIME__                "       << __TIME__
    <<'\n'<< "  time_hhmmss_str(\":\")    "     << uc::time_hhmmss_str(":")
    <<'\n'<< "  time_hhmmss_str()       "       << uc::time_hhmmss_str()
    <<'\n'<< "  time_hhmmss()           "       << uc::time_hhmmss()
    <<'\n'<< "  time_hh_str()           "       << uc::time_hh_str()
    <<'\n'<< "  time_hh()               "       << uc::time_hh()
    <<'\n'<< "  time_mm_str()             "     << uc::time_mm_str()
    <<'\n'<< "  time_mm()                 "     << uc::time_mm()
    <<'\n'<< "  time_ss_str()               "   << uc::time_ss_str()
    <<'\n'<< "  time_ss()                   "   << uc::time_ss()
    <<'\n';
}

} // anonymous --------------------------------------------------------------

int
main(int argc, char* argv[])
{
  test_compile();
  return 0;
}

//===========================================================================//
