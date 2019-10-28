//===========================================================================//
// Nathan Lucas
// 2015
//===========================================================================//
#ifndef SCREEN_HPP
#define SCREEN_HPP

#include <iostream>   // std::cout, std::endl
#include <string>     // std::string
#include <sstream>    // std::ostringstream

#include <FL/Fl.H>    // FLTK GUI libraries

namespace utl_test {


// \brief  Screen configuration data.
//
struct Screen
{
  int   index;    // Screen number
  int   x_px;     // Screen/window horizontal position
  int   y_px;     // Screen/window vertical position
  int   w_px;     // Screen/window width in pixels
  int   h_px;     // Screen/window height in pixels
  float w_m;      // Physical screen width in meters
  float h_m;      // Physical screen height in meters

  // \brief  Construct an empty screen information structure.
  //
  Screen(int index=0)
  : index(index)
  , x_px(0)  , y_px(0)
  , w_px(0)  , h_px(0)
  , w_m(0.0) , h_m(0.0)
  {}
};


//---------------------------------------------------------------------------


// \brief          Configure screen position and size.
// \param[in,out]  s   Screen configuration data
inline void
screen_config(utl_test::Screen& s)
{
  // Get the bounding box of the work area of the given screen
  // Note: No window position and size offsets due to fullscreen mode
  Fl::screen_work_area(s.x_px, s.y_px, s.w_px, s.h_px, s.index);

  // Get screen resolution in dots-per-inch
  float screen_dpi_h(0);
  float screen_dpi_v(0);
  Fl::screen_dpi(screen_dpi_h, screen_dpi_v, s.index);

  // Compute physical screen size in meters
  s.w_m = (0.0254 * (s.w_px / screen_dpi_h));
  s.h_m = (0.0254 * (s.h_px / screen_dpi_v));
}


// \brief      List postion and size of all screens,
//             and indicate selected screen.
// Example:\n
// [ ] screen 0: (    0,     0)  1600 x 900\n
// [x] screen 1: ( 1600,     0)  1920 x 1200\n
// [ ] screen 2: ( 3520,     0)  1920 x 1200\n
// \param[in]  s   Screen configuration data
inline void
screen_list(utl_test::Screen const& s)
{
  std::cout << "screen selection" << std::endl;
  int screen_count = Fl::screen_count();
  for (int i=0; i < screen_count; ++i)
  {
    int x, y, w, h;
    Fl::screen_xywh(x, y, w, h, i);
    std::cout << "[" << ((i == s.index) ? "x" : " ")
              << "] screen " << i << " : " << w << " x " << h
              << "  (" << x << ", " << y << ")" << std::endl;
  }
}


// \brief  Returns a string containing lines of comma separated values.
// \param[in]  screen  Screen data
//
inline std::string
screen_csv(utl_test::Screen const& screen)
{
  std::ostringstream oss;
  oss << "screen.index" << ',' << screen.index << '\n'
      << "screen.x_px"  << ',' << screen.x_px  << '\n'
      << "screen.y_px"  << ',' << screen.y_px  << '\n'
      << "screen.w_px"  << ',' << screen.w_px  << '\n'
      << "screen.h_px"  << ',' << screen.h_px  << '\n'
      << "screen.w_m"   << ',' << screen.w_m   << '\n'
      << "screen.h_m"   << ',' << screen.h_m   << '\n';
  return oss.str();
}


// \brief      Output to stdout.
// \param[in]  screen  Screen data
inline void
screen_stdout(utl_test::Screen const& screen)
{
  std::cout << "screen"
    << "\n.index  : " << screen.index
    << "\n.x/y_px : ("<< screen.x_px << ", "<< screen.y_px <<")"
    << "\n.w/h_px : " << screen.w_px <<" x "<< screen.h_px
    << "\n.w/h_m  : " << screen.w_m  <<" x "<< screen.h_m
    << std::endl;
}


} // utl_test

#endif // SCREEN_HPP
//===========================================================================//
