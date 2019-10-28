/*
Licensed under the MIT License <http://opensource.org/licenses/MIT>

Copyright 2016 Nathan Lucas <nathan.lucas@wayne.edu>

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
/// @brief    JavaScript Object Notation (JSON) utilities.
/// @author   Nathan Lucas
/// @date     2016
//===========================================================================//
#ifndef UTL_JSON_HPP
#define UTL_JSON_HPP

#ifndef __cplusplus
#error must be compiled as C++
#endif

//-----------------------------------------------------------
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wall"

// JSON for Modern C++ (nlohmann-json) is released under MIT license
// (https://github.com/nlohmann/json).
#include <utl/json/nlohmann/json.hpp>

#pragma GCC diagnostic pop
//-----------------------------------------------------------

#include <vector>

/// @defgroup utl_json  json
/// @brief    JSON utility library.
///
/// Utilities for JavaScript Object Notation (JSON) serialization and
/// deserialization.  JSON is an open-standard data-interchange format
/// that is both human- and machine-readable.  It is commonly used for
/// client/server communication in web applications.
///
/// http://json.org/
///
/// This library relies in part on JSON for Modern C++ (nlohmann-json),
/// which is released under MIT license (https://github.com/nlohmann/json).

namespace utl { namespace json {

using nlohmann::json;

/// @addtogroup utl_json
/// @{
//---------------------------------------------------------------------------

template<typename T> bool
is_type(nlohmann::json const& j);

template<> inline bool
is_type<bool>(nlohmann::json const& j)      { return j.is_boolean(); }

template<> inline bool
is_type<int>(nlohmann::json const& j)       { return j.is_number_integer(); }

template<> inline bool
is_type<unsigned>(nlohmann::json const& j)  { return j.is_number_unsigned(); }

template<> inline bool
is_type<float>(nlohmann::json const& j)     { return j.is_number_float(); }

template<> inline bool
is_type<double>(nlohmann::json const& j)    { return j.is_number_float();}

template<> inline bool
is_type<std::string>(nlohmann::json const& j)   { return j.is_string(); }

//---------------------------------------------------------------------------

// bool, int, unsigned, float, double
template<typename T>
inline bool
value(nlohmann::json const& j, std::string const& key, T& val)
{
  if (j.count(key))
  {
    nlohmann::json j_val = j[key];
    if (utl::json::is_type<T>(j_val))
    {
      val = j_val.get<T>();
      return true;
    }
    //else { /* wrong type */ }
  }
  //else { /* key not found */ }
  return false;
}


// JSON array
template<typename T>
inline bool
value(nlohmann::json const& j, std::string const& key, std::vector<T>& val)
{
  if (j.count(key))
  {
    nlohmann::json j_val = j[key];
    if (j_val.is_array())
    {
      val = j_val.get<std::vector<T>>();
      return true;
    }
    //else { /* wrong type */ }
  }
  //else { /* key not found */ }
  return false;
}


//// JSON object
inline bool
value(nlohmann::json const& j, std::string const& key, nlohmann::json& val)
{
  if (j.count(key))
  {
    nlohmann::json obj = j[key];
    if (obj.is_object())
    {
      val = obj;
      return true;
    }
  }
  return false;
}

//---------------------------------------------------------------------------

// JSON for Modern C++ (nlohmann-json) overloads the std::setw
// manipulator to set the indentation for pretty printing
//std::cout << std::setw(4) << j << std::endl;

inline void
print(nlohmann::json const& j)
{
  std::cout << "{\n";
  for (auto it = j.begin(); it != j.end(); ++it)
  {
    if (it.value().is_object())
    {
      std::cout << it.key() << " : ";
      utl::json::print(it.value());   // recursive call
    }
    else
    {
      if (it.value().is_array())
      {
        std::cout << "!";
      }
      std::cout << it.key() << " : " << it.value() << "\n";
    }
  }
  std::cout << "}\n";
}

//---------------------------------------------------------------------------

//// Check enum value_t value.
//using value_t = nlohmann::json::value_t
//if (j.type() == value_t::null) {}            // null value
//if (j.type() == value_t::object) {}          // object (unordered set of name/value pairs)
//if (j.type() == value_t::array) {}           // array (ordered collection of values)
//if (j.type() == value_t::string) {}          // string value
//if (j.type() == value_t::boolean) {}         // boolean value
//if (j.type() == value_t::number_integer) {}  // number value (integer)
//if (j.type() == value_t::number_unsigned) {} // number value (unsigned integer)
//if (j.type() == value_t::number_float) {}    // number value (floating-point)
//if (j.type() == value_t::discarded) {}       // discarded by the the parser callback function


//// nlohmann::json j;
//// json_type_name(j.type());
////
//std::string
//type_name(nlohmann::json::value_t const& type) const noexcept
//{
//  using value_t = nlohmann::json::value_t
//  switch (type)
//  {
//    case value_t::null:             return "null";
//    case value_t::object:           return "object";
//    case value_t::array:            return "array";
//    case value_t::string:           return "string";
//    case value_t::boolean:          return "boolean";
//    case value_t::number_integer:   return "integer"
//    case value_t::number_unsigned:  return "unsigned"
//    case value_t::number_float:     return "float";
//    case value_t::discarded:        return "discarded";
//    default:                        return "unknown";
//  }
//}

//---------------------------------------------------------------------------
/// @}
// utl_json

} } // utl::json

#endif // UTL_JSON_HPP
//===========================================================================//
