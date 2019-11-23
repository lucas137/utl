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
/// @brief    Popup window.
/// @author   Nathan Lucas
/// @date     2017
//===========================================================================//
#ifndef UTL_OPENCV_POPUP_HPP
#define UTL_OPENCV_POPUP_HPP

//-----------------------------------------------------------
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wall"

// OpenCV is released under 3-clause BSD License.
// https://opencv.org/license.html

#include <opencv2/core.hpp>     // cv::Mat, cv::Point, cv::Scalar
#include <opencv2/highgui.hpp>  // cv::imshow, cv::namedWindow, cv::moveWindow
#include <opencv2/imgproc.hpp>  // cv::LINE_AA, cv::putText

#pragma GCC diagnostic pop
//-----------------------------------------------------------

#include <string>     // std::string

namespace utl { namespace opencv {
//---------------------------------------------------------------------------
/// @addtogroup utl_opencv
/// @{
//-----------------------------------------------------------
/// @name   Window
/// @{

/// Popup types.
enum class PopupType
{
  error,      ///< Critical issue.
  message,    ///< Informational.
  warning,    ///< Non-critical issue.
};

/// Displays a popup window on the screen.
/*inline*/
bool
popup(utl::opencv::PopupType const& type,
      std::string const& name, cv::Point const& center,
      std::string const& text, std::string const& more = "");

/// @}
//-----------------------------------------------------------
/// @}
//---------------------------------------------------------------------------
// Implementation

namespace detail {  //---------------------------------------

// Window background
namespace background {
  cv::Scalar const    color_bgr = { 240, 240, 240 };
  constexpr unsigned  width     = 400;
  constexpr unsigned  height    = 100;
}

// Normal font
namespace font {
  constexpr int     face      = cv::FONT_HERSHEY_SIMPLEX;
  constexpr double  scale     = 0.45;
  cv::Scalar const  color_bgr = { 0, 0, 0 };
  constexpr int     thickness = 1;
}

// Label font
namespace label_font {
  constexpr int     face      = cv::FONT_HERSHEY_DUPLEX;
  constexpr double  scale     = 0.45;
  constexpr int     thickness = 1;
}

// Label colors
namespace label_color {
  cv::Scalar const  error_bgr   = { 0, 0, 224 };
  cv::Scalar const  message_bgr = { 96, 96, 96 };
  cv::Scalar const  warning_bgr = { 0, 128, 224 };
}

} // detail -------------------------------------------------

inline bool
popup(utl::opencv::PopupType const& type,
      std::string const& name, cv::Point const& center,
      std::string const& text, std::string const& more)
{
  if (text.empty()) { return false; }

  namespace background  = detail::background;
  namespace font        = detail::font;
  namespace label_font  = detail::label_font;
  namespace label_color = detail::label_color;

  int x = (center.x - (background::width / 2));
  int y = (center.y - (background::height / 2));

  // Create window with cv::WINDOW_AUTOSIZE option to show image
  // at its original size, rather than scaling image to fit window
  cv::namedWindow(name, cv::WINDOW_AUTOSIZE);
  cv::moveWindow(name, x, y);   // window position

  // Image on which to draw text
  cv::Mat image(background::height, background::width,
                CV_8UC3, background::color_bgr);

  // Text offset (x, y)
  cv::Point offset(10, 27);

  // Define label text and color based on popup type
  std::string label_text;
  cv::Scalar  label_color_bgr;
  switch (type)
  {
    case utl::opencv::PopupType::error:
      label_text      = "ERROR";
      label_color_bgr = label_color::error_bgr;
      break;
    case utl::opencv::PopupType::message:
      label_text      = "MESSAGE";
      label_color_bgr = label_color::message_bgr;
      break;
    case utl::opencv::PopupType::warning:
      label_text      = "WARNING";
      label_color_bgr = label_color::warning_bgr;
      break;
    default:  // invalid PopupType
      return false;
  }

  // Label text
  cv::putText(image, label_text, offset, label_font::face, label_font::scale,
              label_color_bgr, label_font::thickness, cv::LINE_AA);

  // First line of text
  offset += cv::Point(0, 27);
  cv::putText(image, text, offset, font::face, font::scale,
              font::color_bgr, font::thickness, cv::LINE_AA);

  // Second line of text
  if (!more.empty())
  {
    offset += cv::Point(0, 20);
    cv::putText(image, more, offset, font::face, font::scale,
                font::color_bgr, font::thickness, cv::LINE_AA);
  }

  // Display on the screen
  cv::imshow(name, image);

  return true;
}

//---------------------------------------------------------------------------
} } // utl::opencv

#endif // UTL_OPENCV_POPUP_HPP
//===========================================================================//
