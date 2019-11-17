//===========================================================================//
//  Nathan Lucas
//  2015
//===========================================================================//
#ifndef UTL_MUTEX_HPP
#define UTL_MUTEX_HPP

//---------------------------------------------------------------------------
// Thread support options
//---------------------------------------------------------------------------

//#define UTL_MUTEX_STD_THREAD
//#define UTL_MUTEX_BOOST_THREAD
#define UTL_MUTEX_MINGW_STD_THREAD


//===========================================================================//

#ifdef UTL_MUTEX_STD_THREAD

//---------------------------------------------------------------------------
// STD Multi-threading
//---------------------------------------------------------------------------

#include <mutex>                // std::mutex

#else
  #ifdef UTL_MUTEX_BOOST_THREAD

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

#include <boost/thread.hpp>     // boost::mutex

namespace std {
typedef boost::mutex                mutex;
}

  #else
    #ifdef UTL_MUTEX_MINGW_STD_THREAD

//---------------------------------------------------------------------------
// mingw-std-threads
//
// Standard C++11 mutex classes, in lieu class missing from MinGW.
// Include <mutex> before <mingw.mutex.h> for STL mutex helper classes.
//---------------------------------------------------------------------------

#include <mutex>                      // std::unique_lock
#include <mingw.mutex.h>              // std::mutex

    #else
      #error Define thread support option
    #endif
  #endif
#endif

#endif // UTL_MUTEX_HPP
//===========================================================================//
