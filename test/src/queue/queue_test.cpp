//===========================================================================//
//  Experimental code test.
//  Nathan Lucas
//  2015
//===========================================================================//

#include <iostream>

#include "utl/queue.hpp"  // utl::queue

#include "consumer.hpp"   // utl_test::Consumer
#include "producer.hpp"   // utl_test::Producer

namespace {   //-------------------------------------------------------------

void
produce_items(utl::queue<int>& q)
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


void
consume_items(utl::queue<int>& q)
{
  while (true)
  {
    auto item = q.pop();
    std::cout << "consume_items():" << item << '\n';
    if (!item)
    {
      break;
    }
  }
}

} // anonymous --------------------------------------------------------------


// Test queue with multiple producers and multiple consumers

int
main(int argc, char* argv[])
{
  utl::queue<int> cq;

  // create consumer process
  utl_test::Consumer consumer1;
  consumer1.run(cq);

  // create producer process
  utl_test::Producer producer1;
  producer1.run(cq);

  // spawn additional threads
  std::thread consumer2(consume_items, std::ref(cq));
  std::thread producer2(produce_items, std::ref(cq));

  // synchronize threads
  producer2.join();   // blocks until thread finishes
  consumer2.join();   // blocks until thread finishes

  return 0;
}

//===========================================================================//
