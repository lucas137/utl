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
/// @brief    %Rectangle widget.
/// @author   Nathan Lucas
/// @date     2016
//===========================================================================//
#ifndef UTL_OPENCV_RECTANGLE_HPP
#define UTL_OPENCV_RECTANGLE_HPP

#ifndef __cplusplus
#error must be compiled as C++
#endif

//-----------------------------------------------------------
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wall"

// OpenCV is released under 3-clause BSD License.
// https://opencv.org/license.html
#include <opencv2/core.hpp>     // cv::Mat, cv::Point, cv::Rect, cv::Scalar
#include <opencv2/imgproc.hpp>  // cv::rectangle

#pragma GCC diagnostic pop
//-----------------------------------------------------------

#include <array>    // std::array

namespace utl { namespace opencv {
//---------------------------------------------------------------------------
/// @addtogroup utl_opencv
/// @{

/// %Rectangle widget.
template<typename T>
class Rectangle_
{
public:

  /// Construct with specified origin, dimensions, and BGR color.
  Rectangle_(T x, T y, T width, T height,
             bool visible, cv::Scalar const& color_bgr,
             int thickness=1, int line_type=cv::LINE_8, int shift=0);

  /// Construct with specified vertices and BGR color.
  Rectangle_(cv::Point_<T> const& pt1, cv::Point_<T> const& pt2,
             bool visible, cv::Scalar const& color_bgr,
             int thickness=1, int line_type=cv::LINE_8, int shift=0);

  /// Construct with BGR color.
  Rectangle_(cv::Scalar const& color_bgr,
             int thickness=1, int line_type=cv::LINE_8, int shift=0);

  /// Default constructor.
  Rectangle_() = default;

  //-----------------------------------------------------------

  int  area(cv::Point_<T> const& pt) const; ///< Area (width*height).
  void clear();               ///< Clear points and is_visible flag.

  /// Returns `true` if the rectangle contains the point.
  bool contains(cv::Point_<T> const& pt) const;

  void draw(cv::Mat& image) const;  ///< If visible, draw on `image`.

  bool is_visible() const;    ///< Returns `true` if visible.
  void is_visible(bool val);  ///< `true` to make visible.

  void point1(T x, T y);      ///< Set first vertex.
  void point2(T x, T y);      ///< Set second vertex.

  cv::Size_<T> size() const;          ///< Return size (width, height).
  void size(cv::Size_<T> const& sz);  ///< Set size (width, height).

  //-----------------------------------------------------------

private:
  cv::Scalar const  color_bgr_ {128,128,128};  // blue, green, red
  int const         thickness_ {1};
  int const         line_type_ {cv::LINE_8};
  int const         shift_     {0};

  cv::Point_<T>     point1_  {};
  cv::Point_<T>     point2_  {};
  cv::Rect_<T>      rect_    {};
  bool              visible_ {false};
};

//-----------------------------------------------------------

typedef Rectangle_<int> Rectangle2i;
typedef Rectangle_<float> Rectangle2f;
typedef Rectangle_<double> Rectangle2d;
typedef Rectangle2i Rectangle;

/// @}
//---------------------------------------------------------------------------

template<typename T>
inline
Rectangle_<T>::Rectangle_(T x, T y, T width, T height,
                         bool visible, cv::Scalar const& color_bgr,
                         int thickness, int line_type, int shift)
: color_bgr_(color_bgr)
, thickness_(thickness)
, line_type_(line_type)
, shift_(shift)
, point1_(x, y)
, point2_(x + width, y + height)
, rect_(point1_, point2_)
, visible_(visible)
{}

template<typename T>
inline
Rectangle_<T>::Rectangle_(cv::Point_<T> const& pt1, cv::Point_<T> const& pt2,
                          bool visible, cv::Scalar const& color_bgr,
                          int thickness, int line_type, int shift)
: color_bgr_(color_bgr)
, thickness_(thickness)
, line_type_(line_type)
, shift_(shift)
, point1_(pt1)
, point2_(pt2)
, rect_(pt1, pt2)
, visible_(visible)
{}

template<typename T>
inline
Rectangle_<T>::Rectangle_(cv::Scalar const& color_bgr,
                          int thickness, int line_type, int shift)
: color_bgr_(color_bgr)
, thickness_(thickness)
, line_type_(line_type)
, shift_(shift)
{}

//-----------------------------------------------------------

template<typename T>
inline int
Rectangle_<T>::area(cv::Point_<T> const& pt) const
{
  return rect_.area(pt);
}

template<typename T>
inline void
Rectangle_<T>::clear()
{
  point1_  = cv::Point_<T>();
  point2_  = cv::Point_<T>();
  rect_    = cv::Rect_<T>();
  visible_ = false;
}

template<typename T>
inline bool
Rectangle_<T>::contains(cv::Point_<T> const& pt) const
{
  return rect_.contains(pt);
}

template<typename T>
inline void
Rectangle_<T>::draw(cv::Mat& image) const
{
  if (visible_)
  {
    // Drawing from cv::Point requires one less redirect that cv::Rect
    cv::rectangle(image, point1_, point2_,
                  color_bgr_, thickness_, line_type_, shift_);
  }
}

template<typename T>
inline bool
Rectangle_<T>::is_visible() const
{
  return visible_;
}

template<typename T>
inline void
Rectangle_<T>::is_visible(bool val)
{
  visible_ = val;
}

template<typename T>
inline void
Rectangle_<T>::point1(T x, T y)
{
  point1_ = cv::Point(x, y);
}

template<typename T>
inline void
Rectangle_<T>::point2(T x, T y)
{
  point2_ = cv::Point(x, y);
  rect_   = cv::Rect(point1_, point2_);
}

template<typename T>
inline cv::Size_<T>
Rectangle_<T>::size() const
{
  return rect_.size();
}

template<typename T>
inline void
Rectangle_<T>::size(cv::Size_<T> const& sz)
{
  point2(point1_.x + sz.width, point1_.y + sz.height);
}

//---------------------------------------------------------------------------
} } // utl::opencv

#endif // UTL_OPENCV_RECTANGLE_HPP
//===========================================================================//
