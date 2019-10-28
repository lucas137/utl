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
/// @brief    Circular region of interest.
/// @author   Nathan Lucas
/// @date     2017-2018
//===========================================================================//
#ifndef UTL_OPENCV_CIRCLE_REGION_HPP
#define UTL_OPENCV_CIRCLE_REGION_HPP

//-----------------------------------------------------------
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wall"

// OpenCV is released under 3-clause BSD License.
// https://opencv.org/license.html
#include <opencv2/core.hpp>       // cv::Mat, cv::Point, cv::Scalar
#include <opencv2/imgproc.hpp>    // cv::circle

#pragma GCC diagnostic pop
//-----------------------------------------------------------

namespace utl { namespace opencv {
//---------------------------------------------------------------------------
/// @addtogroup utl_opencv
/// @{

/// A circular region of interest.
class CircleRegion
{
public:

  /// Constructs a circular region of interest.
  CircleRegion(cv::Point const& center, unsigned radius);

  /// Returns `true` and sets active state if point is within region.
  bool active(cv::Point const& pt);

  cv::Point center() const;               ///< Returns center point of region.
  void      center(cv::Point const& pt);  ///< Sets center point of region.

  /// Returns `true` if point is within region.
  bool contains(cv::Point const& pt) const;

  /// Draws a circle around the region.
  void draw(cv::Mat& image, cv::Scalar const& color_bgr,
            int thickness, int line_type) const;

  /// Draws a circle around the region if active.
  void draw_active(cv::Mat& image, cv::Scalar const& color_bgr,
                   int thickness, int line_type) const;

  /// Returns `true` if last point received via active() is within region.
  bool is_active() const;

  /// Sets/resets active state.
  void is_active(bool a);

private:
  cv::Point center_;            // Coordinates of center point
  bool      is_active_{false};  // True if active point is within region
  int       radius_;            // Radius of click region
  int       radius_sq_;         // Radius squared
};

/// @}
//---------------------------------------------------------------------------
// Implementation

inline
CircleRegion::CircleRegion(cv::Point const& center, unsigned radius)
: center_(center)
, radius_(radius)
, radius_sq_(radius * radius)
{}

inline bool
CircleRegion::active(cv::Point const& pt)
{
  return is_active_ = contains(pt);
}

inline cv::Point
CircleRegion::center() const
{
  return center_;
}

inline void
CircleRegion::center(cv::Point const& pt)
{
  center_ = pt;
}

inline bool
CircleRegion::contains(cv::Point const& pt) const
{
  int dx = (pt.x - center_.x);
  int dy = (pt.y - center_.y);
  return (((dx * dx) + (dy * dy)) <= radius_sq_);
}

inline void
CircleRegion::draw(cv::Mat& image, cv::Scalar const& color_bgr,
                  int thickness, int line_type) const
{
  cv::circle(image, center_, radius_, color_bgr, thickness, line_type);
}

inline void
CircleRegion::draw_active(cv::Mat& image, cv::Scalar const& color_bgr,
                         int thickness, int line_type) const
{
  if (is_active_)
  {
    cv::circle(image, center_, radius_, color_bgr, thickness, line_type);
  }
}

inline bool CircleRegion::is_active() const { return is_active_; }
inline void CircleRegion::is_active(bool a) { is_active_ = a; }

//---------------------------------------------------------------------------
} } // utl::opencv

#endif // UTL_OPENCV_CIRCLE_REGION_HPP
//===========================================================================//
