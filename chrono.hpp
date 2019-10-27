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
/// @brief    Time utility library.
/// @details  Header-only library providing time and date utilities built
///           on C++ standard libraries `<chrono>` and `<ctime>`.
/// @author   Nathan Lucas
/// @version  0.2
/// @date     2015
//===========================================================================//
#ifndef UTL_CHRONO_HPP
#define UTL_CHRONO_HPP

#ifndef __cplusplus
#error must be compiled as C++
#endif

/// @defgroup utl_chrono  chrono
/// @brief    Time utility library.
/// @details  Header-only library providing time and date utilities built
///           on C++ standard libraries `<chrono>` and `<ctime>`.

//---------------------------------------------------------------------------
/// @namespace  utl::chrono
/// @brief  Time utility library.
///
/// Header-only library providing time and date utilities built
/// on C++ standard libraries `<chrono>` and `<ctime>`. @n
/// GNU GCC (g++) compiler settings: @n
///   Compiler flags:  `-std=C++0x` @n
///   Other options:   `-std=gnu++11`
///
/// Reference
/// ---------
/// `std::chrono clocks`:
///
/// - `system_clock`
///   + System-wide realtime clock.
///   + <em> realtime     </em> : Intended to represent the real time,
///                               and thus it can be translated to and
///                               from calendar representations.
///   + <em> signed count </em> : Its time_point values can refer to times
///                               before the epoch (with negative values).
///   + <em> system-wide  </em> : All processes running on the system
///                               shall retrieve the same time_point values
///                               by using this clock.
/// - `steady_clock`
///   + Specifically designed to calculate time intervals.
///   + <em> monotonic    </em> : Its member now() never returns a
///                               lower value than in a previous call.
///   + <em> steady       </em> : Every tick the clock advances the same
///                               amount of time (in terms of physical time).
/// - `high_resolution_clock`
///   + May be synonym for `system_clock` or `steady_clock`.
///   + <em> shortest tick period </em>
///   + <em> highest precision    </em>
///
/// Integer capacity for time:  @n
///
/// `std::uint_fast32_t` is the fastest unsigned integer type with
/// a width of at least 32 bits. It can represent up to at least
/// 4,294,967,295 milliseconds (49.7 days). This data type is
/// insufficient for storing epoch time in seconds or milliseconds.  @n
///
/// `std::uint_fast64_t` is the fastest unsigned integer
/// type with a width of at least 64 bits.  It can represent
/// epoch times up to 18,446,744,073,709,551,616 milliseconds
/// (584 million years elapsed since 1 January 1970).  @n
///
/// Nominal minimum and maximum values representing
/// time duration with integer types. @n
///
/// Type       |              Range Limit |  Seconds |Milliseconds|Microseconds
/// -----------|-------------------------:|---------:|-----------:|-----------:
/// `int`      |            -2,147,483,648|   -68 yr |  -24 days  | -35 minutes
/// `int`      |             2,147,483,647|    68 yr |   24 days  |  35 minutes
/// `unsigned` |             4,294,967,295|   136 yr |   49 days  |  71 minutes
/// `long long`|-9,223,372,036,854,775,808|-2.9e11 yr|  -2.9e8 yr | -292,277 yr
/// `long long`| 9,223,372,036,854,775,807| 2.9e11 yr|   2.9e8 yr |  292,277 yr
/// `unsigned` |18,446,744,073,709,551,615| 5.8e11 yr|   5.8e8 yr |  584,555 yr
///
//---------------------------------------------------------------------------


// Modules

#include "chrono/chrono_clock.hpp"
#include "chrono/chrono_datetime.hpp"
#include "chrono/chrono_timer.hpp"
#include "chrono/chrono_timestamp.hpp"


#endif // UTL_CHRONO_HPP
//===========================================================================//
