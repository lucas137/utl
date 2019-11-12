//===========================================================================//
//  Nathan Lucas
//  2015
//===========================================================================//

#include "utl/keyval.hpp"     // utl::keyval

#include "utl/string.hpp"     // utl::string
#include "utl_test.hpp"       // utl_test::test_label

#include <iostream>     // std::cout, std::endl
#include <string>       // std::string
#include <vector>       // std::vector

namespace {   //-------------------------------------------------------------


// Configuration settings
struct configuration
{
  std::string config_file;  ///< Configuration file name
  int         integer;      ///< Integer value
  double      floating;     ///< Floating point value
  bool        boolean;      ///< A Boolean value
  std::string stdstring;

  /// \brief  Create a structure with default configuration settings.
  ///
  configuration(std::string filename)
  : config_file(filename)
  , integer(0)
  , floating(0.0)
  , boolean(false)
  , stdstring("-")
  {}

};


// Parse input file and store values in the specified structures
bool
config_parse(configuration& c)
{
  utl::keyvalue config;

  if (!config(c.config_file))
  {
    std::cout << "ERROR: Could not open configuration file: \""
              << c.config_file << "\"" << std::endl;
    return false;
  }

  // It would be faster to just check for each value using config.count(),
  // but iterating over the values allows us to check for unrecognized keys.

  for (auto const& i : config.unordered_map())
  {
    std::string key = i.first;
    std::string value = i.second;

    if (key == "integer")
    {
      utl::string::to_number(c.integer, value);
    }
    else if (key == "floating")
    {
      utl::string::to_number(c.floating, value);
    }
    else if (key == "boolean")
    {
      utl::string::to_number(c.boolean, value);
    }
    else if (key == "stdstring")
    {
      c.stdstring = value;
    }
    else
    {
      std::cout << "WARNING: Unrecognized key: " << key << std::endl;
    }
  }

//  std::cout << utl::keyval::list(config, ": ") << std::endl;

//  std::cout << utl::keyval::column(config) << std::endl;

  return true;
}


// Print configuration to console
void
print(configuration const& c)
{
  std::cout << "configuration"                                     << '\n'
            << "  integer   : " << c.integer                         << '\n'
            << "  floating  : " << c.floating                        << '\n'
            << "  boolean   : " << utl::string::to_string(c.boolean) << '\n'
            << "  stdstring : " << c.stdstring                       << '\n';
}


} // anonymous --------------------------------------------------------------


int
main(int argc, char* argv[])
{
  utl_test::test_label("keyval_test");

  configuration config("keyval_config.yml");
  if (!config_parse(config))
  {
    std::cout << "error!" << std::endl;
    return 1;
  }
  print(config);

  return 0;
}

//===========================================================================//
