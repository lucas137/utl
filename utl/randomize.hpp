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
/// @brief    Randomizer.
/// @author   Nathan Lucas
/// @date     2016
//===========================================================================//
#ifndef UTL_RANDOMIZE_HPP
#define UTL_RANDOMIZE_HPP

#ifndef __cplusplus
#error must be compiled as C++
#endif

#include <algorithm>      // std::shuffle
#include <chrono>         // std::chrono::system_clock
#include <random>         // std::default_random_engine
#include <vector>         // std::vector

namespace utl {

/// @brief  Randomizes the order of elements in
/// @tparam T   Type of elements.
/// @param  vec Vector to randomize.
template<typename T>
/*inline*/ void
randomize(std::vector<T>& vec)
{
  // time-based seed for random number generator
  unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();

  // random number generator
  auto engine = std::default_random_engine(seed);

  // randomly rearrange elements
  std::shuffle(std::begin(vec), std::end(vec), engine);
}

} // utl

#endif // UTL_RANDOMIZE_HPP
//===========================================================================//
