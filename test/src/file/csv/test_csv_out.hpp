//===========================================================================//
//  Nathan Lucas
//  2015
//===========================================================================//
#ifndef UTL_TEST_CSV_OUT_HPP
#define UTL_TEST_CSV_OUT_HPP

#include <string>       // std::string
#include <iostream>     // std::cout

#include <utl/csv.hpp>    // utl::csv_out

namespace utl_test {


void
test_csv_out()
{
  std::string str;
  utl::csv_out(str) << "foo" << 0 << 1 << '\n'
                    << "bar" << 2 << 3 << '\n';
  std::cout << str;
}


} // utl_test

#endif // UTL_TEST_CSV_OUT_HPP
//===========================================================================//
