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
/// @brief    FLTK drawing function utility library.
/// @details  Header-only library providing wrapper classes and utilities
///           for Fast Light Toolkit (FLTK) library drawing functions.
///           This library is based in part on the work of the FLTK project
///           (http://www.fltk.org).
/// @author   Nathan Lucas
/// @date     2015
//===========================================================================//
#ifndef UTL_FLTK_HPP
#define UTL_FLTK_HPP

/*
  From https://www.fltk.org/COPYING.php:

  The FLTK library and included programs are provided under the terms of the
  GNU Library General Public License (LGPL) with the following exceptions:

    Modifications to the FLTK configure script, config header file, and
    makefiles by themselves to support a specific platform do not constitute
    a modified or derivative work.

    The authors do request that such modifications be contributed to the
    FLTK project - send all contributions to "fltk-bugs@fltk.org".

    Widgets that are subclassed from FLTK widgets do not constitute a
    derivative work.

    Static linking of applications and widgets to the FLTK library does
    not constitute a derivative work and does not require the author to
    provide source code for the application or widget, use the shared
    FLTK libraries, or link their applications or widgets against a
    user-supplied version of FLTK.

    If you link the application or widget to a modified version of FLTK,
    then the changes to FLTK must be provided under the terms of the LGPL
    in sections 1, 2, and 4.

    You do not have to provide a copy of the FLTK license with programs
    that are linked to the FLTK library, nor do you have to identify the
    FLTK license in your program or documentation as required by section
    6 of the LGPL.

    However, programs must still identify their use of FLTK. The following
    example statement can be included in user documentation to satisfy this
    requirement:

    [program/widget] is based in part on the work of the FLTK project
    (http://www.fltk.org).
*/

#ifndef __cplusplus
#error must be compiled as C++
#endif

/**
  @namespace  utl::fltk
  @brief    FLTK drawing function utility library.

  Header-only library providing wrapper classes and utilities
  for Fast Light Toolkit (FLTK) library drawing functions.

  The FLTK library is provided under the terms of the
  GNU Library General Public License (LGPL) with certain exceptions. @n
  https://www.fltk.org/COPYING.php
*/

/**
  @defgroup utl_fltk  fltk
  @brief    FLTK drawing function utility library.

  Header-only library providing wrapper classes and utilities
  for Fast Light Toolkit (FLTK) library drawing functions.

  The FLTK library is provided under the terms of the
  GNU Library General Public License (LGPL) with certain exceptions. @n
  https://www.fltk.org/COPYING.php
*/

#include <utl/fltk/fltk_circle.hpp>
#include <utl/fltk/fltk_grid.hpp>
#include <utl/fltk/fltk_line.hpp>
#include <utl/fltk/fltk_point.hpp>
#include <utl/fltk/fltk_text.hpp>


namespace utl { namespace fltk {

/// @addtogroup utl_fltk
/// @{

/// RGB color with component values in the range 0-255.
struct Color
{
  unsigned char red;    ///< Red.
  unsigned char green;  ///< Green.
  unsigned char blue;   ///< Blue.
};

/// Point coordinates.
struct Point
{
  int   x_px;   ///< Horizontal position.
  int   y_px;   ///< Vertical position.
  Color color;  ///< RGB color.
};

/// Line segment.
struct Line
{
  Point a;      ///< End point @a a.
  Point b;      ///< End point @a b.
  Color color;  ///< RGB color.
};

/// @}
// end group: utl_fltk

} } // utl::fltk

#endif // UTL_FLTK_HPP
//===========================================================================//
