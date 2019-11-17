//===========================================================================//
/// @file
/// @brief    TCP connection to client.
/// @author   Nathan Lucas
/// @date     2016
//===========================================================================//
#ifndef UTL_IO_TCP_CONNECTION_HPP
#define UTL_IO_TCP_CONNECTION_HPP

#include <utl/asio/tcp/detail/message_handler.hpp>

#include <asio.hpp>     // Asio library

#include <array>        // std::array
#include <deque>        // std::deque
#include <string>       // std::string
#include <set>          // std::set
#include <memory>       // std::shared_ptr, std::enable_shared_from_this

//#include <iostream>   // tmp

namespace utl { namespace io { namespace tcp {

//---------------------------------------------------------------------------//
/// @addtogroup utl_asio
/// @{

class connection_manager;   // forward declaration

/// Connection to a TCP client.
class connection
: public std::enable_shared_from_this<connection>
{
public:

  /// Construct a connect.
  /// @param  [in]  socket    Socket for this connection.
  /// @param  [in]  manager   Connection manager for this connection.
  /// @param  [in]  handler   Handler to process received messages.
  connection(asio::ip::tcp::socket socket,
             connection_manager& manager, message_handler& handler);

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
  message_handler&        read_handler_;        // To process received messages
  std::array<char, 8192>  read_buffer_;         // Buffer for incoming data
  std::deque<std::string> write_queue_;

};

typedef std::shared_ptr<connection> connection_ptr;

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
    connection_manager& manager, message_handler& handler)
: socket_(std::move(socket))
, connection_manager_(manager)
, read_handler_(handler)
, read_buffer_()
, write_queue_()
{}

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
                                    read_buffer_.begin() + bytes_received));
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
