//=============================================================================
/// \brief    Timestamp implementation
/// \author   Nathan P. Lucas
/// \version  0.1
/// \date     2015
//=============================================================================
#ifndef UTL_TIMESTAMP_IMPL_H
#define UTL_TIMESTAMP_IMPL_H

#include <iomanip>      //  std::setfill, std::setw
//#include <iosfwd>       //  std::ostringstream
#include <sstream>      //  std::ostringstream

#include <ctime>        //  time_t, tm, localtime
#include <chrono>       //  std::chrono::system_clock
                        //  std::chrono::system_clock::now
                        //  std::chrono::time_point
                        //  std::chrono::to_time_t
//=============================================================================
namespace utl { namespace timestamp { namespace detail {

  inline tm
  get_local_time()
  {
    using std::chrono::system_clock;
    system_clock::time_point now = system_clock::now();
    time_t tt = system_clock::to_time_t(now);
    return *localtime(&tt);
  }

  inline std::string
  date_stamp(tm const& local_time, std::string const& delim)
  {
    std::ostringstream os;
    os << std::setfill('0') << (local_time.tm_year + 1900) << delim
       << std::setw(2) << (local_time.tm_mon + 1) << delim
       << std::setw(2) << local_time.tm_mday;
    return os.str();
  }

  inline std::string
  time_stamp(tm const& local_time, std::string const& delim)
  {
    std::ostringstream os;
    os << std::setfill('0')
       << std::setw(2) << local_time.tm_hour << delim
       << std::setw(2) << local_time.tm_min << delim
       << std::setw(2) << local_time.tm_sec;
    return os.str();
  }

} } } // utl::timestamp::detail
//=============================================================================

// Get current date in YYYY-MM-DD format
std::string
utl::timestamp::date(std::string const& delim)
{
  tm local_time = detail::get_local_time();
  return utl::timestamp::detail::date_stamp(local_time, delim);
}


// Get current time in hh:mm:ss format
std::string
utl::timestamp::time(std::string const& delim)
{
  tm local_time = detail::get_local_time();
  return utl::timestamp::detail::time_stamp(local_time, delim);
}


// Get current date and time
std::string
utl::timestamp::datetime(std::string const& delim,
                         std::string const& date_delim,
                         std::string const& time_delim)
{
  tm local_time = detail::get_local_time();
  return (utl::timestamp::detail::date_stamp(local_time, date_delim) + delim +
          utl::timestamp::detail::time_stamp(local_time, time_delim));
}

//=============================================================================
#endif // UTL_TIMESTAMP_IMPL_H
