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
/// @brief    Running total.
/// @details  Header-only library providing running total utilities.
/// @author   Nathan Lucas
/// @version  0.1
/// @date     2017-2018
//===========================================================================//
#ifndef UTL_SUMMATION_HPP
#define UTL_SUMMATION_HPP

#ifndef __cplusplus
#error must be compiled as C++
#endif

#include <cstdint>    // std::uint_fast32_t, std::uint_fast64_t
#include <ostream>    // std::ostream

//---------------------------------------------------------------------------
// Integer capacity for distance
//
//  `std::uint_fast64_t` is the fastest unsigned integer type
//  with a width of at least 64 bits, which can store numbers
//  up to 18,446,744,073,709,551,616.
//
//  A 64-bit unsigned integer can represent a squared distance
//  equivalent to 6,865,243,334,406 diagonals across a 1280 x 1024
//  screen (1280 x 1024 = 2,686,976 sq px).  Assuming a robot travels
//  continuously at 15 seconds per diagonal, a sum total distance can be
//  recorded for 3.27 million years before exceeding the integer capacity.
//
//  A 32-bit unsigned integer can store numbers up to 4,294,967,295.
//  For the same 1280 x 1024 resolution as above, it would be capable
//  of accumulating a sum squared distance for 1,598 diagonals, or  At
//  6.67 hours at 15 seconds per diagonal.
//
//    resolution    diagonal    diagonal
//    (pixels)      (pixel^2)   (pixel)
//    -----------   ---------   -------
//    1280 x 1024   2,686,979   1,639
//    1920 x 1200   5,126,400   2,264
//
//---------------------------------------------------------------------------
// Integer capacity for count
//
//  `std::uint_fast32_t` is the fastest unsigned integer type
//  with a width of at least 64 bits, which can store numbers
//  up to 4,294,967,295.
//
//  An unsigned 32-bit counter can be incremented at 60 Hz for
//  up to 828.5 days before exceeding the integer capacity.
//
//---------------------------------------------------------------------------

/// @ingroup  utl_container
/// @defgroup utl_summation   summation
/// @brief    Running total utility library.
/// @details  Header-only library providing a container
///   for computing a running total, and related functions.

namespace utl {

/// @addtogroup utl_summation
/// @{

//---------------------------------------------------------------------------
/// @brief  Running total.
///
/// Accumulates a sum total value and keeps a running count of values added.
class Summation
{
public:

  /// Adds a value to the sum total and increments the count.
  void
  add(std::uint_fast32_t val)
  {
    ++count_;
    sum_ += val;
  }

  /// Returns the numerical count of values added via `add()`.
  std::uint_fast32_t
  count() const       { return count_; }

  /// Returns the sum total of values added via `add()`.
  std::uint_fast64_t
  sum() const      { return sum_; }

private:
  std::uint_fast32_t  count_{0};
  std::uint_fast64_t  sum_{0};
};

//---------------------------------------------------------------------------

/// @name     Non-member function overloads
/// @relates  utl::Summation
/// @{

/// @brief    Insert into output stream.
///
/// Inserts accumulated values from @a sm into stream @a os in the format:
///
///     Sum[N] = S
///
/// where `N` is the number of values accumulated (Summation::count),
/// and `S` is the sum total value (Summation::sum).
inline std::ostream&
operator<<(std::ostream& os, utl::Summation const& sm)
{
  return os << "Sum[" << sm.count() <<"] = " <<  sm.sum();
}

/// @brief  Serialize to string in comma separated value (CSV) format.
///
/// Returns a string containing accumulated values from @a sm:
///
///     N,S
///
/// where `N` is the number of values accumulated (Summation::count),
/// and `S` is the sum total value (Summation::sum).
inline std::string
csv(utl::Summation const& sm)
{
  return (std::to_string(sm.count()) + "," + std::to_string(sm.sum()));
}

/// @}

/// @}

//---------------------------------------------------------------------------
} // utl
#endif // UTL_SUMMATION_HPP
//===========================================================================//
