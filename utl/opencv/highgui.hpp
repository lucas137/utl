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
/// @brief    Utilities related to the OpenCV highgui module.
/// @author   Nathan Lucas
/// @date     2016-2018
//===========================================================================//
#ifndef UTL_OPENCV_HIGHGUI_HPP
#define UTL_OPENCV_HIGHGUI_HPP

#ifndef __cplusplus
#error must be compiled as C++
#endif

//-----------------------------------------------------------
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wall"

// OpenCV is released under 3-clause BSD License.
// https://opencv.org/license.html
#include <opencv2/highgui.hpp>  // cv::EVENT_*

#pragma GCC diagnostic pop
//-----------------------------------------------------------

#include <string>   // std::string

namespace utl { namespace opencv {
//---------------------------------------------------------------------------
/// @addtogroup utl_opencv
/// @{

/// Special keys.
struct special_key
{
  static constexpr int enter       = 0x0000000D;
  static constexpr int escape      = 0x0000001B;
  static constexpr int page_up     = 0x00210000;
  static constexpr int page_down   = 0x00220000;
  static constexpr int end         = 0x00230000;
  static constexpr int home        = 0x00240000;
  static constexpr int arrow_left  = 0x00250000;
  static constexpr int arrow_up    = 0x00260000;
  static constexpr int arrow_right = 0x00270000;
  static constexpr int arrow_down  = 0x00280000;
  static constexpr int insert      = 0x002D0000;
  static constexpr int del         = 0x002E0000;
  static constexpr int F1          = 0x00700000;
  static constexpr int F2          = 0x00710000;
  static constexpr int F3          = 0x00720000;
  static constexpr int F4          = 0x00730000;
  static constexpr int F5          = 0x00740000;
  static constexpr int F6          = 0x00750000;
  static constexpr int F7          = 0x00760000;
  static constexpr int F8          = 0x00770000;
  static constexpr int F9          = 0x00780000;
  static constexpr int F10         = 0x00790000;
  static constexpr int F11         = 0x007A0000;
  static constexpr int F12         = 0x007B0000;


};

/// Returns abbreviated name of the specified special key.
inline std::string
special_key_str(int code)
{
  return (  ((code & 0x7FFFFF) == special_key::enter)       ? "Enter"
          : ((code & 0x7FFFFF) == special_key::escape)      ? "Esc"
          : ((code & 0x7FFFFF) == special_key::page_up)     ? "PgUp"
          : ((code & 0x7FFFFF) == special_key::page_down)   ? "PgDn"
          : ((code & 0x7FFFFF) == special_key::end)         ? "End"
          : ((code & 0x7FFFFF) == special_key::home)        ? "Home"
          : ((code & 0x7FFFFF) == special_key::arrow_left)  ? "ArLf"
          : ((code & 0x7FFFFF) == special_key::arrow_up)    ? "ArUp"
          : ((code & 0x7FFFFF) == special_key::arrow_right) ? "ArRt"
          : ((code & 0x7FFFFF) == special_key::arrow_down)  ? "ArDn"
          : ((code & 0x7FFFFF) == special_key::insert)      ? "Ins"
          : ((code & 0x7FFFFF) == special_key::del)         ? "Del"
          : ((code & 0x7FFFFF) == special_key::F1)  ? "F1"
          : ((code & 0x7FFFFF) == special_key::F2)  ? "F2"
          : ((code & 0x7FFFFF) == special_key::F3)  ? "F3"
          : ((code & 0x7FFFFF) == special_key::F4)  ? "F4"
          : ((code & 0x7FFFFF) == special_key::F5)  ? "F5"
          : ((code & 0x7FFFFF) == special_key::F6)  ? "F6"
          : ((code & 0x7FFFFF) == special_key::F7)  ? "F7"
          : ((code & 0x7FFFFF) == special_key::F8)  ? "F8"
          : ((code & 0x7FFFFF) == special_key::F9)  ? "F9"
          : ((code & 0x7FFFFF) == special_key::F10) ? "F10"
          : ((code & 0x7FFFFF) == special_key::F11) ? "F11"
          : ((code & 0x7FFFFF) == special_key::F12) ? "F12"
          : "unknown");
}

//-----------------------------------------------------------

/// Returns the name of the specified mouse event.
inline std::string
mouse_event_str(int code)
{
  return ( (code == cv::EVENT_MOUSEMOVE)     ? "mouse_move"
         : (code == cv::EVENT_LBUTTONDOWN)   ? "left_press"
         : (code == cv::EVENT_RBUTTONDOWN)   ? "right_press"
         : (code == cv::EVENT_MBUTTONDOWN)   ? "middle_press"
         : (code == cv::EVENT_LBUTTONUP)     ? "left_release"
         : (code == cv::EVENT_RBUTTONUP)     ? "right_release"
         : (code == cv::EVENT_MBUTTONUP)     ? "middle_release"
         : (code == cv::EVENT_LBUTTONDBLCLK) ? "left_doubleclick"
         : (code == cv::EVENT_RBUTTONDBLCLK) ? "right_doubleclick"
         : (code == cv::EVENT_MBUTTONDBLCLK) ? "middle_doubleclick"
         : (code == cv::EVENT_MOUSEWHEEL)    ? "scroll_vertical"
         : (code == cv::EVENT_MOUSEHWHEEL)   ? "scroll_horizontal"
         :                                     "unknown");
}

/// Returns the names of the specified mouse event flags.
inline std::string
mouse_flags_str(int code, std::string const& delim = "|")
{
  std::string str;
  if (code & cv::EVENT_FLAG_LBUTTON)
  {
    str += "left_button";
  }
  if (code & cv::EVENT_FLAG_RBUTTON)
  {
    if (!str.empty()) { str += delim; }
    str += "right_button";
  }
  if (code & cv::EVENT_FLAG_MBUTTON)
  {
    if (!str.empty()) { str += delim; }
    str += "middle_button";
  }
  if (code & cv::EVENT_FLAG_CTRLKEY)
  {
    if (!str.empty()) { str += delim; }
    str += "ctrl_key";
  }
  if (code & cv::EVENT_FLAG_SHIFTKEY)
  {
    if (!str.empty()) { str += delim; }
    str += "shift_key";
  }
  if (code & cv::EVENT_FLAG_ALTKEY)
  {
    if (!str.empty()) { str += delim; }
    str += "alt_key";
  }
  return str;
}

/// @}
//---------------------------------------------------------------------------
} } // utl::opencv

#endif // UTL_OPENCV_HIGHGUI_HPP
//===========================================================================//
