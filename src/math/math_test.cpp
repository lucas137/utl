//===========================================================================//
//  Nathan Lucas
//  2015-2017
//===========================================================================//

#include "utl/math.hpp"

#include <string>
#include <iostream>

namespace {   //-------------------------------------------------------------

void
test_literal()
{
  using namespace utl::math::literals;

  // Use literal operator to define variables
  auto angle_p_i =  180_deg;
  auto angle_n_i = -180_deg;
  auto angle_p_f =  85.943669_deg;
  auto angle_n_f = -85.943669_deg;

  std::cout <<'\n'<< "literal angle conversion" <<'\n'
    <<'\n'<< "  integer           180_deg =  " << angle_p_i     << " rad"
    <<'\n'<< "                   -180_deg = "  << angle_n_i     << " rad"
    <<'\n'<< "  floating    85.943669_deg =  " << angle_p_f     << " rad"
    <<'\n'<< "             -85.943669_deg = "  << angle_n_f     << " rad"
    // Use literal operator in situ
    <<'\n'<< "                1.5_rad     =  " <<  1.5_rad      << " rad"
    <<'\n'<< "               -1.5_rad     = "  << -1.5_rad      << " rad"
    <<'\n'<< "                1.5_rad2deg =  " <<  1.5_rad2deg  << " deg"
    <<'\n'<< "               -1.5_rad2deg = "  << -1.5_rad2deg  << " deg"
    <<'\n';
}


template<typename T>
void
in_radius_test(T x, T y, T r)
{
  std::cout << "(" << x << "," << y << ") in radius " << r << " : "
            << (utl::math::in_radius(x,y,r) ? "true" : "false") << std::endl;
}

void
in_radius_test(char x, char y, char r)
{
  std::cout << "("<< int(x)<< ","<< int(y)<< ") in radius " << int(r) << " : "
            << (utl::math::in_radius(x,y,r) ? "true" : "false") << std::endl;
}

//template<typename T>
//void
//in_range_test(T x, T lower, T upper)
//{
//  std::cout << lower << " <= " << x << " < " << upper << " : "
//            << (utl::in_radius(x,lower,upper) ? "true" : "false") << std::endl;
//}
//
//void
//in_range_test(char x, char lower, char upper)
//{
//  std::cout << int(lower) << " <= " << int(x) << " < " << int(upper) << " : "
//            << (utl::in_radius(x,lower,upper) ? "true" : "false") << std::endl;
//}

} // anonymous --------------------------------------------------------------


int
main(int argc, char* argv[])
{
  test_literal();   // test user-defined literals

  std::cout << "constants" <<'\n'
      <<'\n'<< "    pi = " << utl::math::pi
      <<'\n'<< "  2*pi = " << utl::math::two_pi <<'\n'<<'\n';

  // parameters (x, y, r)

  in_radius_test(char(1), char(1), char(2));
  in_radius_test(char(1), char(1), char(1));
  in_radius_test(char(3), char(4), char(5));
  std::cout << std::endl;

  in_radius_test(int(1), int(1), int(2));
  in_radius_test(int(1), int(1), int(1));
  in_radius_test(int(3), int(4), int(5));
  std::cout << std::endl;

  in_radius_test(double(1.0), double(1.0), double(2.0));
  in_radius_test(double(3.0), double(4.0), double(5.0));
  in_radius_test(double(3.0), double(4.0), double(5.1));
  std::cout << std::endl;

//  // parameters (x, lower, upper)
//
//  in_range_test(char(0), char(-1), char(1));
//  in_range_test(char(1), char(1), char(2));
//  in_range_test(char(2), char(1), char(2));
//  std::cout << std::endl;
//
//  in_range_test(int(0), int(-1), int(1));
//  in_range_test(int(1), int(1), int(2));
//  in_range_test(int(2), int(1), int(2));
//  std::cout << std::endl;
//
//  in_range_test(unsigned(0), unsigned(0), unsigned(0));
//  in_range_test(unsigned(0), unsigned(0), unsigned(2));
//  in_range_test(unsigned(1), unsigned(1), unsigned(2));
//  in_range_test(unsigned(2), unsigned(1), unsigned(2));
//  std::cout << std::endl;
//
//  in_range_test(double(0.0), double(0.0), double(0.0));
//  in_range_test(double(0.0), double(0.0), double(0.1));
//  in_range_test(double(0.1), double(0.1), double(0.2));
//  in_range_test(double(0.2), double(0.1), double(0.2));
//  std::cout << std::endl;


  return 0;
}

//===========================================================================//
