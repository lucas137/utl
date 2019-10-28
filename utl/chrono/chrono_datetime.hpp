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
/// @brief    Date and time utility library.
/// @details  Header-only library providing date and time conversion
///           functions built on C++ standard library `<ctime>`.
/// @author   Nathan Lucas
/// @version  0.2
/// @date     2015
//===========================================================================//
#ifndef UTL_CHRONO_DATETIME_HPP
#define UTL_CHRONO_DATETIME_HPP

#ifndef __cplusplus
#error must be compiled as C++
#endif

#include <ctime>        // std::tm
#include <string>       // std::string

/// @ingroup  utl_chrono
/// @defgroup utl_chrono_datetime   chrono_datetime
/// @brief    Date and time utilities.
/// @details  Header-only library providing date and time conversion
///           functions built on C++ standard library `<ctime>`.

namespace utl { namespace chrono {

/// @addtogroup utl_chrono_datetime
/// @{

//---------------------------------------------------------------------------
/// @name Date and Time Functions
/// Date and time conversion built on C++ standard library `<ctime>`.
/// @{

/// @brief  Calendar day from time structure.
/// @param  [in]  t   Time structure.
/// @return Day of the month: `1`-`31`.
inline int
day(std::tm const& t)       { return t.tm_mday; }


/// @brief  Day of the week from time structure.
/// @param  [in]  t   Time structure.
/// @return Day of the week: `1`-`7`.
inline int
dayweek(std::tm const& t)   { return (t.tm_wday + 1); }


/// @brief  Day of the week from time structure.
/// @param  [in]  t   Time structure.
/// @return `Sunday`, `Monday`, ...
/*inline*/ std::string
dayweek_str(std::tm const& t);


/// @brief  Day of the week from time structure.
/// @param  [in]  t     Time structure.
/// @param  [in]  cap   All upper case letters if `true`.
/// @return `Sun`, `Mon`, ...; or `SUN`, `MON`, ...
/*inline*/ std::string
daywk_str(std::tm const& t, bool cap=false);


/// @brief      Month from time structure.
/// @param[in]  t   Time structure.
/// @return     Month of the year: `1`-`12`.
inline int
month(std::tm const& t)     { return (t.tm_mon + 1); }


/// @brief  Month from time structure.
/// @param  [in]  t   Time structure
/// @return `January`, `February`, ...
/*inline*/ std::string
month_str(std::tm const& t);


/// @brief  Month from time structure.
/// @param  [in]  t     Time structure.
/// @param  [in]  cap   All upper case letters if `true`.
/// @return `Jan`, `Feb`, ...; or `JAN`, `FEB`, ...
/*inline*/ std::string
mon_str(std::tm const& t, bool cap=false);


/// @brief  Year from time structure.
/// @param  [in]  t   Time structure.
/// @return Year.
inline int
year(std::tm const& t)    { return (t.tm_year + 1900); }


/// @brief  Returns a numeric representation of the calendar
///         date contained in the time strucutres.
/// @return Integer value encoding the current date in eight decimal digits.
///         From left-to-right, the first four digits are year, the next two
///         digits are month, and the last two digits are day of the month.
///
/// Returns an integer value with up to eight decimal digits.
/// From right-to-left, the lowest two digits contain day of the month,
/// the next two digits contain the month (`1-12`), and the remaining
/// digits contain the year.  For example, a date of 16 September 2017
/// returns the integer value `20170916`.
inline unsigned
yyyymmdd(std::tm const& t)
{
  return ((10000 * (t.tm_year + 1900)) +
          (  100 * (t.tm_mon  + 1)) +
                    t.tm_mday);
}


/// @brief  Hours from time structure.
/// @param  [in]  t   Time structure.
/// @return Hours since midnight: `0`-`23`.
inline int
hour(std::tm const& t)    { return t.tm_hour; }


/// @brief  Minutes from time structure.
/// @param  [in]  t   Time structure.
/// @return Minutes: `0`-`59`.
inline int
min(std::tm const& t)     { return t.tm_min; }


/// @brief  Seconds from time structure.
/// @param  [in]  t   Time structure.
/// @return Seconds: `0`-`59`.
inline int
sec(std::tm const& t)     { return t.tm_sec; }


/// @brief  Daylight Savings Time (DST) from time structure.
/// @param  [in]  t   Time structure.
/// @return `true` is DST, `false` otherwise.
inline bool
is_dst(std::tm const& t)  { return (t.tm_isdst == 1); }


/// @}
//---------------------------------------------------------------------------

/// @}


//===========================================================================//
// Implementation


inline std::string
dayweek_str(std::tm const& t)
{
  switch (t.tm_wday)
  {
    case 0: return "Sunday";
    case 1: return "Monday";
    case 2: return "Tuesday";
    case 3: return "Wednesday";
    case 4: return "Thursday";
    case 5: return "Friday";
    case 6: return "Saturday";
  }
  return "";
}


inline std::string
daywk_str(std::tm const& t, bool cap)
{
  switch (t.tm_wday)
  {
    case 0: return (cap ? "SUN" : "Sun");
    case 1: return (cap ? "MON" : "Mon");
    case 2: return (cap ? "TUE" : "Tue");
    case 3: return (cap ? "WED" : "Wed");
    case 4: return (cap ? "THU" : "Thu");
    case 5: return (cap ? "FRI" : "Fri");
    case 6: return (cap ? "SAT" : "Sun");
  }
  return "";
}


inline std::string
month_str(std::tm const& t)
{
  switch (t.tm_wday)
  {
    case 0:  return "January";
    case 1:  return "February";
    case 2:  return "March";
    case 3:  return "April";
    case 4:  return "May";
    case 5:  return "June";
    case 6:  return "July";
    case 7:  return "August";
    case 8:  return "September";
    case 9:  return "October";
    case 10: return "November";
    case 11: return "December";
  }
  return "";
}


inline std::string
mon_str(std::tm const& t, bool cap)
{
  switch (t.tm_wday)
  {
    case 0:  return (cap ? "JAN" : "Jan");
    case 1:  return (cap ? "FEB" : "Feb");
    case 2:  return (cap ? "MAR" : "Mar");
    case 3:  return (cap ? "APR" : "Apr");
    case 4:  return (cap ? "MAY" : "May");
    case 5:  return (cap ? "JUN" : "Jun");
    case 6:  return (cap ? "JUL" : "Jul");
    case 7:  return (cap ? "AUG" : "Aug");
    case 8:  return (cap ? "SEP" : "Sep");
    case 9:  return (cap ? "OCT" : "Oct");
    case 10: return (cap ? "NOV" : "Nov");
    case 11: return (cap ? "DEC" : "Dec");
  }
  return "";
}


} } // utl::chrono

#endif // UTL_CHRONO_DATETIME_HPP
//===========================================================================//
