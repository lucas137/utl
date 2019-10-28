//===========================================================================//
//  Nathan Lucas
//  2015
//===========================================================================//
#ifndef UTL_TEST_FILE_WRITER_HPP
#define UTL_TEST_FILE_WRITER_HPP

#include <utl/file.hpp>       // utl::file_writer
                              // std::this_thread::sleep_for
#include <utl/chrono.hpp>     // utl::chrono::datetime
#include <utl/string.hpp>     // utl::to_string

#include <string>       // std::string
#include <iostream>     // std::cout, std::endl
#include <sstream>      // std::ostringstream



namespace utl_test {


namespace detail {  //-------------------------------------------------------

void
write_data(utl::file::file_writer& fw, std::string const& name)
{
  for (int i = 0; i != 8; ++i)
  {
    fw.write(name + "," + utl::to_string(i) + "\n");
    std::this_thread::sleep_for(std::chrono::milliseconds(50));
  }
}

} // detail -----------------------------------------------------------------


void
test_file_writer()
{
  std::string date_time(utl::chrono::datetime("_", "", ""));
  std::string file_name("log/file_writer_" + date_time + ".csv");
  std::cout << "test_file_writer: " << file_name << std::endl;


  // Basic use --------------------------------------------------------------

  utl::file::file_writer fw;
  if (!fw.open(file_name))
  {
    std::cout << "ERROR!" << std::endl;
  }
  fw.write("foo,bar\n");


  // Writing different types ------------------------------------------------

  std::ostringstream oss;
  oss << "A" << "," << "a" << "," << "string"               << "\n"
      << 'B' << ',' << 'b' << ',' << "character"            << '\n'
      << (char)0x43 << (char)44   << (char)0x63 << ",char"  << '\n'
      <<                (int)0    << ",int"                 << '\n'
      <<           (unsigned)1    << ",unsigned"            << '\n'
      <<               (long)2    << ",long"                << '\n'
      <<      (unsigned long)3    << ",unsigned long"       << '\n'
      <<          (long long)4    << ",long long"           << '\n'
      << (unsigned long long)5    << ",unsigned long long"  << '\n'
      <<              (float)6.1  << ",float"               << '\n'
      <<             (double)7.1  << ",double"              << '\n';
  fw.write(oss.str());

  fw.write("");
  fw.write('\n');
  fw.write("\n");


  // Multi-threading test ---------------------------------------------------

  std::string label1("thread1");
  std::string label2("thread2");

  // spawn threads
  std::thread data1(detail::write_data, std::ref(fw), std::ref(label1));
  std::thread data2(detail::write_data, std::ref(fw), std::ref(label2));

  // synchronize threads
  data1.join();   // blocks until thread finishes
  data2.join();   // blocks until thread finishes


  // High duty cycle --------------------------------------------------------

  std::string const letters[] = {"A","B","C","D","E","F","G","H"};
  for (int i = 0; i != 256; ++i)
  {
    for (int j = 0; j != 8; ++j)
    {
      fw.write(letters[j]);
      if (j != 7) { fw.write(","); }
    }
    fw.write(); // write a newline character
  }
}


} // utl_test

#endif // UTL_TEST_FILE_WRITER_HPP
//===========================================================================//
