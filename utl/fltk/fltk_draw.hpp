/*
Licensed under the MIT License <http://opensource.org/licenses/MIT>

Copyright 2016 Nathan Lucas <nathan.lucas@wayne.edu>

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
/// @brief    Drawing functions.
/// @details  These functions are based in part on the work of the FLTK project
///           (http://www.fltk.org).
/// @author   Nathan Lucas
/// @date     2016
//===========================================================================//
#ifndef UTL_FLTK_DRAW_HPP
#define UTL_FLTK_DRAW_HPP

#include <utl/color.hpp>    // utl::color

#include <FL/Fl.H>          // FLTK GUI libraries
#include <FL/fl_draw.H>

namespace utl { namespace fltk {

/// @addtogroup utl_fltk
/// @{

  //-----------------------------------------------------------
  /// @brief  %Circle drawing functions.
  ///
  /// These functions are based in part on the work of the FLTK project
  /// (http://www.fltk.org).
  ///
  namespace circle {

  /// @brief  Draw a circle.
  /// @tparam X         Center point horizontal coordinate.
  /// @tparam Y         Center point vertical coordinate.
  /// @tparam Radius    Arc radius.
  /// @tparam Width     Line width.
  /// @param  color     Fill color.
  ///
  /// Coordinates and dimensions are in pixels.
  /// Angles are in degrees counter-clockwise from 3 o'clock.
  ///
  template<int X, int Y, unsigned Radius, unsigned Width = 0>
  inline void
  draw_circle(color_rgb const& color)
  {
    // Set color and set line width
    fl_color(color.red, color.green, color.blue);
    fl_line_style(FL_SOLID, Width);

    // Draw circle
    fl_arc(X - Radius, Y - Radius, 2 * Radius, 2 * Radius, 0.0, 360.0);

    // Restore default line width (0)
    fl_line_style(0);
  }

  /// @brief  Draw a circle.
  /// @tparam Radius    Arc radius.
  /// @tparam Width     Line width.
  /// @param  x         Center point horizontal coordinate.
  /// @param  y         Center point vertical coordinate.
  /// @param  color     Fill color.
  ///
  /// Coordinates and dimensions are in pixels.
  /// Angles are in degrees counter-clockwise from 3 o'clock.
  ///
  template<unsigned Radius, unsigned Width = 0>
  inline void
  draw_circle(int x, int y, color_rgb const& color)
  {
    // Set color and set line width
    fl_color(color.red, color.green, color.blue);
    fl_line_style(FL_SOLID, Width);

    // Draw circle
    fl_arc(x - Radius, y - Radius, 2 * Radius, 2 * Radius, 0.0, 360.0);

    // Restore default line width (0)
    fl_line_style(0);
  }

  /// @brief  Draw a filled circle.
  /// @tparam X         Center point horizontal coordinate.
  /// @tparam Y         Center point vertical coordinate.
  /// @tparam Radius    Arc radius.
  /// @param  color     Fill color.
  ///
  /// Coordinates and dimensions are in pixels.
  /// Angles are in degrees counter-clockwise from 3 o'clock.
  ///
  template<int X, int Y, unsigned Radius>
  inline void
  draw_disk(color_rgb const& color)
  {
    // Set color and draw filled circle
    fl_color(color.red, color.green, color.blue);
    fl_pie(X - Radius, Y - Radius, 2 * Radius, 2 * Radius, 0.0, 360.0);
  }

  /// @brief  Draw a filled circle.
  /// @tparam Radius    Arc radius.
  /// @param  x         Center point horizontal coordinate.
  /// @param  y         Center point vertical coordinate.
  /// @param  color     Fill color.
  ///
  /// Coordinates and dimensions are in pixels.
  /// Angles are in degrees counter-clockwise from 3 o'clock.
  ///
  template<unsigned Radius>
  inline void
  draw_disk(int x, int y, color_rgb const& color)
  {
    // Set color and draw filled circle
    fl_color(color.red, color.green, color.blue);
    fl_pie(x - Radius, y - Radius, 2 * Radius, 2 * Radius, 0.0, 360.0);
  }

  /// @brief  Draw a circular sector.
  /// @tparam X         Center point horizontal coordinate.
  /// @tparam Y         Center point vertical coordinate.
  /// @tparam Radius    Arc radius.
  /// @tparam BeginDeg  Arc start angle.
  /// @tparam EndDeg    Arc end angle.
  /// @param  color     Fill color.
  ///
  /// Coordinates and dimensions in pixels.
  /// Angles in degrees counter-clockwise from 3 o'clock.
  ///
  template<int X, int Y, unsigned Radius, int BeginDeg, int EndDeg>
  inline void
  draw_sector(color_rgb const& color)
  {
    // Set color and draw filled circular sector
    fl_color(color.red, color.green, color.blue);
    fl_pie(X - Radius, Y - Radius, 2 * Radius, 2 * Radius, BeginDeg, EndDeg);
  }

  /// @brief  Draw a circular sector.
  /// @tparam Radius    Arc radius.
  /// @tparam BeginDeg  Arc start angle.
  /// @tparam EndDeg    Arc end angle.
  /// @param  x         Center point horizontal coordinate.
  /// @param  y         Center point vertical coordinate.
  /// @param  color     Fill color.
  ///
  /// Coordinates and dimensions in pixels.
  /// Angles in degrees counter-clockwise from 3 o'clock.
  ///
  template<unsigned Radius, int BeginDeg, int EndDeg>
  inline void
  draw_sector(int x, int y, color_rgb const& color)
  {
    // Set color and draw filled circular sector
    fl_color(color.red, color.green, color.blue);
    fl_pie(x - Radius, y - Radius, 2 * Radius, 2 * Radius, BeginDeg, EndDeg);
  }

  } // circle
  //-----------------------------------------------------------
  /// @brief  %Line drawing functions.
  ///
  /// These functions are based in part on the work of the FLTK project
  /// (http://www.fltk.org).
  ///
  namespace line {

  /// @brief  Draw a line.
  /// @tparam X             Start point horizontal coordinate.
  /// @tparam Y             Start point vertical coordinate.
  /// @tparam Width         Line width.
  /// @param  [in]  x_px    End point horizontal coordinate.
  /// @param  [in]  y_px    End point vertical coordinate.
  /// @param  [in]  color   Line color.
  ///
  /// Coordinates and dimensions in pixels.
  ///
  template<int X, int Y, unsigned Width>
  inline void
  draw_line(int x_px, int y_px, color_rgb const& color)
  {
    fl_color(color.red, color.green, color.blue); // set color
    fl_line_style(FL_SOLID, Width);               // set line width
    fl_line(X, Y, x_px, y_px);                    // line between points
    fl_line_style(0);                       // restore default line width
  }

  /// @brief  Draw a line.
  /// @tparam Width         Line width.
  /// @param  [in]  ax_px   X coordinate of point a.
  /// @param  [in]  ay_px   Y coordinate of point a.
  /// @param  [in]  bx_px   X coordinate of point b.
  /// @param  [in]  by_px   Y coordinate of point b.
  /// @param  [in]  color   Line color.
  ///
  /// Coordinates and dimensions in pixels.
  ///
  template<unsigned Width>
  inline void
  draw_line(int ax_px, int ay_px, int bx_px, int by_px, color_rgb const& color)
  {
    fl_color(color.red, color.green, color.blue);   // set color
    fl_line_style(FL_SOLID, Width);                 // set line width
    fl_line(ax_px, ay_px, bx_px, by_px);            // line between points
    fl_line_style(0);                       // restore default line width
  }

  } // line
  //-----------------------------------------------------------
  /// @brief  %Point drawing functions.
  ///
  /// These functions are based in part on the work of the FLTK project
  /// (http://www.fltk.org).
  ///
  namespace point {

  /// @brief  Draw a point.
  /// @tparam X         Horizontal coordinate.
  /// @tparam Y         Vertical coordinate.
  /// @param  color     Color.
  ///
  /// Coordinates in pixels.
  ///
  template<int X, int Y>
  inline void
  draw_point(color_rgb const& color)
  {
    // Set color and draw point
    fl_color(color.red, color.green, color.blue);
    fl_point(X, Y);
  }

  } // point
  //-----------------------------------------------------------

/// @}
// end group: utl_fltk

} } // utl::fltk

#endif // UTL_FLTK_DRAW_HPP
//===========================================================================//
