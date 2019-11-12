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
/// @brief    Input/Output stream utility library.
/// @details  Header-only library providing iostream utilities, built
///           on C++ standard libraries `<iostream>` and `<sstream>`. @n
///           Includes formatted standard output via `std::out`.
/// @author   Nathan Lucas
/// @date     2015
//===========================================================================//
#ifndef UTL_IOSTREAM_HPP
#define UTL_IOSTREAM_HPP

#ifndef __cplusplus
#error must be compiled as C++
#endif

#include <iostream>       // std::cout, std::endl, std::dec, std::hex
#include <iomanip>        // std::setfill, std::setw
#include <sstream>        // std::ostream
#include <string>         // std::string

/// @defgroup iostream  iostream
/// @brief    Input/Output stream utility library.
/// @details  Header-only library providing iostream utilities, built
///           on C++ standard libraries `<iostream>` and `<sstream`>. @n
///           Includes formatted standard output via `std::out`.

namespace utl {

/// @addtogroup iostream
/// @{

//---------------------------------------------------------------------------
/// @name Standard Output Stream Functions
/// @{


/// @brief  Output a number to console in decimal format.
/// @tparam       T     Type of value.
/// @param  [in]  name  Variable name or label
/// @param  [in]  n     Number to output
///
template<typename T>
inline void
cout_value(std::string const& name, T n)
{
  std::cout << name << "=" << n;
}


/// @brief  Output a number to console in decimal format.
/// @tparam       T       Type of value.
/// @param  [in]  name    Variable name or label
/// @param  [in]  n       Number to output
/// @param  [in]  digits  Number of digits to output
template<typename T>
inline void
cout_value(std::string const& name, T n, unsigned digits)
{
  std::cout << name << "=" << std::setfill('0') << std::setw(digits) << n;
         // << std::setfill(' ');
  std::cout.copyfmt(std::ios(nullptr));   // restore default
}


/// @brief  Output a number to console in hexidecimal format.
/// @tparam       T       Type of value.
/// @param  [in]  name    Variable name or label
/// @param  [in]  n       Number to output
/// @param  [in]  digits  Number of digits to output
template<typename T>
inline void
cout_hex(std::string const& name, T n, unsigned digits=8)
{
  std::cout << name << "=0x" << std::setfill('0') << std::hex
            << std::setw(digits + 2) << n << std::dec;
            // << std::setfill(' ');
  std::cout.copyfmt(std::ios(nullptr));   // restore default
}


/// @brief  Output a coordinate pair to console.
/// @tparam       T       Type of value.
/// @param  [in]  name    Variable name or label
/// @param  [in]  x       First coordinate
/// @param  [in]  y       Second coordinate
/// @param  [in]  digits  Number of digits to output
template<typename T>
inline void
cout_coord(std::string const& name, T x, T y, unsigned digits=0)
{
  std::cout << name << "=(" << std::setw(digits) << x << ","
                            << std::setw(digits) << y << ")";
  std::cout.copyfmt(std::ios(nullptr));   // restore default
}


/// @brief  Output a coordinate pair to console.
/// @param  [in]  name        Variable name or label
/// @param  [in]  x           First coordinate
/// @param  [in]  y           Second coordinate
/// @param  [in]  precision   Decimal precision
/// @param  [in]  digits      Number of digits to output
inline void
cout_coord(std::string const& name, double x, double y,
           unsigned precision, unsigned digits=0)
{
  std::cout << std::fixed
            << std::setw(digits)
            << std::setprecision(precision)
            << name << "=(" << x << "," << y << ")";
  std::cout.copyfmt(std::ios(nullptr));   // restore default
}


/// @}
//---------------------------------------------------------------------------
/// @brief    Accumulates output stream values.
///
/// Accumulates values in a temporary stream and writes all
/// values into an output stream when the object is destroyed.
/// Use @em accumulate_ostream to synchronize multiple output streams. @n
/// Example usage:
/// ```
///   utl::accumulate_ostream(std::cout) << val1 << val2 << val3;
/// ```
class accumulate_ostream
{
public:

  /// @brief  Constructor.
  /// @param  [out] os  Output stream which to write accumlated values.
  explicit
  accumulate_ostream(std::ostream& os)
  : os_(os)
  , ss_()
  {}

  /// Prohibits copying.
  accumulate_ostream(accumulate_ostream const&) = delete;

  /// Prohibits assignment.
  accumulate_ostream& operator=(accumulate_ostream const&) = delete;

  // Above deletes are not strictly necessary, but are provided for clarity
  // stringstream is not copyable, so copies are already forbidden


  /// @brief  Destructor writes accumulated values to the output stream.
  ~accumulate_ostream()
  {
    os_ << ss_.rdbuf() << std::flush;   // write full expression at once
  }

  /// @brief  Add a value.
  /// @tparam       T     Type of value.
  /// @param  [in]  val   Value to add.
  /// @return Reference to `this` object.
  template<typename T>
  accumulate_ostream& operator<<(T const& val)
  {
    // accumulate into non-shared stringstream to avoid threading issues
    ss_ << val;
    return *this;
  }

private:

  std::ostream&     os_;
  std::stringstream ss_;

};

//---------------------------------------------------------------------------


/// @}
// end group: iostream

} // utl

#endif // UTL_IOSTREAM_HPP
//===========================================================================//
