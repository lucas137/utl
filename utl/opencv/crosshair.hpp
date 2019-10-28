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
/// @brief    %Crosshair widget.
/// @author   Nathan Lucas
/// @date     2016
//===========================================================================//
#ifndef UTL_OPENCV_CROSSHAIR_HPP
#define UTL_OPENCV_CROSSHAIR_HPP

#ifndef __cplusplus
#error must be compiled as C++
#endif

//-----------------------------------------------------------
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wall"

// OpenCV is released under 3-clause BSD License.
// https://opencv.org/license.html
#include <opencv2/core.hpp>     // cv::Mat, cv::Point, cv::Scalar
#include <opencv2/imgproc.hpp>  // cv::line, CV_FILLED

#pragma GCC diagnostic pop
//-----------------------------------------------------------

#include <string>   // std::string, std::to_string

// Example:
// utl::opencv::Crosshair  crosshair_{12, {255,0,0}, 1, true};

namespace utl { namespace opencv {
//---------------------------------------------------------------------------
/// @addtogroup utl_opencv
/// @{

/// %Crosshair widget.
class Crosshair
{
public:
  /// @brief  Construct at a specified point.
  /// @param  [in]  x         X coordinate of center point.
  /// @param  [in]  y         Y coordinate of center point.
  /// @param  [in]  size      Length from center to end points.
  /// @param  [in]  color_bgr Line color (blue, green, red).
  /// @param  [in]  thickness Line width.
  /// @param  [in]  visible   `true` to set visible flag.
  Crosshair(int x, int y, int size, cv::Scalar const& color_bgr,
            int thickness = 1, bool visible = false)
  : h1(x - size, y)
  , h2(x + size, y)
  , v1(x, y - size)
  , v2(x, y + size)
  , size(size)
  , color_bgr(color_bgr)
  , thickness(thickness)
  , visible(visible)
  {}

  /// @brief  Construct.
  /// @param  [in]  size      Length from center to end points.
  /// @param  [in]  color_bgr Line color (blue, green, red)
  /// @param  [in]  thickness Line width.
  /// @param  [in]  visible   `true` to set visible flag.
  Crosshair(int size, cv::Scalar const& color_bgr,
            int thickness = 1, bool visible = false)
  : size(size)
  , color_bgr(color_bgr)
  , thickness(thickness)
  , visible(visible)
  {}

  /// Draw on `image`.
  void
  draw(cv::Mat& image) const
  {
    if (visible)
    {
      /*
        Line styles
          cv::LINE_8
          cv::LINE_4
          cv::LINE_AA
      */
      //cv::line(image, h1, h2, color_bgr, thickness, cv::LINE_8); // horizontal
      //cv::line(image, v1, v2, color_bgr, thickness, cv::LINE_8); // vertical
      cv::rectangle(image, h1, h2, color_bgr, CV_FILLED);//thickness, cv::LINE_8); // horizontal
      cv::rectangle(image, v1, v2, color_bgr, CV_FILLED);//thickness, cv::LINE_8); // vertical
    }
  }

  /// @brief  Center at the specified coordinates.
  /// @param  [in]  x   X coordinate of center point.
  /// @param  [in]  y   Y coordinate of center point.
  void
  center(int x, int y)
  {
    h1 = cv::Point( x-size  , y-1 );
    h2 = cv::Point( x+size-1, y   );
    v1 = cv::Point( x-1, y-size   );
    v2 = cv::Point( x  , y+size-1 );
  }

  bool is_visible() const   { return visible; } ///< Returns `true` if visible.
  void is_visible(bool val) { visible = val; }  ///< `true` to make visible.

private:
  cv::Point   h1{0,0};
  cv::Point   h2{0,0};
  cv::Point   v1{0,0};
  cv::Point   v2{0,0};
  int         size;
  cv::Scalar  color_bgr;
  int         thickness;
  bool        visible;
};

/// @}
//---------------------------------------------------------------------------
} } // utl::opencv

#endif // UTL_OPENCV_CROSSHAIR_HPP
//===========================================================================//
