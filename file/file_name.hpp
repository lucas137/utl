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
/// @brief    Filename utility library.
/// @details  Header-only library providing filename utilities.
/// @author   Nathan P. Lucas
/// @version  0.1
/// @date     2015
//===========================================================================//
#ifndef UTL_FILENAME_IPP
#define UTL_FILENAME_IPP

#ifndef __cplusplus
#error must be compiled as C++
#endif

#include <string>

/// @ingroup  utl_file
/// @defgroup utl_file_name   file_name
/// @brief    Filename utilities.
/// @details  Header-only library providing filename utilities.

namespace utl { namespace file {
//---------------------------------------------------------------------------
/// @addtogroup utl_file_name
/// @{

//-----------------------------------------------------------
/// @name Filename Functions
/// @{

/// @brief  Parses a file path into its directory,
///         base file name, and extension components.
/// @param  [out] dir   Directory path.
/// @param  [out] file  Base file name.
/// @param  [out] ext   File extension.
/// @param  [in]  path  Full system path.
/*inline*/
void
parse_path(std::string& dir, std::string& file, std::string& ext,
           std::string const& path);

std::string parse_dir(std::string const& path);
std::string parse_file(std::string const& path);
std::string parse_ext(std::string const& path);

/// @brief  Removes the extension, if present, from a file name.
/// @param  [in,out]  file_name   File name with or without extension.
/*inline*/
void
remove_extension(std::string& file_name);

/// @brief  Returns a file name without an extension.
/// @param  [in]  file_name   File name with or without extension.
/// @return File name without extension.
/*inline*/
std::string
without_extension(std::string const& file_name);

/// @}
//-----------------------------------------------------------
/// @class  filename
/// @brief  Filename object, including directory path,
///         base file name, and extension.
class filename
{
public:

  /// @brief  Constructs an empty filename.
  /*inline*/
  filename() = default;
  //: dir_(""), file_(""), ext_("") {}

  /// @brief  Constructs a filename.
  /// @param  [in]  path  Full path (e.g., `D:\data\log.txt`).
  /*inline*/
  filename(std::string const& path)
  //: dir_(""), file_(""), ext_("")
  {
    utl::file::parse_path(dir_, file_, ext_, path);
  }

  /// @brief  Constructs a filename.
  /// @param  [in]  dir   Directory path (e.g., `D:\data\`).
  /// @param  [in]  file  Base file name (e.g., `log`).
  /// @param  [in]  ext   File extension (e.g., `.txt`).
  /*inline*/
  filename(std::string const& dir, std::string const& file,
           std::string const& ext)
  : dir_(dir), file_(file), ext_(ext)
  {}

  /// @brief  Returns the directory path (e.g., `D:\data\`).
  /*inline*/
  std::string
  dir() const                   { return dir_; }

  /// @brief  Sets the directory path (e.g., `D:\data\`).
  /// @param  [in]  val   Directory path.
  /*inline*/
  void
  dir(std::string const& val)   { dir_ = val; }

  /// @brief  Returns the base file name (e.g., `log`).
  /*inline*/
  std::string
  file() const                  { return file_; }

  /// @brief  Sets the base file name (e.g., `log`).
  /// @param  [in]  val   Base file name.
  /*inline*/
  void
  file(std::string const& val)  { file_ = val; }

  /// @brief  Returns the file extension (e.g., `.txt`).
  /*inline*/
  std::string
  ext() const                   { return ext_; }

  /// @brief  Sets file extension (e.g., `.txt`).
  /// @param  [in]  val   File extension.
  /*inline*/
  void
  ext(std::string const& val)   { ext_ = val; }

  /// @brief  Returns the full path (e.g., `D:\data\log.txt`).
  /*inline*/
  std::string
  path() const                  { return (dir_ + file_ + ext_); }

  /// @brief  Sets the full path (e.g., `D:\data\log.txt`).
  /// @param  [in]  val   Full file path.
  /*inline*/
  void
  path(std::string const& val)
  {
    utl::file::parse_path(dir_, file_, ext_, val);
  }


private:
  std::string dir_{};
  std::string file_{};
  std::string ext_{};
};


/// @}


//===========================================================================//
// Implementation

inline void
parse_path(std::string& dir, std::string& file, std::string& ext,
           std::string const& path)
{
  // If no directory delimiter was found, find_last_of() returns
  // std::string::npos (-1), which is incremented to 0 (beginning of string).
  std::size_t file_index = path.find_last_of(PATH_DELIM) + 1;

  // Get the index of the last occurence of the extension delimiter.
  std::size_t ext_index = path.find_last_of('.');

  // If a path delimiter was found, generate a substring that starts
  // at the beginning of path and ends with the last path delimiter.
  if (file_index > 0)
  {
    dir = path.substr(0, file_index);
  }

  // The file substring ends at the extension delimiter,
  // or the end of the string if the delimiter is found.
  file = path.substr(file_index, ext_index - file_index);

  // Confirm an extension delimiter was found
  if (ext_index != std::string::npos)
  {
    // Ignore special cases ..<path_delim> and .<path_delim>
    if (path.substr(ext_index,2) != std::string{'.', PATH_DELIM})
    {
      // The extension substring starts at the last extension delimiter,
      // and includes all remaining characters up to the end of path.
      ext = path.substr(ext_index);
    }
  }
}

inline std::string
parse_dir(std::string const& path)
{
  std::size_t file = path.find_last_of(PATH_DELIM) + 1;
  if (file > 0)
  {
    return path.substr(0, file);
  }
  return std::string();
}

inline std::string
parse_file(std::string const& path)
{
  std::size_t file = path.find_last_of(PATH_DELIM) + 1;
  std::size_t ext  = path.find_last_of('.');
  return path.substr(file, ext - file);
}

inline std::string
parse_ext(std::string const& path)
{
  std::size_t ext  = path.find_last_of('.');
  if (ext != std::string::npos)
  {
    if (path.substr(ext, 2) != std::string{'.', PATH_DELIM})
    {
      return path.substr(ext);
    }
  }
  return std::string();
}

//-----------------------------------------------------------

inline void
remove_extension(std::string& file_name)
{
  // Remove application name extension if present
  size_t index = 0;
  index = file_name.find('.', index);
  if (index != std::string::npos)
  {
    file_name.erase(index);
  }
}

inline std::string
without_extension(std::string const& file_name)
{
  std::string ret(file_name);
  size_t index = 0;
  index = ret.find('.', index);
  if (index != std::string::npos)
  {
    ret.erase(index);
  }
  return ret;
}

//---------------------------------------------------------------------------
} } // utl::file

#endif // UTL_FILENAME_IPP
//===========================================================================//
