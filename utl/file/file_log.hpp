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
/// @brief    Data logger library.
/// @details  Header-only library providing a data logger.
/// @note     Not thread-safe.
/// @author   Nathan Lucas
/// @date     2015
//===========================================================================//
#ifndef UTL_FILE_LOG_HPP
#define UTL_FILE_LOG_HPP

#ifndef __cplusplus
#error must be compiled as C++
#endif

#include <string>         // std::string
#include <iostream>       // std::cout
#include <fstream>        // std::ofstream

/// @ingroup  utl_file
/// @defgroup utl_file_log  file_log
/// @brief    Data logger.
/// @details  Header-only library providing a data logger.

namespace utl { namespace file {

/// @addtogroup utl_file_log
/// @{

//---------------------------------------------------------------------------
/// @brief  Data logger.
/// @note   Not thread-safe.
///
class logfile
{
public:

  /// @brief  Create data logger.
  /// @param  [in]  filename
  /*inline*/
  explicit                            // direct initialization only
  logfile(std::string const& filename)
  : file_(filename.c_str(), std::ios::out | std::ios::app)
  {} // do nothing

  logfile(logfile const&) = delete;             ///< Disallow copying.
  logfile& operator=(logfile const&) = delete;  ///< Disallow assignment.

  /// Destructor.
  /*inline*/
  ~logfile()
  {
    try
    {
      file_.close();
    }
    catch(...)
    {
      std::cout << "ERROR: concurrent_logfile : exception closing file";
    }
  }

  /// @brief  Append data to log file.
  /// @param  [in]  data
  /// @return `0` for success, `-1` for error
  /*inline*/
  int
  append(std::string const& data)
  {
    if (!file_.is_open()) { return -1; }
    file_ << data;
    file_.flush();
    return 0;
  }

private:
  std::ofstream file_;
};

//---------------------------------------------------------------------------

/// @}

} } // utl::file


#endif // UTL_FILE_LOG_HPP
//===========================================================================//
