//===========================================================================//
//  Nathan Lucas
//  2016
//===========================================================================//

#include <utl/app.hpp>  // utl::app::wait_key()

#include <asio.hpp>     // Asio library

#include <array>        // std::array
#include <vector>       // std::vector
#include <iostream>     // std::cout
#include <thread>       // std::thread

namespace {   //-------------------------------------------------------------

void
read(asio::ip::tcp::socket& socket, bool& loop)
{
  while (loop)
  {
    // The buffer must have an initial size, because
    // asio::buffer does not automatically resize it.
    std::array<char, 128> buf;
    asio::error_code ec;

    // Read the response from the connected service.
    std::size_t bytes_received = socket.read_some(asio::buffer(buf), ec);

    // When the server closes the connection, read_some() will exit with
    // the asio::error::eof error, which is how we know to exit the loop.
    if (ec == asio::error::eof)
    {
      std::cout << "\nconnection closed\n";
      break;  // Connection closed cleanly by peer.
    }
    else if (ec)
    {
      throw asio::system_error(ec);  // Some other error.
    }

    // Append buffer to the message.
    //message.insert(message.end(), buf.begin(), buf.begin() + bytes_received);

    std::cout << std::string(buf.begin(), buf.begin() + bytes_received);

    std::string reply = "!";
    std::cout << reply;
    asio::write(socket, asio::buffer(reply, reply.size()), ec);
  }
}

} // anonymous --------------------------------------------------------------

int
main(int argc, char* argv[])
{
  using tcp = asio::ip::tcp;

  try
  {
    std::string host = "127.0.0.1";
    std::string port = "13";
//    if (argc >= 2)
//    {
//      host = argv[1];
//      if (argc == 3)
//      {
//        port = argv[2];
//      }
//    }
//
//    if (argc != 2)
//    {
//      std::cerr << "Usage: tcp_client_sync <host> [<port>]" << std::endl;
//      return 1;
//    }

    std::cout << '\n' << "host : " << host << '\n'
                      << "port : " << port << '\n';

    // Core I/O functionality
    asio::io_service io_service;

    // TCP resolve turns the server name into TCP endpoints
    tcp::resolver resolver(io_service);

    // Get list of endpoints
    // name of the server:  argv[1]
    // name of the service: "daytime"
    tcp::resolver::query query(host, port);
    auto endpoint_iterator = resolver.resolve(query);

    // Create and connect the socket.
    // asio.connect trys both IPv4 and IPv6
    // endpoints until it finds one that works.
    tcp::socket socket(io_service);
    asio::connect(socket, endpoint_iterator);

    bool loop = true;
  #undef WAIT_KEY_THREAD
  //#define WAIT_KEY_THREAD
  #ifdef WAIT_KEY_THREAD
    std::thread read_thread(
        [&socket, &loop]
        {
          read(socket, loop);
        });

    // Use a lambda in order to call wait_key with default arguments
    std::thread wait_thread([]{ utl::app::wait_key(); });

    wait_thread.join();   // Block until thread finishes

    loop = false;
    read_thread.join();  // Block until thread finishes
  #else
    read(socket, loop);
  #endif
  }
  catch (std::exception& e)
  {
    std::cerr << e.what() << std::endl;
  }
  return 0;
}

//===========================================================================//
