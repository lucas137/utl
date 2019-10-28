//===========================================================================//
//  Nathan Lucas
//  2016
//===========================================================================//

#include <utl/asio/tcp/client.hpp>  // utl::io::tcp::server
#include <utl/app.hpp>            // utl::app::wait_key()

#include <asio.hpp>   // Asio library

#include <iostream>   // std::cout
#include <string>     // std::string
#include <chrono>     // std::chrono::milliseconds
#include <thread>     // std::thread

namespace {   //-------------------------------------------------------------

void
write(utl::io::tcp::client& client, bool& loop)
{
  while (loop)
  {
    // Send message to the server.
    std::string message = "!";
    std::cout << message;
    client.write(message);
    std::this_thread::sleep_for(std::chrono::milliseconds(200));
  }
  std::cout << '\n';
}

#define READ_HANDLER_FUNCTION
#define READ_HANDLER_CLASS

#if defined(READ_HANDLER_FUNCTION)
void
read_handler(std::string const& str)
{
  std::cout << str;
}
#elif defined(READ_HANDLER_CLASS)
class ReadHandler
{
public:
  void callback(std::string const& str)
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

    std::string host("127.0.0.1");
    std::string port("13");

  #if defined(READ_HANDLER_FUNCTION)
    // Free function read handler -------------------------------
    utl::io::tcp::client client(host, port, read_handler);
  #elif defined(READ_HANDLER_CLASS)
    // Class method read handler --------------------------------
    ReadHandler handler;
    utl::io::tcp::client client(host, port
        std::bind(&ReadHandler::callback, handler, std::placeholders::_1));
  #else
    // Lambda function read handler -----------------------------
    utl::io::tcp::client client(host, port,
        [](std::string const& str){ std::cout << str; });
  #endif

    std::cout << "run" << std::endl;

    // Run io_service in its own thread so it operates
    // asynchronously with respect to the rest of the program.
    std::thread client_thread([&client](){ client.run(); });

    bool write_loop = true;
    std::thread write_thread(
        [&client, &write_loop]{ write(client, write_loop); });

    std::thread wait_thread([]{ utl::app::key_wait(27, 200); });

    wait_thread.join();   // Block until thread finishes

    write_loop = false;   // Stop write loop
    write_thread.join();  // Block until thread finishes

    client.stop();          // Close all connections and stop client
    client_thread.join();   // Block until thread finishes

    std::cout << "exit" << std::endl;
  }
  catch (std::exception& e)
  {
    std::cerr << e.what() << std::endl;
  }
  return 0;
}

//===========================================================================//
