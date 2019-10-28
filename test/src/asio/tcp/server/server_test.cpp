//===========================================================================//
//  Nathan Lucas
//  2016
//===========================================================================//

#include <utl/asio/tcp/server.hpp>  // utl::io::tcp::server
#include <utl/app.hpp>            // utl::app::wait_key()

#include <asio.hpp>   // Asio library

#include <iostream>   // std::cout
#include <string>     // std::string
#include <chrono>     // std::chrono::milliseconds
#include <thread>     // std::thread

namespace {   //-------------------------------------------------------------

void
write(utl::io::tcp::server& server, bool& loop)
{
  while (loop)
  {
    // Send message to the client that is accessing this service.
    std::string message = ".";
    std::cout << message;
    server.write(message);
    std::this_thread::sleep_for(std::chrono::milliseconds(200));
  }
  std::cout << '\n';
}

#define READ_HANDLER_FUNCTION
#define READ_HANDLER_CLASS

#if defined(READ_HANDLER_FUNCTION)
void
read_handler(std::string const& str, utl::io::tcp::connection_ptr con)
{
  std::cout << str;
  con->write("`");
}
#elif defined(READ_HANDLER_CLASS)
class ReadHandler
{
public:
  void callback(std::string const& str, utl::io::tcp::connection_ptr con)
  {
    std::cout << str;
  }
};
#endif

} // anonymous --------------------------------------------------------------

int
main(int argc, char* argv[])
{
  try
  {
    std::cout << "setup" << std::endl;

//    asio::io_service io_service;

  #if defined(READ_HANDLER_FUNCTION)
    // Free function read handler -------------------------------
    utl::io::tcp::server server(13, read_handler);
  #elif defined(READ_HANDLER_CLASS)
    // Class method read handler --------------------------------
    ReadHandler handler;
    utl::io::tcp::server server(13,
        std::bind(&ReadHandler::callback, handler, std::placeholders::_1));
  #else
    // Lambda function read handler -----------------------------
    utl::io::tcp::server server(13,
        [](std::string const& str, utl::io::tcp::connection_ptr con)
        {
          std::cout << str;
        });
  #endif

    std::cout << "run" << std::endl;

    // Run server in its own thread so it operates
    // asynchronously with respect to the rest of the program.
    std::thread server_thread([&server](){ server.run(); });

    bool write_loop = true;
    std::thread write_thread(
        [&server, &write_loop]{ write(server, write_loop); });

    std::thread wait_thread([]{ utl::app::key_wait(27, 200); });

    wait_thread.join();   // Block until thread finishes

    write_loop = false;   // Stop write loop
    write_thread.join();  // Block until thread finishes

    server.stop();          // Close all connections and stop server
    server_thread.join();   // Block until thread finishes

    std::cout << "exit" << std::endl;
  }
  catch (std::exception& e)
  {
    std::cerr << e.what() << std::endl;
  }
  return 0;
}

//===========================================================================//
