//////===========================================================================//
/////// @file
/////// @brief    TCP server.
/////// @author   Nathan Lucas
/////// @date     2016
//////===========================================================================//
////#ifndef UTL_TCP_SERVER_HPP
////#define UTL_TCP_SERVER_HPP
////
////#include <iostream>
////#include <string>
////#include <boost/bind.hpp>
////
////#include <boost/enable_shared_from_this.hpp>
////
////#include <asio.hpp>
////
////namespace utl { namespace asio {
////
/////// @addtogroup utl_asio
/////// @{
////
////
/////*
////  //int port = std::atoi(argv[1]);              // <cstdlib>
////  //unsigned long port = std::stoul(argv[1]);   // <string>
////
////  asio::io_service ios;
////  utl::asio::tcp_server server(ios, 13);
////  nlohmann::json j = json_fast();   // JSON object
////  std::string message = j.dump();   // serialize to string
////  server.write(message);            // blocking call
////*/
////#if 0
////class session
////: public std::enable_shared_from_this<session>
////{
////public:
////  session(tcp::socket socket)
////    : socket_(std::move(socket))
////  {
////  }
////
////  void start()
////  {
////    do_read();
////  }
////
////private:
////  void do_read()
////  {
////    auto self(shared_from_this());
////    socket_.async_read_some(asio::buffer(data_, max_length),
////        [this, self](std::error_code ec, std::size_t length)
////        {
////          if (!ec)
////          {
////            do_write(length);
////          }
////        });
////  }
////
////  void do_write(std::size_t length)
////  {
////    auto self(shared_from_this());
////    asio::async_write(socket_, asio::buffer(data_, length),
////        [this, self](std::error_code ec, std::size_t /*length*/)
////        {
////          if (!ec)
////          {
////            do_read();
////          }
////        });
////  }
////
////  tcp::socket socket_;
////  enum { max_length = 1024 };
////  char data_[max_length];
////};
////#endif
////
////
////class tcp_server
////{
////public:
////
////  /// @brief  ...
////  /// @param  [in]  ios   I/O services.
////  /// @param  [in]  port  TCP port number.
////  tcp_server(asio::io_service& ios, unsigned short port)
////  // Will listen on the specified port for IP version 4 (IPv4).
////  : acceptor_(ios, asio::ip::tcp::endpoint(asio::ip::tcp::v4(), port))
////  , socket_(ios)
////  {
//////    start();
////  }
////
////
////  // Blocking call...
////  void
////  write(std::string const& message)
////  {
////    // This is an iterative server - it will handle one connection at a time.
////    // Wait for a connection.
////    acceptor.accept(socket);          // blocking call
////
////    // Send message to the client that is accessing this service.
////    asio::error_code ignored_error;
////    asio::write(socket, asio::buffer(message), ignored_error);
////  }
////
////private:
////
////  void accept()
////  {
////    acceptor_.async_accept(socket_,
////        [this](std::error_code ec)
////        {
////          if (!ec)
////          {
////            std::make_shared<session>(std::move(socket_))->start();
////          }
////          accept();
////        });
////  }
////
////private:
////  asio::ip::tcp::acceptor_;   // Accepts incoming TCP connections
////  asio::ip::tcp::socket_;     // Stream-oriented socket functionality.
////};
////
////
/////// @}
////// utl_asio
////
////} } // utl::asio
////
////#endif // UTL_TCP_SERVER_HPP
//////===========================================================================//
