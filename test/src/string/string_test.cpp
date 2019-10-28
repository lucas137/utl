//===========================================================================//
//  Nathan Lucas
//  2015
//===========================================================================//

#include "utl/string.hpp"
#include "utl/chrono.hpp"   // utl::timer
#include "utl_test.hpp"

#include <iostream>     //  std::cout, std::endl
#include <string>       //  std::string
#include <sstream>      //  std::ostringstream
#include <vector>       //  std::vector

namespace {   //-------------------------------------------------------------

void print_vector(std::vector<std::string> const& v)
{
  for (auto i : v)
  {
    std::cout << "  \"" << i << "\"";
  }
  std::cout << std::endl;
}

//void print_vector(std::vector<std::string> const& v)
//{
//  for (auto it = v.begin(); it != v.end(); ++it)
//  {
//    std::cout << " \"" << (*it) << "\"";
//  }
//  std::cout << std::endl;
//}

typedef utl::chrono::timer::us us;

const std::string usec(" microseconds");

} // anonymous --------------------------------------------------------------


namespace utl_test {


// Test utl::string utilities
void
string_test(int& n)
{
  utl_test::test_label(n, "utl::to_string");
  std::cout << "\n  to_string(11)       : "
            << utl::to_string(11)
            << "\n  to_string_dec(11)   : "
            << utl::to_string_dec(11)
            << "\n  to_string_hex(0x11) : "
            << utl::to_string_hex(0x11)
            << "\n  to_string_oct(011)  : "
            << utl::to_string_oct(011)
            << "\n" << std::endl;

  utl_test::test_label(n, "utl::to_number");
  std::string str("11");
  std::cout << "\n  utl::to_number<int>(str) : "
            << utl::to_number<int>(str) << "\n" << std::endl;
}


// Test string concatenation methods
void
string_test_concat(int& n)
{
  utl_test::test_label(n, "String Concatenation Methods");

  std::string str1 = "string1 ";
  std::string dest = "";
  utl::chrono::timer t;


  // Arithmetic operator+
  t.reset();
  for (int i = 0; i < 100000; ++i)
  {
    dest = str1 + "string2 " + "string3 " + "string4 ";
  }
  std::cout << "  Arithmetic operator+            : "
            << t.elapsed<us>().count() << usec << std::endl;


  // Compound assignment operator+=
  t.reset();
  for (int i = 0; i < 100000; ++i)
  {
    dest = str1;
    dest += "string2 ";
    dest += "string3 ";
    dest += "string4 ";
  }
  std::cout << "  Compound assignment operator+=  : "
            << t.elapsed<us>().count() << usec << std::endl;


  // std::append()
  t.reset();
  for (int i = 0; i < 100000; ++i)
  {
    dest = str1;
    dest.append("string2 ");
    dest.append("string3 ");
    dest.append("string4 ");
  }
  std::cout << "  std::string::append()           : "
            << t.elapsed<us>().count() << usec << std::endl;


  // String stream
  t.reset();
  for (int i = 0; i < 100000; ++i)
  {
    std::ostringstream oss;
    oss << str1
        << "string2 "
        << "string3 "
        << "string4 ";
    oss.flush();
    dest = oss.str();
  }
  std::cout << "  String stream                   : "
            << t.elapsed<us>().count() << usec << "\n" << std::endl;
}


// Test string concatenation methods with casting
void
string_test_concat_cast(int& n)
{
  utl_test::test_label(n, "String Concatenation w/ Casting");

  std::string str = "string1 ";
  std::string dest = "";
  utl::chrono::timer t;


  // Arithmetic operator+
  t.reset();
  for (int i = 0; i < 100000; ++i)
  {
    dest = str + utl::to_string(0)
           + " foo" + utl::to_string(1);
  }
  std::cout << "  Arithmetic operator+            : "
            << t.elapsed<us>().count() << usec << std::endl;


  // Compound assignment
  t.reset();
  for (int i = 0; i < 100000; ++i)
  {
    dest = str;
    dest += utl::to_string(0);
    dest += " foo ";
    dest += utl::to_string(1);
  }
  std::cout << "  Compound assignment operator+=  : "
            << t.elapsed<us>().count() << usec << std::endl;


  // std::append()
  t.reset();
  for (int i = 0; i < 100000; ++i)
  {
    dest = str;
    dest.append(utl::to_string(0));
    dest.append(" foo ");
    dest.append(utl::to_string(0));
  }
  std::cout << "  std::string::append()           : "
            << t.elapsed<us>().count() << usec << std::endl;


  // String stream
  t.reset();
  for (int i = 0; i < 100000; ++i)
  {
    std::ostringstream oss;
    oss << str
        << 0
        << " foo "
        << 1;
    oss.flush();
    dest = oss.str();
  }
  std::cout << "  String stream                   : "
            << t.elapsed<us>().count() << usec << "\n" << std::endl;
}


// Test string parsing
void
string_test_parse(int& n)
{
  utl_test::test_label(n, "utl::parse");

  std::string s = "00:01:10:11";

  std::vector<std::string> v = utl::parse(s, ":");
  print_vector(v);

  v = utl::parse(s, ":");
  print_vector(v);

  std::vector<std::string> vv = utl::parse(s, ':');
  print_vector(v);

  vv = utl::parse(s, ':');
  print_vector(v);
}


// Test string parsing
void
string_test_option(int& n)
{
  utl_test::test_label(n, "utl::contains");

  std::string s("-o:arg");
  if (utl::contains(s, "-o"))
  {
    std::cout << "  option -o" << std::endl;
  }

  utl_test::test_label(n, "utl::checkparse");

  std::string arg("");
  if (utl::checkparse(s, "-o", ":", arg))
  {
    if (!arg.empty())
    {
      std::cout << "  option -o, argument " << arg << std::endl;
    }
  }
}

} // utl_test

//===========================================================================//

int
main(int argc, char* argv[])
{
  int n = 0;  // test number

  utl_test::string_test(n);           // string to number, number to string

  utl_test::string_test_concat(n);        // concatenation methods
  utl_test::string_test_concat_cast(n);   // concatenation w/ casting
  utl_test::string_test_parse(n);         // parse string by delimiter
  utl_test::string_test_option(n);        // parse option and argument

  return 0;
}

//===========================================================================//
