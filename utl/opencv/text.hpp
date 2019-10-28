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
/// @brief    Text drawing functions.
/// @author   Nathan Lucas
/// @date     2017-2018
//===========================================================================//
#ifndef UTL_OPENCV_TEXT_HPP
#define UTL_OPENCV_TEXT_HPP

#ifndef __cplusplus
#error must be compiled as C++
#endif

//-----------------------------------------------------------
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wall"

// OpenCV is released under 3-clause BSD License.
// https://opencv.org/license.html
#include <opencv2/core.hpp>     // cv::Mat, cv::Point, cv::Rect, cv::Scalar
#include <opencv2/imgproc.hpp>  // cv::getTextSize, cv::putText
/*
  Fonts in OpenCV
    https://codeyarns.com/2015/03/11/fonts-in-opencv/
*/
#pragma GCC diagnostic pop
//-----------------------------------------------------------

#include <algorithm>  // std::max
#include <cmath>      // std::round
#include <sstream>    // std::stringstream
#include <string>     // std::string, std::to_string
#include <vector>     // std::vector

namespace utl { namespace opencv {
//---------------------------------------------------------------------------
/// @addtogroup utl_opencv
/// @{

//-----------------------------------------------------------

/// Return the vertical distance in pixels from the font
/// baseline to the top of the highest ascending glyph.
inline unsigned
text_ascent_px(int face, double scale)
{
  int baseline = 0;
  cv::Size text_size = cv::getTextSize("Xy", face, scale, 1, &baseline);
  return text_size.height;
}

/// Return the vertical distance in pixels from the font
/// baseline to the bottom of the lowest descending glyph.
inline unsigned
text_descent_px(int face, double scale)
{
  int baseline = 0;
  cv::getTextSize("Xy", face, scale, 1, &baseline);
  return baseline;
}

/// Return the vertical distance in pixels from the top of the highest
/// ascending glyph to the bottom of the lowest descending glyph.
inline unsigned
text_height_px(int face, double scale)
{
  int baseline = 0;
  cv::Size text_size = cv::getTextSize("Xy", face, scale, 1, &baseline);
  return text_size.height + baseline;   // ascent + descent
}

/// @brief  Return line spacing in pixels.
///
/// Returns leading ("ledding"), the distance between the baselines
/// of successive lines of text.  The default value of the multiplier
/// `mult` results in a leading that is 120% of the font height,
/// a commonly recommended minimum spacing.
inline unsigned
text_line_spacing_px(int face, double scale, double mult = 1.2)
{
  return std::round(mult * (double)text_height_px(face, scale));
}

/// Returns the maximum width in pixels of the strings in `text`.
inline unsigned
text_max_width_px(std::vector<std::string> const& text,
                  int face, double scale)
{
  int baseline  = 0;
  int max_width = 0;
  if (!text.empty())
  {
    for (auto const& t : text)
    {
      if (!t.empty())
      {
        cv::Size sz = cv::getTextSize(t, face, scale, 1, &baseline);
        max_width = std::max(max_width, sz.width);
      }
    }
  }
  return max_width;
}

/// Returns the width in pixels of the string `text`.
inline unsigned
text_width_px(std::string const& text, int face, double scale)
{
  int baseline  = 0;
  if (text.empty())
  {
    return 0;
  }
  cv::Size sz = cv::getTextSize(text, face, scale, 1, &baseline);
  return sz.width;
}

//-----------------------------------------------------------

/// @brief  Render multiple lines of text in `image`.
///
/// Parses string `text` on newline delimiter ("`\n`")
/// and renders each line of text in the image.
inline void
draw_multitext(cv::Mat& image, std::string const& text,
    cv::Point origin, int font_face, double font_scale,
    cv::Scalar const& color_bgr, int thickness,
    unsigned line_spacing_px, int line_type = cv::LINE_AA)
{
  if (text.empty()) { return; }
  std::stringstream ss(text);
  std::string line;

  // Parse text string on newline delimiter
  while(std::getline(ss, line, '\n'))
  {
    origin = origin + cv::Point(0, line_spacing_px);
    if (line.empty())
    {
      // Replace each blank line with a space because
      // cv::putText can't handle empty strings
      line = " ";
    }
    // `origin` is the left-most end of the text baseline
    cv::putText(image, line, origin, font_face, font_scale,
                color_bgr, thickness, line_type);
  }
}

/// @brief  Render multiple lines of text in `image`.
///
/// Parses each string in `text` on newline delimiter ("`\n`")
/// and renders each line of text in the image.
inline void
draw_multitext(cv::Mat& image, std::vector<std::string> const& text,
    cv::Point origin, int font_face, double font_scale,
    cv::Scalar const& color_bgr, int thickness,
    unsigned line_spacing_px, int line_type = cv::LINE_AA)
{
  if (text.empty()) { return; }
  for (auto const& t : text)
  {
    draw_multitext(image, t, origin, font_face, font_scale,
                   color_bgr, thickness, line_spacing_px, line_type);
    origin = origin + cv::Point(0, line_spacing_px);
  }
}

//-----------------------------------------------------------

///// Draws rectangle coordinates and dimensions.
//inline void
//draw_rect_parameters(cv::Mat& image, cv::Rect const& rect,
//    cv::Scalar const& color_bgr, double font_scale = 0.4,
//    cv::Point const& xy_offset = {5, 15},
//    cv::Point const& wh_offset = {5, 30})
//{
//  std::string xy(std::to_string(rect.tl().x) +","+
//                 std::to_string(rect.tl().y));
//
//  std::string wh(std::to_string(rect.size().width) +"x"+
//                 std::to_string(rect.size().height));
//
//  auto xy_pt = (rect.tl() + xy_offset);
//  auto wh_pt = (rect.tl() + wh_offset);
//
//  cv::putText(image, xy, xy_px, cv::FONT_HERSHEY_SIMPLEX,
//              font_scale, color_bgr, 1, cv::LINE_AA);
//
//  cv::putText(image, wh, wh_pt, cv::FONT_HERSHEY_SIMPLEX,
//              font_scale, color_bgr, 1, cv::LINE_AA);
//}

//-----------------------------------------------------------

/// Text font properties and other typography info.
class TextRender
{
public:

  /// Create font properties object.
  ///
  /// @param  [in]  font        Font type.
  /// @param  [in]  scale       Font scale factor.
  /// @param  [in]  color_bgr   Color (blue, green, red).
  /// @param  [in]  thick       Line thickness.
  /// @param  [in]  linetype    Line type.
  /// @param  [in]  spacing     Line spacing multiplier.
  ///
  TextRender(int font, double scale, cv::Scalar const& color_bgr,
             int thick, int linetype = cv::LINE_AA, double spacing = 1.2)
  : color_bgr_(color_bgr)
  , font_(font)
  , linetype_(linetype)
  , scale_(scale)
  , spacing_mult_(spacing)
  , thick_(thick)
  {
    int baseline = 0;
    cv::Size sz = cv::getTextSize("Xy", font_, scale_, 1, &baseline);
    ascent_px_  = sz.height;
    descent_px_ = baseline;
    height_px_  = sz.height + baseline;
    spacing_px_ = std::round(spacing_mult_ * (double)height_px_);
  }

  // Accessors ----------------

  /// Vertical distance from the font baseline to the top-most point.
  unsigned ascent_px()  const { return ascent_px_; }

  /// Vertical distance from the font baseline to the bottom-most point.
  unsigned descent_px() const { return descent_px_; }

  /// Vertical distance between the font top-most and bottom-most points.
  unsigned height_px()  const { return height_px_; }

  /// Returns leading ("ledding"), the distance between the baselines
  /// of successive lines of text, as a multiplier of the font height.
  double spacing_mult() const { return spacing_mult_; }

  /// Returns leading ("ledding"), the distance between
  /// the baselines of successive lines of text, in pixels.
  unsigned spacing_px() const { return spacing_px_; }

  // Operations ---------------

  /// Render @a str in @a image, with the bottom-left
  /// corner of the text at point @a bl.
  void
  draw(cv::Mat& image, std::string const& str, cv::Point const& bl) const
  {
    cv::putText(image, str, bl, font_, scale_,
                color_bgr_, thick_, linetype_);
  }

  /// Render the string elements of @a vstr in @a image, with the
  /// bottom-left corner of the first line of text at point @a bl.
  void
  draw(cv::Mat& image, std::vector<std::string> const& vstr,
       cv::Point const& bl) const
  {
    auto origin = bl;
    utl::opencv::draw_multitext(image, vstr, origin, font_, scale_,
                                color_bgr_, thick_, spacing_px_, linetype_);
  }

  /// Returns the width in pixels @a str would be if rendered.
  unsigned
  width_px(std::string const& str) const
  {
    return utl::opencv::text_width_px(str, font_, scale_);
  }

  /// Returns the maximum width in pixels @a vstr
  /// would be if all lines of text were rendered.
  unsigned
  width_px(std::vector<std::string> const& vstr) const
  {
    return utl::opencv::text_max_width_px(vstr, font_, scale_);
  }

private:
  // Specified properties
  cv::Scalar  color_bgr_;     // color (blue, green, red)
  int         font_;          // font type
  int         linetype_;      // line type
  double      scale_;         // font scale factor
  double      spacing_mult_;  // line spacing multiplier
  int         thick_;         // text line thickness
  // Derived properties
  unsigned ascent_px_{};    // distance from baseline to top-most point
  unsigned descent_px_{};   // distance from baseline to bottom-most point
  unsigned height_px_{};    // distance from top-most to bottom-most point
  unsigned spacing_px_{};   // line spacing in pixels
};

//-----------------------------------------------------------

/// @}
//---------------------------------------------------------------------------
} } // utl::opencv

#endif // UTL_OPENCV_TEXT_HPP
//===========================================================================//
