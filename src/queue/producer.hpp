//===========================================================================//
//  Concurrent queue code test.
//  Nathan Lucas
//  2015
//===========================================================================//
#ifndef UTL_TEST_PRODUCER_HPP
#define UTL_TEST_PRODUCER_HPP

#include <iostream>       // std::cout
#include <atomic>         // std::atomic
#include <system_error>   // std::system_error

#include "utl/queue.hpp"  // utl::queue, std::thread,
                          // std::this_thread::sleep_for
namespace utl_test {

class Producer
{
public:

  Producer()
  : run_(true)
  , thread_()
  {}

  Producer(Producer const&) = delete;               // disallow copying
  Producer& operator=(Producer const&) = delete;    // disallow assignment

  ~Producer()
  {
    run_ = false;
    try
    {
      thread_.join();
    }
    catch(std::system_error const& e)
    {
      std::cout << "ERROR: exception joining thread";
      if (e.code() == std::errc::invalid_argument)
      { std::cout << ": invalid argument\n"; }
      else if (e.code() == std::errc::no_such_process)
      { std::cout << ": no such process\n"; }
      else if (e.code() == std::errc::resource_deadlock_would_occur)
      { std::cout << ": invalid argument\n"; }
    }
    catch(...) { std::cout << "ERROR: exception joining thread"; }
  }

  void
  run(utl::queue<int>& q)
  {
    thread_ = std::thread(&Producer::loop, this, std::ref(q));
  }

private:

  void
  loop(utl::queue<int>& q)
  {
    for (int i = 5; i >= 0; --i)
    {
      q.push(i);
      std::this_thread::sleep_for(std::chrono::milliseconds(200));
    }
    // send a bunch of zeros just to make sure
    // consumers get the signal to stop processing
    for (int i = 0; i != 10; ++i) { q.push(0); }
  }

  std::atomic<bool> run_;
  std::thread       thread_;

};

} // utl_test

#endif // UTL_TEST_PRODUCER_HPP
//===========================================================================//
