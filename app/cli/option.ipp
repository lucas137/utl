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
// Command line interface option.
// Nathan Lucas
// 2015
//===========================================================================//
#ifndef UTL_APP_CLI_OPTION_IPP
#define UTL_APP_CLI_OPTION_IPP

#include "detail/parse.ipp"

#include <iomanip>      //  std::left, std::setfill, std::setw
#include <sstream>      //  std::ostringstream

namespace utl { namespace app { namespace cli {


inline
option::option(std::string const& option_spec,
                         std::string const& description)
: opt(utl::app::cli::detail::parse_option(option_spec)),
  arg(utl::app::cli::detail::parse_arg(option_spec)),
  descr(description)
{}  // do nothing


inline
void
option::push_arg(std::string const& arg, std::string const& descr)
{
  if (!arg.empty())
  {
    valid_args.push_back(arg);
    valid_descr.push_back(descr);
  }
}


inline
std::string
option::spec() const
{
  if (arg.empty())
  {
    return opt;
  }
  return opt + ":" + arg;
}


inline
std::string
option::usage(int descr_indent) const
{
  const int option_indent = 4;  // Indent options four spaces
  std::ostringstream oss;       // Output string stream

  // Output option specification and description
  oss << std::left << std::setfill(' ')
      << std::setw(option_indent) << " "
      << std::setw(descr_indent) << spec() << descr << "\n";

  // If one or more valid arguments
  if (!valid_args.empty())
  {
    // Get maximum length of valid arguments
    int max_arg_size = 0;
    for (auto a : valid_args)
    {
      int arg_size = a.size();
      if (arg_size > max_arg_size) { max_arg_size = arg_size; }
    }
    // Compute indents for argument and argument description
    int arg_indent = (option_indent + opt.size() + 1);
    int arg_descr_indent = (descr_indent - spec().size() + 1);
    if (arg_descr_indent <= max_arg_size)
    {
        arg_descr_indent = (max_arg_size + 2);
    }
    // Output arguments and descriptions
    for (std::size_t i = 0; i != valid_args.size(); ++i)
    {
      oss << std::left << std::setfill(' ')
          << std::setw(arg_indent) << " "
          << std::setw(arg_descr_indent) << valid_args[i]
                                         << valid_descr[i] << "\n";
    }
  }
  return oss.str();
}


inline
bool
option::match(std::string const& str) const
{
  std::string s = utl::app::cli::detail::parse_option(str);
  if (s == opt)
  {
    return true;
  }
  return false;
}


inline
std::string
option::any_arg(std::string const& str) const
{
  if (utl::app::cli::detail::parse_option(str) == opt)
  {
    return utl::app::cli::detail::parse_arg(str);
  }
  return std::string();
}


inline std::string
option::valid_arg(std::string const& str) const
{
  std::string str_opt = utl::app::cli::detail::parse_option(str);
  std::string str_arg = utl::app::cli::detail::parse_arg(str);
  if (str_opt == opt)
  {
    for (auto a : valid_args)
    {
      if (str_arg == a)
      {
        return str_arg;
      }
    }
  }
  return std::string();
}


} } } // utl::app::cli

#endif // UTL_APP_CLI_OPTION_IPP
//===========================================================================//
