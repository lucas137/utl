//===========================================================================//
/// @file
/// @brief    TCP server.
/// @author   Nathan Lucas
/// @date     2016
//===========================================================================//
#ifndef UTL_IO_TCP_SERVER_HPP
#define UTL_IO_TCP_SERVER_HPP

#include <utl/asio/tcp/detail/message_handler.hpp>
#include <utl/asio/tcp/detail/connection.hpp>

#include <asio.hpp>     // Asio library

#include <string>       // std::string

namespace utl { namespace io { namespace tcp {
/// @addtogroup utl_asio
/// @{

/// TCP server that asynchronously accepts
/// connections, reads data, and writes data.
class server
{
public:

  /// @brief  Construct a TCP server.
  /// @param  [in]  port    TCP port number.
  /// @param  [in]  handler Callback to process received messages.
  explicit
  server(unsigned short port,
         message_handler handler = [](std::string const& str){})
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
  message_handler         handler_;      // Callback to read messages

};

/// @}
} } } // utl::io::tcp

#endif // UTL_IO_TCP_SERVER_HPP
//===========================================================================//
