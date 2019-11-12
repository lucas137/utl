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
/// @brief    Clock and time utility library.
/// @details  Header-only library providing clock and time functions
///           built on C++ standard library `<chrono>`.
/// @author   Nathan Lucas
/// @date     2015
//===========================================================================//
#ifndef UTL_CHRONO_CLOCK_HPP
#define UTL_CHRONO_CLOCK_HPP

#ifndef __cplusplus
#error must be compiled as C++
#endif

#include <chrono>       // std::chrono
#include <ctime>        // std::time_t, std::tm, std::localtime
#include <string>       // std::string
#include <sstream>      // std::ostringstream
#include <iomanip>      // std::setfill std::setw
#include <ios>          // std::fixed
#include <ratio>        // std::ratio_less_equal,
                        // std::micro, std::mega, std::milli, std::kilo


// TODO -- eliminate dependence on std::ostringstream

/// @ingroup  utl_chrono
/// @defgroup utl_chrono_clock  chrono_clock
/// @brief    Clock utilities.
///
/// Header-only library providing clock and time
/// functions built on C++ standard library `<chrono>`.

namespace utl { namespace chrono {

/// @addtogroup utl_chrono_clock
/// @{

//---------------------------------------------------------------------------
/// @name Clock Functions
/// Clock and time functions built on C++ standard library `<chrono>`.
/// @{


/// @brief  Checks precision of type @em Clock.
/// @tparam Clock   A clock class, such as `std::system_clock`,
///                 `std::steady_clock`, `std::high_resolution_clock`,
///                 or a custom clock class.
/// @return Description of clock precision.
///
template<typename Clock>
std::string
clock_precision();


/// @brief  Checks if type @em Clock is a steady clock.
/// @tparam Clock   A clock class, such as `std::system_clock`,
///                 `std::steady_clock`, `std::high_resolution_clock`,
///                 or a custom clock class.
/// @return "true" if @em Clock is a steady clock, "false" otherwise.
///
template<typename Clock>
/*inline*/ std::string
clock_is_steady()   { return (Clock::is_steady ? "true" : "false"); }


/// @brief  Combines time components in hours, minutes, seconds,
///         and milliseconds into a single value in milliseconds.
/// @param  [in]  hr    Hours.
/// @param  [in]  min   Minutes.
/// @param  [in]  sec   Seconds.
/// @param  [in]  ms    Milliseconds.
/// @return Sum total in milliseconds.
inline
std::chrono::milliseconds
combine(int hr, int min, int sec, int ms)
{
  return std::chrono::milliseconds(1000 * (60 * ((60*hr) + min) + sec) + ms);
}


/// @brief  Get current time.
/// @tparam Clock   A clock class, such as `std::system_clock`,
///                 `std::steady_clock`, `std::high_resolution_clock`,
///                 or a custom clock class.
/// @tparam Duration  A duration type.
/// @return A duration object.
///
/// Returns the current time in the frame of @em Clock. @n
/// Example:
/// ```
/// auto t_ms = utl::chrono::now<std::chrono::steady_clock, std::chrono::milliseconds>();
/// std::cout << t_ms.count() << " milliseconds relative to steady_clock's epoch\n";
/// ```
template<typename Clock, typename Duration>
/*inline*/
Duration
now()
{
  auto t_now = Clock::now();
  auto t_duration = t_now.time_since_epoch();
  return std::chrono::duration_cast<Duration>(t_duration);
}


/// @brief  Get current time.
/// @tparam Clock   A clock class, such as `std::system_clock`,
///                 `std::steady_clock`, `std::high_resolution_clock`,
///                 or a custom clock class.
/// @return A duration object.
///
/// Returns the current time in seconds, in the frame of @em Clock.
template<typename Clock>
/*inline*/
std::chrono::seconds
now_seconds()
{
  return utl::chrono::now<Clock, std::chrono::seconds>();
}


/// @brief  Get current time.
/// @tparam Clock   A clock class, such as `std::system_clock`,
///                 `std::steady_clock`, `std::high_resolution_clock`,
///                 or a custom clock class.
/// @return A duration object.
///
/// Returns the current time in milliseconds, in the frame of @em Clock.
template<typename Clock>
/*inline*/
std::chrono::milliseconds
now_milliseconds()
{
  return utl::chrono::now<Clock, std::chrono::milliseconds>();
}


/// @brief  Get current time.
/// @tparam Clock   A clock class, such as `std::system_clock`,
///                 `std::steady_clock`, `std::high_resolution_clock`,
///                 or a custom clock class.
/// @return A duration object.
///
/// Returns the current time in microseconds, in the frame of @em Clock.
template<typename Clock>
/*inline*/
std::chrono::microseconds
now_microseconds()
{
  return utl::chrono::now<Clock, std::chrono::microseconds>();
}


/// @brief  Returns the current time in the frame of @em Clock.
/// @tparam Clock   A clock class, such as `std::system_clock`,
///                 `std::steady_clock`, `std::high_resolution_clock`,
///                 or a custom clock class.
/// @return Time value.
template<typename Clock>
/*inline*/
std::time_t
now_t()     { return Clock::to_time_t(Clock::now()); }


/// @brief  By default returns current time in the
///         frame of `std::chrono::system_clock`.
/// @return Time value.
inline
std::time_t
now_t()     { return std::chrono::system_clock::to_time_t(
                       std::chrono::system_clock::now()); }


/// @brief  Returns current time in the frame of @em Clock.
/// @tparam Clock   A clock class, such as `std::system_clock`,
///                 `std::steady_clock`, `std::high_resolution_clock`,
///                 or a custom clock class.
/// @return Time structure.
///
template<typename Clock>
/*inline*/
std::tm
now_tm()    { std::time_t tt = Clock::to_time_t(Clock::now());
              return *std::localtime(&tt); }


/// @brief  By default returns current time in the
///         frame of `std::chrono::system_clock`.
/// @return Time structure.
inline std::tm
now_tm()    { return utl::chrono::now_tm<std::chrono::system_clock>(); }


/// @brief  Returns a numeric representation of the current calendar
///         date in the frame of `std::chrono::system_clock`.
/// @return Integer value encoding the current date in eight decimal digits.
///
/// Returns an integer value with eight decimal digits.
/// From right-to-left, the lowest two digits contain day of the month,
/// the next two digits contain the month (`1-12`), and the highest four
/// digits contain the year.  For example, on 16 September 2017
/// `now_yyyymmdd` returns the integer value `20170916`.
inline unsigned
now_yyyymmdd()
{
  auto t = now_tm<std::chrono::system_clock>();
  return ((10000 * (t.tm_year + 1900)) +
          (  100 * (t.tm_mon  + 1)) +
                    t.tm_mday);
}


/// @brief  Parses millisecond value into a string representation
///         of hours, minutes, seconds, and milliseconds.
/// @param  [in]  msec  Millisecond value.
/// @return String format `HH:MM:SS.mmm`.
///
/// Returns a string format `HH:MM:SS.mmm`, where `HH` is hours,
/// `MM` is minutes, `SS` is seconds, and `mmm` is milliseconds.
inline std::string
segment(std::chrono::milliseconds const& msec);


/// @brief  Parses millisecond value into hours,
///         minutes, seconds, and milliseconds.
/// @param  [out] hr    Hours
/// @param  [out] min   Minutes
/// @param  [out] sec   Seconds
/// @param  [out] ms    Milliseconds
/// @param  [in]  msec  Millisecond value
/// @return String format <tt>HH:MM:SS.mmm</tt>.
inline void
segment(std::chrono::hours& hr, std::chrono::minutes& min,
        std::chrono::seconds& sec, std::chrono::milliseconds& ms,
        std::chrono::milliseconds const& msec);


/// @brief  Returns the time span between the epoch and the current time.
/// @tparam Duration  A duration type.
/// @return A duration object.
template<typename Duration> Duration
/*inline*/
time_since_epoch()
{
  return std::chrono::duration_cast<Duration>(
          std::chrono::system_clock::now().time_since_epoch());
}


/// @brief  Converts the specified time point to a string representation.
/// @param  [in]  tp  Time point.
/// @return String representation of time.
inline std::string
to_string(std::chrono::system_clock::time_point const& tp);


/// @}
//---------------------------------------------------------------------------

/// @}


//===========================================================================//
// Implementation


template<typename Clock>
std::string
clock_precision()
{
  std::ostringstream oss;
  // if time unit is less or equal one microsecond
  typedef typename Clock::period P;// type of time unit
  if (std::ratio_less_equal<P, std::micro>::value)
  {
    // convert to and print as microseconds
    typedef typename std::ratio_multiply<P, std::mega>::type TT;
    oss << std::fixed << double(TT::num)/TT::den << " microseconds";
  }
  // if time unit is less or equal one millisecond
  else if (std::ratio_less_equal<P, std::milli>::value)
  {
    // convert to and print as milliseconds
    typedef typename std::ratio_multiply<P, std::kilo>::type TT;
    oss << std::fixed << double(TT::num)/TT::den << " milliseconds";
  }
  else
  {
    // print as seconds
    oss << std::fixed << double(P::num)/P::den << " seconds";
  }
  return oss.str();
}


//typedef std::chrono::duration<double> seconds, s;
//typedef std::chrono::milliseconds milliseconds, ms;
//typedef std::chrono::microseconds microseconds, us;
//typedef std::chrono::nanoseconds nanoseconds, ns;


inline std::string
segment(std::chrono::milliseconds const& msec)
{
  using std::chrono::hours;
  using std::chrono::minutes;
  using std::chrono::seconds;
  using std::chrono::milliseconds;

  // split into hours, minutes, seconds, and milliseconds
  hours        hh(std::chrono::duration_cast<hours>(msec));
  minutes      mm(std::chrono::duration_cast<minutes>(msec % hours(1)));
  seconds      ss(std::chrono::duration_cast<seconds>(msec % minutes(1)));
  milliseconds ms(std::chrono::duration_cast<milliseconds>(msec % seconds(1)));

  // durations and values
  std::ostringstream oss;
  oss << std::setfill('0')
      << std::setw(2) << hh.count() << ":"
      << std::setw(2) << mm.count() << ":"
      << std::setw(2) << ss.count() << "."
      << std::setw(3) << ms.count();
  return oss.str();
}


inline void
segment(std::chrono::hours& hr, std::chrono::minutes& min,
        std::chrono::seconds& sec, std::chrono::milliseconds& ms,
        std::chrono::milliseconds const& msec)
{
  using std::chrono::hours;
  using std::chrono::minutes;
  using std::chrono::seconds;
  using std::chrono::milliseconds;

  hr  = std::chrono::duration_cast<hours>(msec);
  min = std::chrono::duration_cast<minutes>(msec % hours(1));
  sec = std::chrono::duration_cast<seconds>(msec % minutes(1));
  ms  = std::chrono::duration_cast<milliseconds>(msec % seconds(1));
}


inline std::string
to_string(std::chrono::system_clock::time_point const& tp)
{
  // convert to system time
  std::time_t t = std::chrono::system_clock::to_time_t(tp);
  std::string ts = std::ctime(&t);  // convert to calendar time
  ts.resize(ts.size()-1);           // skip trailing newline
  return ts;
}


} } // utl::chrono

#endif // UTL_CHRONO_CLOCK_HPP
//===========================================================================//
