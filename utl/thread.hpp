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
/// @brief    Header-only library providing thread utilities.
/// @author   Nathan Lucas
/// @version  0.1
/// @date     2016
//===========================================================================//
#ifndef UTL_THREAD_HPP
#define UTL_THREAD_HPP

#ifndef __cplusplus
#error must be compiled as C++
#endif

#include <thread>       // std::thread, std::this_thread::sleep_for
#include <functional>   // std::function, std::bind
#include <chrono>       // std::chrono::milliseconds
#include <utility>      // std::forward
#include <type_traits>  // std::result_of

/// @defgroup utl_thread  thread
/// @brief    Thread utility library.

namespace utl {

//---------------------------------------------------------------------------//
/// @addtogroup utl_thread
/// @{

/// @brief  Schedule invocation of a callable object and return immediately.
/// Spawns and detaches a thread which blocks @a duration_ms
/// milliseconds before invoking @a f with arguments @a args.
template <typename Callable, typename... Args>
inline void
delay_async(unsigned duration_ms, Callable&& f, Args&&... args)
{
  std::function<typename std::result_of<Callable(Args...)>::type()>
    call(std::bind(std::forward<Callable>(f), std::forward<Args>(args)...));

  std::thread([duration_ms, call]() {
      std::this_thread::sleep_for(std::chrono::milliseconds(duration_ms));
      call();
    }).detach();
}

/// @brief  Schedule and wait for invocation of a callable object.
///
/// Blocks @a duration_ms milliseconds before
/// invoking @a f with arguments @a args.
template <typename Callable, typename... Args>
inline void
delay_sync(unsigned duration_ms, Callable&& f, Args&&... args)
{
  std::function<typename std::result_of<Callable(Args...)>::type()>
    call(std::bind(std::forward<Callable>(f), std::forward<Args>(args)...));

  std::this_thread::sleep_for(std::chrono::milliseconds(duration_ms));
  call();
}

/// @}

} // utl

#endif // UTL_THREAD_HPP
//===========================================================================//
