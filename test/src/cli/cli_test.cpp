//===========================================================================//
//  Nathan Lucas
//  2015
//===========================================================================//

#include <iostream>     //  std::cout, std::endl
#include <string>       //  std::string
#include <vector>       //  std::vector

#include "utl_test.hpp"
#include "utl/cli.hpp"

namespace utl_test {


void
cli_test(int& n)
{
  utl_test::test_label(n, "utl::cli::print_separator");

  std::string str(79, '-');
  std::cout << utl::cli::separator(79) << std::endl;
  std::cout << utl::cli::separator('-') << std::endl;
  std::cout << utl::cli::separator() << std::endl;
}


void
cli_option_test(int& n)
{
  utl_test::test_label(n, "utl::cli::option");

  // program name would normally be passed to main as argv[0]
  std::string program_name("cli_test");

  typedef utl::cli::option Option;

  // list of possible command line options and arguments
  Option help("-h", "show this help message");
  Option xopt("-x:N", "number of some import");
  xopt.push_arg("one", "the number one");
  xopt.push_arg("two", "the number two");
  Option yopt("-y:L", "another number of import");
  yopt.push_arg("a", "the letter a");
  yopt.push_arg("b", "the letter b");
  Option zopt("-z", "one more number of import");

  // suppose the user specified "-h" option for help
  std::string user_option("-h");
  if (help.match(user_option))
  {
    // create vector of options
    std::vector<Option> options {help, xopt, yopt, zopt};
    // output program usage
    std::cout << utl::cli::usage(program_name, options, 8) << std::endl;
  }

  // suppose the user specified "-x:1" (i.e, option "-x" with argument "1")
  user_option = "-x:1";
  if (xopt.match(user_option))
  {
    std::string num = xopt.any_arg(user_option);
    std::cout << "x = " << num << std::endl;
  }
}


} // utl_test

//===========================================================================//

int
main(int argc, char* argv[])
{
  int n = 0;  // test number

  utl_test::cli_test(n);          // command line interface utilities
  utl_test::cli_option_test(n);   // command line interface options

  return 0;
}

//===========================================================================//
