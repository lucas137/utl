//===========================================================================//
//  Nathan Lucas
//  2015
//===========================================================================//
#ifndef UTL_THREAD_HPP
#define UTL_THREAD_HPP

//---------------------------------------------------------------------------
// Thread support options
//---------------------------------------------------------------------------

//#define UTL_THREAD_STD_THREAD
//#define UTL_THREAD_BOOST_THREAD
#define UTL_THREAD_MINGW_STD_THREAD


//===========================================================================//

#ifdef UTL_THREAD_STD_THREAD

//---------------------------------------------------------------------------
// STD Multi-threading
//---------------------------------------------------------------------------

#include <thread>               // std::thread

#else
  #ifdef UTL_THREAD_BOOST_THREAD

//---------------------------------------------------------------------------
// Boost.Thread
//
//  Search directories
//    Compiler: $(#boost)
//    Linker: $(#boost.lib)
//  Link libraries:
//    libboost_system-mgw48-mt-s-1_57
//    libboost_thread-mgw48-mt-s-1_57
//---------------------------------------------------------------------------

#include <boost/thread.hpp>     // boost::mutex, boost::mutex::scoped_lock

namespace std {
typedef boost::thread               thread;
}

  #else
    #ifdef UTL_THREAD_MINGW_STD_THREAD

//---------------------------------------------------------------------------
// mingw-std-threads
//
// Standard C++11 thread classes, in lieu class missing from MinGW.
// Include <mutex> before <mingw.mutex.h> for STL mutex helper classes.
//---------------------------------------------------------------------------

#include <mingw.thread.h>             // std::thread

    #else
      #error Define thread support option
    #endif
  #endif
#endif

#endif // UTL_THREAD_HPP
//===========================================================================//
