//===========================================================================//
//  Nathan Lucas
//  2015
//===========================================================================//

#include <iostream>   // std::cout, std::endl
#include <string>     // std::string
#include <sstream>    // std::ostringstream

#include "screen.hpp"

namespace {   //-------------------------------------------------------------

} // anonymous --------------------------------------------------------------


int
main(int argc, char* argv[])
{
  utl_test::Screen screen;
  utl_test::screen_config(screen);
  utl_test::screen_list(screen);
  utl_test::screen_stdout(screen);
  return 0;
}

//===========================================================================//
