//===========================================================================//
//  Nathan Lucas
//  2015
//===========================================================================//

#include <iostream>     //  std::cout, std::endl
#include <string>       //  std::string

#include "utl/time.hpp"     // utl::timestamp::datetime
#include "utl/logfile.hpp"

int
main(int argc, char* argv[])
{
  std::string datetime(utl::timestamp::datetime("_", "", ""));
  std::string filename("log/logfile_test_" + datetime + ".csv");

  std::cout <<  "  filename: " << filename << "\n" << std::endl;

  utl::logfile log(filename);

  std::string header("one,two,three\n");
  log.append(header);

  std::string data("1,2,3\n");
  log.append(data);

  return 0;
}

//===========================================================================//
