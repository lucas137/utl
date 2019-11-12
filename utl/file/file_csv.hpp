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
/// @brief    CSV file utility library.
/// @details  Header-only library providing comma-separated
///           value (CSV) file format utilities.
/// @author   Nathan P. Lucas
/// @date     2015
//===========================================================================//
#ifndef UTL_FILE_CSV_HPP
#define UTL_FILE_CSV_HPP

#ifndef __cplusplus
#error must be compiled as C++
#endif

#include <utl/file/file_writer.hpp>  // utl::file::file_writer

#include <string>         // std::string
#include <sstream>        // std::ostringstream

/// @ingroup  utl_file
/// @defgroup utl_file_csv  file_csv
/// @brief    CSV file utilities.
/// @details  Header-only library providing comma-separated
///           value (CSV) file format utilities.

namespace utl { namespace file {

/// @addtogroup utl_file_csv
/// @{


//---------------------------------------------------------------------------
/// @brief  Accumulates values in comma separated value (CSV) format.
///
/// Accumulates values in a temporary stream and writes all values
/// to the specified string when csv_out is destroyed. @n
/// A comma is automatically inserted after each value added,
/// unless that value ends with a newline character. @n
/// Example usage:
/// ```
///   csv_out(str) << val1 << val2 << val3 << "\n";
/// ```
/// @note
/// The caller is responsible for terminating each CSV line
/// with a newline character (`'\n'` or `"\n"`).
///
class csv_out
{
public:

  /// @brief  Constructor.
  /// @param  [out] str   String which to write comma separated values.
  /*inline*/
  explicit
  csv_out(std::string& str);

  // ostringstream is not copyable, so copies are already forbidden

  /// @brief  Destructor writes accumulated values to the output stream.
  ~csv_out();

  /// @brief  Add a value.
  /// @tparam       T     Type of value.
  /// @param  [in]  val   Value to add.
  /// @return Reference to `this` object.
  ///
  /// Added values accumulate in a non-shared std::ostringstream
  /// in order to avoid multi-threading issues.
  ///
  /// @note A comma is automatically inserted after each value added,
  ///       unless that value ends with a newline character.
  /*inline*/
  template<typename T>
  csv_out& operator<<(T const& val);

private:
  std::string&      str_;
  std::ostringstream ss_;
};


//---------------------------------------------------------------------------
/// @brief  Comma separated value (CSV) file writer.
///
/// Accumulates values in a temporary stream and writes all values
/// to the specified file_writer when csv_writer is destroyed. @n
/// A comma is automatically inserted after each value added,
/// unless that value ends with a newline character. @n
/// Example usage:
/// ```
///   csv_writer(fw) << val1 << val2 << val3 << "\n";
/// ```
/// @note
/// The caller is responsible for terminating each CSV line
/// with a newline character (`'\n'` or `"\n"`).
///
class csv_writer
{
public:

  /// @brief  Constructor.
  /// @param  [out] fw  file_writer which to write comma separated values.
  /*inline*/
  explicit
  csv_writer(utl::file::file_writer& fw);

  // ostringstream is not copyable, so copies are already forbidden

  /// @brief  Destructor writes accumulated values to the output stream.
  ~csv_writer();

  /// @brief  Add a value.
  /// @tparam       T     Type of value.
  /// @param  [in]  val   Value to add.
  /// @return Reference to `this` object.
  ///
  /// Added values accumulate in a non-shared `std::ostringstream`
  /// in order to avoid multi-threading issues.
  ///
  /// @note A comma is automatically inserted after each value added,
  ///       unless that value ends with a newline character.
  /*inline*/
  template<typename T>
  csv_writer& operator<<(T const& val);

private:
  utl::file::file_writer& fw_;
  std::ostringstream ss_;
};

//---------------------------------------------------------------------------

/// @}


//===========================================================================//
// Implementation


namespace detail {  //-------------------------------------------------------

// Returns true if str1 ends a line or str2 begins a new line.
inline bool
newline(std::string const& str1, std::string const& str2)
{
  //if (str2.empty()) { return false; }
  if (str1.empty()) { return true; }
  return (('\n' == str1.back()) || ('\n' == str2.front()));
}

} // detail -----------------------------------------------------------------

inline
csv_out::csv_out(std::string& str)
: str_(str)
, ss_()
{}

inline
csv_out::~csv_out()
{
  str_ = ss_.str();
}

template<typename T>
inline
csv_out& csv_out::operator<<(T const& val)
{
  // Accumulated string so far
  std::string ss_str(ss_.str());

  // Convert val to string
  std::ostringstream ss;
  ss << val;
  std::string str(ss.str());

  if (str.empty())
  {
    // If accumulated string is empty or ends with a newline
    if (ss_str.empty() || ('\n' == ss_str.back()))
    {
      // Add a space character so a comma will be
      // inserted later if another string is added
      ss_ << ' ';
    }
    else
    {
      // ...otherwise insert a comma to force an empty cell
      ss_ << ',';
    }
  }
  else
  {
    // Insert a comma if the val does not start a new line
    if (!detail::newline(ss_str, str))
    {
      if (!ss_str.empty())
      {
        ss_ << ',';
      }
    }
  }
  ss_ << str;
  return *this;
}

//---------------------------------------------------------------------------

inline
csv_writer::csv_writer(utl::file::file_writer& fw)
: fw_(fw)
, ss_()
{}

inline
csv_writer::~csv_writer()
{
  fw_.write(ss_.str());
}

template<typename T>
inline
csv_writer& csv_writer::operator<<(T const& val)
{
  // Accumulated string so far
  std::string ss_str(ss_.str());

  // Convert val to string
  std::ostringstream ss;
  ss << val;
  std::string str(ss.str());

  if (str.empty())
  {
    // If accumulated string is empty or ends with a newline
    if (ss_str.empty() || ('\n' == ss_str.back()))
    {
      // Add a space character so a comma will be
      // inserted later if another string is added
      ss_ << ' ';
    }
    else
    {
      // ...otherwise insert a comma to force an empty cell
      ss_ << ',';
    }
  }
  else
  {
    // Insert a comma if the val does not start a new line
    if (!detail::newline(ss_str, str))
    {
      if (!ss_str.empty())
      {
        ss_ << ',';
      }
    }
  }
  ss_ << str;
  return *this;
}

//---------------------------------------------------------------------------

} } // utl::file

#endif // UTL_FILE_CSV_HPP
//===========================================================================//
