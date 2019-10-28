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
// Command line interface program usage.
// Nathan Lucas
// 2015
//===========================================================================//
#ifndef UTL_APP_CLI_USAGE_IPP
#define UTL_APP_CLI_USAGE_IPP

#include <iomanip>      //  std::left, std::setfill, std::setw
#include <sstream>      //  std::ostringstream

namespace utl { namespace app { namespace cli {


inline
std::string
usage(std::string const& name, std::vector<option> const& options, int indent)
{
  const int usage_indent = 4;
  std::ostringstream oss;
  oss << "\nUsage:\n" << std::left << std::setfill(' ')
      << std::setw(usage_indent) << " " << name;
  for (auto o : options)
  {
    oss << " [" << o.spec() << "]";
  }
  oss << "\n\nOptions:\n";
  for (auto o : options)
  {
    oss << o.usage(indent);
  }
  return oss.str();
}


} } } // utl::app::cli

#endif // UTL_APP_CLI_USAGE_IPP
//===========================================================================//
