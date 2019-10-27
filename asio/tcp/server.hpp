/*
Licensed under the MIT License <http://opensource.org/licenses/MIT>

Copyright 2016 Nathan Lucas <nathan.lucas@wayne.edu>

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/
//===========================================================================//
/// @file
/// @brief    TCP server.
/// @author   Nathan Lucas
/// @date     2016
//===========================================================================//
#ifndef UTL_IO_TCP_SERVER_HPP
#define UTL_IO_TCP_SERVER_HPP

#ifndef __cplusplus
#error must be compiled as C++
#endif

#include <utl/asio/tcp/connection.hpp>

//-----------------------------------------------------------
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wall"

// The Asio C++ Library is released under Boost Software License.
//  https://think-async.com/Asio/License
//  http://www.boost.org/LICENSE_1_0.txt
#include <asio.hpp>     // Asio library

#pragma GCC diagnostic pop
//-----------------------------------------------------------

#include <string>       // std::string

namespace utl { namespace io { namespace tcp {
/// @addtogroup utl_asio
/// @{

/// TCP server that asynchronously accepts
/// connections, reads data, and writes data.
class server
{
public:

  using read_handler = connection::read_handler;

  /// @brief  Construct a TCP server.
  /// @param  [in]  port    TCP port number.
  /// @param  [in]  handler Callback to process received messages.
  explicit
  server(unsigned short port,
         read_handler handler = [](std::string const&, connection_ptr){})
  : io_service_()
  , work_(io_service_)
  , acceptor_(io_service_, asio::ip::tcp::endpoint(asio::ip::tcp::v4(), port))
  , connections_()
  , socket_(io_service_)
  , handler_(handler)
  {
    // Endpoint to associated with sockets.
    // Will listen on the specified port for IP version 4 (IPv4).
//    asio::ip::tcp::endpoint ep(asio::ip::tcp::v4(), port);
//    // Open the acceptor using the specified protocol.
//    acceptor_.open(ep.protocol());
//    // All the socket to be bound to an address that is already in use.
//    acceptor_.set_option(asio::ip::tcp::acceptor::reuse_address(true));
//    // Bind the acceptor to the specified endpoint.
//    acceptor_.bind(ep);
//    // Place acceptor in state to listen for new connections.
//    acceptor_.listen();
    // Start accepting client connections.
    do_accept();
  }

  /// @brief  Run the server loop.
  ///
  /// The run() function blocks until stop() is called to discontinue
  /// accepting client connections and close all open connections.
  void
  run()
  {
    // io_service::run() will block until all asynchronous
    // operations have finished, including the asynchronous
    // accept call waiting for new incoming connections.
    io_service_.run();
  }

  /// @brief  Stop accepting client connections and close all open connections.
  ///
  /// Cancels all outstanding asynchronous operations.  Once all
  /// operations have finished the io_service::run() call can exit.
  void
  stop()
  {
    acceptor_.close();
    connections_.stop_all();

    // Initiate graceful connection closure.
    // Shutdown both send and receive on the socket.
    asio::error_code ignored_ec;
    socket_.shutdown(asio::ip::tcp::socket::shutdown_both, ignored_ec);
    socket_.close(ignored_ec);
    io_service_.stop();
  }

  /// @brief  Returns the number of open connections.
  std::size_t
  connection_count() const
  {
    return connections_.size();
  }

  /// @brief  Writes the specified data to all open connections.
  void
  write(std::string const& str)
  {
    connections_.write(str);
  }

  /// Get the Asio io_service associated with the object.
  asio::io_service&
  io_service()
  {
    return io_service_;
  }

private:

  // Asynchronously accept client connections.
  void
  do_accept()
  {
    acceptor_.async_accept(socket_,
        [this](std::error_code ec)
        {
          // Verify the server is still running.
          if (!acceptor_.is_open())
          {
            return;
          }
          if (!ec)
          {
            connections_.start(std::make_shared<connection>(
                std::move(socket_), connections_ , handler_));
          }
          do_accept();
        });
  }

  asio::io_service        io_service_;   // To perform asynchronous operations
  asio::io_service::work  work_;         // Inform when work starts & finishes
  asio::ip::tcp::acceptor acceptor_;     // Accepts incoming TCP connections
  connection_manager      connections_;  // Owns all live connections
  asio::ip::tcp::socket   socket_;       // Socket to be accepted
  read_handler            handler_;      // Callback to read messages

};

/// @}
} } } // utl::io::tcp

#endif // UTL_IO_TCP_SERVER_HPP
//===========================================================================//
