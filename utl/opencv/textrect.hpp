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
/// @brief    Drawable solid rectangle with centered text.
/// @author   Nathan Lucas
/// @date     2017-2018
//===========================================================================//
#ifndef UTL_OPENCV_TEXTRECT_HPP
#define UTL_OPENCV_TEXTRECT_HPP

//-----------------------------------------------------------
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wall"

// OpenCV is released under 3-clause BSD License.
// https://opencv.org/license.html
#include <opencv2/core.hpp>       // cv::LINE_AA, cv::Mat, cv::Point, cv::Rect
                                  // cv::Scalar, cv::Size, cv::String
#include <opencv2/imgproc.hpp>    // cv::putText, cv::rectangle, CV_FILLED

#pragma GCC diagnostic pop
//-----------------------------------------------------------

namespace utl { namespace opencv {
//---------------------------------------------------------------------------
/// @addtogroup utl_opencv
/// @{

/// Drawable solid rectangle with centered text.
class TextRect
{
public:
  /// @brief  Creates a drawable solid rectangle with centered text.
  /// @param  [in]  rect        Background location and size.
  /// @param  [in]  rect_color  Background color (BGR format).
  /// @param  [in]  text        Text to draw on background.
  /// @param  [in]  text_color  Text color (BGR format).
  /// @param  [in]  text_font   Text font type.
  /// @param  [in]  text_scale  Text font scale factor.
  /// @param  [in]  text_thick  Text line thickness.
  ///
  TextRect(cv::Rect   const& rect, cv::Scalar const& rect_color,
           cv::String const& text, cv::Scalar const& text_color,
           int text_font = cv::FONT_HERSHEY_SIMPLEX,
           double text_scale = 0.45, int text_thick = 1);

  void draw(cv::Mat& image) const;          ///< Draws the rectangle and text.
  void rect_color(cv::Scalar const& bgr);   ///< Sets the background color.
  void text_str(cv::String const& text);    ///< Sets the text string.
  void text_color(cv::Scalar const& bgr);   ///< Sets the text color.

private:
  cv::Rect    rect_;            // background rectangle
  cv::Scalar  rect_color_;      // background color (BGR format)
  cv::String  text_{};          // text drawn on background
  cv::Point   text_origin_{};   // text location
  cv::Scalar  text_color_;      // text color (BGR format)
  int         text_font_;       // font face
  double      text_scale_;      // font scale factor
  int         text_thick_;      // text line thickness
};

/// @}
//-----------------------------------------------------------
/// @}
//---------------------------------------------------------------------------
// Implementation

TextRect::TextRect(cv::Rect   const& rect, cv::Scalar const& rect_color,
                   cv::String const& text, cv::Scalar const& text_color,
                   int text_font, double text_scale, int text_thick)
: rect_(rect)
, rect_color_(rect_color)
, text_color_(text_color)
, text_font_(text_font)
, text_scale_(text_scale)
, text_thick_(text_thick)
{
  text_str(text);
}

void
TextRect::draw(cv::Mat& image) const
{
  cv::rectangle(image, rect_, rect_color_, CV_FILLED);
  cv::putText(image, text_, text_origin_, text_font_, text_scale_,
              text_color_, text_thick_, cv::LINE_AA);
}

void
TextRect::rect_color(cv::Scalar const& bgr)
{
  rect_color_ = bgr;
}

void
TextRect::text_str(cv::String const& text)
{
  text_ = text;

  // Compute the origin point to center text in the rectangle
  int  baseline  = 0;
  auto text_size = cv::getTextSize(text_, text_font_, text_scale_,
                                   text_thick_, &baseline);
  //baseline += text_thick_;  // unused
  text_origin_ = cv::Point(
    rect_.x + ((rect_.width  - text_size.width) / 2),
    rect_.y + ((rect_.height + text_size.height - text_thick_) / 2));
}

void
TextRect::text_color(cv::Scalar const& bgr)
{
  text_color_ = bgr;
}

//---------------------------------------------------------------------------
} } // utl::opencv

#endif // UTL_OPENCV_TEXTRECT_HPP
//===========================================================================//
