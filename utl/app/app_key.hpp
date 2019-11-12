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
/// @brief    Keyboard input.
/// @author   Nathan Lucas
/// @date     2016
//===========================================================================//
#ifndef UTL_APP_KEY_HPP
#define UTL_APP_KEY_HPP

#ifndef __cplusplus
#error must be compiled as C++
#endif

/// @todo Implementations of getch() and kbhit() supporting Linux.
#ifdef _WIN32
# include <conio.h>
#else
# include <termios.h>
# include <unistd.h>
int getch() {}
int kbhit() {}
#endif

#include <chrono>   // std::chrono::milliseconds()
#include <thread>   // std::this_thread::sleep_for()

namespace utl { namespace app {

/// @addtogroup utl_app
/// @{

/// @brief  Get key input.
/// @return Key code integer, or 0 if no key input.
inline int
key()
{
  if (kbhit())
  {
    return getch();  // capture input key
  }
  return 0;
}

/// @brief  Wait for key input.
/// @param  [in]  wait_ms   Sleep duration in milliseconds.
/// @return Key code integer.
/// @note   Blocking call.
inline int
key_wait(unsigned wait_ms)
{
  int key = 0;
  while (!key)
  {
    if (kbhit())
    {
      key = getch();  // capture input key
    }
    std::this_thread::sleep_for(std::chrono::milliseconds(wait_ms));
  }
  return key;
}

/**
 @brief  Wait for specified key input.
 @param  [in]  key_code  Key to wait for.
 @param  [in]  wait_ms   Sleep duration in milliseconds.
 @note   Blocking call.

 To use within a thread, call with arguments:
 ```
 unsigned esc_key = 27;
 unsigned wait_ms = 200;
 std::thread wait_thread(utl::app::key_wait, esc_key, wait_ms);
 ```
 ...or use a lambda expression:
 ```
 // Define arguments within closure
 std::thread wait_thread([]{ utl::app::key_wait(27, 200); });

 // Or capture arguments
 std::thread wait_thread([esc_key, wait_ms]{ utl::app::key_wait(esc_key, wait_ms); });
 ```
*/
inline void
key_wait(int key_code, unsigned wait_ms)
{
  int key = 0;
  while (key != key_code)
  {
    if (kbhit())
    {
      key = getch();  // capture input key
    }
    std::this_thread::sleep_for(std::chrono::milliseconds(wait_ms));
  }
}

/// @}
// utl_app

} } // utl::app

#endif // UTL_APP_WAIT_KEY_HPP
//===========================================================================//
