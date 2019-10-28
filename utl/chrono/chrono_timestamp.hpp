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
/// @brief    Date/timestamp utility library
/// @details  Header-only library providing date/timestamp functions
///           using `std::chrono::system_clock` to obtain date and/or
///           time from the system-wide realtime clock.  This clock is
///           intended to represent the real time, and can be translated
///           to and from calendar representations.
/// @author   Nathan Lucas
/// @version  0.2
/// @date     2015
//===========================================================================//
#ifndef UTL_CHRONO_TIMESTAMP_HPP
#define UTL_CHRONO_TIMESTAMP_HPP

#ifndef __cplusplus
#error must be compiled as C++
#endif

#include <chrono>       // std::chrono
#include <ctime>        // std::tm
#include <string>       // std::string
#include <sstream>      // std::ostringstream
#include <iomanip>      // std::setfill, std::setw

// TODO -- eliminate dependence on std::ostringstream

/** @ingroup  utl_chrono
    @defgroup utl_chrono_timestamp  chrono_timestamp
    @brief    Date/timestamp utilities

    Header-only library providing date/timestamp functions using
    `std::chrono::system_clock` to obtain date and/or time from the
    system-wide realtime clock.  This clock is intended to represent the
    real time, and can be translated to and from calendar representations.
*/

namespace utl { namespace chrono {

/// @addtogroup utl_chrono_timestamp
/// @{

//---------------------------------------------------------------------------
/// @name Date/Timestamp Functions
///
/// Date/Timestamp functions use `std::chrono::system_clock` to obtain date
/// and/or time from the system-wide realtime clock.  This clock is intended
/// to represent the real time, and can be translated to and from calendar
/// representations.
/// @{


/// @brief  Get current date in `YYYY-MM-DD` format.
/// @param  [in]  delim     delimiter between year, month, and day.
/// @return Current date
/*inline*/
std::string
date(std::string const& delim="-");


/// @brief  Get current time in `hh:mm:ss` format.
/// @param  [in]  delim     delimiter between hours, minutes, and seconds.
/// @return Current time.
/*inline*/
std::string
time(std::string const& delim=":");


/// @brief  Get current date and time.
///
/// @param  [in]  delim       Delimiter between date and time.
/// @param  [in]  date_delim  Delimiter between year, month, and day.
/// @param  [in]  time_delim  Delimiter between hour, minute, and second.
/// @return Current date and time.
///
/// Returns date in `YYYY-MM-DD` format and time in `hh:mm:ss` format.
/// A delimiter @em delim separates the date and time.  Optional
/// @em date_delim specifies the delimiter between year, month, and day.
/// Optional @em time_delim specifies the delimiter between hours, minutes,
/// and seconds.  The default parameter values return date and time in
/// ISO 8601 extended format (e.g., `2015-02-20T13:02:03`).
/*inline*/
std::string
datetime(std::string const& delim="T",
         std::string const& date_delim="-",
         std::string const& time_delim=":");

/// @brief  Get current date and time in ISO 8601 format.
/// @param  [in]  extended  Extended format.
/// @return Basic `YYYYMMDDThhmmss` (e.g., `20160514T232533`), or
///         extended `YYYY-MM-DDThh:mm:ss` (e.g., `2016-05-14T23:25:33`).
/*inline*/
std::string
datetime_ISO_8601(bool extended=false);


/// @}
//---------------------------------------------------------------------------

/// @}


//===========================================================================//
// Implementation

// TODO -- fractions of second:  YYYY-MM-DDThh:mm:ss.msec
// TODO -- eliminate dependence on std::ostringstream


inline std::string
date(std::string const& delim)
{
  std::tm local_time = utl::chrono::now_tm();
  std::ostringstream oss;
  oss << std::setfill('0') << (local_time.tm_year + 1900) << delim
      << std::setw(2)      << (local_time.tm_mon + 1)     << delim
      << std::setw(2)      <<  local_time.tm_mday;
  return oss.str();
}


inline std::string
time(std::string const& delim)
{
  std::tm local_time = utl::chrono::now_tm();
  std::ostringstream oss;
  oss << std::setfill('0')
      << std::setw(2) << local_time.tm_hour << delim
      << std::setw(2) << local_time.tm_min  << delim
      << std::setw(2) << local_time.tm_sec;
  return oss.str();
}


inline std::string
datetime(std::string const& delim, std::string const& date_delim,
         std::string const& time_delim)
{
  std::tm local_time = utl::chrono::now_tm();
  std::ostringstream oss;
  oss << std::setfill('0') << (local_time.tm_year + 1900) << date_delim
      << std::setw(2)      << (local_time.tm_mon + 1)     << date_delim
      << std::setw(2)      <<  local_time.tm_mday
      << delim
      << std::setfill('0')
      << std::setw(2) << local_time.tm_hour << time_delim
      << std::setw(2) << local_time.tm_min  << time_delim
      << std::setw(2) << local_time.tm_sec;
  return oss.str();
}


inline std::string
datetime_ISO_8601(bool extended)
{
  std::tm local_time = utl::chrono::now_tm();
  std::ostringstream oss;
  oss << std::setfill('0')<< (local_time.tm_year + 1900)<< (extended ? "-":"")
      << std::setw(2)     << (local_time.tm_mon + 1)    << (extended ? "-":"")
      << std::setw(2)     <<  local_time.tm_mday
      << 'T'
      << std::setfill('0')
      << std::setw(2) << local_time.tm_hour << (extended ? ":" : "")
      << std::setw(2) << local_time.tm_min  << (extended ? ":" : "")
      << std::setw(2) << local_time.tm_sec;
  return oss.str();
}


} } // utl::chrono

#endif // UTL_CHRONO_TIMESTAMP_HPP
//===========================================================================//
