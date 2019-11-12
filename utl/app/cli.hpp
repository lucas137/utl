/*
Licensed under the MIT License <http://opensource.org/licenses/MIT>

Copyright 2015 Nathan Lucas <nathan.lucas@wayne.edu>

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
/// @brief    Command line interface utilities.
/// @details  Header-only library providing command line interface utilities.
/// @author   Nathan Lucas
/// @date     2015
//===========================================================================//
#ifndef UTL_APP_CLI_HPP
#define UTL_APP_CLI_HPP

#ifndef __cplusplus
#error must be compiled as C++
#endif

#include <string>       //  std::string
#include <vector>       //  std::vector

/// @ingroup  utl_app
/// @defgroup utl_app_cli   app_cli
/// @brief    Command line interface utilities.
/// @details  Header-only library providing command line interface utilities.


/// @namespace utl::cli
/// @brief    Command line interface utilities.
/// @details  Header-only library providing command line interface utilities.

namespace utl { namespace app { namespace cli {

/// @addtogroup utl_app_cli
/// @{


//---------------------------------------------------------------------------
/// @brief  Command line option.
///
class option
{
public:

  // TODO: Document "option specification"

  /// @brief  Creates a command line option.
  /// @param  [in]  option_spec   Option specification.
  /// @param  [in]  description   Description.
  /*inline*/
  option(std::string const& option_spec,
         std::string const& description);

  // Uses default destructor, copy constructor, and assignment operator

  /// @brief  Add a valid argument.
  /// @param  [in]  arg   Argument.
  /// @param  [in]  descr Description.
  /*inline*/
  void
  push_arg(std::string const& arg, std::string const& descr);

  /// @brief  Returns option specification (option[:argument]).
  /// @return Option specification.
  /*inline*/
  std::string
  spec() const;

  /// @brief  Option and argument usage.
  /// @param  [in]  descr_indent  Description indent
  /// @return Usage string
  /*inline*/
  std::string
  usage(int descr_indent) const;

  //-------------------------------------------------------------------

  /// @brief  Checks if string contains matching option.
  /// @param  [in]  str   String to check.
  /// @return `true` if string matches, `false` otherwise.
  /*inline*/
  bool
  match(std::string const& str) const;

  /// @brief  If option matches, returns any accompanying argument.
  /// @param  [in]  str   String to check.
  /// @return Argument.
  /*inline*/
  std::string
  any_arg(std::string const& str) const;

  /// @brief  If option matches, returns the accompanying argument
  ///         if successfully validated (matches a pushed argument).
  /// @param  [in]  str   String to check.
  /// @return Argument.
  /*inline*/
  std::string
  valid_arg(std::string const& str) const;

  //-------------------------------------------------------------------

//private:  // member functions
//  option(option const&);              // prevent copying
//  option& operator=(option const&);   // prevent assignment

private:  // data members
  const std::string opt;      // option
  const std::string arg;      // argument label
  const std::string descr;    // usage description
  std::vector<std::string> valid_args;    // list of valid arguments
  std::vector<std::string> valid_descr;   // argument descriptions
};


//---------------------------------------------------------------------------
/// @name Command Line Interface Functions
/// @{


/// @brief  Constructs a string that repeats a single character.
/// @param  [in]  n   Number of times to repeat
/// @param  [in]  c   Character to repeat
/// @return String of repeating character
inline std::string
separator(int n = 79, char c = '-')
{
  std::string str(n, c);
  return str;
}


/// @brief  Build program usage string for output.
/// @param  [in]  name      Program name
/// @param  [in]  options   Command line options
/// @param  [in]  indent    Number of characters to ident the description
/// @return Usage string
///
/// Example:
/// ```
///   Option h("-h", "show this help message");
///   Option x("-x:N", "option x with argument N");
///   std::vector<Option> options { h, x };
///   std::cout << usage(argv[0], options, 8) << std::endl;
/// ```
/// Output:
///
///     Usage:
///         name  [-h] [-x] [-y:N]
///
///     Options:
///         -h      show this help message
///         -x:N    option x with argument N
///
/*inline*/
std::string
usage(std::string const& name, std::vector<option> const& options, int indent);


/// @}
//---------------------------------------------------------------------------

/// @}

} } } // utl::app::cli


//===========================================================================//
// Implementation

// TODO -- eliminate dependence on std::ostringstream

#include "cli/option.ipp"
#include "cli/usage.ipp"


#endif // UTL_APP_CLI_HPP
//===========================================================================//
