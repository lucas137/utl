//===========================================================================//
/// \file
/// \brief    Key-value pair utility.
/// \details  Header-only library.
/// \author   Nathan P. Lucas
/// \version  0.1
/// \date     2015
//===========================================================================//
#ifndef UTL_KEYVAL_HPP
#define UTL_KEYVAL_HPP

#include <string>         // std::string
#include <unordered_map>  // std::unordered_map
#include <vector>         // std::vector

namespace utl {


/// \brief  Associative container for key-value pairs with unique keys.
///
class keyvalue
{
public:

  typedef std::unordered_map<std::string, std::string>::size_type size_type;

  /// \brief      Constructs an empty key-value map.
  /// \param[in]  delim     Key-value delimiter.
  /// \param[in]  comment   Comment delimiter.
  ///
  keyvalue(char delim=':', char comment='#')
  : kv_map_()
  , delim_(delim)
  , comment_(comment)
  {}

  /// \brief      Parses \a filename and stores key-value pairs in \a keyval.
  /// \param[in]  filename  File name and path.
  /// \return     \c true if successful, \c false otherwise.
  bool
  operator()(std::string const& filename);

  //-----------------------------------------------------------
  /// \name Capacity
  /// \{

  /// \brief    Tests whether the container is empty.
  /// \details  Returns a \c bool value indicating whether the container
  ///           is empty, i.e. whether its size is \c 0.  This function
  ///           does not modify the content of the container in any way.
  bool
  empty() const     { return kv_map_.empty(); }

  /// \brief    Returns the number of elements in the container.
  /// \returns  The number of elements in the container.
  size_type
  size() const      { return kv_map_.size(); }

  /// \brief    Returns the maximum number of elements the container can hold.
  /// \returns  The maximum number of elements the object can hold as content.
  size_type
  max_size() const  { return kv_map_.max_size(); }

  /// \}
  //-----------------------------------------------------------
  /// \name Element Access
  /// \{

  /// \brief      Searches for \a key and returns the associated value.
  /// \details
  /// Returns the value associated with \a key.  If \a key does not match
  /// any element in the container, the function returns an empty string.
  /// Use \c is_key to check for a match prior to accessing the value.
  ///
  /// \param[in]  key   Search key.
  /// \return     The value associated with \a key.
  std::string
  value(std::string const& key) const
  {
    if (is_key(key))
    {
      return kv_map_.at(key);
    }
    return "";
  }

//  /// \brief    Returns an unordered vector of keys.
//  /// \return   Element keys.
//  std::vector<std::string>
//  keys() const;

//  /// \brief      Search for an element with the specified
//  ///             key and returns the associated value.
//  /// \param[in]  key     Search key.
//  /// \param[out] value   Element value.
//  /// \return     \c true if key was found.
//  bool
//  value(std::string const& key, std::string& value) const;

//  /// \brief    Returns an unordered vector of values.
//  /// \return   Element values.
//  std::vector<std::string>
//  values() const;

  /// \}
  //-----------------------------------------------------------
  /// \name Element Lookup
  /// \{

  /// \brief      Searches for an element whose key is \a k.
  /// \param[in]  k   Search term.
  /// \return     \c true if an element with a key equivalent
  ///             to \a k is found, or \c false otherwise.
  bool
  is_key(std::string const& k) const
  {
    if (kv_map_.count(k) > 0)
    {
      return true;
    }
    return false;
  }

  /// \}
  //-----------------------------------------------------------
  /// \name Access to Underlying Data
  /// \{

  /// \brief    Returns the underlying key-value map.
  /// \return   Key-value map.
  std::unordered_map<std::string, std::string>
  unordered_map() const   { return kv_map_; }

  /// \brief    Returns the key-value pair delimiter.
  /// \returns  Key-value delimiter character.
  char
  delimiter() const   { return delim_; }

  /// \brief    Returns the comment delimiter.
  /// \returns  Comment delimiter character.
  char
  comment() const     { return comment_; }

  /// \}

private:

  std::unordered_map<std::string, std::string> kv_map_;

  char delim_;     // key-value delimiter
  char comment_;   // comment delimiter

};


// Non-member functions -----------------------------------------------------


///// \brief      Returns unordered vectors of keys and values.
///// \param[out] keys    Element keys
///// \param[out] values  Element values
//void
//elements(std::vector<std::string>& keys,
//         std::vector<std::string>& values) const;


///// \brief      Returns a list key-value pairs in left-justified columns,
/////             with whitespace after the keys to align delimiters and values.
///// \relates    utl::keyvalue
///// \return     A newline-separated list of key-value pairs in columns.
//std::string
//column(utl::keyvalue const& kv) const;
//
///// \brief      Returns a list key-value pairs in left-justified columns,
/////             with whitespace after the keys to align delimiters and values.
///// \param[in]  delim   Delimiter to insert between key and value
///// \return     A newline-separated list of key-value pairs in columns.
//std::string
//column(utl::keyvalue const& kv, char delim) const;
//
///// \brief      Returns a list key-value pairs in left-justified columns,
/////             with whitespace after the keys to align delimiters and values.
///// \param[in]  delim   Delimiter to insert between key and value
///// \return     A newline-separated list of key-value pairs in columns.
//std::string
//column(utl::keyvalue const& kv, std::string const& delim) const;


///// \brief    Returns a newline separated list of key-value pairs.
///// \return   A newline-separated list of key-value pairs.
//std::string
//list_str(utl::keyvalue const& kv) const;
//
///// \brief      Returns a newline separated list of key-value pairs.
///// \param[in]  delim   Delimiter to insert between key and value
///// \return     A newline-separated list of key-value pairs.
//std::string
//list_str(utl::keyvalue const& kv, char delim) const;
//
///// \brief      Returns a newline separated list of key-value pairs.
///// \param[in]  delim   Delimiter to insert between key and value
///// \return     A newline-separated list of key-value pairs.
//std::string
//list_str(utl::keyvalue const& kv, std::string const& delim) const;


///// \brief      Returns the size of the longest key string.
///// \return     Size of the longest key string
//size_t
//max_key() const;
//
///// \brief      Returns the sizes of the longest
/////             key string and longest value string.
///// \param[out] key_size    Size of the longest key string
///// \param[out] value_size  Size of the longest value string
//void
//max_size(size_t& key_size, size_t& value_size) const;
//
///// \brief    Returns the size of the longest value string.
///// \return   Size of the longest value string
//size_t
//max_value() const;


} // utl


//===========================================================================//


// Implementation

#include <iostream>       // std::left
#include <iomanip>        // std::setfill, std::setw
#include <fstream>        // std::ifstream
#include <sstream>        // std::istringstream, std::ostringstream

namespace utl {


inline bool
keyvalue::operator()(std::string const& filename)
{
  // Confirm filename is not empty
  if (filename.empty())
  {
    return false;
  }

  std::ifstream keyval_file(filename);

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
    if (std::getline(in_line, key, delim_))
    {
      // Trim leading and trail whitespace; key must contain no whitespace
      std::stringstream trimmer;
      trimmer << key;
      key.clear();
      trimmer >> key;

      // Ignore lines that start with the comment delimiter
      if (key[0] == comment_) { continue; }

      std::string value;

      // Get key value and trim leading whitespace
      if (std::getline(in_line >> std::ws, value))
      {
        // If value exists, record key-value pair
        if (!value.empty())
        {
          kv_map_[key] = value;
        }
      }
    }
  }
  return true;
}


//---------------------------------------------------------------------------


//inline void
//keyvalue::elements(std::vector<std::string>& keys,
//                   std::vector<std::string>& values) const
//{
//  for (auto const& i : kv_map_)
//  {
//    keys.push_back(i.first);
//    values.push_back(i.second);
//  }
//}


//inline std::vector<std::string>
//keyvalue::keys() const
//{
//  std::vector<std::string> keys;
//  for (auto const& i : kv_map_)
//  {
//    keys.push_back(i.first);
//  }
//  return keys;
//}



//inline bool
//keyvalue::value(std::string const& key, std::string& value) const
//{
//  auto it = kv_map_.find(key);
//  if (it == kv_map_.end()) { return false; }   // not found
//  value = it->second;
//  return true;
//}


//inline std::vector<std::string>
//keyvalue::values() const
//{
//  std::vector<std::string> values;
//  for (auto const& i : kv_map_)
//  {
//    values.push_back(i.second);
//  }
//  return values;
//}


//---------------------------------------------------------------------------


//inline std::string
//keyvalue_map::column(utl::keyvalue const& kv) const
//{
//  return column(delim_);
//}
//
//
//inline std::string
//keyvalue_map::column(utl::keyvalue const& kv, char delim) const
//{
//  return column(std::string(1, delim));
//}
//
//
//inline std::string
//keyvalue_map::column(utl::keyvalue const& kv, std::string const& delim) const
//{
//  size_t key_size = max_key();
//
//  std::ostringstream oss;
//  for (auto const& i : kv_map_)
//  {
//    // Output key-value pairs to console, aligning the
//    // delimiter according to the maximum key length
//    oss << std::left << std::setfill(' ')
//        << std::setw(key_size + 1) << i.first
//        << delim << " " << i.second << std::endl;
//  }
//  return oss.str();
//}


//---------------------------------------------------------------------------


//inline std::string
//keyvalue_map::list_str(utl::keyvalue const& kv) const
//{
//  return list_str(delim_);
//}
//
//
//inline std::string
//keyvalue_map::list_str(utl::keyvalue const& kv, char delim) const
//{
//  return list_str(std::string(1, delim));
//}
//
//
//inline std::string
//keyvalue_map::list_str(utl::keyvalue const& kv, std::string const& delim) const
//{
//  std::ostringstream oss;
//  for (auto const& i : kv_map_)
//  {
//    oss << i.first << delim << i.second << std::endl;
//  }
//  return oss.str();
//}


//---------------------------------------------------------------------------


//inline size_t
//keyvalue_map::max_key() const
//{
//  size_t key_size = 0;
//  for (auto const& i : kv_map_)
//  {
//    if (i.first.size() > key_size)
//    {
//      key_size = i.first.size();
//    }
//  }
//  return key_size;
//}
//
//
//inline void
//keyvalue_map::max_size(size_t& key_size, size_t& value_size) const
//{
//  key_size = 0;
//  value_size = 0;
//  for (auto const& i : kv_map_)
//  {
//    if (i.first.size() > key_size)
//    {
//      key_size = i.first.size();
//    }
//    if (i.second.size() > value_size)
//    {
//      value_size = i.second.size();
//    }
//  }
//}
//
//
//inline size_t
//keyvalue_map::max_value() const
//{
//  size_t value_size = 0;
//  for (auto const& i : kv_map_)
//  {
//    if (i.second.size() > value_size)
//    {
//      value_size = i.second.size();
//    }
//  }
//  return value_size;
//}


} // utl

#endif // UTL_KEYVAL_HPP
//===========================================================================//
