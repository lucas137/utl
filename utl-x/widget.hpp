//===========================================================================//
/// @file
/// @brief    FLTK drawing widget.
/// @author   Nathan Lucas
/// @version  0.1
/// @date     2015
//===========================================================================//
#ifndef UTL_FLTK_WIDGET_HPP
#define UTL_FLTK_WIDGET_HPP

namespace utl { namespace fltk {

/// @addtogroup FLTK
/// @{

/// @brief  Color components.
///
struct color
{
  unsigned char red_;
  unsigned char green_;
  unsigned char blue_;

  /** @brief  Create color structure.
  @param [in] red     Red component
  @param [in] green   Green component
  @param [in] blue    Blue component
  */
  color(unsigned char red=0, unsigned char green=0, unsigned char blue=0)
  : red_(red)
  , green_(green)
  , blue_(blue)
  {} // do nothing

  /// @brief  Set color component values.
  /// @param [in] red     Red component
  /// @param [in] green   Green component
  /// @param [in] blue    Blue component
  void
  set(unsigned char red, unsigned char green, unsigned char blue)
  {
    red_   = red;
    green_ = green;
    blue_  = blue;
  }

};

/// @}
// group FLTK

} } // utl::fltk

#endif // UTL_FLTK_WIDGET_HPP
//===========================================================================//
