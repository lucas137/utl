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
/// @brief    Window overlay panels.
/// @author   Nathan Lucas
/// @date     2018
//===========================================================================//
#ifndef UTL_OPENCV_PANEL_HPP
#define UTL_OPENCV_PANEL_HPP

#include <utl/opencv/text.hpp>    // utl::opencv::TextRender
#include <utl/string.hpp>         // utl::parse

//-----------------------------------------------------------
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wall"

// OpenCV is released under 3-clause BSD License.
// https://opencv.org/license.html
#include <opencv2/core.hpp>     // cv::FONT_*, cv::Mat, cv::Point,
                                // cv::Scalar, cv::Size
#include <opencv2/imgproc.hpp>  // cv::rectangle

#pragma GCC diagnostic pop
//-----------------------------------------------------------

#include <algorithm>  // std::max
#include <string>     // std::string
#include <vector>     // std::vector

namespace utl { namespace opencv {
//---------------------------------------------------------------------------
/// @addtogroup utl_opencv
/// @{

/// @brief Window overlay panel.
///
/// Width is automatically expanded as necessary to the fit the title text.
class Panel
{
public:

  /// @brief    Create a panel.
  /// @details  All colors are in BGR format (blue, green, red).
  ///
  /// @param  [in]  title_bgr   Title bar fill color.
  /// @param  [in]  font_face   Title font type.
  /// @param  [in]  font_scale  Title font scale factor.
  /// @param  [in]  font_bgr    Title color.
  /// @param  [in]  font_thick  Title line thickness.
  /// @param  [in]  body_bgr    Body background color.
  ///
  Panel(cv::Scalar const& title_bgr, int font_face, double font_scale,
    cv::Scalar const& font_bgr, int font_thick, cv::Scalar const& body_bgr);

  cv::Rect  body() const;                 ///< Location and size of body.
  cv::Point center() const;               ///< Get the center point.
  void      center(cv::Point const& pt);  ///< Position the center point.
  void      draw(cv::Mat& image) const;   ///< Render the panel in @a image.

  /// @brief    Panel location and size.
  /// @details  Returns a `cv::Rect` object, which provides direct access to
  /// `x`, `y`, `width`, and `height` values.  The returned object also has
  /// methods to access top-left corner, bottom-right corner, size, and area.
  cv::Rect
  rect() const;

  /// @brief    Resize to the minimum panel height.
  /// @details  Resizes to the overall minimum panel width.
  /// The panel location stays fixed with respect to the
  /// top-left corner.  See size() for details.
  inline void
  shrink_height();

  /// @brief    Resize to the minimum width.
  /// @details  Resizes to the minimum width necessary for the title text,
  /// subject to the overall minimum panel width.  The panel location stays
  /// fixed with respect to the top-left corner.  See size() for details.
  inline void
  shrink_width();

  /// @brief    Set size (width, height).
  /// @details  Resizing is subject to minimum dimensions.  The location
  /// of the top-left corner of the panel remains the same.  Callers are
  /// responsible for re-centering or other desired changes to location.
  /// The `center()` accessor can be called to save the center point before
  /// resizing.  The save point can then passed to the `center()` setter
  /// method to re-center the panel.
  void
  size(cv::Size const& sz);

  void  title(std::string const& str);    ///< Set title text.
  void  topleft(cv::Point const& pt);     ///< Position the top-left corner.

private:
  void fit_text_width();
  void update_height(int h);
  void update_width(int w);

  cv::Rect      panel_box_{};       // location and size
  cv::Size      panel_min_size_{};  // minimum panel dimensions

  cv::Rect      title_bar_{};       // location and size
  cv::Scalar    title_bar_color_;   // fill color
  cv::Point     title_org_;         // bottom-left corner of text
  std::string   title_str_{"X"};    // text string
  TextRender    title_text_;        // text renderer

  cv::Scalar    body_color_;        // fill color
  cv::Rect      body_rect_{};       // location and size

};

/// @}
//---------------------------------------------------------------------------
// Implementation

inline
Panel::Panel(cv::Scalar const& title_bgr, int font_face, double font_scale,
    cv::Scalar const& font_bgr, int font_thick, cv::Scalar const& body_bgr)
: title_bar_color_(title_bgr)
, title_text_(font_face, font_scale, font_bgr, font_thick)
, body_color_(body_bgr)
{
  // Top and bottom margins proportional to body line height
  title_bar_.height = ((2 * title_text_.spacing_px()) -
                       title_text_.height_px());
  title_bar_.height += 3;   // additional margin for border
  title_bar_.width  = (2 * title_bar_.height);

  // The panel and components (title bar and body) are all the same width
  panel_box_ = title_bar_;
  panel_box_.height += (2 * title_text_.spacing_px());  // initial height
  panel_min_size_ = panel_box_.size();

  // The body is positioned below the title bar,
  // and sized to fit within the panel height
  body_rect_ = panel_box_;                  // copy panel location and size
  body_rect_.y += title_bar_.height;        // shift down to below title bar
  body_rect_.height -= title_bar_.height;   // decrease height

  // The title text origin is the left-most end of the text baseline
  auto title_spacing = title_text_.spacing_px();
  auto offset = cv::Point(title_spacing / 2, title_text_.height_px() + 1);
  title_org_ = (panel_box_.tl() + offset);
}

inline cv::Rect
Panel::body() const { return body_rect_; }

inline cv::Point
Panel::center() const
{
  return { panel_box_.x + (panel_box_.width / 2),
           panel_box_.y + (panel_box_.height / 2) };
}

inline void
Panel::center(cv::Point const& pt)
{
  // Compute offset
  auto offset = (pt - center());
  // Shift components
  panel_box_ += offset;
  title_bar_ += offset;
  title_org_ += offset;
  body_rect_ += offset;
}

inline void
Panel::draw(cv::Mat& image) const
{
  // Panel background
  cv::rectangle(image, panel_box_, body_color_, CV_FILLED);
  // Title bar background and text
  cv::rectangle(image, title_bar_, title_bar_color_, CV_FILLED);
  title_text_.draw(image, title_str_, title_org_);
  // Borders
  cv::rectangle(image, title_bar_, {  32,  32,  32 }, 4);  // outer  / bottom
  cv::rectangle(image, title_bar_, { 240, 240, 240 }, 2);  // middle / middle
  cv::rectangle(image, title_bar_, { 160, 160, 160 }, 1);  // inner  / top
  cv::rectangle(image, panel_box_, {  32,  32,  32 }, 5);  // outter / bottom
  cv::rectangle(image, panel_box_, { 240, 240, 240 }, 3);  // middle / middle
  cv::rectangle(image, panel_box_, { 160, 160, 160 }, 2);  // inner  / top
}

inline cv::Rect
Panel::rect() const  { return panel_box_; }

inline void
Panel::shrink_height()  { update_height(panel_min_size_.height); }

inline void
Panel::shrink_width()  { update_width(panel_min_size_.width); }

inline void
Panel::size(cv::Size const& sz)
{
  update_width(sz.width);
  fit_text_width();
  update_height(sz.height);
}

inline void
Panel::title(std::string const& str)
{
  title_str_ = str;
  fit_text_width();
}

inline void
Panel::topleft(cv::Point const& pt)
{
  auto offset = (pt - panel_box_.tl());
  // Shift components
  panel_box_ += offset;
  title_bar_ += offset;
  title_org_ += offset;
  body_rect_ += offset;
}

//-----------------------------------------------------------
// private

// Increase panel width if necessary to fit title text
inline void
Panel::fit_text_width()
{
  // Get width of bounding rectangle around text
  int w = title_text_.width_px(title_str_);
  // Add left and right margins, each equal to
  // half the sum of line height and border width
  w += (title_text_.height_px() + 5);
  // Update component widths if necessary to fit title text
  if (w > panel_box_.width)
  {
    update_width(w);
  }
}

inline void
Panel::update_height(int h)
{
  // Apply minimum height
  int hh = std::max(h,  panel_min_size_.height);
  // Update component widths if necessary
  if (hh != panel_box_.height)
  {
    panel_box_.height = hh;
    body_rect_.height = (hh - title_bar_.height);
  }
}

inline void
Panel::update_width(int w)
{
  // Apply minimum width
  int ww = std::max(w,  panel_min_size_.width);
  // Update component widths if necessary
  if (ww != panel_box_.width)
  {
    panel_box_.width = ww;
    title_bar_.width = ww;
    body_rect_.width = ww;
  }
}

//---------------------------------------------------------------------------
/// @addtogroup utl_opencv
/// @{

/// @brief Window overlay panel for displaying text.
///
/// The height and width of the panel are automatically
/// expanded as necessary to the fit the title and body text.
class TextPanel
{
public:

  /// @brief  Create a text panel.
  ///
  /// @param  [in]  title_fill_bgr  Title bar fill color (BGR values).
  /// @param  [in]  title_font      Title bar text font type.
  /// @param  [in]  title_scale     Title bar text font scale factor.
  /// @param  [in]  title_text_bgr  Title bar text color (BGR values).
  /// @param  [in]  title_thick     Title bar text line thickness.
  /// @param  [in]  body_fill_bgr   Body fill color (BGR values).
  /// @param  [in]  body_text_bgr   Body text color (BGR values).
  /// @param  [in]  body_font       Body text font type.
  /// @param  [in]  body_scale      Body text font scale factor.
  /// @param  [in]  body_thick      Body text line thickness.
  ///
  TextPanel(
    cv::Scalar const& title_fill_bgr, int title_font, double title_scale,
    cv::Scalar const& title_text_bgr, int title_thick,
    cv::Scalar const& body_fill_bgr, int body_font, double body_scale,
    cv::Scalar const& body_text_bgr, int body_thick);

  cv::Rect  body() const;                 ///< Location and size of text body.
  cv::Point center() const;               ///< Get the center point.
  void      center(cv::Point const& pt);  ///< Position the center point.
  void      draw(cv::Mat& image) const;   ///< Render the panel in @a image.

  /// @brief    Panel location and size.
  /// @details  Returns a `cv::Rect` object, which provides direct access to
  /// `x`, `y`, `width`, and `height` values.  The returned object also has
  /// methods to access top-left corner, bottom-right corner, size, and area.
  cv::Rect
  rect() const;

  /// @brief    Resize to the minimum panel height.
  /// @details  Resizes to the overall minimum panel width.
  /// The panel location stays fixed with respect to the
  /// top-left corner.  See size() for details.
  inline void
  shrink_height();

  /// @brief    Resize to the minimum width.
  /// @details  Resizes to the minimum width necessary for the title text,
  /// subject to the overall minimum panel width.  The panel location stays
  /// fixed with respect to the top-left corner.  See size() for details.
  inline void
  shrink_width();

  /// @brief    Set size (width, height).
  /// @details  Resizing is subject to minimum dimensions.  The location
  /// of the top-left corner of the panel remains the same.  Callers are
  /// responsible for re-centering or other desired changes to location.
  /// The `center()` accessor can be called to save the center point before
  /// resizing.  The save point can then passed to the `center()` setter
  /// method to re-center the panel.
  void
  size(cv::Size const& sz);

  /// @brief    Set body text.
  /// @details  @a str is parsed into multiple lines on newline characters.
  void
  text(std::string const& str);

  /// @brief    Set body text.
  /// @details  Each element of @a vstr is parsed into
  ///           multiple lines on newline characters.
  void
  text(std::vector<std::string> const& vstr);

  cv::Point text_origin() const;                ///< Get text origin.
  void      text_origin(cv::Point const& org);  ///< Set text origin.
  void      title(std::string const& str);      ///< Set title text.
  void      topleft(cv::Point const& pt);       ///< Position top-left corner.

private:
  utl::opencv::Panel        panel_;             // basic panel
  cv::Size                  panel_min_size_{};  // minimum dimensions
  cv::Point                 text_origin_{};     // bottom-left corner of text
  utl::opencv::TextRender   text_render_;       // body text renderer
  std::vector<std::string>  text_vstr_{};       // parsed body text stings
};

/// @}
//---------------------------------------------------------------------------
// Implementation

inline
TextPanel::TextPanel(
    cv::Scalar const& title_fill_bgr, int title_font, double title_scale,
    cv::Scalar const& title_text_bgr, int title_thick,
    cv::Scalar const& body_fill_bgr, int body_font, double body_scale,
    cv::Scalar const& body_text_bgr, int body_thick)
: panel_(title_fill_bgr, title_font, title_scale,
         title_text_bgr, title_thick, body_fill_bgr)
, text_render_(body_font, body_scale, body_text_bgr, body_thick)
{
  // The body text origin is the left-most end of the text baseline
  auto body_spacing = text_render_.spacing_px();
  int space = (body_spacing - text_render_.height_px());
  auto offset = cv::Point(body_spacing / 2, space);
  text_origin_ = (panel_.body().tl() + offset);
  // Initial minimum panel size
  panel_min_size_ = panel_.rect().size();
}

inline cv::Rect
TextPanel::body() const { return panel_.body(); }

inline cv::Point
TextPanel::center() const  { return panel_.center(); }

inline void
TextPanel::center(cv::Point const& pt)
{
  auto offset = (pt - panel_.center());
  text_origin_ += offset;
  panel_.center(pt);
}

inline void
TextPanel::draw(cv::Mat& image) const
{
  // Render basic panel, including borders and title bar
  panel_.draw(image);
  // Render body text
  text_render_.draw(image, text_vstr_, text_origin_);
}

inline cv::Rect
TextPanel::rect() const  { return panel_.rect(); }

inline void
TextPanel::shrink_height()
{
  panel_.shrink_height();
  // Expensive hack?
  text(text_vstr_);
}

inline void
TextPanel::shrink_width()
{
  panel_.shrink_width();
  // Expensive hack?
  text(text_vstr_);
}

inline void
TextPanel::size(cv::Size const& sz)
{
  // Apply minimum dimensions, then request resizing
  int w = std::max(sz.width, panel_min_size_.width);
  int h = std::max(sz.height, panel_min_size_.height);
  panel_.size({w, h});
}

inline void
TextPanel::text(std::string const& str)
{
  std::vector<std::string> vstr = {str};
  text(vstr);
}

inline void
TextPanel::text(std::vector<std::string> const& vstr)
{
  if (vstr != text_vstr_)
  {
    // Remove all elements from `text_vstr_`,
    // leaving the container with a size of 0
    text_vstr_.clear();

    // Parse each element of `vstr` on newline characters
    // and insert each token at the end of `text_vstr_`
    for (auto const& str : vstr)
    {
      if (str.empty())
      {
        text_vstr_.push_back("");
        continue;
      }
      auto v = utl::parse(str, "\n");
      // Add one or more elements at the end of `text_vstr_`
      text_vstr_.insert(text_vstr_.end(), v.begin(), v.end());
    }
  }

  // Get panel dimensions
  auto panel_size = panel_.rect().size();
  auto body_size = panel_.body().size();

  // Compute minimum width to fit body text
  int w = text_render_.width_px(text_vstr_);
  w += text_render_.spacing_px();   // margin proportional to body line height

  // Add text offset
  int x_offset = (text_origin_.x - panel_.rect().x);
  if (x_offset > 0)
  {
    w += x_offset;
  }

  // Add left and right margins, each equal to
  // half the sum of line height and border width
  w += (text_render_.height_px() + 5);

  // Compute text height according to number of lines
  unsigned line_count = text_vstr_.size();
  int h = ((line_count + 1) * text_render_.spacing_px());

  // Add title height
  h += (panel_size.height - body_size.height);

  // Minimum panel size
  panel_min_size_ = cv::Size(w, h);

  // Expand the panel if necessary
  w = std::max(w, panel_size.width);
  h = std::max(h, panel_size.height);
  panel_.size({w, h});
}

inline cv::Point
TextPanel::text_origin() const
{
  return text_origin_;
}

inline void
TextPanel::text_origin(cv::Point const& org)
{
  text_origin_ = org;
}

inline void
TextPanel::title(std::string const& str)  { panel_.title(str); }

inline void
TextPanel::topleft(cv::Point const& pt)
{
  auto offset = (pt - panel_.rect().tl());
  text_origin_ += offset;
  panel_.topleft(pt);
}

//---------------------------------------------------------------------------
/// @addtogroup utl_opencv
/// @{

/// @brief Window overlay panel for displaying a color key.
///
/// The height and width of the panel are automatically
/// expanded as necessary to the fit the title and body.
class KeyPanel
{
public:

  /// @brief  Create a key panel.
  ///
  /// @param  [in]  title_fill_bgr  Title bar fill color (BGR values).
  /// @param  [in]  title_font      Title bar text font type.
  /// @param  [in]  title_scale     Title bar text font scale factor.
  /// @param  [in]  title_text_bgr  Title bar text color (BGR values).
  /// @param  [in]  title_thick     Title bar text line thickness.
  /// @param  [in]  body_fill_bgr   Body fill color (BGR values).
  /// @param  [in]  body_text_bgr   Body text color (BGR values).
  /// @param  [in]  body_font       Body text font type.
  /// @param  [in]  body_scale      Body text font scale factor.
  /// @param  [in]  body_thick      Body text line thickness.
  /// @param  [in]  title           Panel title.
  /// @param  [in]  colors          Key colors.
  /// @param  [in]  labels          Key labels.
  ///
  KeyPanel(
    cv::Scalar const& title_fill_bgr, int title_font, double title_scale,
    cv::Scalar const& title_text_bgr, int title_thick,
    cv::Scalar const& body_fill_bgr, int body_font, double body_scale,
    cv::Scalar const& body_text_bgr, int body_thick,
    std::string const& title,
    std::vector<cv::Scalar> const& colors,
    std::vector<std::string> const& labels);

  cv::Point center() const;                 ///< Get the center point.
  void      center(cv::Point const& pt);    ///< Position the center point.
  void      draw(cv::Mat& image) const;     ///< Render the panel in @a image.

  /// @brief    Panel location and size.
  /// @details  Returns a `cv::Rect` object, which provides direct access to
  /// `x`, `y`, `width`, and `height` values.  The returned object also has
  /// methods to access top-left corner, bottom-right corner, size, and area.
  cv::Rect
  rect() const;

  /// Position the top-left corner.
  void
  topleft(cv::Point const& pt);

private:
  std::vector<cv::Scalar>   colors_;
  utl::opencv::TextPanel    panel_;
  cv::Point                 swatch_origin_{};
  cv::Point                 swatch_size_{};
  unsigned                  swatch_spacing_px_{};
  //unsigned                text_px_{};
};

/// @}

//---------------------------------------------------------------------------
// Implementation

inline
KeyPanel::KeyPanel(
    cv::Scalar const& title_fill_bgr, int title_font, double title_scale,
    cv::Scalar const& title_text_bgr, int title_thick,
    cv::Scalar const& body_fill_bgr, int body_font, double body_scale,
    cv::Scalar const& body_text_bgr, int body_thick,
    std::string const& title,
    std::vector<cv::Scalar> const& colors,
    std::vector<std::string> const& labels)
: colors_(colors)
, panel_(title_fill_bgr, title_font, title_scale, title_text_bgr, title_thick,
         body_fill_bgr, body_font, body_scale, body_text_bgr, body_thick)
{
  panel_.title(title);
  panel_.text(labels);
  auto org = panel_.text_origin();

  // Color swatch vertical spacing, size, and origin
  swatch_spacing_px_ = text_line_spacing_px(body_font, body_scale);
  swatch_size_ = cv::Point(swatch_spacing_px_, swatch_spacing_px_ / 2);
  swatch_origin_ = (org - cv::Point(0, swatch_spacing_px_ / 2));

  // Text offset
  org += cv::Point(swatch_spacing_px_ + (swatch_spacing_px_ / 2), 0);
  panel_.text_origin(org);
}

inline cv::Point
KeyPanel::center() const { return panel_.center(); }

inline void
KeyPanel::center(cv::Point const& pt)
{
  auto offset = (pt - panel_.center());
  swatch_origin_ += offset;
  panel_.center(pt);
}

inline void
KeyPanel::draw(cv::Mat& image) const
{
  // Draw panel and text
  panel_.draw(image);

  auto org = swatch_origin_;

  // Draw a solid colored rectangle for each element in `colors_`.
  // The rectangles are arranged vertically and center aligned.
  // `spacing_px_` specifies the vertical spacing between rectangles in pixels
  // (i.e., the pixel distance between the same point on two rectangles).
  for (auto const& c : colors_)
  {
    org += cv::Point(0, swatch_spacing_px_);
    cv::rectangle(image, org, org + swatch_size_, c,  CV_FILLED);
  }
}

inline cv::Rect
KeyPanel::rect() const { return panel_.rect(); }

inline void
KeyPanel::topleft(cv::Point const& pt)
{
  auto offset = (pt - panel_.rect().tl());
  swatch_origin_ += offset;
  panel_.topleft(pt);
}

//---------------------------------------------------------------------------

} } // utl::opencv

#endif // UTL_OPENCV_PANEL_HPP
//===========================================================================//
