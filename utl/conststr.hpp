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
/// @brief    ...
/// @author   Nathan Lucas
/// @date     2016
//===========================================================================//
#ifndef UTL_CONSTSTR
#define UTL_CONSTSTR

#ifndef __cplusplus
#error must be compiled as C++
#endif

//#include <iostream>
#include <ostream>    // std::ostream

namespace utl {

/// @brief  constexpr string literal.
class conststr
{
public:
  template<std::size_t N> constexpr
  conststr(const char(&a)[N]) : p_(a), sz_(N - 1) {}

  constexpr char operator[](std::size_t n) const
  {
    return n < sz_? p_[n] : throw std::out_of_range("");
  }

  constexpr std::size_t size() const { return sz_; }

  char const* c_str() const { return p_; }

private:
  const char* p_;
  std::size_t sz_;
};

inline std::ostream&
operator<<(std::ostream& os, conststr const& val)
{
  return os << ((val.size() > 0) ? val.c_str() : "");
}

//constexpr conststr test_request("hello world");

//template<int n>
//struct conststrSize
//{
//  conststrSize() { std::cout << n << '\n'; }
//};
//
//inline void
//conststr_test(eye::tracker::message::conststr const& message)
//{
//  eye::tracker::message::conststrSize<eye::tracker::message::message.size()> test;
//  std::cout << std::string(message.c_str()) << std::endl;
//}

//using request_t = char const[];
//
//constexpr char const* test_request()
//{
//  return "hello world";
//}

} // utl

#endif // UTL_CONSTSTR
//===========================================================================//
