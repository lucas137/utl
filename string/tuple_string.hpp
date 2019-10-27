/*
Licensed under the MIT License <http://opensource.org/licenses/MIT>

Copyright 2017 Nathan Lucas <nathan.lucas@wayne.edu>

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
/// @file
/// @brief    Tuple to string formatter.
/// @author   Nathan Lucas
/// @version  0.1
/// @date     2017
//===========================================================================//
#ifndef UTL_TUPLE_STRING_HPP
#define UTL_TUPLE_STRING_HPP

#ifndef __cplusplus
#error must be compiled as C++
#endif

#include <vector>       // std::vector
#include <algorithm>    // std::copy
#include <iterator>     // std::ostream_iterator
#include <string>       // std::string
#include <sstream>      // std::ostringstream

/// @defgroup string  string
/// @brief    String utility library.
/// @details  Header-only library providing string utilities built primarily
///           on C++ standard libraries `<string>` and `<sstream>`.

namespace utl {

/// @addtogroup string
/// @{

//---------------------------------------------------------------------------
/// @name String formatter
/// @{

/// Tuple to string formatter.
template <typename T>
struct TupleString
{
  std::string     delim{};    ///< Delimiter between elements.
  std::string     prefix{};   ///< Prefix before elements.
  std::vector<T>  vector{};   ///< Tuple elements.

  /// Constructor.
  TupleString(std::string const& delim = ",",
              std::string const& prefix = "")
  : delim(delim), prefix(prefix) {}

  /// Returns a formatted string.
  std::string
  str() const
  {
    if (vector.empty()) { return prefix; }
    // Accumulate elements [https://stackoverflow.com/a/6693088]
    std::ostringstream ss;
    std::copy(vector.cbegin(), vector.cend() - 1,
              std::ostream_iterator<T>(ss, delim.c_str()));
    ss << vector.back();
    return (prefix + ss.str());
  }
};

/// @}
//---------------------------------------------------------------------------

/// @}
// end group: string

} // utl

#endif // UTL_TUPLE_STRING_HPP
//===========================================================================//
