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
/// @brief    Draw a rotated rectangle.
/// @author   Nathan Lucas
/// @date     2017
//===========================================================================//
#ifndef UTL_OPENCV_ROTATED_RECT_HPP
#define UTL_OPENCV_ROTATED_RECT_HPP

#ifndef __cplusplus
#error must be compiled as C++
#endif

//-----------------------------------------------------------
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wall"

// OpenCV is released under 3-clause BSD License.
// https://opencv.org/license.html
#include <opencv2/core.hpp>       // cv::LINE_8, cv::Mat, cv::Point,
                                  // cv::Point2f cv::RotatedRect,
                                  // cv::Scalar, cv::Size
#include <opencv2/imgproc.hpp>    // cv::fillConvexPoly, CV_FILLED, cv::line

#pragma GCC diagnostic pop
//-----------------------------------------------------------

#ifndef CV_FILLED
#define CV_FILLED -1
#endif

#include <cmath>      // std::fmod

namespace utl { namespace opencv {
//---------------------------------------------------------------------------
/// @addtogroup utl_opencv
/// @{

/// @brief  Draw a rotated rectangle.
/// @param  [in]  img       Image.
/// @param  [in]  pt        Center point.
/// @param  [in]  sz        Length and width.
/// @param  [in]  deg       Clockwise rotation in degrees.
/// @param  [in]  color     Line or fill color.
/// @param  [in]  thickness Line thickness.
/// @param  [in]  lineType  Type of line.
void rotatedRect(cv::Mat& img, cv::Point const& pt, cv::Size const& sz,
                 double deg, cv::Scalar const& color, int thickness=1,
                 int lineType=cv::LINE_8)
{
  // Create a rotated rectangle
  cv::RotatedRect rotated_rect(pt, sz, deg);

  // Simplified method for up-right (orthogonal) rectangles
  if (std::fmod(deg, 90) == 0)
  {
    // Draw minimal up-right bounding rectangle
    cv::rectangle(img, rotated_rect.boundingRect(),
                  color, thickness, lineType);
    return; // done
  }

  // Get vertices of the rectangle
  cv::Point2f vertices2f[4];
  rotated_rect.points(vertices2f);

  // Convert coordinates from float to int
  cv::Point vertices[4];
  for (unsigned i = 0; i != 4; ++i)
  {
    vertices[i] = vertices2f[i];
  }

  // Filled rectangle
  if (thickness == CV_FILLED)
  {
    // Fill a rotated rectangle with specified color
    cv::fillConvexPoly(img, vertices, 4, color, lineType);
  }
  else
  {
    cv::line(img, vertices[0], vertices[1], color, thickness, lineType);
    cv::line(img, vertices[1], vertices[2], color, thickness, lineType);
    cv::line(img, vertices[2], vertices[3], color, thickness, lineType);
    cv::line(img, vertices[3], vertices[0], color, thickness, lineType);
  }
}

/// @}
//---------------------------------------------------------------------------
} } // utl::opencv

#endif // UTL_OPENCV_ROTATED_RECT_HPP
//===========================================================================//
