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
/// @brief    Application utility library.
/// @author   Nathan Lucas
/// @date     2015
//===========================================================================//
#ifndef UTL_APP_HPP
#define UTL_APP_HPP

#ifndef __cplusplus
#error must be compiled as C++
#endif

/// @defgroup utl_app  app
/// @brief    Application utility library.
/// @details  Header-only library providing application utilities.

//---------------------------------------------------------------------------
/// @namespace  utl::app
/// @brief  Application utility library.
///
/// Header-only library providing application utilities.

#include <utl/app/cli.hpp>
#include <utl/app/app_key.hpp>  // Keyboard input


namespace utl { namespace app {
//---------------------------------------------------------------------------
/// @addtogroup utl_app
/// @{

/// Program arguments.
using Arguments = std::vector<std::string>;

/// @brief  Returns program arguments.
/// @param  [in]  argc  Standard argument count.
/// @param  [in]  argv  Standard argument array.
/// @param  [in]  name  `true` to parse program name.
/// @note   The first argument is the program executable file
///         name @a without the directory path and extension.
inline Arguments
parse_args(int argc, char* argv[], bool name=false)
{
  Arguments args(argv, argv + argc);

  // Optionally parse program file name from path
  if (name)
  {
   #ifdef _WIN32
    std::size_t file = args[0].find_last_of('\\') + 1;
   #else
    std::size_t file = args[0].find_last_of('/') + 1;
   #endif
    std::size_t ext = args[0].find_last_of('.');
    args[0] = args[0].substr(file, ext - file);
  }
  return args;
}

/// @}
//---------------------------------------------------------------------------
} } // utl::app

#endif // UTL_APP_HPP
//===========================================================================//
