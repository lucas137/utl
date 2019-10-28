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
/// @brief    %Coordinates widget.
/// @author   Nathan Lucas
/// @date     2016
//===========================================================================//
#ifndef UTL_OPENCV_COORDINATES_HPP
#define UTL_OPENCV_COORDINATES_HPP

#ifndef __cplusplus
#error must be compiled as C++
#endif

//-----------------------------------------------------------
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wall"
#pragma GCC diagnostic ignored "-Wextra"
#pragma GCC diagnostic ignored "-Weffc++"

// OpenCV is released under 3-clause BSD License.
// https://opencv.org/license.html
#include <opencv2/core.hpp>     // cv::Mat, cv::Point, cv::Scalar
#include <opencv2/imgproc.hpp>  // cv::putText

#pragma GCC diagnostic pop
//-----------------------------------------------------------

#include <string>   // std::string, std::to_string

namespace utl { namespace opencv {
//---------------------------------------------------------------------------
/// @addtogroup utl_opencv
/// @{

/// %Coordinates widget.
class Coordinates
{
public:

  /// Constructor.
  Coordinates(cv::Point const& point, cv::Scalar const& color_bgr,
              double font_scale = 0.4,
              cv::Point const& offset = cv::Point(5,-8))
  : str_(std::to_string(point.x) + "," + std::to_string(point.y))
  , org_(point + offset)
  , color_bgr_(color_bgr)
  , font_scale_(font_scale)
  , offset_(offset)
  {}

  /// Draw coordinates on `image` at the %point set via `point()`.
  void
  draw(cv::Mat& image) const
  {
    // OpenCV fonts:
    //  Serif
    //    cv::FONT_HERSHEY_COMPLEX          // normal size serif
    //    cv::FONT_HERSHEY_COMPLEX_SMALL    // small size serif
    //    cv::FONT_HERSHEY_TRIPLEX          // more complex serif
    //    cv::FONT_HERSHEY_SCRIPT_SIMPLEX   // normal size hand-writing style
    //    cv::FONT_HERSHEY_SCRIPT_COMPLEX   // more complex hand-writing style
    //  Sans-serif
    //    cv::FONT_HERSHEY_SIMPLEX          // normal size sans-serif
    //    cv::FONT_HERSHEY_PLAIN            // small size sans-serif
    //    cv::FONT_HERSHEY_DUPLEX           // more complex sans-serif
    //  Each font can be optionally combined with cv::FONT_ITALIC

    cv::putText(image, str_, org_, cv::FONT_HERSHEY_SIMPLEX,
                font_scale_, color_bgr_, 1, cv::LINE_AA);
  }

  /// Set point for which to display coordinates.
  void
  point(cv::Point const& pt)
  {
    str_ = (std::to_string(pt.x) + "," + std::to_string(pt.y));
    org_ = (pt + offset_);
  }

  /// Returns the point for which coordinates are displayed.
  cv::Point
  point() const
  {
    return org_;
  }

private:
  std::string str_;
  cv::Point   org_;
  cv::Scalar  color_bgr_;
  double      font_scale_;
  cv::Point   offset_;
};

/// @}
//---------------------------------------------------------------------------
} } // utl::opencv

#endif // UTL_OPENCV_COORDINATES_HPP
//===========================================================================//
