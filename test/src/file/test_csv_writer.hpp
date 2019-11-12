//===========================================================================//
//  Nathan Lucas
//  2015
//===========================================================================//
#ifndef UTL_TEST_CSV_WRITER_HPP
#define UTL_TEST_CSV_WRITER_HPP

#include "utl/csv_writer.hpp"

#include <iostream>     //  std::cout, std::endl
#include <string>       //  std::string

namespace utl_test {


namespace detail {  //-------------------------------------------------------

void
write_csv_data(utl::file_writer& fw, std::string const& name)
{
  for (int i = 0; i != 8; ++i)
  {
    utl::csv_writer(fw) << name << i << "count\n";
    std::this_thread::sleep_for(std::chrono::milliseconds(50));
  }
}

} // detail -----------------------------------------------------------------


void
test_csv_writer(std::string const& filename)
{
  std::cout << "test_csv_writer: " << filename << std::endl;

  utl::file_writer fw;
  if (!fw.open(filename))
  {
    std::cout << "ERROR!" << std::endl;
  }

  utl::csv_writer(fw) << "foo" << 0 << 1 << '\n';
  utl::csv_writer(fw) << "foo" << 2 << 3 << '\n';


  // Test multi-threading

  std::string label1("thread1");
  std::string label2("thread2");

  // spawn threads
  std::thread data1(detail::write_csv_data, std::ref(fw), std::ref(label1));
  std::thread data2(detail::write_csv_data, std::ref(fw), std::ref(label2));

  // synchronize threads
  data1.join();   // blocks until thread finishes
  data2.join();   // blocks until thread finishes
}


} // utl_test

#endif // UTL_TEST_CSV_WRITER_HPP
//===========================================================================//
