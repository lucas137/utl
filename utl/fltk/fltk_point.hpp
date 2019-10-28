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
/// @brief    Draws a point using FLTK.
/// @details  Point is based in part on the work of the FLTK project
///           (http://www.fltk.org).
/// @author   Nathan Lucas
/// @version  0.1
/// @date     2015
//===========================================================================//
#ifndef UTL_FLTK_POINT_HPP
#define UTL_FLTK_POINT_HPP

#include <utl/color.hpp>    // utl::color
#include <FL/fl_draw.H>     // fl_point, fl_color

namespace utl { namespace fltk {

/// @addtogroup utl_fltk
/// @{

/// @brief  Draws a point.
///
/// All coordinates and dimensions are in pixels.@n
///
/// Point is based in part on the work of the FLTK project
/// (http://www.fltk.org).
///
class Point
{
public:
  //-----------------------------------------------------------

  /// Construct a point.
  Point(int x_px, int y_px, color_rgb const& c)
  : x_(x_px)
  , y_(y_px)
  , c_(c)
  {}

  /// Draw point.
  void
  draw() const
  {
    //auto prev_color = fl_color();         // save current color
    fl_color(c_.red, c_.green, c_.blue);  // set color
    fl_point(x_px, y_px);                 // draw a point
    //fl_color(prev_color);                 // restore previous color
  }

  //-----------------------------------------------------------
  /// @name Position
  /// @{

  /// Set coordinates.
  void
  center(int x_px, int y_px)
  {
    x_ = x_px;
    y_ = y_px;
  }

  /// Translate by the specified values.
  void
  translate(int x_px, int y_px)
  {
    x_ += x_px;
    y_ += y_px;
  }

  int  x_px() const     { return x_; }    ///< Return X coordinate.
  void x_px(int val)    { x_ = val; }     ///< Set X coordinate.
  int  y_px() const     { return y_; }    ///< Return Y coordinate.
  void y_px(int val)    { y_ = val; }     ///< Set Y coordinate.

  /// @}
  //-----------------------------------------------------------
  /// @name Attributes
  /// @{

  color_rgb color() const           { return c_; }  ///< Return color.
  void color(color_rgb const& c)    { c_ = c; }     ///< Set color.

  /// @}
  //-----------------------------------------------------------

private:
  int        x_;   // horizontal position in pixels
  int        y_;   // vertical position in pixels
  color_rgb  c_;   // point color
};

/// @}
// end group: utl_fltk

} } // utl::fltk

#endif // UTL_FLTK_POINT_HPP
//===========================================================================//
