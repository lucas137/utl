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
/// @brief    TCP client.
/// @author   Nathan Lucas
/// @date     2016
//===========================================================================//
#ifndef UTL_IO_TCP_CLIENT_HPP
#define UTL_IO_TCP_CLIENT_HPP

#ifndef __cplusplus
#error must be compiled as C++
#endif

//-----------------------------------------------------------
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wall"

// The Asio C++ Library is released under Boost Software License.
//  https://think-async.com/Asio/License
//  http://www.boost.org/LICENSE_1_0.txt
#include <asio.hpp>     // Asio library

#pragma GCC diagnostic pop
//-----------------------------------------------------------

#include <array>        // std::array
#include <deque>        // std::deque
#include <functional>   // std::function
#include <string>       // std::string

namespace utl { namespace io { namespace tcp {

/// @addtogroup utl_asio
/// @{

/// TCP client that asynchronously reads and writes data.
class client
{
public:

  using read_handler =  std::function<void(std::string const&)>;

  /// @brief  Construct a TCP client.
  /// @param  [in]  host    Name or numeric address string.
  /// @param  [in]  service Service name or numeric port number string.
  /// @param  [in]  handler Callback to process received messages.
  explicit
  client(std::string const& host, std::string const& service,
         read_handler handler = [](std::string const&){})
  : io_service_()
  , work_(io_service_)
  , resolver_(io_service_)
  , query_(host, service)
  , socket_(io_service_)
  , read_handler_(handler)
  , read_buffer_()
  , write_queue_()
  {
    do_connect();
//    auto endpoint_iterator = resolver_.resolve(query_);
//    // Create and connect the socket.
//    // asio.connect trys both IPv4 and IPv6
//    // endpoints until it finds one that works.
//    asio::connect(socket_, endpoint_iterator);
//    do_read();
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

  /// @brief  Close connection.
  ///
  /// Cancels all outstanding asynchronous operations.  Once all
  /// operations have finished the io_service::run() call can exit.
  void
  stop()
  {
    io_service_.post(
        [this]()
        {
          // Cancel any asynchronous operations waiting on the resolver.
          resolver_.cancel();
          // Initiate graceful connection closure.
          if (socket_.is_open())
          {
            asio::error_code ignored_ec;
            // Disable send and receive options.
            socket_.shutdown(asio::ip::tcp::socket::shutdown_both, ignored_ec);
            // Close the socket.  Any asynchronous send, receive,
            // or connect operations will be cancelled immediately.
            socket_.close(ignored_ec);
          }
        });
    // Non-blocking call to stop even processing loop.
    io_service_.stop();
  }

  /// @brief  Sends the specified data to the server.
  void
  write(std::string const& str)
  {
    io_service_.post(
        [this, str]()
        {
          if (!socket_.is_open())   // const
          {
            return;   // socket not open
          }

          // Socket may be open but not connected.
          // One option is to use an is_connected_ flag.
          //   http://stackoverflow.com/questions/9920370
          //   http://stackoverflow.com/questions/1511129
          // Here we check for a remote endpoint.
          asio::error_code ec;
          /*asio::ip::tcp::endpoint endpoint =*/
          socket_.remote_endpoint(ec);   // const
          if (ec)
          {
            return;   // no remote endpoint
          }

          bool write_in_progress = !write_queue_.empty();   // const
          write_queue_.push_back(str);
          if (!write_in_progress)
          {
            do_write();
          }
        });
  }

  /// Get the Asio io_service associated with the object.
  asio::io_service&
  io_service()
  {
    return io_service_;
  }

private:

  // Asynchronously establish a socket connection.
  void
  do_connect()
  {
    using asio::ip::tcp;
    asio::error_code ignored_ec;
    socket_.shutdown(tcp::socket::shutdown_both, ignored_ec);
    socket_.close();
    // Get list of endpoints
    resolver_.async_resolve(query_,
        [this](std::error_code ec, tcp::resolver::iterator it)
        {
          if (!ec)
          {
            asio::async_connect(socket_, it,
                [this](std::error_code ec, tcp::resolver::iterator it)
                {
                  if (!ec)
                  {                 // If connected,
                    do_read();      // start receiving data.
                  }
                  else
                  {                 // If not connected,
                    do_connect();   // keep trying to connect.
                  }
                });
          }
        });
  }

  // Perform an asynchronous read.
  void
  do_read()
  {
    socket_.async_read_some(asio::buffer(read_buffer_),
        [this](std::error_code ec, std::size_t bytes_received)
        {
          if (!ec)
          {
            read_handler_(std::string(read_buffer_.begin(),
                                      read_buffer_.begin() + bytes_received));
            do_read();
          }
          else if (ec != asio::error::operation_aborted)
          {
            do_connect();
          }
        });
  }

  // Perform an asynchronous write.
  void
  do_write()
  {
    asio::async_write(socket_,
        asio::buffer(write_queue_.front(), write_queue_.front().size()),
        [this](asio::error_code ec, std::size_t /*bytes_sent*/)
        {
          if (!ec)
          {
            write_queue_.pop_front();
            if (!write_queue_.empty())
            {
              do_write();
            }
          }
          //else if (ec != asio::error::operation_aborted) {}
        });
  }

  asio::io_service                io_service_;
  asio::io_service::work          work_;
  asio::ip::tcp::resolver         resolver_;
  asio::ip::tcp::resolver::query  query_;
  asio::ip::tcp::socket           socket_;

  // /*mutable*/ std::mutex write_mutex;

  read_handler            read_handler_;    // To process received messages
  std::array<char, 8192>  read_buffer_;     // Buffer for incoming data
  std::deque<std::string> write_queue_;

};

/// @}

} } } // utl::io::tcp

#endif // UTL_IO_TCP_CLIENT_HPP
//===========================================================================//
