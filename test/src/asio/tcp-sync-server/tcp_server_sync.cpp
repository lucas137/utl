//===========================================================================//
//  Nathan Lucas
//  2016
//===========================================================================//

#include <asio.hpp>   // Asio library

#include <iostream>   // std::cout
#include <string>     // std::string

namespace {   //-------------------------------------------------------------

} // anonymous --------------------------------------------------------------

int
main(int argc, char* argv[])
{
  using asio::ip::tcp;
  try
  {
    // Core I/O functionality.
    asio::io_service io_service;

    // We will listen on TCP port 13, for IP version 4 (IPv4).
    tcp::acceptor acceptor(io_service, tcp::endpoint(tcp::v4(), 13));

//    for (;;)
//    {
      // This is an iterative server - it will handle one connection at a time.
      // Create a socket and wait for a connection.
      tcp::socket socket(io_service);
      acceptor.accept(socket);

      // Send message to the client that is accessing this service.
      std::string message = ".";
      asio::error_code ignored_error;
      asio::write(socket, asio::buffer(message), ignored_error);
//    }
  }
  catch (std::exception& e)
  {
    std::cerr << e.what() << std::endl;
  }
  return 0;
}

//===========================================================================//
