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
/// @brief    Timer utility library.
/// @details  Header-only library providing a steady monotonic
///           timer built on C++ standard library `<chrono>`.
/// @author   Nathan Lucas
/// @date     2015
//===========================================================================//
#ifndef UTL_CHRONO_TIMER_HPP
#define UTL_CHRONO_TIMER_HPP

#ifndef __cplusplus
#error must be compiled as C++
#endif

#include <chrono>       // std::chrono

/// @ingroup  utl_chrono
/// @defgroup utl_chrono_timer  chrono_timer
/// @brief    Timer utilities.
/// @details  Header-only library providing a steady monotonic
///           timer built on C++ standard library `<chrono>`.

namespace utl { namespace chrono {

/// @addtogroup utl_chrono_timer
/// @{


//---------------------------------------------------------------------------
/// @brief  Uses a steady monotonic clock to compute time intervals.
/// @details
/// Example: @n
/// ```
/// utl::timer tmr;
/// compute();
/// std::cout << "compute time:\n  "
///           << tmr.elapsed<utl::timer::s>().count()
///           << " seconds, or\n  "
///           << tmr.elapsed<utl::timer::ms>().count()
///           << " microseconds" << std::endl;
/// ```
/// GNU GCC (g++) compiler settings: @n
///   Compiler flags:  `-std=C++0x` @n
///   Other options:   `-std=gnu++11`
///
class timer
{
public:

  typedef std::chrono::duration<double> seconds, s;
  typedef std::chrono::milliseconds milliseconds, ms;
  typedef std::chrono::microseconds microseconds, us;
  typedef std::chrono::nanoseconds nanoseconds, ns;

  /// @brief  Creates timer.
  ///
  /*inline*/
//  explicit                            // direct initialization only
  timer()
  : t0_(std::chrono::steady_clock::now())
  {} // do nothing

  /// @brief  Returns time elapsed since instantiation or last reset.
  /// @tparam Duration  A duration type.
  /// @return A duration object.
  ///
  template<typename Duration>
  /*inline*/
  Duration
  elapsed() const
  {
    auto t  = std::chrono::steady_clock::now();
    auto dt = std::chrono::duration_cast<Duration>(t - t0_);
    return dt;
  }

  /// @brief  Resets timer.
  /*inline*/
  void
  reset()
  {
    t0_ = std::chrono::steady_clock::now();
  }

//private:  // member functions
//  timer(timer const&);              ///< Disallow copying.
//  timer& operator=(timer const&);   ///< Disallow assignment.

private:  // data members

  std::chrono::steady_clock::time_point t0_;

};


//---------------------------------------------------------------------------
/// @name Timer Functions
/// @{

/// @brief  Returns time elapsed since instantiation
///         or last reset of timer @em t.
/// @param  [in]  t   Timer.
/// @return Duration in milliseconds.
inline
unsigned long
timer_elapsed_ms(utl::chrono::timer const& t)
{
  return t.elapsed<utl::chrono::timer::ms>().count();
}

/// @}
//---------------------------------------------------------------------------

/// @}

} } // utl::chrono

#endif // UTL_CHRONO_TIMER_HPP
//===========================================================================//
