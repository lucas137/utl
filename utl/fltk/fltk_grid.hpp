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
/// @brief    Draw a grid using FLTK.
/// @details  Grid is based in part on the work of the FLTK project
///           (http://www.fltk.org).
/// @author   Nathan Lucas
/// @date     2015
//===========================================================================//
#ifndef UTL_FLTK_GRID_HPP
#define UTL_FLTK_GRID_HPP

#include <utl/color.hpp>    // utl::color

#include <FL/fl_draw.H>     // fl_color, fl_line, fl_line_style

namespace utl { namespace fltk {

/// @addtogroup utl_fltk
/// @{

/// @brief  Draws a two-dimensional grid.
///
/// Grid is based in part on the work of the FLTK project
/// (http://www.fltk.org).
///
class Grid
{
public:

  /** @brief   Construct a grid with evenly spaced lines.
  @param  [in]  x_px    Horizontal origin in pixels.
  @param  [in]  y_px    Vertical origin in pixels.
  @param  [in]  w_px    Total grid width in pixels.
  @param  [in]  h_px    Total grid height in pixels.
  @param  [in]  dx_px   Horizontal grid spacing in pixels.
  @param  [in]  dy_px   Vertical grid spacing in pixels.
  @param  [in]  c       Line color.
  @param  [in]  lw_px   Line width in pixels.
  */
  Grid(unsigned x_px, unsigned y_px, unsigned w_px, unsigned h_px,
       unsigned dx_px, unsigned dy_px,
       color_rgb const& c, unsigned lw_px = 0)
  : x_min_(x_px)
  , y_min_(y_px)
  , x_max_(x_px + w_px)
  , y_max_(y_px + h_px)
  , x_grid_(dx_px)
  , y_grid_(dy_px)
  , color_(c)
  , line_w_(lw_px)
  {}

  /// Draw grid.
  void
  draw() const
  {
    //auto prev_color = fl_color();                     // save current color
    fl_color(color_.red, color_.green, color_.blue);  // set line color
    fl_line_style(FL_SOLID, line_w_);                 // set line width
    for (unsigned x = x_min_; x <= x_max_; x += x_grid_)
    {
      fl_line(x, y_min_, x, y_max_);      // draw vertical line
    }
    for (unsigned y = y_min_; y <= y_max_; y += y_grid_)
    {
      fl_line(x_min_, y, x_max_, y);      // draw horizontal line
    }
    fl_line_style(0);           // restore default line width (0)
    //fl_color(prev_color);       // restore previous color
  }

  /// Set grid color.
  void
  color_rgb(color_rgb const& c)
  {
    color_ = c;
  }

  /// Set line width in pixels.
  void
  line_width(unsigned lw_px)
  {
    lw_ = lw_px;
  }

private:
  unsigned    x_min_;     // grid origin in pixels
  unsigned    y_min_;
  unsigned    x_max_;     // grid maximum in pixels
  unsigned    y_max_;
  unsigned    x_grid_;    // grid line spacing in pixels
  unsigned    y_grid_;
  color_rgb   color_;     // line color
  unsigned    line_w_;    // line width in pixels
};

/// @}
// end group: utl_fltk

} } // utl::fltk

#endif // UTL_FLTK_GRID_HPP
//===========================================================================//
