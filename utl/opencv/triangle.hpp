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
/// @brief    Isosceles triangle widget.
/// @author   Nathan Lucas
/// @date     2016
//===========================================================================//
#ifndef UTL_OPENCV_TRIANGLE_HPP
#define UTL_OPENCV_TRIANGLE_HPP

#ifndef __cplusplus
#error must be compiled as C++
#endif

//-----------------------------------------------------------
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wall"

// OpenCV is released under 3-clause BSD License.
// https://opencv.org/license.html
#include <opencv2/core.hpp>     // cv::Mat, cv::Point, cv::Scalar
#include <opencv2/imgproc.hpp>  // cv::fillPoly

#pragma GCC diagnostic pop
//-----------------------------------------------------------

#include <cmath>      // std::cos, std::sin

namespace utl { namespace opencv {
//---------------------------------------------------------------------------
/// @addtogroup utl_opencv
/// @{

/// Isosceles triangle widget.
struct Triangle
{
  /// Construct an isosceles triangle.
  inline
  Triangle();

  /// @brief  Construct an isosceles triangle.
  /// @param  [in]  center      Position (x, y).
  /// @param  [in]  rotation    Rotation in radians.
  /// @param  [in]  length      Center to tip in pixels.
  /// @param  [in]  ratio       Ratio of the width to length.
  /// @param  [in]  color_bgr   Fill color.
  /// @param  [in]  offset      Euclidean distance from the center point
  ///   to the centroid of the triangle in the direction of the rotation.
  /// @param  [in]  visible     `true` to draw triangle.
  inline
  Triangle(cv::Point const& center, double rotation, int length, double ratio,
           cv::Scalar const& color_bgr, int offset = 0, bool visible = true);

  ///// Set color (blue, green, red).
  //void color(cv::Scalar const& color_bgr);

  /// Draws triangle on `image`.
  inline void draw(cv::Mat& image) const;

  /// Sets position and orientation.
  inline void pose(cv::Point const& center, double rotation);

  /// Returns center point.
  cv::Point center() const  { return center_; }

  /// Returns orientation in radians.
  double rotation() const   { return rotation_; }

  /// Returns `true` if shown when drawn.
  bool is_visible() const   { return visible_; }

  /// Returns `true` to show when draw.
  void is_visible(bool val) { visible_ = val; }

private:
  static constexpr double half_pi = 3.14159265358979323846 / 2;   // π/2

  cv::Point   center_{0};                 // Postion (x, y)
  double      rotation_{0};               // Rotation in radians
  cv::Point   pts_[3];                    // Polygon points
  int         length_{10};                // Center to tip in pixels
  int         width_{10};                 // Center to left/right corner
  cv::Scalar  color_bgr_{255,255,255};    // Fill color
  int         offset_{0};                 // Center to triangle centroid
                                          // in the direction of rotation
  bool        visible_{true};             // `true` to draw triangle
};

/// @}

//---------------------------------------------------------------------------
// Implementation
//---------------------------------------------------------------------------

Triangle::Triangle()
{
  pose(center_, rotation_);
}

Triangle::Triangle(
    cv::Point const& center, double rotation, int length, double ratio,
    cv::Scalar const& color_bgr, int offset, bool visible)
: center_(center)
, rotation_(rotation)
, pts_({ center, center, center })
, length_(length)
, width_(ratio*length)
, color_bgr_(color_bgr)
, offset_(offset)
, visible_(visible)
{
  pose(center_, rotation_);
}

//void
//Triangle::color(cv::Scalar const& color_bgr)
//{
//  color_bgr_ = color_bgr;
//}

void
Triangle::draw(cv::Mat& image) const
{
  if (!visible_) { return; }

  cv::Point const* ppt[1] = { pts_ }; // Array of polygons
  int npt[] = { 3 };  // Array of polygon vertex counters

  cv::fillPoly(image, ppt, npt, 1 /*contours*/, color_bgr_, cv::LINE_AA);
}

void
Triangle::pose(cv::Point const& center, double rotation)
{
  center_   = center;
  rotation_ = rotation;

  // Offset
  cv::Point offset = cv::Point(offset_ * std::cos(rotation_),
                               offset_ * std::sin(rotation_));
  // Tip
  pts_[0] = center_ + offset + cv::Point(length_ * std::cos(rotation_),
                                         length_ * std::sin(rotation_));
  // Left
  pts_[1] = center_ + offset + cv::Point(width_ * std::cos(rotation_+half_pi),
                                         width_ * std::sin(rotation_+half_pi));
  // Right
  pts_[2] = center_ + offset + cv::Point(width_ * std::cos(rotation_-half_pi),
                                         width_ * std::sin(rotation_-half_pi));
}


//---------------------------------------------------------------------------
} } // utl::opencv

#endif // UTL_OPENCV_TRIANGLE_HPP
//===========================================================================//
