//===========================================================================//
// \brief    Test utilities
// \author   Nathan P. Lucas
// \version  0.1
// \date     2015
//===========================================================================//
#ifndef UTL_TEST_HPP
#define UTL_TEST_HPP

#include <iostream>     //  std::cout. std::endl
#include <string>       //  std::string

namespace utl_test {


inline void
test_label(int& n, std::string const& name)
{
  std::cout << "\n[" << (++n) << "]  "
            << "---- " << name << " ----\n" << std::endl;
}


inline void
test_label(std::string const& name)
{
  std::cout << "---- " << name << " ----\n" << std::endl;
}


} // utl_test

#endif // UTL_TEST_HPP
//===========================================================================//
