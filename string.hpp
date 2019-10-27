//===========================================================================//
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
/// @brief    String utility library.
/// @details  Header-only library providing string utilities.
/// @author   Nathan Lucas
/// @date     2015-2018

/// @defgroup string  string
/// @brief    String utility library.
/// @details  Header-only library providing character string utilities
///   built primarily on C++ standard libraries `string` and `sstream`.
///   This library also includes ASCII utilities.

//===========================================================================//
//
// TODO -- eliminate dependence on std::istringstream and std::ostringstream
//
//#include <iosfwd>       //  std::istringstream
//                        //  std::ostringstream
//                        //  std::stringstream
//#include <sstream>      //  std::istringstream
//                        //  std::ostringstream
//                        //  std::stringstream
//
//===========================================================================//
// Note:  Would prefer C++11 string conversion if available
//        As of 10 Oct 2015, MinGW does not support
//
// Update:  Mingw-w64 supports C++11 string conversion
//
//float              stof(const string& str, size_t* idx = 0);
//double             stod(const string& str, size_t* idx = 0);
//long double        stold(const string& str, size_t* idx = 0);
//int                stoi(const string& str, size_t* idx = 0, int base = 10);
//long               stol(const string& str, size_t* idx = 0, int base = 10);
//unsigned long      stoul(const string& str, size_t* idx = 0, int base = 10);
//long long          stoll(const string& str, size_t* idx = 0, int base = 10);
//unsigned long long stoull(const string& str, size_t* idx = 0, int base = 10);
//===========================================================================//

#ifndef UTL_STRING_HPP
#define UTL_STRING_HPP

#ifndef __cplusplus
#error must be compiled as C++
#endif

#include <utl/string/tuple_string.hpp>

#include <string>       // std::string, std::getline
#include <sstream>      // std::stringstream
                        // std::istringstream, std::ostringstream
#include <vector>       // std::vector
#include <ios>          // std::ios_base, std::dec, std::hex, std::oct
#include <iomanip>      // std::setfill, std::setw

//---------------------------------------------------------------------------
/**
  @namespace  utl::ascii
  @brief  ASCII character utilities.

  ASCII control characters

   DEC |  HEX   | Symbol | Description
  -----|--------|--------|-------------
   `0` | `0x00` | `NUL`  | Null char
   `1` | `0x01` | `SOH`  | Start of Heading
   `2` | `0x02` | `STX`  | Start of Text
   `3` | `0x03` | `ETX`  | End of Text
   `4` | `0x04` | `EOT`  | End of Transmission
   `5` | `0x05` | `ENQ`  | Enquiry
   `6` | `0x06` | `ACK`  | Acknowledgment
   `7` | `0x07` | `BEL`  | Bell
   `8` | `0x08` | `BS`   | Back Space
   `9` | `0x09` | `HT`   | Horizontal Tab
  `10` | `0x0A` | `LF`   | Line Feed
  `11` | `0x0B` | `VT`   | Vertical Tab
  `12` | `0x0C` | `FF`   | Form Feed
  `13` | `0x0D` | `CR`   | Carriage Return
  `14` | `0x0E` | `SO`   | Shift Out / X-On
  `15` | `0x0F` | `SI`   | Shift In / X-Off
  `16` | `0x10` | `DLE`  | Data Line Escape
  `17` | `0x11` | `DC1`  | Device Control 1 (oft\. XON)
  `18` | `0x12` | `DC2`  | Device Control 2
  `19` | `0x13` | `DC3`  | Device Control 3 (oft\. XOFF)
  `20` | `0x14` | `DC4`  | Device Control 4
  `21` | `0x15` | `NAK`  | Negative Acknowledgement
  `22` | `0x16` | `SYN`  | Synchronous Idle
  `23` | `0x17` | `ETB`  | End of Transmit Block
  `24` | `0x18` | `CAN`  | Cancel
  `25` | `0x19` | `EM`   | End of Medium
  `26` | `0x1A` | `SUB`  | Substitute
  `27` | `0x1B` | `ESC`  | Escape
  `28` | `0x1C` | `FS`   | File Separator
  `29` | `0x1D` | `GS`   | Group Separator
  `30` | `0x1E` | `RS`   | Record Separator
  `31` | `0x1F` | `US`   | Unit Separator

  ASCII printable characters

   DEC  |  HEX   | Symbol | Description
  ------|--------|--------|-------------
   `32` | `0x20` |  ` `   | Space
   `33` | `0x21` |  `!`   | Exclamation mark
   `34` | `0x22` | `\"`   | Double quotes (or speech marks)
   `35` | `0x23` | `\#`   | Number
   `36` | `0x24` | `\$`   | Dollar
   `37` | `0x25` | `\%`   | Procenttecken
   `38` | `0x26` | `\&`   | Ampersand
   `39` | `0x27` |  `'`   | Single quote
   `40` | `0x28` |  `(`   | Open parenthesis (or open bracket)
   `41` | `0x29` |  `)`   | Close parenthesis (or close bracket)
   `42` | `0x2A` |  `*`   | Asterisk
   `43` | `0x2B` |  `+`   | Plus
   `44` | `0x2C` |  `,`   | Comma
   `45` | `0x2D` |  `-`   | Hyphen
   `46` | `0x2E` | `\.`   | Period, dot or full stop
   `47` | `0x2F` |  `/`   | Slash or divide
   `48` | `0x30` |  `0`   | Zero
   `49` | `0x31` |  `1`   | One
   `50` | `0x32` |  `2`   | Two
   `51` | `0x33` |  `3`   | Three
   `52` | `0x34` |  `4`   | Four
   `53` | `0x35` |  `5`   | Five
   `54` | `0x36` |  `6`   | Six
   `55` | `0x37` |  `7`   | Seven
   `56` | `0x38` |  `8`   | Eight
   `57` | `0x39` |  `9`   | Nine
   `58` | `0x3A` |  `:`   | Colon
   `59` | `0x3B` |  `;`   | Semicolon
   `60` | `0x3C` | `\<`   | Less than (or open angled bracket)
   `61` | `0x3D` |  `=`   | Equals
   `62` | `0x3E` | `\>`   | Greater than (or close angled bracket)
   `63` | `0x3F` |  `?`   | Question mark
   `64` | `0x40` | `\@`   | At symbol
   `65` | `0x41` |  `A`   | Uppercase A
   `66` | `0x42` |  `B`   | Uppercase B
   `67` | `0x43` |  `C`   | Uppercase C
   `68` | `0x44` |  `D`   | Uppercase D
   `69` | `0x45` |  `E`   | Uppercase E
   `70` | `0x46` |  `F`   | Uppercase F
   `71` | `0x47` |  `G`   | Uppercase G
   `72` | `0x48` |  `H`   | Uppercase H
   `73` | `0x49` |  `I`   | Uppercase I
   `74` | `0x4A` |  `J`   | Uppercase J
   `75` | `0x4B` |  `K`   | Uppercase K
   `76` | `0x4C` |  `L`   | Uppercase L
   `77` | `0x4D` |  `M`   | Uppercase M
   `78` | `0x4E` |  `N`   | Uppercase N
   `79` | `0x4F` |  `O`   | Uppercase O
   `80` | `0x50` |  `P`   | Uppercase P
   `81` | `0x51` |  `Q`   | Uppercase Q
   `82` | `0x52` |  `R`   | Uppercase R
   `83` | `0x53` |  `S`   | Uppercase S
   `84` | `0x54` |  `T`   | Uppercase T
   `85` | `0x55` |  `U`   | Uppercase U
   `86` | `0x56` |  `V`   | Uppercase V
   `87` | `0x57` |  `W`   | Uppercase W
   `88` | `0x58` |  `X`   | Uppercase X
   `89` | `0x59` |  `Y`   | Uppercase Y
   `90` | `0x5A` |  `Z`   | Uppercase Z
   `91` | `0x5B` |  `[`   | Opening bracket
   `92` | `0x5C` | `\\`   | Backslash
   `93` | `0x5D` |  `]`   | Closing bracket
   `94` | `0x5E` |  `^`   | Caret - circumflex
   `95` | `0x5F` |  `_`   | Underscore
   `96` | `0x60` | `\``   | Grave accent
   `97` | `0x61` |  `a`   | Lowercase a
   `98` | `0x62` |  `b`   | Lowercase b
   `99` | `0x63` |  `c`   | Lowercase c
  `100` | `0x64` |  `d`   | Lowercase d
  `101` | `0x65` |  `e`   | Lowercase e
  `102` | `0x66` |  `f`   | Lowercase f
  `103` | `0x67` |  `g`   | Lowercase g
  `104` | `0x68` |  `h`   | Lowercase h
  `105` | `0x69` |  `i`   | Lowercase i
  `106` | `0x6A` |  `j`   | Lowercase j
  `107` | `0x6B` |  `k`   | Lowercase k
  `108` | `0x6C` |  `l`   | Lowercase l
  `109` | `0x6D` |  `m`   | Lowercase m
  `110` | `0x6E` |  `n`   | Lowercase n
  `111` | `0x6F` |  `o`   | Lowercase o
  `112` | `0x70` |  `p`   | Lowercase p
  `113` | `0x71` |  `q`   | Lowercase q
  `114` | `0x72` |  `r`   | Lowercase r
  `115` | `0x73` |  `s`   | Lowercase s
  `116` | `0x74` |  `t`   | Lowercase t
  `117` | `0x75` |  `u`   | Lowercase u
  `118` | `0x76` |  `v`   | Lowercase v
  `119` | `0x77` |  `w`   | Lowercase w
  `120` | `0x78` |  `x`   | Lowercase x
  `121` | `0x79` |  `y`   | Lowercase y
  `122` | `0x7A` |  `z`   | Lowercase z
  `123` | `0x7B` |  `{`   | Opening brace
  `124` | `0x7C` | `\|`   | Vertical bar
  `125` | `0x7D` |  `}`   | Closing brace
  `126` | `0x7E` |  `~`   | Equivalency sign - tilde
  `127` | `0x7F` |  ` `   | Delete

  Extended ASCII codes

   DEC  |  HEX   | Symbol | Description
  ------|--------|--------|-------------
  `128` | `0x80` |  `€`   | Euro sign
  `129` | `0x81` |        |
  `130` | `0x82` |  `‚`   | Single low-9 quotation mark
  `131` | `0x83` |  `ƒ`   | Latin small letter f with hook
  `132` | `0x84` |  `„`   | Double low-9 quotation mark
  `133` | `0x85` |  `…`   | Horizontal ellipsis
  `134` | `0x86` |  `†`   | Dagger
  `135` | `0x87` |  `‡`   | Double dagger
  `136` | `0x88` |  `ˆ`   | Modifier letter circumflex accent
  `137` | `0x89` |  `‰`   | Per mille sign
  `138` | `0x8A` |  `Š`   | Latin capital letter S with caron
  `139` | `0x8B` |  `‹`   | Single left-pointing angle quotation
  `140` | `0x8C` |  `Œ`   | Latin capital ligature OE
  `141` | `0x8D` |        |
  `142` | `0x8E` |  `Ž`   | Latin captial letter Z with caron
  `143` | `0x8F` |        |
  `144` | `0x90` |        |
  `145` | `0x91` |  `‘`   | Left single quotation mark
  `146` | `0x92` |  `’`   | Right single quotation mark
  `147` | `0x93` |  `“`   | Left double quotation mark
  `148` | `0x94` |  `”`   | Right double quotation mark
  `149` | `0x95` |  `•`   | Bullet
  `150` | `0x96` |  `–`   | En dash
  `151` | `0x97` |  `—`   | Em dash
  `152` | `0x98` |  `˜`   | Small tilde
  `153` | `0x99` |  `™`   | Trade mark sign
  `154` | `0x9A` |  `š`   | Latin small letter S with caron
  `155` | `0x9B` |  `›`   |  Single right-pointing angle quotation mark
  `156` | `0x9C` |  `œ`   | Latin small ligature oe
  `157` | `0x9D` |        |
  `158` | `0x9E` |  `ž`   | Latin small letter z with caron
  `159` | `0x9F` |  `Ÿ`   | Latin capital letter Y with diaeresis
  `160` | `0xA0` |  ` `   | Non-breaking space
  `161` | `0xA1` |  `¡`   | Inverted exclamation mark
  `162` | `0xA2` |  `¢`   | Cent sign
  `163` | `0xA3` |  `£`   | Pound sign
  `164` | `0xA4` |  `¤`   | Currency sign
  `165` | `0xA5` |  `¥`   | Yen sign
  `166` | `0xA6` |  `¦`   | Pipe, Broken vertical bar
  `167` | `0xA7` |  `§`   | Section sign
  `168` | `0xA8` |  `¨`   | Spacing diaeresis - umlaut
  `169` | `0xA9` |  `©`   | Copyright sign
  `170` | `0xAA` |  `ª`   | Feminine ordinal indicator
  `171` | `0xAB` |  `«`   | Left double angle quotes
  `172` | `0xAC` |  `¬`   | Not sign
  `173` | `0xAD` |  `­`   | Soft hyphen
  `174` | `0xAE` |  `®`   | Registered trade mark sign
  `175` | `0xAF` |  `¯`   | Spacing macron - overline
  `176` | `0xB0` |  `°`   | Degree sign
  `177` | `0xB1` |  `±`   | Plus-or-minus sign
  `178` | `0xB2` |  `²`   | Superscript two - squared
  `179` | `0xB3` |  `³`   | Superscript three - cubed
  `180` | `0xB4` |  `´`   | Acute accent - spacing acute
  `181` | `0xB5` |  `µ`   | Micro sign
  `182` | `0xB6` |  `¶`   | Pilcrow sign - paragraph sign
  `183` | `0xB7` |  `·`   | Middle dot - Georgian comma
  `184` | `0xB8` |  `¸`   | Spacing cedilla
  `185` | `0xB9` |  `¹`   | Superscript one
  `186` | `0xBA` |  `º`   | Masculine ordinal indicator
  `187` | `0xBB` |  `»`   | Right double angle quotes
  `188` | `0xBC` |  `¼`   | Fraction one quarter
  `189` | `0xBD` |  `½`   | Fraction one half
  `190` | `0xBE` |  `¾`   | Fraction three quarters
  `191` | `0xBF` |  `¿`   | Inverted question mark
  `192` | `0xC0` |  `À`   | Latin capital letter A with grave
  `193` | `0xC1` |  `Á`   | Latin capital letter A with acute
  `194` | `0xC2` |  `Â`   | Latin capital letter A with circumflex
  `195` | `0xC3` |  `Ã`   | Latin capital letter A with tilde
  `196` | `0xC4` |  `Ä`   | Latin capital letter A with diaeresis
  `197` | `0xC5` |  `Å`   | Latin capital letter A with ring above
  `198` | `0xC6` |  `Æ`   | Latin capital letter AE
  `199` | `0xC7` |  `Ç`   | Latin capital letter C with cedilla
  `200` | `0xC8` |  `È`   | Latin capital letter E with grave
  `201` | `0xC9` |  `É`   | Latin capital letter E with acute
  `202` | `0xCA` |  `Ê`   | Latin capital letter E with circumflex
  `203` | `0xCB` |  `Ë`   | Latin capital letter E with diaeresis
  `204` | `0xCC` |  `Ì`   | Latin capital letter I with grave
  `205` | `0xCD` |  `Í`   | Latin capital letter I with acute
  `206` | `0xCE` |  `Î`   | Latin capital letter I with circumflex
  `207` | `0xCF` |  `Ï`   | Latin capital letter I with diaeresis
  `208` | `0xD0` |  `Ð`   | Latin capital letter ETH
  `209` | `0xD1` |  `Ñ`   | Latin capital letter N with tilde
  `210` | `0xD2` |  `Ò`   | Latin capital letter O with grave
  `211` | `0xD3` |  `Ó`   | Latin capital letter O with acute
  `212` | `0xD4` |  `Ô`   | Latin capital letter O with circumflex
  `213` | `0xD5` |  `Õ`   | Latin capital letter O with tilde
  `214` | `0xD6` |  `Ö`   | Latin capital letter O with diaeresis
  `215` | `0xD7` |  `×`   | Multiplication sign
  `216` | `0xD8` |  `Ø`   | Latin capital letter O with slash
  `217` | `0xD9` |  `Ù`   | Latin capital letter U with grave
  `218` | `0xDA` |  `Ú`   | Latin capital letter U with acute
  `219` | `0xDB` |  `Û`   | Latin capital letter U with circumflex
  `220` | `0xDC` |  `Ü`   | Latin capital letter U with diaeresis
  `221` | `0xDD` |  `Ý`   | Latin capital letter Y with acute
  `222` | `0xDE` |  `Þ`   | Latin capital letter THORN
  `223` | `0xDF` |  `ß`   | Latin small letter sharp s - ess-zed
  `224` | `0xE0` |  `à`   | Latin small letter a with grave
  `225` | `0xE1` |  `á`   | Latin small letter a with acute
  `226` | `0xE2` |  `â`   | Latin small letter a with circumflex
  `227` | `0xE3` |  `ã`   | Latin small letter a with tilde
  `228` | `0xE4` |  `ä`   | Latin small letter a with diaeresis
  `229` | `0xE5` |  `å`   | Latin small letter a with ring above
  `230` | `0xE6` |  `æ`   | Latin small letter ae
  `231` | `0xE7` |  `ç`   | Latin small letter c with cedilla
  `232` | `0xE8` |  `è`   | Latin small letter e with grave
  `233` | `0xE9` |  `é`   | Latin small letter e with acute
  `234` | `0xEA` |  `ê`   | Latin small letter e with circumflex
  `235` | `0xEB` |  `ë`   | Latin small letter e with diaeresis
  `236` | `0xEC` |  `ì`   | Latin small letter i with grave
  `237` | `0xED` |  `í`   | Latin small letter i with acute
  `238` | `0xEE` |  `î`   | Latin small letter i with circumflex
  `239` | `0xEF` |  `ï`   | Latin small letter i with diaeresis
  `240` | `0xF0` |  `ð`   | Latin small letter eth
  `241` | `0xF1` |  `ñ`   | Latin small letter n with tilde
  `242` | `0xF2` |  `ò`   | Latin small letter o with grave
  `243` | `0xF3` |  `ó`   | Latin small letter o with acute
  `244` | `0xF4` |  `ô`   | Latin small letter o with circumflex
  `245` | `0xF5` |  `õ`   | Latin small letter o with tilde
  `246` | `0xF6` |  `ö`   | Latin small letter o with diaeresis
  `247` | `0xF7` |  `÷`   | Division sign
  `248` | `0xF8` |  `ø`   | Latin small letter o with slash
  `249` | `0xF9` |  `ù`   | Latin small letter u with grave
  `250` | `0xFA` |  `ú`   | Latin small letter u with acute
  `251` | `0xFB` |  `û`   | Latin small letter u with circumflex
  `252` | `0xFC` |  `ü`   | Latin small letter u with diaeresis
  `253` | `0xFD` |  `ý`   | Latin small letter y with acute
  `254` | `0xFE` |  `þ`   | Latin small letter thorn
  `255` | `0xFF` |  `ÿ`   | Latin small letter y with diaeresis
  */
namespace utl { namespace ascii {

/// @addtogroup string
/// @{

/// ASCII control characters.
enum class control : unsigned char
{
  NUL = 0x00,   ///< Null character.
  SOH = 0x01,   ///< Start of Heading.
  STX = 0x02,   ///< Start of Text.
  ETX = 0x03,   ///< End of Text.
  EOT = 0x04,   ///< End of Transmission.
  ENQ = 0x05,   ///< Enquiry.
  ACK = 0x06,   ///< Acknowledgment.
  BEL = 0x07,   ///< Bell.
  BS  = 0x08,   ///< Back Space.
  HT  = 0x09,   ///< Horizontal Tab.
  LF  = 0x0A,   ///< Line Feed.
  VT  = 0x0B,   ///< Vertical Tab.
  FF  = 0x0C,   ///< Form Feed.
  CR  = 0x0D,   ///< Carriage Return.
  SO  = 0x0E,   ///< Shift Out / X-On.
  SI  = 0x0F,   ///< Shift In / X-Off.
  DLE = 0x10,   ///< Data Line Escape.
  DC1 = 0x11,   ///< Device Control 1 (oft\. XON).
  DC2 = 0x12,   ///< Device Control 2.
  DC3 = 0x13,   ///< Device Control 3 (oft\. XOFF).
  DC4 = 0x14,   ///< Device Control 4.
  NAK = 0x15,   ///< Negative Acknowledgement.
  SYN = 0x16,   ///< Synchronous Idle.
  ETB = 0x17,   ///< End of Transmit Block.
  CAN = 0x18,   ///< Cancel.
  EM  = 0x19,   ///< End of Medium.
  SUB = 0x1A,   ///< Substitute.
  ESC = 0x1B,   ///< Escape.
  FS  = 0x1C,   ///< File Separator.
  GS  = 0x1D,   ///< Group Separator.
  RS  = 0x1E,   ///< Record Separator.
  US  = 0x1F    ///< Unit Separator.
};

/// Returns `true` if `val` corresponds to an ASCII control character.
inline bool
is_control(int val)
{
  return (val >= 0x00) && (val <= 0x1F);
}

/// Returns `true` if `val` corresponds to an extended ASCII character.
inline bool
is_extended(int val)
{
  return (val >= 0x80) && (val <= 0xFF);
}

/// Returns `true` if `val` corresponds to an ASCII printable character.
inline bool
is_printable(int val)
{
  return (val >= 0x20) && (val <= 0x7F);
}

/// @brief  Convert an ASCII-encoded digit to the integer value it represents.
/// @param  [in]  c   ASCII encoded digit.
/// @return Integer value from `0`-`9`, or `-1` if @a c
///         does not represent an ASCII-encoded digit.
inline int
to_int(char const& c)
{
  int n(c);
  n -= 0x30;
  if (n < 0 || n > 9) { return -1; }
  return n;
}

/// ASCII control characters.
inline std::string
to_string(unsigned char val)
{
  return
    (val == 0x00) ? "NUL" :  (val == 0x01) ? "SOH" :  (val == 0x02) ? "STX" :
    (val == 0x03) ? "ETX" :  (val == 0x04) ? "EOT" :  (val == 0x05) ? "ENQ" :
    (val == 0x06) ? "ACK" :  (val == 0x07) ? "BEL" :  (val == 0x08) ? "BS"  :
    (val == 0x09) ? "HT"  :  (val == 0x0A) ? "LF"  :  (val == 0x0B) ? "VT"  :
    (val == 0x0C) ? "FF"  :  (val == 0x0D) ? "CR"  :  (val == 0x0E) ? "SO"  :
    (val == 0x0F) ? "SI"  :  (val == 0x10) ? "DLE" :  (val == 0x11) ? "DC1" :
    (val == 0x12) ? "DC2" :  (val == 0x13) ? "DC3" :  (val == 0x14) ? "DC4" :
    (val == 0x15) ? "NAK" :  (val == 0x16) ? "SYN" :  (val == 0x17) ? "ETB" :
    (val == 0x18) ? "CAN" :  (val == 0x19) ? "EM"  :  (val == 0x1A) ? "SUB" :
    (val == 0x1B) ? "ESC" :  (val == 0x1C) ? "FS"  :  (val == 0x1D) ? "GS"  :
    (val == 0x1E) ? "RS"  :  (val == 0x1F) ? "US"  :  (val == 0x7F) ? "DEL" :
    std::string(1, val);  // char to string
};

/// @}

} } // utl::ascii

//---------------------------------------------------------------------------

namespace utl {

/// @addtogroup string
/// @{

//---------------------------------------------------------------------------
/// @name String to Boolean
/// @{

/// @brief  Convert a std::string to type bool.
/// @param  [in]  str   String describing a Boolean value.
/// @return `true` if string equals "true", "TRUE", or "1";
///         `false` otherwise.
inline bool
to_bool(std::string const& str)
{
  if (str == "true" || str == "TRUE" || str == "1")
  {
    return true;
  }
  return false;
}

/// @brief  Converts a std::string to a Boolean vaue.  The
///         output variable is unchanged if an error occurs.
/// @param  [out] val   Boolean value.
/// @param  [in]  str   String encoded numeric value.
/// @return `true` if successful, `false` if an error occurred.
inline bool
to_bool(bool& val, std::string const& str)
{
  if (str == "true" || str == "TRUE" || str == "1")
  {
    val = true;
    return true;
  }
  if (str == "false" || str == "FALSE" || str == "0")
  {
    val = false;
    return true;
  }
  return false;
}

/// @}
//---------------------------------------------------------------------------
/// @name String to Number
/// @{

/// @brief  Converts a std::string to a number.
/// @tparam       T     Type of value.
/// @param  [in]  str   String encoded numeric value.
/// @param  [in]  flg   Format flags (e.g., std::dec, std::hex).
/// @return Numeric value, or `0` for error.
template<typename T>
inline T
to_number(std::string const& str,
          std::ios_base& (*flg)(std::ios_base&)=std::dec)
{
  std::istringstream ss(str);
  T val;
  return (ss >> flg >> val) ? val : 0;
}

/// @brief  Converts a std::string to a number.
/// @tparam       T     Type of value.
/// @param  [out] val   Numeric value.
/// @param  [in]  str   String encoded numeric value.
/// @param  [in]  flg   Format flags (e.g., std::dec, std::hex).
/// @return     `true` if successful, `false` if an error occurred.
///
/// The output variable is unchanged if an error occurs.
template<typename T>
inline bool
to_number(T& val, std::string const& str,
          std::ios_base& (*flg)(std::ios_base&)=std::dec)
{
  std::istringstream iss(str);
  T tmp;
  if ((iss >> flg >> tmp).fail())
  {
    return false;
  }
  val = tmp;
  return true;
}

// Template specializations ............

// unsigned up to 2,147,483,647 (0x7FFFFFFF)
template<>
inline bool
to_number<unsigned>(unsigned& val, std::string const& str,
                    std::ios_base& (*flg)(std::ios_base&))
{
  std::istringstream iss(str);
  unsigned tmp;
  if ((iss >> flg >> tmp).fail())
  {
    return false;
  }
  // Check for conversion of a negative number
  if (tmp & 0x80000000)
  {
    return false;
  }
  val = tmp;
  return true;
}

// unsigned long up to 4,294,967,295 (0xFFFFFFFF)
template<>
inline bool
to_number<unsigned long>(unsigned long& val, std::string const& str,
                         std::ios_base& (*flg)(std::ios_base&))
{
  std::istringstream iss(str);
  unsigned long tmp;
  if ((iss >> flg >> tmp).fail())
  {
    return false;
  }
  // Check for conversion of a negative number
  if (tmp & 0x100000000)
  {
    return false;
  }
  val = tmp;
  return true;
}

// unsigned long long up to 9,223,372,036,854,775,808 (0x7FFFFFFFFFFFFFFF)
template<>
inline bool
to_number<unsigned long long>(unsigned long long& val, std::string const& str,
                              std::ios_base& (*flg)(std::ios_base&))
{
  std::istringstream iss(str);
  unsigned long long tmp;
  if ((iss >> flg >> tmp).fail())
  {
    return false;
  }
  // Check for conversion of a negative number
  if (tmp & 0x8000000000000000)
  {
    return false;
  }
  val = tmp;
  return true;
}

//......................................

///// @brief  Converts a std::string to a Boolean vaue.
///// @param  [out] val   Boolean value.
///// @param  [in]  str   String encoded numeric value.
///// @return `true` if successful, `false` if an error occurred.
/////
///// The output variable is unchanged if an error occurs. @n
///// Although somewhat misleading, the function name `to_number` provides
///// consistent call syntax for conversion to either Boolean or numeric types.
//inline bool
//to_number(bool& val, std::string const& str)
//{
//  if (str == "true" || str == "TRUE" || str == "1")
//  {
//    val = true;
//    return true;
//  }
//  if (str == "false" || str == "FALSE" || str == "0")
//  {
//    val = false;
//    return true;
//  }
//  return false;
//}

/// @brief  Converts a std::string containing space-separated
///         numbers (e.g., "1 2 3") into multiple numeric values
///         appended to the specified vector.
/// @tparam       T     Type of value.
/// @param  [out] vec   Vector of unsigned numeric values.
/// @param  [in]  str   String encoded numeric values.
/// @param  [in]  flg   Format flags (e.g., std::dec, std::hex).
/// @return `true` if successful, `false` if an error occurred.
///
/// Skips numbers that result in an error.  The returned
/// vector omits numbers that resulted in error.
template<typename T>
inline bool
to_number(std::vector<T>& vec, std::string const& str,
          std::ios_base& (*flg)(std::ios_base&)=std::dec)
{
  std::istringstream iss(str);
  T tmp;
  bool no_error = true;
  while (iss >> flg >> tmp)
  {
    if (iss.fail())
    {
      no_error = false;
    }
    else
    {
      vec.push_back(tmp);
    }
  }
  return no_error;
}

/// @}
//---------------------------------------------------------------------------
/// @name Number to String
/// @{

// https://isocpp.org/wiki/faq/templates#template-specialization-example

#if 0
  // Double expansion stringification macros
  #define STRINGIFY(x) #x
  #define STRINGIFY_(x) STRINGIFY(x)
#endif

//#define STRINGIFY_RUNTIME_ERROR_CHECK
#ifdef STRINGIFY_RUNTIME_ERROR_CHECK
  template<typename T>
  inline std::string
  stringify(const T& val)
  {
      std::ostringstream oss;
      if (!(oss << val)) { throw std::runtime_error("stringify(val)"); }
      return oss.str();
  }
#endif // STRINGIFY_RUNTIME_ERROR_CHECK

/// @brief  Converts an arithmetic (numeric) type value to std::string.
/// @note   Use `std::to_string` instead for C++11 or later.
/// @tparam       T     Type of value.
/// @param  [in]  val   Numeric value.
/// @return String representing numeric value.
template<typename T>
inline std::string
to_string(T const& val)
{
  std::ostringstream out;
  out << val;
  return out.str();
}

//template<>
//inline std::string
//to_string<bool>(bool const& val)
//{
//  return (val ? "true" : "false");
//}

/// @brief  Converts a Boolean type value to std::string.
/// @param  [in]  val   Boolean value.
/// @return String representing Boolean literal.
inline std::string
to_string(bool val)
{
  return (val ? "true" : "false");
}

/// @brief  Converts an arithmetic (numeric) value to a
///         std::string in decimal format (e.g., 00000000).
/// @tparam     T     Type of value.
/// @param  [in]  val     Numerical value.
/// @param  [in]  width   Number of digits.
/// @return String representing @em val.
template<typename T>
inline std::string
to_string_dec(T val, size_t width=8)
{
  std::ostringstream oss;
  oss << std::dec             // decimal
      << std::setfill('0')    // fill with 0s
      << std::setw(width)     // sets output field width
      << val;                 // e.g., 00000000
  return oss.str();
}

/// @brief  Converts an arithmetic (numeric) value to a
///         std::string in hexidecimal format (e.g., 0x00000000).
/// @tparam       T     Type of value.
/// @param  [in]  val     Numerical value.
/// @param  [in]  width   Number of digits.
/// @return String representing @em val.
template<typename T>
inline std::string
to_string_hex(T val, size_t width=8)
{
  std::ostringstream oss;
  oss << "0x" << std::hex     // hexadecimal
      << std::setfill('0')    // fill with 0s
      << std::setw(width)     // sets output field width
      << val;                 // e.g., 0x00000000
  return oss.str();
}

/// @brief  Converts an arithmetic (numeric) value to a
///         std::string in octal format (e.g., 00000000).
/// @tparam       T     Type of value.
/// @param  [in]  val     Numerical value.
/// @param  [in]  width   Number of digits.
/// @return String representing @em val.
template<typename T>
inline std::string
to_string_oct(T val, size_t width=8)
{
  std::ostringstream oss;
  oss << std::oct             // octal
      << std::setfill('0')    // fill with 0s
      << std::setw(width)     // sets output field width
      << val;                 // e.g., 00000000
  return oss.str();
}

#if 0
//#include <iostream>
//#include <sstream>
//#include <iomanip>
//#include <string>
//#include <limits>
template<typename T>
inline std::string
stringify(T val)
{
  std::ostringstream oss;
  oss << val;
  return oss.str();
}

template<>
inline std::string
stringify<bool>(bool val)
{
  std::ostringstream oss;
  oss << std::boolalpha << val;
  return oss.str();
}

template<>
inline std::string
stringify<double>(double val)
{
  const int sigdigits = std::numeric_limits<double>::digits10;
  // or perhaps std::numeric_limits<double>::max_digits10 if that is available on your compiler
  std::ostringstream oss;
  oss << std::setprecision(sigdigits) << val;
  return oss.str();
}

template<>
inline std::string
stringify<float>(float val)
{
  const int sigdigits = std::numeric_limits<float>::digits10;
  // or perhaps std::numeric_limits<float>::max_digits10 if that is available on your compiler
  std::ostringstream oss;
  oss << std::setprecision(sigdigits) << val;
  return oss.str();
}

template<>
inline std::string
stringify<long double>(long double val)
{
  const int sigdigits = std::numeric_limits<long double>::digits10;
  // or perhaps std::numeric_limits<long_double>::max_digits10 if that is available on your compiler
  std::ostringstream oss;
  oss << std::setprecision(sigdigits) << val;
  return oss.str();
}

std::string
device_name_string(unsigned int n)
{
  #ifdef _WIN32
    return "\\\\.\\COM" + stringify(n);
  #elif __linux__
    return "/dev/ttyS" + stringify(n);
  #endif
}
#endif

/// @}
//---------------------------------------------------------------------------
/// @name Parse String
/// @{

// TODO:  std::strtok

//-------------------------------------------------------------------
// Parse and return results in existing vector of strings
//-------------------------------------------------------------------

/// @brief  Parses @a str by character delimiter @a delim and
///         adds the resulting tokens at the end of @a tokens.
/// @details  If @a delim is empty, a value of `0` is
///           returned and @a tokens remains unchanged.
/// @param  [in]  str       Source string.
/// @param  [in]  delim     Delimiter.
/// @param  [out] tokens    Results vector.
/// @param  [in]  skipblank `true` to skip each blank token;
///                         `false` to add an empty string.
/// @return  Returns the count of tokens parsed.
inline std::size_t
parse(std::string const& str, std::string const& delim,
      std::vector<std::string>& tokens, bool skipblank = false)
{
  std::size_t count = 0;
  if (!delim.empty())
  {
    std::string ss(str);
    size_t pos = 0;
    std::string tkn;  // individual token
    while ((pos = ss.find(delim)) != std::string::npos)
    {
      tkn = ss.substr(0, pos);
      if (!tkn.empty())
      {
        tokens.push_back(tkn);
        ++count;
      }
      else if (!skipblank)
      {
        tokens.push_back("");
        ++count;
      }
      ss.erase(0, pos + delim.length());
    }
    // process residual string
    if (!ss.empty())
    {
      tokens.push_back(ss);
      ++count;
    }
    else if (!skipblank)
    {
      tokens.push_back("");
      ++count;
    }
  }
  return count;
}

/// @brief  Parses @a str by character delimiter @a delim and
///         adds the resulting tokens at the end of @a tokens.
/// @details  If @a delim is not a printable character, a value
///           of `0` is returned and @a tokens remains unchanged.
/// @param  [in]  str       Source string.
/// @param  [in]  delim     Delimiter.
/// @param  [out] tokens    Results vector.
/// @param  [in]  skipblank `true` to skip each blank token;
///                         `false` to add an empty string.
/// @return  Returns the count of tokens parsed.
inline std::size_t
parse(std::string const& str, char delim,
      std::vector<std::string>& tokens, bool skipblank = false)
{
  std::size_t count = 0;
  //if (utl::ascii::is_printable(delim))    // Doesn't work with '\n'!!
  //{
    std::stringstream ss(str);
    std::string tkn;  // individual token
    while (std::getline(ss, tkn, delim))
    {
      if (!tkn.empty())
      {
        tokens.push_back(tkn);
        ++count;
      }
      else if (!skipblank)
      {
        tokens.push_back("");
        ++count;
      }
    }
  //}
  return count;
}

//------------------------------------------------------------------
// Parse and return results in a new vector of strings
//------------------------------------------------------------------

/// @brief  Parses @a str by string delimiter @a delim
///         and puts the results in a vector of strings.
/// @param  [in]  str     Source string.
/// @param  [in]  delim   Delimiter.
/// @return Vector of tokens, exluding delimiters.
inline
std::vector<std::string>
parse(std::string const& str, std::string const& delim)
{
  std::vector<std::string> tokens;
  parse(str, delim, tokens);
  return tokens;
}

/// @brief  Parses @em str by character delimiter @em delim
///         and puts the results in a vector of strings.
/// @param  [in]  str     Source string.
/// @param  [in]  delim   Delimiter.
/// @return  Vector of tokens, exluding delimiters.
inline
std::vector<std::string>
parse(std::string const& str, char delim)
{
  std::vector<std::string> tokens;
  parse(str, delim, tokens);
  return tokens;
}

/// @}
//---------------------------------------------------------------------------
/// @name String Search
/// @{

/// @brief  Searches string @em str for @em term.
/// @param  [in]  str   Source string to search within.
/// @param  [in]  term  Search term.
/// @return `true` if @em str contains @em term, `false` otherwise.
inline bool
contains(std::string const& str, std::string const& term)
{
  std::size_t pos = str.find(term);
  if (pos == std::string::npos) { return false; }   // not found
  return true;
}

/// @brief  Searches string @em str for @em term, parsing by a delimiter.
/// @param  [in]  str     Source string to search within.
/// @param  [in]  term    Search term.
/// @param  [in]  delim   Delimiter.
/// @param  [in]  res     Destination string.
/// @return `true` if @em str contains @em term, `false` otherwise.
///
/// Checkes if @em str contains @em term, and puts the
/// contents of @em str after @em delim into @em res.
inline bool
checkparse(std::string const& str, std::string const& term,
           std::string const& delim, std::string& res)
{
  std::size_t pos = str.find(term);
  if (pos == std::string::npos) { return false; }   // not found
  pos = str.find(delim);
  if (pos != std::string::npos)
  {
    res = str.substr(pos + delim.length());
  }
  return true;
}

/// @brief  Search @em str and replace all occurrences
///         of @em search with @em replace.
inline bool
replace(std::string& str, std::string const& search,
                          std::string const& replace)
{
  if (str.empty())      { return false; }
  if (search.empty())   { return false; }

  size_t pos = 0;
  while ((pos = str.find(search, pos)) != std::string::npos)
  {
     str.replace(pos, search.length(), replace);
     pos += replace.length();
  }
  return true;
}

//---------------------------------------------------------------------------
/// @}

//---------------------------------------------------------------------------
/// @}
// end group: string

} // utl

#endif // UTL_STRING_HPP
//===========================================================================//
