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
/// @brief    Lockable object with automatic duration.
/// @details  scoped_locl is based in part on the work of the FLTK project
///           (http://www.fltk.org).
/// @author   Nathan Lucas
/// @version  0.1
/// @date     2016
//===========================================================================//
#ifndef UTL_FLTK_LOCK_HPP
#define UTL_FLTK_LOCK_HPP

#include <FL/Fl.H>          // FLTK GUI libraries

namespace utl { namespace fltk {

/// @addtogroup utl_fltk
/// @{

/// @brief  FLKT lock with automatic duration.
///
/// Wrapper for Fl::lock() and Fl::unlock().  A `scoped_lock` can be locked
/// and unlocked by calling member functions `lock` and `unlock` respectively.
/// The destructor unlocks automatically if the object is a locked state.@n
///
/// scoped_lock is based in part on the work of the FLTK project
/// (http://www.fltk.org).
///
struct scoped_lock
{
  explicit
  scoped_lock()   { lock(); }     ///< Constructor
  ~scoped_lock()  { unlock(); }   ///< Destructor

  scoped_lock(const scoped_lock&) = delete;            ///< Prohibit copying
  scoped_lock& operator=(const scoped_lock&) = delete; ///< Prohibit assignment

  /// Lock.  `scoped_lock` is unchanged if already locked.
  void lock()
  {
    if (!locked_)
    {
      locked_ = true;
      Fl::lock();
    }
  }

  /// Unlock.  `scoped_lock` is unchanged if it is not
  /// in a locked state before calling `unlock`.
  void unlock()
  {
    if (locked_)
    {
      locked_ = false;
      Fl::unlock();
    }
  }

private:
  bool locked_{false};
};

/// @}
// end group: utl_fltk

} } // utl::fltk

#endif // UTL_FLTK_LOCK_HPP
//===========================================================================//
