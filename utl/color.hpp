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
/// @brief    Header-only library providing color utilities.
/// @author   Nathan Lucas
/// @date     2016
//===========================================================================//
#ifndef UTL_COLOR_HPP
#define UTL_COLOR_HPP

#ifndef __cplusplus
#error must be compiled as C++
#endif

#include <string>       // std::string
#include <ostream>      // std::ostream
//#include <sstream>      // std::ostringstream

/// @defgroup utl_color  color
/// @brief    Color utility library.

namespace utl {
//---------------------------------------------------------------------------
/// @addtogroup utl_color
/// @{

/// RGB color with component values in the range 0-255.
struct color_rgb
{
  unsigned char red;    ///< Red.
  unsigned char green;  ///< Green.
  unsigned char blue;   ///< Blue.
};

// Non-member functions -----------------------------------------------

/// @brief  Insert into output stream.
/// @relates  utl::color
///
/// @par Output Stream
///
///     c.red,c.green,c.blue
///
inline std::ostream&
operator<<(std::ostream& os, color_rgb const& c)
{
  return os << static_cast<unsigned>(c.red)   << ','
            << static_cast<unsigned>(c.green) << ','
            << static_cast<unsigned>(c.blue);
}

/// @brief  Return a composite color value.
/// @relates  utl::color
///
/// The composite value is computed:
/// ```
/// (c.red << 24) | (c.green << 16) | (c.blue << 8)
/// ```
inline unsigned
color_value(color_rgb const& c)
{
  return ((c.red << 24) | (c.green << 16) | (c.blue << 8));
}

///// @brief  Return a string containing comma separated values.
///// @relates  utl::color
/////
///// @par CSV Format
///// The returned string contains a row of color component values.
///// ```
///// c.red,c.green,c.blue
///// ```
//inline std::string
//csv(color const& c)
//{
//  std::ostringstream oss;
//  oss << c;
//  return oss.str();
//}

/// @}
//---------------------------------------------------------------------------
} // utl

#endif // UTL_COLOR_HPP
//===========================================================================//
