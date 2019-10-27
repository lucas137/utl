/*
Licensed under the MIT License <http://opensource.org/licenses/MIT>

Copyright 2015 Nathan Lucas <nathan.lucas@wayne.edu>

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/
//===========================================================================//
// Command line interface option parsing.
// Nathan Lucas
// 2015
//===========================================================================//
#ifndef UTL_APP_CLI_PARSE_IPP
#define UTL_APP_CLI_PARSE_IPP

#include <string>

namespace utl { namespace app { namespace cli { namespace detail {


// used by parse_arg() and parse_descr()
template<typename T>
std::string
parse_after(std::string const& str, T const& delim)
{
  std::size_t pos = str.find(delim);
  if (pos != std::string::npos)
  {
    return str.substr(pos + 1);
  }
  return std::string();
}


// used by parse_option() and parse_arg()
template<typename T>
std::string
parse_before(std::string const& str, T const& delim)
{
  std::size_t pos = str.find(delim);
  return str.substr(0, pos);
}


// parse "-option:argument description" and return option
inline std::string
parse_option(std::string const& str)
{
  std::string option = parse_before(str, ':');
  option = parse_before(option, ' ');
  return option;
}


// parse "-option:argument description" and return argument
inline std::string
parse_arg(std::string const& str)
{
  std::string arg = parse_after(str, ':');
  arg = parse_before(arg, ' ');
  return arg;
}


// parse "-option:argument description" and return description
inline std::string
parse_descr(std::string const& str)
{
  return parse_after(str, ' ');
}


} } } } // utl::app::cli::detail

#endif // UTL_APP_CLI_PARSE_IPP
//===========================================================================//
