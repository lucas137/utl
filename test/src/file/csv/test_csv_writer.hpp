//===========================================================================//
//  Nathan Lucas
//  2015
//===========================================================================//
#ifndef UTL_TEST_CSV_WRITER_HPP
#define UTL_TEST_CSV_WRITER_HPP

#include <utl/file/file_csv.hpp>  // utl::file::csv_writer,
                                  // utl::file::file_writer,
                                  // std::this_thread::sleep_for

#include <utl/chrono.hpp>         // utl::chrono::datetime

#include <iostream>     //  std::cout, std::endl
#include <string>       //  std::string

namespace utl_test {


namespace detail {  //-------------------------------------------------------

void
write_csv_data(utl::file::file_writer& file, std::string const& name)
{
  for (int i = 0; i != 8; ++i)
  {
    utl::file::csv_writer(file) << name << i << "count\n";
    std::this_thread::sleep_for(std::chrono::milliseconds(50));
  }
}

} // detail -----------------------------------------------------------------


void
test_csv_writer()
{
  std::string datetime(utl::chrono::datetime("_", "", ""));
  std::string filename("log/csv_writer_" + datetime + ".csv");
  std::cout << "test_csv_writer: " << filename << '\n';

  utl::file::file_writer file;
  if (!file.open(filename))
  {
    std::cout << "ERROR!\n";
  }

  utl::file::csv_writer(file) << "foo" << 0 << 1 << '\n';
  utl::file::csv_writer(file) << "foo" << 2 << 3 << '\n';


  // Test multi-threading ---------------------------------------------------

  std::string label1("thread1");
  std::string label2("thread2");

  // spawn threads
  std::thread data1(detail::write_csv_data, std::ref(file), std::ref(label1));
  std::thread data2(detail::write_csv_data, std::ref(file), std::ref(label2));

  // synchronize threads
  data1.join();   // blocks until thread finishes
  data2.join();   // blocks until thread finishes
}


} // utl_test

#endif // UTL_TEST_CSV_WRITER_HPP
//===========================================================================//
