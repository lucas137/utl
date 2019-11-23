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
/// @brief    Circular countdown graphic.
/// @author   Nathan Lucas
/// @date     2018
//===========================================================================//
#ifndef UTL_OPENCV_COUNTDOWN_HPP
#define UTL_OPENCV_COUNTDOWN_HPP

//-----------------------------------------------------------
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wall"

// OpenCV is released under 3-clause BSD License.
// https://opencv.org/license.html
#include <opencv2/core.hpp>     // cv::Mat, cv::Point, cv::Scalar
#include <opencv2/imgproc.hpp>  // cv::LINE_AA, cv::circle, cv::ellipse

#pragma GCC diagnostic pop
//-----------------------------------------------------------

namespace utl { namespace opencv {
//---------------------------------------------------------------------------

/// @addtogroup utl_opencv
/// @{

/// @brief    Draw a circular countdown graphic with flat ends.
///
/// @param  [in,out]  image   Image on which the graphic is drawn.
/// @param  [in]  ratio       Fraction of countdown consumed,
///                           as a value between`0` and `1`.
/// @param  [in]  center      Center of circular graphic.
/// @param  [in]  radius      Radius of circular graphic.
/// @param  [in]  color_bgr   Shrinking foreground color (blue, green, red).
/// @param  [in]  back_bgr    Expanding background color (blue, green, red).
/// @param  [in]  line_thick  Thickness of the circle outline.
inline void
countdown_circle_flat(cv::Mat& image, double ratio, cv::Point const& center,
                      int radius, cv::Scalar const& color_bgr,
                      cv::Scalar const& back_bgr, int line_thick)
{
  // Background circle
  cv::circle(image, center, radius, back_bgr, line_thick, cv::LINE_AA);

  double angle = (360.0 * ratio);
  if (angle <=  0.0) { return; } else
  if (angle > 360.0) { angle = 360.0; }

  // Foreground arc
  int rad = radius + ((line_thick + 1) / 2);
  for (int i = 0; i <= line_thick; ++i)
  {
    // Draw arc twice to cover both edges of the background
    // and prevent background from bleeding through
    cv::ellipse(image, center, {rad, rad}, -90, angle, 360,
                color_bgr, 1, cv::LINE_AA);
    if ((--rad) <= 0) { return; }
    cv::ellipse(image, center, {rad, rad}, -90, angle, 360,
                color_bgr, 1, cv::LINE_AA);
  }
}

//---------------------------------------------------------------------------

/// @brief    Draw a circular countdown graphic with rounded ends.
///
/// @param  [in,out]  image   Image on which the graphic is drawn.
/// @param  [in]  ratio       Fraction of countdown consumed,
///                           as a value between`0` and `1`.
/// @param  [in]  center      Center of circular graphic.
/// @param  [in]  radius      Radius of circular graphic.
/// @param  [in]  color_bgr   Shrinking foreground color (blue, green, red).
/// @param  [in]  back_bgr    Expanding background color (blue, green, red).
/// @param  [in]  line_thick  Thickness of the circle outline.
inline void
countdown_circle_round(cv::Mat& image, double ratio, cv::Point const& center,
                       int radius, cv::Scalar const& color_bgr,
                       cv::Scalar const& back_bgr, int line_thick)
{
  // Background circle
  cv::circle(image, center, radius, back_bgr, line_thick, cv::LINE_AA);

  double angle = (360.0 * ratio);
  if (angle <=  0.0) { return; } else
  if (angle > 360.0) { angle = 360.0; }

  // Foreground arc
  cv::ellipse(image, center, {radius, radius}, -90, angle, 360,
              color_bgr, line_thick, cv::LINE_AA);
}

//---------------------------------------------------------------------------
} } // utl::opencv

#endif // UTL_OPENCV_COUNTDOWN_HPP
//===========================================================================//
