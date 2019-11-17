//===========================================================================//
//  Nathan Lucas
//  2015
//===========================================================================//
#error DO NOT COMPILE


#include "utl/string.hpp" // utl::string::to_string


namespace utl {


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


} // utl

//===========================================================================//
