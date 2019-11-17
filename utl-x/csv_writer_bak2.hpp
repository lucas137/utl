//===========================================================================//
/// \brief    Comma separated value (CSV) file writer.
/// \author   Nathan P. Lucas
/// \version  0.1
/// \date     2015
//===========================================================================//
#ifndef UTL_CSV_WRITER_HPP
#define UTL_CSV_WRITER_HPP

#include <string>         // std::string

#include <utl/file_writer.hpp>


//#include <utl/ostream.hpp>

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


char const csv = '\n';


/// \brief  Comma separated value (CSV) file writer.
///
class csv_writer
{
public:

  /// \brief      Constructor.
  /// \param[in]  file  File name.
  explicit                    // direct initialization only
  csv_writer() = default;

  /// Prohibits copying.
  csv_writer(csv_writer const&) = delete;

  /// Prohibits assignment.
  csv_writer& operator=(csv_writer const&) = delete;

  /// Destructor.
  ~csv_writer() = default;

  /// \brief      Open file.
  /// \param[in]  filename  String with the name of the file to open.
  /// \param[in]  mode      Flags describing the requested
  ///                       output mode for the file.
  /// \return     \c true if a file is open, otherwise \c false.
  bool
  open(std::string const& filename, std::ios_base::openmode mode=
                                    std::ios::out|std::ios::app)
  {
    return file_.open(filename, mode);
  }

  /// \brief  Check if file is open.
  /// \return \c if the file is open, otherwise \c false.
  bool
  is_open() const   { return file_.is_open(); }

  /// \brief    Close file.
  void
  close()  { file_.close(); }


//  /// \brief      Add a value.
//  /// \param[in]  val   Value to add.
//  /// \return     Reference to \c this object.
//  template <typename T>
//  csv_writer& operator<<(T const& val)
//  {
//    // accumulate into non-shared stringstream to avoid threading issues
//    ss_ << val;
//    std::string str = ss_.str();
//    if (!str.empty())
//    {
//      if ('\n' == str.back())
//      {
//        file_.write(str);         // write line to file
//        ss_.str(std::string());   // clear contents of stringstream
//      }
//      else
//      {
//        ss_ << ',';
//      }
//    }
//    return *this;
//  }


private:

  /// \brief      Writes data to file (see operator<<).
  /// \param[in]  str   String to write to file.
  void
  write(std::string const& str)
  {
    if (str.empty())  { return; }
    if ('\n' != str.back())
    {
      file_.write(str + ",");
    }
    else
    {
      file_.write(str);
    }
  }

  friend csv_writer&
  operator<<(csv_writer& cw, std::string const& str);

  std::stringstream ss_;
  utl::file_writer  file_;

};


//===========================================================================//


/// \brief    Acculates output stream values.
/// \details
/// Accumlates values in a temporary stream and writes all values
/// into an output stream when the full_expression is destroyed. \n
/// Example usage:
/// \code
///   accumulate_ostream(std::cout) << val1 << val2 << val3;
/// \endcode
class csv_write
{
public:

  /// \brief      Constructor.
  /// \param[out] os  Output stream which to write accumlated values.
  explicit
  csv_write(utl::csv_writer& cw)
  : cw_(cw)
  , ss_()
  {}

  // stringstream is not copyable, so copies are already forbidden

  /// \brief  Destructor writes accumulated values to the output stream.
  ~csv_write()
  {
//    cw_ << ss_.rdbuf() << std::flush;   // write full expression at once
    cw_ << ss_.str();
  }

  /// \brief      Add a value.
  /// \param[in]  val   Value to add.
  /// \return     Reference to \c this object.
  template <typename T>
  csv_write& operator<<(T const& val)
  {
    // accumulate into non-shared stringstream to avoid threading issues
    ss_ << val;
    return *this;
  }

private:

  utl::csv_writer&   cw_;
  std::stringstream ss_;

};


///@{
/// \brief  Writes data to file.

inline csv_writer&
operator<<(csv_writer& cw, std::string const& str)
{
  cw.write(str);
  return cw;
}

template<typename T>
inline
csv_writer&
operator<<(csv_writer& cw, T const& val)
{
  return (cw << utl::string::to_string(val));
}

inline
csv_writer&
operator<<(csv_writer& cw, char const* str)
{
  return (cw << std::string(str));
}

inline
csv_writer&
operator<<(csv_writer& cw, char* val)
{
  return (cw << utl::string::to_string(val));
}

///@}


} // utl

#endif // UTL_CSV_WRITER_HPP
//===========================================================================//
