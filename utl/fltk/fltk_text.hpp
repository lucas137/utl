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
/// @brief    Draw text using FLTK.
/// @details  Text is based in part on the work of the FLTK project
///           (http://www.fltk.org).
/// @author   Nathan Lucas
/// @version  0.1
/// @date     2015
//===========================================================================//
#ifndef UTL_FLTK_TEXT_HPP
#define UTL_FLTK_TEXT_HPP

#include <FL/Fl.H>    // FLTK library

#include <string>     // std::string

namespace utl { namespace fltk {

/// @addtogroup utl_fltk
/// @{


/// @brief  Horizontal alignment.
///
enum class AlignX
{
  LEFT,     ///< Align horizontally to the left.
  CENTER,   ///< Align horizontally in the center.
  RIGHT,    ///< Align horizontally to the right.
};

/// @brief  Vertical alignment.
///
enum class AlignY
{
  TOP,      ///< Align vertically to the top.
  MIDDLE,   ///< Align vertically in the middle.
  BOTTOM,   ///< Align vertically to the bottom.
};

/// @brief  Draws text.@n
///
/// Text is based in part on the work of the FLTK project
/// (http://www.fltk.org).
///
class Text
{
public:

  /** @brief  Creates a left-aligned text object for drawing.
  @param  [in]  str         String to draw on screen.
  @param  [in]  x_px        Horizontal position of text in pixels.
  @param  [in]  y_px        Vertical position of text in pixels.
  @param  [in]  font_face   Text font number
  @param  [in]  font_size   Font size in pixels
  @param  [in]  bold        Flag to make font bold
  @param  [in]  italic      Flag to make font italic
  */ /*inline*/
  Text(std::string const& str, int x_px, int y_px, Fl_Font font_face,
       int font_size, bool bold=false, bool italic=false);

  /** @brief  Creates a text object for drawing with specified alignment.
  @param  [in]  str         String to draw on screen.
  @param  [in]  x_px        Horizontal position of text in pixels.
  @param  [in]  y_px        Vertical position of text in pixels.
  @param  [in]  font_face   Text font number
  @param  [in]  font_size   Font size in pixels
  @param  [in]  align       Text alignment
  @param  [in]  bold        Flag to make font bold
  @param  [in]  italic      Flag to make font italic
  */ /*inline*/
  Text(std::string const& str, int x_px, int y_px, Fl_Font font_face,
       int font_size, AlignX align, bool bold=false, bool italic=false);

  /// @brief Draws the text.
  /*inline*/
  void
  draw() const;

  /// @brief  Sets the text string.
  /// @param  [in]  str
  /*inline*/
  void
  set(std::string const& str);

private:

  /*inline*/ int width();    // get width of text string

  std::string str_;   // string to draw on screen
  int         x_;     // horizontal position of aligned text
  int         xp_;    // horizontal position, beginning of text
  int         y_;     // vertical position of text

  Fl_Font font_face_;   // FLTK font number
  int     font_size_;   // font size in pixels
  AlignX  align_;       // text alignment

};


/// @}
// end group: utl_fltk

} } // utl::fltk


//===========================================================================//
// Implementation

#include <FL/fl_draw.H>

namespace utl { namespace fltk {


inline
Text::Text(std::string const& str, int x_px, int y_px, Fl_Font font_face,
           int font_size, bool bold, bool italic)
: str_("")
, x_(x_px)
, xp_(x_px)
, y_(y_px)
, font_face_(font_face + (bold ? FL_BOLD : 0) + (italic ? FL_ITALIC : 0))
, font_size_(font_size)
, align_(AlignX::LEFT)
{
  set(str);
}

inline
Text::Text(std::string const& str, int x_px, int y_px, Fl_Font font_face,
           int font_size, AlignX align, bool bold, bool italic)
: str_("")
, x_(x_px)
, xp_(x_px)
, y_(y_px)
, font_face_(font_face + (bold ? FL_BOLD : 0) + (italic ? FL_ITALIC : 0))
, font_size_(font_size)
, align_(align)
{
  set(str);
}

inline void
Text::draw() const
{
  fl_font(font_face_, font_size_);
  fl_draw(str_.c_str(), xp_, y_);
}

inline void
Text::set(std::string const& str)
{
  str_ = str;
  switch (align_)
  {
    case AlignX::CENTER:
    {
      // Determine horizontal position of the
      // beginning of the text to center-align
      xp_ = (x_ - (width() / 2));
      break;
    }
    case AlignX::LEFT:
      // Do nothing
      break;
    case AlignX::RIGHT:
    {
      // Determine horizontal position of the
      // beginning of the text to right-align
      xp_ = (x_ - (width() / 2));
      break;
    }
    default:
      break;
  }
}


// private ------------------------------------------------------------------

inline int
Text::width()
{
  // Offset of the first "colored in" pixel
  // of the string, from the draw origin
  int dx = 0;
  int dy = 0;
  // Dimensions of the bounding box around the text
  int w = 0;
  int h = 0;
  // Set text font prior to getting dimensions
  fl_font(font_face_, font_size_);
  // Determine the minimum pixel dimensions of the string
  fl_text_extents(str_.c_str(), dx, dy, w, h);
  // Return text width in pixels
  return w;
}


} } // utl::fltk

#endif // UTL_FLTK_TEXT_HPP
//===========================================================================//
