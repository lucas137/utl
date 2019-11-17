//=============================================================================
/// \brief    Timestamps
/// \author   Nathan P. Lucas
/// \version  0.1
/// \date     2015
//=============================================================================
#ifndef UTL_TIMESTAMP_H
#define UTL_TIMESTAMP_H

// Client is responsible for including:
//  #include <string>       //  std::string


// TODO -- fractions of second:  YYYY-MM-DDThh:mm:ss.msec
// TODO -- eliminate dependence on std::ostringstream


//=============================================================================
/// Functions returning current date and time.
///
/// Timestamp functions uses \c std::chrono::system_clock to obtain date
/// and/or time from the system-wide realtime clock.  This clock is intended
/// to represent the real time, and can be translated to and from calendar
/// representations.
/// \verbatim
/// GNU GCC (g++) compiler settings:
///   Compiler flags:   -std=C++0x
///   Other options:    -std=gnu++11
/// \endverbatim
///
namespace utl { namespace timestamp {

  /// Get current date in YYYY-MM-DD format.
  ///
  /// \param  delim     delimiter between year, month, and day.
  ///
  inline std::string
  date(std::string const& delim="-");


  /// Get current time in hh:mm:ss format.
  ///
  /// \param  delim     delimiter between hours, minutes, and seconds.
  ///
  inline std::string
  time(std::string const& delim=":");


  /// Get current date and time.
  ///
  /// Returns date in YYYY-MM-DD format and time in hh:mm:ss format.
  /// A delimiter \p delim separates the date and time.  Optional
  /// \p date_delim specifies the delimiter between year, month, and day.
  /// Optional \p time_delim specifies the delimiter between hours, minutes,
  /// and seconds.  The default parameter values return date and time in
  /// ISO 8601 extended format (e.g., "2015-02-20T13:02:03").
  ///
  /// \param  extended  date and/or time in extended format.
  /// \param  delim     delimiter between date and time.
  ///
  inline std::string
  datetime(std::string const& delim="T",
           std::string const& date_delim="-",
           std::string const& time_delim=":");

} } // utl::timestamp

#include "timestamp/timestamp_impl.hpp"   // implementation details

//=============================================================================
#endif // UTL_TIMESTAMP_H
