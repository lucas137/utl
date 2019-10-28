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
/// @file
/// @brief    Math utility library.
/// @details  Header-only library providing math utilities.
/// @author   Nathan Lucas
/// @version  0.2
/// @date     2015-2017
//===========================================================================//
#ifndef UTL_MATH_HPP
#define UTL_MATH_HPP

#ifndef __cplusplus
#error must be compiled as C++
#endif

#include <cmath>          // std::abs, std::fmod, std::atan2
#include <deque>          // std::deque
#include <type_traits>    // std::is_arithmetic

/// @defgroup math  math
/// @brief    Math utility library.
/// @details  Header-only library providing math utilities.

/// @namespace  utl::math
/// @brief  Math utility library.
///
/// Header-only library providing math utilities.@n
/// See also standard libraries:
/// - `<cmath>`
/// - `<algorithm>`
///
namespace utl { namespace math {

/// @addtogroup math
/// @{
//---------------------------------------------------------------------------

/// Mathematical constant @a π to `20` digits.
constexpr double pi = 3.14159265358979323846;

/// For convience, @a π multiplied by `2`.
constexpr double two_pi = 2.0 * utl::math::pi;    // 2·π

//---------------------------------------------------------------------------
/// @namespace  utl::math::literals
/// @brief  Math utility literals.
///
/// This nested namespace contains user-defined literals to prevent
/// clashes in the global namespace.  End users are responsible for
/// importing these literals where they are needed:
///
///     {
///       using namespace utl::math::literals;    // make _deg visible
///       auto a_rad = -180_deg;    // integer degrees to floating radians
///       auto b_rad = 85.9_deg;    // floating degrees to floating radians
///     }
///
/// https://akrzemi1.wordpress.com/2012/10/29/user-defined-literals-part-iii/
namespace literals {

/// User-defined literal angle conversion from
/// integer degrees to floating-point radians.
constexpr long double
operator"" _deg(unsigned long long int deg)
{
  return ((utl::math::pi * deg) / 180.0);
}

/// User-defined literal angle conversion from
/// floating-point degrees to floating-point radians.
constexpr long double
operator"" _deg(long double deg)
{
  return ((utl::math::pi * deg) / 180.0);
}

/// User-defined literal floating-point angle in radians.
constexpr long double
operator"" _rad(long double rad)
{
    return rad;
}

/// User-defined literal angle conversion from
/// floating-point radians to floating-point degrees.
constexpr long double
operator"" _rad2deg(long double rad)
{
    return ((180.0 * rad) / utl::math::pi);
}

} // literals
//---------------------------------------------------------------------------
/// @name   Angle functions
/// @{

/// Normalize @a angle to be within the interval `[-180, 180]` degrees.
template<typename T>
inline T
standard_deg(T angle)
{
  static_assert(std::is_arithmetic<T>::value, "T must be numeric");
  if (angle >= 0) { return std::fmod(angle + 180,  360) - 180; }
  else            { return std::fmod(angle - 180, -360) + 180; }
}

/// Normalize @a angle to be within the interval `[-π, π]` radians.
inline double
standard_rad(double angle)
{
  if (angle >= 0) { return std::fmod(angle + pi,  two_pi) - pi; }
  else            { return std::fmod(angle - pi, -two_pi) + pi; }
}

/// Convert @a angle from degrees to radians.
template<typename T>
inline double
deg_to_rad(T angle)
{
  static_assert(std::is_arithmetic<T>::value, "T must be numeric");
  return ((static_cast<double>(angle) * utl::math::pi) / 180);
}

/// Convert @a angle from radians to degrees.
template<typename T>
inline T
rad_to_deg(double angle)
{
  static_assert(std::is_arithmetic<T>::value, "T must be numeric");
  return static_cast<T>((180.0 * angle) / utl::math::pi);
}

/// @brief  Checks if point (@a x , @a y ) is within radial limit @a r.
/// @tparam       T   Type of value.
/// @param  [in]  x   Tuple element value.
/// @param  [in]  y   Tuple element value.
/// @param  [in]  r   Radial limit.
/// @return `true` if (@a x , @a y) is within @a r, `false` otherwise.
template<typename T>
inline bool
in_radius(T x, T y, T r)
{
  static_assert(std::is_arithmetic<T>::value, "T must be numeric");
  return (((x * x) + (y * y)) < (r * r));
}


///// @brief  Check if a number is within lower and upper limits.
///// @tparam       T       Type of value.
///// @param  [in]  x       Value to check
///// @param  [in]  lower   Lower limit
///// @param  [in]  upper   Upper limit
///// @return `true` if @a number is between @a lower and @a upper
//template<typename T>
//inline bool
//in_range(T x, T lower, T upper)
//{
//   return ((unsigned)(x - lower) <= (upper - lower));
//}

/// @}
//---------------------------------------------------------------------------
/// @name   Displacement functions
/// @{

/// @brief Returns the squared Euclidean distance between the
///        the points (@a x1 , @a y1 ) and (@a x2 , @a y2 ).
/// @tparam       T   Type of value.
/// @param  [in]  x1  X coordinate of first point.
/// @param  [in]  y1  Y coordinate of first point.
/// @param  [in]  x2  X coordinate of second point.
/// @param  [in]  y2  Y coordinate of second point.
/// @return Squared Euclidean distance.
template<typename T>
inline T
squared_distance(T x1, T y1, T x2, T y2)
{
  static_assert(std::is_arithmetic<T>::value, "T must be numeric");
  T dx = (x2 - x1);
  T dy = (y2 - y1);
  return ((dx * dx) + (dy * dy));
}

/// @}
//---------------------------------------------------------------------------
/// @name   Minimum, maximum, and difference functions
/// @{

/// @brief  Applies an upper and lower bound.
/// @tparam       T     Type of value.
/// @param  [in]  x     Value for which to apply bounds.
/// @param  [in]  min   Lower bound.
/// @param  [in]  max   Upper bound.
/// @return The bounded value of @a x such that @a min ≤ @a x ≤ @a max.
template<typename T>
inline T
bound(T x, T min, T max)
{
  static_assert(std::is_arithmetic<T>::value, "T must be numeric");
  return ((x < min) ? min :
          (x > max) ? max : x);
}

/// @}
//---------------------------------------------------------------------------

//template <typename T, std::size_t N,
//  typename = typename std::enable_if<std::is_arithmetic<T>::value>, T>::type

/// @brief  Computes simple moving average of numeric data.
/// @tparam T   Numeric type.
/// @tparam N   Window size.
template <typename T, std::size_t N>
struct sample_window
{
  static_assert(std::is_arithmetic<T>::value, "T must be numeric");

  /// Returns maximum value within window.
  T  max() const  { return max_ ; }

  /// Returns minimum value within window.
  T  min() const  { return min_; }

  /// Returns mean of values within window.
  T  mean() const { return ( vals_.empty() ? 0 : (sum_ / vals_.size()) ); }

  /// Returns sum total of values within window.
  T  sum() const  { return sum_; }

  //-----------------------------------------------------------
  /// @name Capacity
  /// @{

  /// Tests whether underlying container is empty.
  bool
  empty() const     {  return vals_.empty(); }

  /// Returns number of samples in the window.
  std::size_t
  size() const      { return vals_.size(); }

  /// Returns size of the moving window.
  std::size_t
  window_size() const     { return N; }

  /// @}
  //-----------------------------------------------------------
  /// @name Modifiers
  /// @{

  /// Clears content of the window.
  void
  clear()
  {
    sum_ = 0;
    vals_.clear();
  }

  /// Adds a sample to moving the window.
  void
  push(T val)
  {
    if ((val > max_) || vals_.empty()) { max_ = val; }
    if ((val < min_) || vals_.empty()) { min_ = val; }
    sum_ += val;
    vals_.push_back(val);
    if (vals_.size() > N)
    {
      sum_ -= vals_.front();
      vals_.pop_front();
    }
  }

  /// @}
  //-----------------------------------------------------------
private:
  T max_{0};
  T min_{0};
  T sum_{0};
  std::deque<T> vals_{};
};

//---------------------------------------------------------------------------
/// @}
// end group: math

} } // utl::math

#endif // UTL_MATH_HPP
//===========================================================================//
