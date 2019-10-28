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
/// @brief    Thread-safe file writer.
/// @details  Header-only library providing a thread-safe
///           file writer built on `utl::queue`.
/// @author   Nathan Lucas
/// @version  0.1
/// @date     2015
//===========================================================================//
#ifndef UTL_FILE_WRITER_HPP
#define UTL_FILE_WRITER_HPP

#ifndef __cplusplus
#error must be compiled as C++
#endif

#include <utl/string.hpp>   // utl::to_string
#include <utl/queue.hpp>    // utl::queue

#include <string>         // std::string
#include <fstream>        // std::ofstream
#include <iostream>       // std::cout
#include <atomic>         // std::atomic
#include <thread>

/// @ingroup  utl_file
/// @defgroup utl_file_writer   file_writer
/// @brief    Thread-safe file writer.
/// @details  Header-only library providing a thread-safe
///           file writer built on `utl::queue`.

namespace utl { namespace file {

/// @addtogroup utl_file_writer
/// @{

/// @brief  Thread-safe file writer.
///
class file_writer
{
public:

  /// @brief  Constructor.
  /*inline*/
  explicit          // direct initialization only
  file_writer();

  /// Prohibits copying.
  file_writer(file_writer const&) = delete;

  /// Prohibits assignment.
  file_writer& operator=(file_writer const&) = delete;

  /// Destructor.
  /*inline*/
  ~file_writer();

  /// @brief  Opens @em filename for writing.
  /// @param  [in]  filename  String with the name of the file to open.
  /// @param  [in]  mode      Flags describing the requested
  ///                         output mode for the file.
  /// @return `true` if the file was successfully opened, otherwise `false`.
  /*inline*/
  bool
  open(std::string const& filename, std::ios_base::openmode mode=
                                    std::ios::out|std::ios::app);

  /// @brief  Checks if a file is open.
  /// @return `true` if a file is open, `false` otherwise.
  /*inline*/
  bool
  is_open() const;

  /// @brief  Closes the file.
  /*inline*/
  void
  close();

  /// @brief  Writes a newline (`\n`) character to file.
  /*inline*/
  void
  write();

  /// @brief  Writes data to file.
  /// @tparam T     Type of value.
  /// @param  [in]  val   Data to write to file.
  /*inline*/
  template<typename T>
  void
  write(T const& val);

  /// @brief  Writes data to file.
  /// @param  [in]  str   String to write to file.
  /*inline*/
  void
  write(std::string const& str);

private:

  void loop();    // process data in the queue

  std::ofstream           file_;
  utl::queue<std::string> queue_;
  std::atomic<bool>       open_;
  std::atomic<bool>       loop_;
  std::thread             thread_;

};

/// @}


//===========================================================================//
// Implementation


inline
file_writer::file_writer()
: file_()
, queue_()
, open_(false)
, loop_(false)
, thread_()
{} // do nothing


inline
file_writer::~file_writer()
{
  close();  // stop queue processing loop and close output file
}


// Unfortunately, (some) compilers do not (yet) support ofstream swap.
#undef UTL_FILE_WRITER_OFSTREAM_SWAP
#ifdef UTL_FILE_WRITER_OFSTREAM_SWAP

inline bool
file_writer::open(std::string const& filename, std::ios_base::openmode mode)
{
  if (open_) { return true; }
  std::ofstream tmp_file;     // temporary object
  bool          tmp_open;
  try
  {
    tmp_file.open(filename.c_str(), (mode & ~std::ios::in));  // open file
    tmp_open = tmp_file.is_open();
  }
  catch(...)
  {
    std::cout << "file_writer::open() : error! failed to "
                 "open file \"" << filename << "\"" << std::endl;
    return false;   // tmp_file automatically closed when destroyed
  }
  try
  {
    thread_ = std::thread(&file_writer::loop, this);
  }
  catch(...)
  {
    std::cout << "file_writer::open() : error! exception "
                 "spawning thread" << std::endl;
    return false;
  }
  std::swap(file_, tmp_file);   // swap temporary and member objects
  open_ = tmp_open;
  return open_;
}

#else   // !defined UTL_FILE_WRITER_OFSTREAM_SWAP

// A workaround for ofstream swap not being available is to start the
// thread before opening the file, and rely on member open_=false to
// prevent additions to the queue until after the output file is opened.
inline bool
file_writer::open(std::string const& filename, std::ios_base::openmode mode)
{
  if (open_) { return false; }  // stop here if a file is already open
  bool tmp_open = false;
  try
  {
    file_.open(filename.c_str(), (mode & ~std::ios::in));  // open file
    tmp_open = file_.is_open();
  }
  catch(...)
  {
    std::cout << "file_writer::open() : error! failed to "
                 "open file \"" << filename << "\"" << std::endl;
    return false;
  }
  open_ = tmp_open;

  // If file was successfully opened, start the file writing thread
  if (open_)
  {
    try
    {
      thread_ = std::thread(&file_writer::loop, this);
    }
    catch(...)
    {
      std::cout << "file_writer::open() : error! exception "
                   "spawning thread" << std::endl;
    }
  }
  return open_;
}

#endif  // !defined UTL_FILE_WRITER_OFSTREAM_SWAP


inline bool
file_writer::is_open() const
{
  return open_;
}


inline void
file_writer::close()
{
  if (!open_) { return; }     // file not open
  while (!queue_.empty()) {}  // wait for queue to clear
  loop_ = false;              // signal loop to stop
  queue_.push("");            // trigger one more cycle in loop()
  try { thread_.join(); }     // synchronize thread
  catch(...)
  {
    std::cout << "file_writer::close() : error! "
                 "exception joining thread" << std::endl;
  }
  try { if (file_.is_open()) { file_.close(); } }  // close file
  catch(...)
  {
    std::cout << "file_writer::close() : error! "
                 "exception closing file" << std::endl;
  }
  open_ = file_.is_open();
}


inline void
file_writer::write()
{
  write("\n");
}


template<typename T>
inline void
file_writer::write(T const& val)
{
  if (open_) { queue_.push(utl::to_string(val)); }
}


inline void
file_writer::write(std::string const& str)
{
  if (!str.empty())
  {
    if (open_) { queue_.push(str); }
  }
}


// private ------------------------------------------------------------------

inline void
file_writer::loop()
{
  if (loop_) { return; }
  loop_ = true;
  while (loop_)
  {
    //std::string item = queue_.pop();
    //queue_.pop(item);
    //file_ << item;
    file_ << queue_.pop();
    file_.flush();
  }
}


} } // utl::file

#endif // UTL_FILE_WRITER_HPP
//===========================================================================//
