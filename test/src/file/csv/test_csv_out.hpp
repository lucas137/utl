//===========================================================================//
//  Nathan Lucas
//  2015
//===========================================================================//
#ifndef UTL_TEST_CSV_OUT_HPP
#define UTL_TEST_CSV_OUT_HPP

#include <utl/file/file_csv.hpp>  // utl::file::csv_out

#include <string>       // std::string
#include <iostream>     // std::cout

namespace utl_test {


void
test_csv_out()
{
  std::string str;
  utl::file::csv_out(str) << "foo" << 0 << 1 << '\n'
                          << "bar" << 2 << 3 << '\n';
  std::cout << str;
}


} // utl_test

#endif // UTL_TEST_CSV_OUT_HPP
//===========================================================================//
