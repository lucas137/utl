/*
Licensed under the MIT License <http://opensource.org/licenses/MIT>

Copyright 2017 Nathan Lucas <nathan.lucas@wayne.edu>

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
/// @brief    File utility library.
/// @details  Header-only library providing file utilities.
/// @author   Nathan Lucas
/// @version  0.3
/// @date     2015
//===========================================================================//
#ifndef UTL_FILE_HPP
#define UTL_FILE_HPP

#ifndef __cplusplus
#error must be compiled as C++
#endif

#include <fstream>    // std::ifstream
#include <sstream>    // std::stringstream
#include <string>     // std::string
#include <io.h>       // mkdir

/// @defgroup utl_file  file
/// @brief    File utility library.
/// @details  Header-only library providing file utilities.

/// @namespace utl::file
/// @brief    File utility library.
/// @details  Header-only library providing file utilities.

namespace utl { namespace file {

/// @addtogroup utl_file
/// @{


/// @var      PATH_DELIM
/// @brief    File path delimiter.
/// @details  The file path delimiter is determined at compile time. @n
/// Platform    | Delimiter
/// ------------|----------------
/// Non-Windows | `\\`
/// Windows     | `/`

#ifdef _WIN32
const char PATH_DELIM = '\\';
#else
const char PATH_DELIM = '/';
#endif


// TODO -- support for parsing CSV files
//---------------------------------------------------------------------------
///// @name File Parse Functions
///// @{
//
//template<typename T>
//bool
//parse(std::vector<T>& values, std::string const& file, char delim);
//
//template<typename T>
//bool
//parse(std::vector<std::vector<T> >& values,
//      std::string const& file, char val_delim, char rec_delim);
//
///// @}
//---------------------------------------------------------------------------

/// @brief  Create a directory if it does not already exist.
inline void
create_directory(std::string const& path)
{
  // Create the directory if it does not exist
  mkdir(path.c_str());
}

/// @brief  Opens a text file and gets the character length of its contents.
///
/// @param  [in]  filename  File path and name.
/// @param  [out] length    Character length of file contents.
/// @return Returns `true` if successful, or `false` if
///   the file does not exist or another error occurs.
inline bool
file_length(std::string const& filename, std::size_t& length)
{
  if (filename.size() == 0) { return false; }
  try
  {
    std::ifstream file(filename, std::ifstream::in);
    if (file.is_open())
    {
      std::stringstream buffer;
      buffer << file.rdbuf();
      length = buffer.str().size();
      return true;
    }
  }
  catch (...) {}  // catch and swallow any exception
  return false;
}

/// @}
// end group: utl_file

} } // utl::file


//===========================================================================//
// Modules

#include <utl/file/file_csv.hpp>
#include <utl/file/file_keyval.hpp>
#include <utl/file/file_log.hpp>
#include <utl/file/file_name.hpp>
#include <utl/file/file_writer.hpp>


#endif // UTL_FILE_HPP
//===========================================================================//
