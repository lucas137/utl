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
/// @brief    TCP connection to client.
/// @author   Nathan Lucas
/// @date     2016
//===========================================================================//
#ifndef UTL_IO_TCP_CONNECTION_HPP
#define UTL_IO_TCP_CONNECTION_HPP

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
#include <memory>       // std::shared_ptr, std::enable_shared_from_this
#include <string>       // std::string
#include <set>          // std::set

//#include <iostream>   // tmp

namespace utl { namespace io { namespace tcp {

// Forward declarations
class connection;
class connection_manager;

//---------------------------------------------------------------------------//
/// @addtogroup utl_asio
/// @{

typedef std::shared_ptr<connection> connection_ptr;

/// Connection to a TCP client.
class connection
: public std::enable_shared_from_this<connection>
{
public:

  using read_handler =
        std::function<void(std::string const&, connection_ptr)>;

  /// Construct a connect.
  /// @param  [in]  socket    Socket for this connection.
  /// @param  [in]  manager   Connection manager for this connection.
  /// @param  [in]  handler   Handler to process received messages.
  connection(asio::ip::tcp::socket socket,
             connection_manager& manager, read_handler& handler);

  /// Returns `true` if the socket is open.
  bool is_open() const;

  /// Start asynchronous operations for this connection.
  void start();

  /// Stop all asynchronous operations for this connection.
  void stop();

  /// Write data to the connection.
  void write(std::string const& str);

private:

  void do_read();   // Perform an asynchronous read.
  void do_write();  // Perform an asynchronous write.

  asio::ip::tcp::socket   socket_;              // Socket for this connection
  connection_manager&     connection_manager_;  // Manager for this connection
  read_handler&           read_handler_;        // To process received messages
  std::array<char, 8192>  read_buffer_;         // Buffer for incoming data
  std::deque<std::string> write_queue_;

};

//typedef std::shared_ptr<connection> connection_ptr;

//---------------------------------------------------------------------------//

/// Manages open connections for the server.
class connection_manager
{
public:

  /// Construct a connection manager.
  connection_manager() {}

  // Prohibit copying and assignment.
  connection_manager(const connection_manager&) = delete;
  connection_manager& operator=(const connection_manager&) = delete;

  //-----------------------------------------------------------
  /// @name Capacity
  /// @{

  /// Returns the number of connections.
  std::size_t
  size() const
  {
    return connections_.size();
  }

  /// @}
  //-----------------------------------------------------------
  /// @name Modifiers
  /// @{

  /// Add the specified connection to the manager and start it.
  void
  start(connection_ptr c)
  {
    connections_.insert(c);
    c->start();
  }

  /// Stop and delete the specified connection.
  void
  stop(connection_ptr c)
  {
    c->stop();
    connections_.erase(c);
  }

  /// Stop and delete all connections.
  void
  stop_all()
  {
    for (auto c : connections_)
    {
      c->stop();
    }
    connections_.clear();
  }

  /// @}
  //-----------------------------------------------------------
  /// @name Connection Access
  /// @{

  /// Write data to a connection.
  void
  write(std::string const& str, connection_ptr const& con)
  {
    con->write(str);
  }

  /// Write data to all connections.
  void
  write(std::string const& str)
  {
    for (auto c : connections_)
    {
      c->write(str);
    }
  }

  /// @}
  //-----------------------------------------------------------

private:

  std::set<connection_ptr> connections_;

};

/// @}

//---------------------------------------------------------------------------//
// Implementation

inline
connection::connection(asio::ip::tcp::socket socket,
    connection_manager& manager, read_handler& handler)
: socket_(std::move(socket))
, connection_manager_(manager)
, read_handler_(handler)
, read_buffer_()
, write_queue_()
{}

inline bool
connection::is_open() const
{
  return socket_.is_open();
}

inline void
connection::start()
{
  do_read();
}

inline void
connection::stop()
{
  if (socket_.is_open())
  {
    // Initiate graceful connection closure.
    // Shutdown both send and receive on the socket.
    asio::error_code ignored_ec;
    socket_.shutdown(asio::ip::tcp::socket::shutdown_both, ignored_ec);
    socket_.close(ignored_ec);
  }
}

inline void
connection::write(std::string const& str)
{
  bool write_in_progress = !write_queue_.empty();
  write_queue_.push_back(str);
  if (!write_in_progress)
  {
    do_write();
  }
}

// private ----------------------------------------------------

inline void
connection::do_read()
{
  auto self(shared_from_this());
  socket_.async_read_some(asio::buffer(read_buffer_),
      [this, self](std::error_code ec, std::size_t bytes_received)
      {
        if (!ec)
        {
          read_handler_(std::string(read_buffer_.begin(),
                                    read_buffer_.begin() + bytes_received),
                        shared_from_this());
          do_read();
        }
        else if (ec != asio::error::operation_aborted)
        {
          connection_manager_.stop(shared_from_this());
        }
      });
}

inline void
connection::do_write()
{
  auto self(shared_from_this());
  asio::async_write(socket_, asio::buffer(write_queue_.front(),
                                          write_queue_.front().size()),
      [this, self](std::error_code ec, std::size_t /*bytes_sent*/)
      {
        if (!ec)
        {
          write_queue_.pop_front();
          if (!write_queue_.empty())
          {
            do_write();
          }
        }
        else if (ec != asio::error::operation_aborted)
        {
          connection_manager_.stop(shared_from_this());
        }
      });
}

//---------------------------------------------------------------------------//
} } } // utl::io::tcp

#endif // UTL_IO_TCP_CONNECTION_HPP
//===========================================================================//
