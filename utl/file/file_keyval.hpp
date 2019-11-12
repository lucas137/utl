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
/// @brief    Key-value file parsing utility library.
/// @details  Header-only library providing key-value file parsing utilities.
/// @author   Nathan Lucas
/// @date     2015
//===========================================================================//
#ifndef UTL_FILE_KEYVAL_HPP
#define UTL_FILE_KEYVAL_HPP

#ifndef __cplusplus
#error must be compiled as C++
#endif

#include <string>         // std::string
#include <fstream>        // std::ifstream
#include <sstream>        // std::istringstream
#include <map>            // std::map
#include <unordered_map>  // std::unordered_map

/// @ingroup  utl_file
/// @defgroup utl_file_keyval   file_keyval
/// @brief    Key-value file parsing utilities.
/// @details  Header-only library providing
///           key-value file parsing utilities.

namespace utl { namespace file {

/// @addtogroup utl_file_keyval
/// @{

//---------------------------------------------------------------------------
/// @name Key-Value File Functions
/// @{


// TODO
///// @brief  Parses @em file and stores key-value pairs in @em keyval.
///// @tparam T         Type of value.
///// @param  [out] keyval    Associative map.
///// @param  [in]  file      File name.
///// @param  [in]  delim     Key-value delimiter.
///// @return `true` if successful, `false` otherwise.
/////
///// Distinguishes keys and values by searching for @em delim.
/////
//template<typename T>
//bool
//parse(std::map<std::string, T>& keyval, std::string const& file, char delim);


/// @brief  Parses @em file and stores key-value pairs in @em keyval.
/// @tparam       T         Type of value.
/// @param  [out] keyval    Associative map.
/// @param  [in]  file      File name.
/// @param  [in]  delim     Key-value delimiter.
/// @param  [in]  comment   Comment delimiter.
/// @return `true` if successful, `false` otherwise.
///
/// Distinguishes keys and values by searching for @em delim.
/// Lines beginning with the @em comment delimiter are ignored.
/*inline*/
template<typename T>
bool
parse(std::map<std::string, T>& keyval,
      std::string const& file, char delim, char comment);


// TODO
///// @brief    Parses @em file and stores key-value pairs in @em keyval.
///// @details  Distinguishes keys and values by searching for @em delim.
///// @tparam       T         Type of value.
///// @param  [out] keyval    Associative map.
///// @param  [in]  file      File name.
///// @param  [in]  delim     Key-value delimiter.
///// @return `true` if successful, `false` otherwise.
/////
//template<typename T>
//bool
//parse(std::unordered_map<std::string, T>& keyval,
//      std::string const& file, char delim);


/// @brief  Parses @em file and stores key-value pairs in @em keyval.
/// @tparam       T         Type of value.
/// @param  [out] keyval    Associative map.
/// @param  [in]  file      File name.
/// @param  [in]  delim     Key-value delimiter.
/// @param  [in]  comment   Comment delimiter.
/// @return `true` if successful, `false` otherwise.
///
/// Distinguishes keys and values by searching for @em delim.
/// Lines beginning with the @em comment delimiter are ignored.
/*inline*/
template<typename T>
bool
parse(std::unordered_map<std::string, T>& keyval,
      std::string const& file, char delim, char comment);


/// @}
//---------------------------------------------------------------------------

/// @}


//===========================================================================//
// Implementation


template<typename T>
inline bool
parse(std::map<std::string, T>& keyval,
      std::string const& file, char delim, char comment)
{
  // Confirm file name is not empty
  if (file.empty())
  {
    return false;
  }

  std::ifstream keyval_file(file);

  // Confirm file was successfully opened
  if (!keyval_file.is_open())
  {
    return false;
  }

  std::string line;

  // Process file line-by-line;
  // std::ws trims leading whitespace and removes empty lines
  while (std::getline(keyval_file >> std::ws, line))
  {
    std::istringstream in_line(line);
    std::string key;
    if (std::getline(in_line, key, delim))
    {
      // Trim leading and trail whitespace; key must contain no whitespace
      std::stringstream trimmer;
      trimmer << key;
      key.clear();
      trimmer >> key;

      // Ignore lines that start with the comment delimiter
      if (key[0] == comment) { continue; }

      std::string value;

      // Get key value and trim leading whitespace
      if (std::getline(in_line >> std::ws, value))
      {
        // If value exists, record key-value pair
        if (!value.empty())
        {
          keyval[key] = value;
        }
      }
    }
  }
  return true;
}


template<typename T>
inline bool
parse(std::unordered_map<std::string, T>& keyval,
      std::string const& file, char delim, char comment)
{
  // Confirm file name is not empty
  if (file.empty())
  {
    return false;
  }

  std::ifstream keyval_file(file);

  // Confirm file was successfully opened
  if (!keyval_file.is_open())
  {
    return false;
  }

  std::string line;

  // Process file line-by-line;
  // std::ws trims leading whitespace and removes empty lines
  while (std::getline(keyval_file >> std::ws, line))
  {
    std::istringstream in_line(line);
    std::string key;
    if (std::getline(in_line, key, delim))
    {
      // Trim leading and trail whitespace; key must contain no whitespace
      std::stringstream trimmer;
      trimmer << key;
      key.clear();
      trimmer >> key;

      // Ignore lines that start with the comment delimiter
      if (key[0] == comment) { continue; }

      std::string value;

      // Get key value and trim leading whitespace
      if (std::getline(in_line >> std::ws, value))
      {
        // If value exists, record key-value pair
        if (!value.empty())
        {
          keyval[key] = value;
        }
      }
    }
  }
  return true;
}


} } // utl::file

#endif // UTL_FILE_KEYVAL_HPP
//===========================================================================//
