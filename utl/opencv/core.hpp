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
/// @brief    Utilities for the OpenCV core module, including basic data types.
/// @author   Nathan Lucas
/// @date     2017
//===========================================================================//
#ifndef UTL_OPENCV_CORE_HPP
#define UTL_OPENCV_CORE_HPP

#ifndef __cplusplus
#error must be compiled as C++
#endif

//-----------------------------------------------------------
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wall"

// OpenCV is released under 3-clause BSD License.
// https://opencv.org/license.html
#include <opencv2/core.hpp>     // cv::Point, cv::Rect, cv::Size

#pragma GCC diagnostic pop
//-----------------------------------------------------------

#include <cmath>      // std::abs, std::atan2
#include <string>     // std::string, std::to_string

namespace utl { namespace opencv {
//---------------------------------------------------------------------------
/// @addtogroup utl_opencv
/// @{
//-----------------------------------------------------------
/// @name   Angle
/// @{

/// Mathematical constant @a π to `20` digits.
constexpr double pi = 3.14159265358979323846;

/// For convience, @a π multiplied by `2`.
constexpr double two_pi = 2.0 * utl::opencv::pi;    // 2·π

/// Compute angle in radians from @a a to @a b.
inline double
angle_rad(cv::Point const& a, cv::Point const& b)
{
  return std::atan2(b.y - a.y, b.x - a.x);
}

/// Compute angle in degrees from @a a to @a b.
inline double
angle_deg(cv::Point const& a, cv::Point const& b)
{
  return 180 * utl::opencv::angle_rad(a, b) / utl::opencv::pi;
}

/// @}
//-----------------------------------------------------------
/// @name   Geometry
/// @{

/// @brief    Collinear point.
/// @details  Returns a point collinear with @a a and @a b that is
///           distance @a d from point @a a in the direction toward @a b.
template <typename T>
inline cv::Point_<T>
collinear_point(cv::Point_<T> const& a, cv::Point_<T> const& b, double d)
{
  // Dimensions of line from a to b
  auto ab = b - a;

  // Compute scaling factor
  double s = d / std::sqrt((ab.x * ab.x) + (ab.y * ab.y));

  // Compute and return point
  return { a.x + static_cast<T>(s * ab.x),
           a.y + static_cast<T>(s * ab.y) };
}
// Reference:
//  https://stackoverflow.com/a/7741655
// Note: Euclidean distance between points a and b (both of type cv::Point)
// can be computed using OpenCV function cv::norm or standard C++.
//     cv::norm(b - a);                    // OpenCV
//     auto d = b - a;
//     std::sqrt((d.x*d.x) + (d.y*d.y));   // standard C++
// cv::norm appears optimized for higher dimensional vectors, but
// std::sqrt is likely better for simple cases such as the above example.

/**
  @brief  Intersection of two lines.

  Returns `true` if the line between @a a1 and @a a2 intersects with the
  line between @a b1 and @a b2.  Returns `false` if the lines are parallel
  within the error specified by the epsilon value @a eps.  If the lines
  intersect, the point of intersection is returned in @a pt.  Otherwise,
  the value of @a pt remains unchanged.

  If the lines intersect, the value of @a seg will be `true` if the
  intersection point lies between the specified end points of both line
  segments, or `false` if it is beyond at least one end point.  If the
  lines do not intersect, the value of @a seg remains unchanged.

  @note The intersection may lie outside one or both of the
        line segments between the specified pairs of points.
*/
template <typename T>
inline bool
intersect(cv::Point_<T> const& a1, cv::Point_<T> const& a2,
          cv::Point_<T> const& b1, cv::Point_<T> const& b2,
          bool& seg, cv::Point_<T>& pt, double eps=1e-8)
{
  cv::Point_<T> a = a2 - a1;      // vector from a1 to a2
  cv::Point_<T> b = b2 - b1;      // vector from b1 to b2

  double cross = a.cross(b);      // (a.x * b.y) - (a.y * b.x);

  if (std::abs(cross) < eps)      // compare with epsilon value
  {
    return false;   // lines are parallel within specified error
  }

  cv::Point_<T> c = b1 - a1;      // vector from b to a

  double t = c.cross(b) / cross;    // ((c.x * b.y) - (c.y * b.x)) / cross;
  double u = c.cross(a) / cross;

  // Intersection point -- may be beyond an
  // end point of one or both line segments
  pt = a1 + (a * t);

  // True if within end points of both line segments
  seg = ((t >= 0) && (t <= 1) && (u >= 0) && (u <= 1));

  return true;
}
// References:
//  http://stackoverflow.com/a/565282
//  http://stackoverflow.com/a/7448287

/**
  @brief  Intersection of two lines.

  Returns `true` if the line between @a a1 and @a a2 intersects with the
  line between @a b1 and @a b2, and the intersection point lies between
  the specified end points.  Returns `false` if the lines are parallel
  within the error specified by the epsilon value @a eps.  If the lines
  intersect, the point of intersection is returned in @a pt.  Otherwise,
  the value of @a pt remains unchanged.
*/
template <typename T>
inline bool
intersect(cv::Point_<T> const& a1, cv::Point_<T> const& a2,
          cv::Point_<T> const& b1, cv::Point_<T> const& b2,
          cv::Point_<T>& pt, double eps=1e-8)
{
  cv::Point_<T> a = a2 - a1;      // vector from a1 to a2
  cv::Point_<T> b = b2 - b1;      // vector from b1 to b2

  double cross = a.cross(b);      // (a.x * b.y) - (a.y * b.x);

  if (std::abs(cross) < eps)      // compare with epsilon value
  {
    return false;   // lines are parallel within specified error
  }

  cv::Point_<T> c = b1 - a1;      // vector from b to a

  double t = c.cross(b) / cross;
  double u = c.cross(a) / cross;

  if ((t >= 0) && (t <= 1) && (u >= 0) && (u <= 1))
  {
    pt = a1 + (a * t);    // intersection point
    return true;
  }
  return false;
}
// References:
//  http://stackoverflow.com/a/565282
//  http://stackoverflow.com/a/7448287

/**
  @brief  Intersection of two lines.

  Returns `true` if the line between @a a1 and @a a2 intersects with the
  line between @a b1 and @a b2, and the intersection point lies between
  the specified end points.  Returns `false` if the lines are parallel
  within the error specified by the epsilon value @a eps.
*/
template <typename T>
inline bool
intersect(cv::Point_<T> const& a1, cv::Point_<T> const& a2,
          cv::Point_<T> const& b1, cv::Point_<T> const& b2, double eps=1e-8)
{
  cv::Point_<T> a = a2 - a1;      // vector from a1 to a2
  cv::Point_<T> b = b2 - b1;      // vector from b1 to b2

  double cross = a.cross(b);      // (a.x * b.y) - (a.y * b.x);

  if (std::abs(cross) < eps)      // compare with epsilon value
  {
    return false;   // lines are parallel within specified error
  }

  cv::Point_<T> c = b1 - a1;      // vector from b to a

  double t = c.cross(b) / cross;
  double u = c.cross(a) / cross;

  return ((t >= 0) && (t <= 1) && (u >= 0) && (u <= 1));
}
// References:
//  http://stackoverflow.com/a/565282
//  http://stackoverflow.com/a/7448287

/**
  @brief  Returns `true` if the lines are parallel.

  Returns `true` if the line between @a a1 and @a a2 is parallel with the line
  between @a b1 and @a b2 within the error specified by epsilon value @a eps.
*/
template <typename T>
inline bool
parallel(cv::Point_<T> const& a1, cv::Point_<T> const& a2,
         cv::Point_<T> const& b1, cv::Point_<T> const& b2, double eps=1e-8)
{
  cv::Point_<T> a = a2 - a1;      // vector from a1 to a2
  cv::Point_<T> b = b2 - b1;      // vector from b1 to b2

  return (std::abs(a.cross(b)) < eps);
}

/// Rotates the specified rectangle by 90 degrees.
inline void
rotate_90_deg(cv::Rect& rect)
{
  int w = rect.height;
  int h = rect.width;
  rect.x += ((rect.width  - w) / 2);
  rect.y += ((rect.height - h) / 2);
  rect.width  = w;
  rect.height = h;
}

/// @}
//-----------------------------------------------------------
/// @name   Serialization
/// @{

/// Returns a string containing the coordinates of
/// point @a pt separated by delimiter @a delim.
inline std::string
to_string(cv::Point const& pt, std::string const& delim = ",")
{
  return (std::to_string(pt.x) + delim + std::to_string(pt.y));
}

/// Returns a string containing the origin ( @a x and @a y coordinates of the
/// top-left corner) and dimensions (width and height) of rectangle @a rect,
/// with values separated by delimiter @a delim.
inline std::string
to_string(cv::Rect const& rect, std::string const& delim = ",")
{
  return (std::to_string(rect.x) + delim + std::to_string(rect.y) + delim +
          std::to_string(rect.width) + delim + std::to_string(rect.height));
}

/// Returns a string containing the dimensions (width and height)
/// of size @a sz separated by delimiter @a delim.
inline std::string
to_string(cv::Size const& sz, std::string const& delim = "x")
{
  return (std::to_string(sz.width) + delim + std::to_string(sz.height));
}

/// @}
//-----------------------------------------------------------
/// @name   Size
/// @{

/// Applies an upper bound on the size of @a rect.
inline void
apply_max_size(cv::Rect& rect, cv::Size const& sz)
{
  if (rect.width  > sz.width)   { rect.width = sz.width; }
  if (rect.height > sz.height)  { rect.height = sz.height; }
}

/// Applies a lower bound on the size of @a rect.
inline void
apply_min_size(cv::Rect& rect, cv::Size const& sz)
{
  if (rect.width  < sz.width)   { rect.width = sz.width; }
  if (rect.height < sz.height)  { rect.height = sz.height; }
}

/// Rounds the width and height of the rectangle up as needed
/// to make the value of each dimension an even number.
inline void
make_size_even(cv::Rect& rect)
{
  if ((rect.width  % 2) != 0) { ++rect.width; }
  if ((rect.height % 2) != 0) { ++rect.height; }
}

/// Returns the larger of @a a and @a b based on area.
/// If both are equivalent, @a a is returned.
inline cv::Rect
max(cv::Rect const& a, cv::Rect const& b)
{
  return ((a.area() >= b.area()) ? a : b);
}

/// Returns the smaller of @a a and @a b based on area.
/// If both are equivalent, @a a is returned.
inline cv::Rect
min(cv::Rect const& a, cv::Rect const& b)
{
  return ((a.area() <= b.area()) ? a : b);
}

/// @}
//-----------------------------------------------------------
/// @name     Squared distance
/// Comparison between squared distance values avoids the computation of
/// square roots that would be necessary to compare absolute distances.  See
/// OpenCV function `cv::norm` for computing absolute distance between points.
///
/// @note Euclidean distance between points a and b (both of type cv::Point)
/// can be computed using OpenCV function `cv::norm` or standard C++.
///
///     cv::norm(b - a);                    // OpenCV
///     auto d = b - a;
///     std::sqrt((d.x*d.x) + (d.y*d.y));   // standard C++
///
/// `cv::norm` appears optimized for higher dimensional vectors, but
/// `std::sqrt` may be better for simple cases such as the above example.
/// @{

/// Returns the squared Euclidean distance computed
/// from the @a x and @a y displacement values in @a pt.
template <typename T>
inline T
squared_distance(cv::Point_<T> const& d)
{
  return ((d.x * d.x) + (d.y * d.y));
}

/// Returns the squared Euclidean distance computed
/// from the width and height values in @a sz.
template <typename T>
inline T
squared_distance(cv::Size_<T> const& s)
{
  return ((s.width * s.width) + (s.height * s.height));
}

/// @}
//-----------------------------------------------------------
/// @}
//---------------------------------------------------------------------------
} } // utl::opencv

#endif // UTL_OPENCV_CORE_HPP
//===========================================================================//
