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
/// @brief    Draws a circle using FLTK.
/// @details  Circle is based in part on the work of the FLTK project
///           (http://www.fltk.org).
/// @author   Nathan Lucas
/// @version  0.2
/// @date     2015
//===========================================================================//
#ifndef UTL_FLTK_CIRCLE_HPP
#define UTL_FLTK_CIRCLE_HPP

#include <utl/color.hpp>    // utl::color

#include <FL/fl_draw.H>     // fl_arc, fl_color, fl_line_style, fl_pie

namespace utl { namespace fltk {

/// @addtogroup utl_fltk
/// @{

/// @brief  %Circle widget.
///
/// Coordinates and dimensions are in pixels. @n
///
/// Circle is based in part on the work of the FLTK project
/// (http://www.fltk.org).
///
class Circle
{
public:

  /// Construct circle.
  Circle(int x_px, int y_px, unsigned radius_px, unsigned line_width_px,
         color_rgb const& line_color, color_rgb const& fill_color)
  : x_(x_px - radius_px)
  , y_(y_px - radius_px)
  , d_(2 * radius_px)
  , lw_(line_width_px)
  , lc_(line_color)
  , fc_(fill_color)
  {}

  /// Default construct circle.
  Circle() = default;

  /// Draw filled circle.
  void draw_fill() const
  {
    //auto prev_color = fl_color();             // save current color
    fl_color(fc_.red, fc_.green, fc_.blue);   // set line and fill color
    fl_pie(x_, y_, d_, d_, 0.0, 360.0);       // draw a filled circle
    //fl_color(prev_color);                     // restore previous color
  }

  /// Draw circle line.
  void draw_line() const
  {
    //auto prev_color = fl_color();           // save current color
    fl_color(lc_.red, lc_.green, lc_.blue); // set line color
    fl_line_style(FL_SOLID, lw_);           // set line width
    fl_arc(x_, y_, d_, d_, 0.0, 360.0);     // draw a circle
    fl_line_style(0);                       // restore default line width (0)
    //fl_color(prev_color);                   // restore previous color
  }

  //-----------------------------------------------------------
  /// @name Center Point
  /// @{

  /// Set the center point coordinates.
  void center(int x_px, int y_px)
  {
    x(x_px);
    y(y_px);
  }

  /// Move the center point by the specified values.
  void translate(int x_px, int y_px)
  {
    x_ += x_px;
    y_ += y_px;
  }

  int  x_px() const   { return ( x_  + (d_ / 2) ); }  ///< Return X coordinate.
  void x_px(int val)  {   x_ = ( val - (d_ / 2) ); }  ///< Set X coordinate.
  int  y_px() const   { return ( y_  + (d_ / 2) ); }  ///< Return Y coordinate.
  void y_px(int val)  {   y_ = ( val - (d_ / 2) ); }  ///< Set Y coordinate.

  /// @}
  //-----------------------------------------------------------
  /// @name Attributes
  /// @{

  //-------------------------------------------------------
  // Radius is used to compute a fl_pie bounding box from
  // the center of the circle.  A public interface to
  // diameter was not provided in order to avoid rounding
  // results of diameter/2 for odd values of diameter.

  unsigned radius_px() const          { return (d_ / 2); }  ///< Return radius.
  void radius_px(unsigned r_px)       { d_ = (2 * r_px); }  ///< Set radius.
  void line_color(color_rgb const& c) { lc_ = c; }        ///< Set line color.
  void line_width(unsigned lw_px)     { lw_ = lw_px; }    ///< Set line width.
  void fill_color(color_rgb const& c) { fc_ = c; }        ///< Set fill color.

  /// @}
  //-----------------------------------------------------------

private:
  int       x_{0};      // bounding box X position in pixels
  int       y_{0};      // bounding box Y position in pixels
  unsigned  d_{16};     // diameter in pixels
  unsigned  lw_{0};     // line width

  color_rgb  lc_{0,0,0};         // line color
  color_rgb  fc_{127,127,127};   // fill color
};

/// @}
// end group: utl_fltk

} } // utl::fltk

#endif // UTL_FLTK_CIRCLE_HPP
//===========================================================================//
