//===========================================================================//
/// @file
/// @brief    Thread-safe concurrent queue library.
/// @details  Header-only library providing a thread-safe concurrent queue
///           built on `std::queue` from C++ standard library `<queue>`.
/// @author   Nathan Lucas
/// @version  0.1
/// @date     2015
//===========================================================================//
#ifndef UTL_QUEUE_HPP
#define UTL_QUEUE_HPP

#ifndef __cplusplus
#error must be compiled as C++
#endif

//---------------------------------------------------------------------------
// Thread support build options

#define UTL_QUEUE_STD_THREAD
//#define UTL_QUEUE_BOOST_THREAD
//#define UTL_QUEUE_MINGW_STD_THREAD

#ifdef UTL_QUEUE_STD_THREAD

#include <thread>               // std::thread
#include <mutex>                // std::mutex
#include <condition_variable>   // std::condition_variable

#else
  #ifdef UTL_QUEUE_BOOST_THREAD

// Search directories
//  Compiler: $(#boost)
//  Linker: $(#boost.lib)
// Link libraries:
//  libboost_system-mgw48-mt-s-1_57
//  libboost_thread-mgw48-mt-s-1_57

#include <boost/thread.hpp>     // boost::mutex, boost::mutex::scoped_lock

namespace std {
typedef boost::mutex                mutex;
typedef boost::condition_variable   condition_variable;
typedef boost::unique_lock          unique_lock;  // ?
     // boost::mutex::scoped_lock ?
}

  #else
    #ifdef UTL_QUEUE_MINGW_STD_THREAD

// mingw-std-threads
// Standard C++11 threading classes, in lieu of those missing from MinGW.
// Include <mutex> before <mingw.mutex.h> for STL mutex helper classes.

#include <mingw.thread.h>             // std::thread
#include <mutex>                      // std::unique_lock
#include <mingw.mutex.h>              // std::mutex
#include <mingw.condition_variable.h> // std::condition_variable

    #else
      #error Define thread support option
    #endif
  #endif
#endif
//---------------------------------------------------------------------------

#include <queue>    // std::queue

/// @defgroup queue   queue
/// @brief    Thread-safe concurrent queue library.
///
/// Header-only library providing a thread-safe concurrent queue
/// built on `std::queue` from C++ standard library `<queue>`.

namespace utl {

/// @addtogroup queue
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
