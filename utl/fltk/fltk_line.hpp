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
/// @brief    Draw a line using FLTK.
/// @details  Line is based in part on the work of the FLTK project
///           (http://www.fltk.org).
/// @author   Nathan Lucas
/// @date     2015
//===========================================================================//
#ifndef UTL_FLTK_LINE_HPP
#define UTL_FLTK_LINE_HPP

#include <utl/color.hpp>    // utl::color

#include <FL/fl_draw.H>     // fl_color, fl_line, fl_line_style

namespace utl { namespace fltk {

/// @addtogroup utl_fltk
/// @{

/// @brief  Draws a line.
///
/// Coordinates and dimensions are in pixels. @n
///
/// Line is based in part on the work of the FLTK project
/// (http://www.fltk.org).
///
class Line
{
public:

  /** @brief  Construct line.
  @param  [in]  xa_px     X coordinate of point a.
  @param  [in]  ya_px     Y coordinate of point a.
  @param  [in]  xb_px     X coordinate of point b.
  @param  [in]  yb_px     Y coordinate of point b.
  @param  [in]  color     Line color.
  @param  [in]  width_px  Line width.
  */
  Line(int xa_px, int ya_px, int xb_px, int yb_px,
       color_rgb const& color, unsigned width_px = 0)
  : xa_(xa_px)
  , ya_(ya_px)
  , xb_(xb_px)
  , yb_(yb_px)
  , c_(color)
  , lw_(width_px)
  {}

  /// Draw line.
  void
  draw() const
  {
    //auto prev_color = fl_color();         // save current color
    fl_color(c_.red, c_.green, c_.blue);  // set line color
    fl_line_style(FL_SOLID, lw_);         // set line width
    fl_line(xa_, ya_, xb_, yb_);          // line between points a and b
    fl_line_style(0);                     // restore default line width (0)
    //fl_color(prev_color);                 // restore previous color
  }

  //-----------------------------------------------------------
  /// @name Position
  /// @{

  /// Return center position X coordinate.
  int x() const
  {
    return (xa_ < xb_) ? (xb_ - xa_) : (xa_ - xb_);
  }

  /// Return center position Y coordinate.
  int y() const
  {
    return (ya_ < yb_) ? (yb_ - ya_) : (ya_ - yb_);
  }

  int xa_px() const  { return xa_; } ///< Return X coordinate of point a.
  int ya_px() const  { return ya_; } ///< Return Y coordinate of point a.
  int xb_px() const  { return xb_; } ///< Return X coordinate of point b.
  int yb_px() const  { return yb_; } ///< Return Y coordinate of point b.

  void xa_px(int val)  { xa_ = val; }  ///< Set X coordinate of point a.
  void ya_px(int val)  { ya_ = val; }  ///< Set Y coordinate of point a.
  void xb_px(int val)  { xb_ = val; }  ///< Set X coordinate of point b.
  void yb_px(int val)  { yb_ = val; }  ///< Set Y coordinate of point b.

  /// Set coordinates of point a.
  void
  a_px(int x_px, int y_px)
  {
    xa_ = x_px;
    ya_ = y_px;
  }

  /// Set coordinates of point b.
  void
  b_px(int x_px, int y_px)
  {
    xb_ = x_px;
    yb_ = y_px;
  }

  /// Set coordinates of points a and b.
  void
  point_px(int xa_px, int ya_px, int xb_px, int yb_px)
  {
    xa_ = xa_px;
    ya_ = ya_px;
    xb_ = xb_px;
    yb_ = yb_px;
  }

  /// Translate the line.
  void
  translate(int x_px, int y_px)
  {
    x_a_ += x_px;
    y_a_ += y_px;
    x_b_ += x_px;
    y_b_ += y_px;
  }

  /// @}
  //-----------------------------------------------------------
  /// @name Attributes
  /// @{

  void color(color_rgb const& c)    { c_ = c; }       ///< Set line color.
  void line_width(unsigned lw_px)   { lw_ = lw_px; }  ///< Set line width.

  /// @}
  //-----------------------------------------------------------

private:
  int        x_a_;   // point A horizontal position in pixels
  int        y_a_;   // point A vertical position in pixels
  int        x_b_;   // point B horizontal position in pixels
  int        y_b_;   // point B vertical position in pixels
  color_rgb  c_;     // line color
  unsigned   lw_;    // line width in pixels
};

/// @}
// end group: utl_fltk

} } // utl::fltk

#endif // UTL_FLTK_LINE_HPP
//===========================================================================//
