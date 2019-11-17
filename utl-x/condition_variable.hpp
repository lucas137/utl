//===========================================================================//
//  Nathan Lucas
//  2015
//===========================================================================//
#ifndef UTL_CONDITION_VARIABLE_HPP
#define UTL_CONDITION_VARIABLE_HPP

//---------------------------------------------------------------------------
// Thread support options

//#define UTL_CONDITION_VARIABLESTD_THREAD
//#define UTL_CONDITION_VARIABLEBOOST_THREAD
#define UTL_CONDITION_VARIABLEMINGW_STD_THREAD

//---------------------------------------------------------------------------

#ifdef UTL_CONDITION_VARIABLESTD_THREAD

#include <condition_variable>   // std::condition_variable

#else
  #ifdef UTL_CONDITION_VARIABLEBOOST_THREAD

// Search directories
//  Compiler: $(#boost)
//  Linker: $(#boost.lib)
// Link libraries:
//  libboost_system-mgw48-mt-s-1_57
//  libboost_thread-mgw48-mt-s-1_57

#include <boost/thread.hpp>     // boost::mutex, boost::mutex::scoped_lock

namespace std {
typedef boost::condition_variable   condition_variable;
}

  #else
    #ifdef UTL_CONDITION_VARIABLEMINGW_STD_THREAD

// mingw-std-threads
// Standard C++11 condition_variable class, in lieu class missing from MinGW.

#include <mingw.condition_variable.h> // std::condition_variable

    #else
      #error Define thread support option
    #endif
  #endif
#endif
//---------------------------------------------------------------------------

#endif // UTL_CONDITION_VARIABLE_HPP
//===========================================================================//
