/*
Licensed under the MIT License <http://opensource.org/licenses/MIT>

Copyright 2015 Nathan Lucas <nathan.lucas@wayne.edu>

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
/// @brief    Thread-safe concurrent queue library.
/// @details  Header-only library providing a thread-safe concurrent queue
///           built on `std::queue` from C++ standard library `<queue>`.
/// @author   Nathan Lucas
/// @date     2015
//===========================================================================//
#ifndef UTL_QUEUE_HPP
#define UTL_QUEUE_HPP

#ifndef __cplusplus
#error must be compiled as C++
#endif

#include <thread>               // std::thread
#include <mutex>                // std::mutex
#include <condition_variable>   // std::condition_variable
#include <queue>                // std::queue

/// @ingroup  utl_container
/// @defgroup utl_queue   queue
/// @brief    Thread-safe concurrent queue library.
/// @details  Header-only library providing a thread-safe concurrent
///   queue built on `std::queue` from C++ standard library `<queue>`.

namespace utl {

/// @addtogroup utl_queue
/// @{

/// @brief  Thread-safe concurrent queue supporting
///         multiple producers and multiple consumers.
/// @tparam T   Type of elements.
///
template<typename T>
class queue
{
 public:

  /// Constructor.
  /*inline*/
  explicit            // direct initialization only
  queue() = default;

  queue(queue const&) = delete;               ///< Prohibits copying.
  queue& operator=(queue const&) = delete;    ///< Prohibits assignment.


  /// @brief  Test whether the queue is empty
  ///         (i.e., whether its size is zero).
  /// @return `true` if the queue size is zero, otherwise `false`.
  /*inline*/
  bool
  empty() const;

  /// @brief  Returns the number of elements in the queue.
  /// @return The number of elements in the underlying container.
  /*inline*/
  typename std::queue<T>::size_type
  size() const;


  /// @brief  Insert a new element at the end of the queue.
  /// @param  [in]  val   Value to which the inserted element is initialized.
  /*inline*/
  void
  push(T const& val);

  /// @brief  Insert a new element at the end of the queue.
  /// @param  [in]  val   Value to which the inserted element is initialized.
  ///
  /// Accepts rvalue reference to take advantage of move semantics.
  /*inline*/
  void
  push(T&& val);


  /// @brief  Removes the next element in the queue,
  ///         effectively reducing its size by one.
  /// @return A reference to the next element in the queue.
  ///
  /// If the queue is empty, execution is blocked until a new element is added.
  /*inline*/
  T
  pop();

  /// @brief  Removes the next element in the queue,
  ///         effectively reducing its size by one.
  /// @param  [out] val   Returns the next element in the queue.
  ///
  /// If the queue is empty, execution is blocked until a new element is added.
  /*inline*/
  void
  pop(T& val);   // enhanced exception safety over pop()

  /// @brief  Removes the next element in the queue,
  ///         effectively reducing its size by one.
  /// @param  [out] val   Returns the next element in the queue.
  /// @return `true` if an element was popped
  ///         from the queue, otherwise `false`.
  ///
  /// Non-blocking function: returns `true` if the value of
  /// an element was obtained, `false` if the queue is empty.
  /*inline*/
  bool
  try_pop(T& val);


 private:   //---------------------------------------------------------------

  std::queue<T>             queue_{};
  mutable std::mutex        mutex_{};
  std::condition_variable   cv_{};    // requires use of std::unique_lock

};

/// @}
// end group: queue


//===========================================================================//
// Implementation


template<typename T>
inline bool
queue<T>::empty() const
{
  std::unique_lock<std::mutex> lock(mutex_);
  return queue_.empty();
}


template<typename T>
inline typename std::queue<T>::size_type
queue<T>::size() const
{
  std::unique_lock<std::mutex> lock(mutex_);
  return queue_.size();
}


template<typename T>
inline void
queue<T>::push(T const& val)
{
  // unlock before notification to minimize mutex contention
  {
    std::unique_lock<std::mutex> lock(mutex_);  // scope lock
    queue_.push(val);
  }
  // notify one waiting thread that at least one element is in the queue
  cv_.notify_one();
}


// Accepts an rvalue reference to benefit from move semantics
template<typename T>
inline void
queue<T>::push(T&& val)
{
  {
    std::unique_lock<std::mutex> lock(mutex_);  // scope lock
    queue_.push(std::move(val));
  }
  // notify one waiting thread that at least one element is in the queue
  cv_.notify_one();
}


template<typename T>
inline T
queue<T>::pop()
{
  std::unique_lock<std::mutex> lock(mutex_);
  // std::condition_variable can be subject to spurious wakeups, so use the
  // while loop confirms the wakeup was triggered by the awaited condition
  while (queue_.empty())
  {
    cv_.wait(lock);   // release lock and join waiting thread queue
  }
  auto val = queue_.front();
  queue_.pop();
  return val;
}


template<typename T>
inline void
queue<T>::pop(T& val)   // enhanced exception safety over pop()
{
  std::unique_lock<std::mutex> lock(mutex_);
  // std::condition_variable can be subject to spurious wakeups, so use the
  // while loop confirms the wakeup was triggered by the awaited condition
  while (queue_.empty())
  {
    cv_.wait(lock);
  }
  val = queue_.front();
  queue_.pop();
}


template<typename T>
inline bool
queue<T>::try_pop(T& val)
{
  std::unique_lock<std::mutex> lock(mutex_);
  if(queue_.empty())
  {
    return false;
  }
  val = queue_.front();
  queue_.pop();
  return true;
}


} // utl

#endif // UTL_QUEUE_HPP
//===========================================================================//
