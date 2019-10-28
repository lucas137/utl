//===========================================================================//
/// @file
/// @brief    TCP message handler.
/// @author   Nathan Lucas
/// @date     2016
//===========================================================================//
#ifndef UTL_IO_TCP_MESSAGE_HANDLER_HPP
#define UTL_IO_TCP_MESSAGE_HANDLER_HPP

#include <functional>   // std::function
#include <string>       // std::string

namespace utl { namespace io { namespace tcp {

/// @addtogroup utl_asio
/// @{

using message_handler = std::function<void(std::string const&)>;

/// @}

} } } // utl::io::tcp

#endif // UTL_IO_TCP_MESSAGE_HANDLER_HPP
//===========================================================================//
