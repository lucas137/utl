//===========================================================================//
//  Concurrent queue code test.
//  Nathan Lucas
//  2015
//===========================================================================//
#ifndef UTL_TEST_CONSUMER_HPP
#define UTL_TEST_CONSUMER_HPP

#include <iostream>       // std::cout
#include <atomic>         // std::atomic
#include <system_error>   // std::system_error

#include "utl/queue.hpp"  // utl::queue, std::thread

namespace utl_test {

class Consumer
{
public:

  Consumer()
  : run_(true)
  , thread_()
  {}

  Consumer(Consumer const&) = delete;               // disallow copying
  Consumer& operator=(Consumer const&) = delete;    // disallow assignment

  ~Consumer()
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
    thread_ = std::thread(&Consumer::loop, this, std::ref(q));
  }

private:

  void
  loop(utl::queue<int>& q)
  {
    while (run_)
    {
      auto item = q.pop();
      std::cout << "Consumer::loop():" << item << '\n';
      if (!item) { break; }
    }
  }

  std::atomic<bool> run_;
  std::thread       thread_;

};

} // utl_test

#endif // UTL_TEST_CONSUMER_HPP
//===========================================================================//
