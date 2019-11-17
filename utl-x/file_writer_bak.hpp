//===========================================================================//
/// \brief    File writer.
/// \author   Nathan P. Lucas
/// \version  0.1
/// \date     2015
//===========================================================================//
#ifndef UTL_FILE_WRITER_HPP
#define UTL_FILE_WRITER_HPP

#include <string>         // std::string
#include <fstream>        // std::ofstream
#include <iostream>       // std::cout
#include <atomic>         // std::atomic

#include "utl/string.hpp" // utl::string::to_string
#include "utl/queue.hpp"  // utl::queue, std::thread


// utl::csv_writer
//  use << to automatically insert comma separated values
//  char const utl::csv = '\n';
//
//inline csv_writer&
//operator<<(csv_writer& cw, std::string const& str)
//{
//  if (!str.empty())
//  {
//    if ('\n' != str.back())
//    {
//      cw.file_writer_.write(str + ",");
//    }
//    else
//    {
//      cw.file_writer_.write(str);
//    }
//  }
//  return cw;
//}


namespace utl {

/// \brief  File writer.
///
class file_writer
{
public:

  /// \brief      Constructor.
  /// \param[in]  file  File name.
  explicit                    // direct initialization only
  file_writer();

  /// Prohibits copying.
  file_writer(file_writer const&) = delete;

  /// Prohibits assignment.
  file_writer& operator=(file_writer const&) = delete;

  /// Destructor.
  ~file_writer();

  /// \brief      Open file.
  /// \param[in]  filename  String with the name of the file to open.
  /// \param[in]  mode      Flags describing the requested
  ///                       output mode for the file.
  /// \return     \c true if a file is open, otherwise \c false.
  bool
  open(std::string const& filename, std::ios_base::openmode mode=
                                    std::ios::out|std::ios::app);

  /// \brief  Check if file is open.
  /// \return \c if the file is open, otherwise \c false.
  bool
  is_open() const   { return open_; }

  /// \brief    Close file.
  void
  close();

  /// \brief      Writes data to file (see operator<<).
  /// \param[in]  str   String to write to file.
  void
  write(std::string const& str);

private:

  void loop();    // process data in the queue

  friend file_writer&
  operator<<(file_writer& fw, std::string const& str);

private:

  std::ofstream           file_;
  utl::queue<std::string> queue_;
  std::atomic<bool>       open_;
  std::atomic<bool>       loop_;
  //std::mutex              mutex_;
  std::thread             thread_;

};


//===========================================================================//


///@{
/// \brief  Writes data to file.

inline file_writer&
operator<<(file_writer& fw, std::string const& str)
{
  fw.write(str);
  return fw;
}

template<typename T>
inline
file_writer&
operator<<(file_writer& fw, T const& val)
{
  return (fw << utl::string::to_string(val));
}

inline
file_writer&
operator<<(file_writer& fw, char const* str)
{
  return (fw << std::string(str));
}

inline
file_writer&
operator<<(file_writer& fw, char* val)
{
  return (fw << utl::string::to_string(val));
}

///@}


//===========================================================================//
// Implementation


inline
file_writer::file_writer()
: file_()
, queue_()
, open_(false)
, loop_(false)
//, mutex_()
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
  if (open_) { return true; }
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
  bool tmp_open;
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
  return open_;
}

#endif  // !defined UTL_FILE_WRITER_OFSTREAM_SWAP


inline void
file_writer::close()
{
  if (!open_) { return; }     // file not open
  while (!queue_.empty()) {}  // wait for queue to clear
  loop_ = false;              // signal loop to stop
  write("\n");                // trigger one more cycle in loop
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
file_writer::write(std::string const& str)
{
  if (!str.empty())
  {
    //std::lock_guard<std::mutex> lock(mutex_);
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


} // utl

#endif // UTL_FILE_WRITER_HPP
//===========================================================================//
