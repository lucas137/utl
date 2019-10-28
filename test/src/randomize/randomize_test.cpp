//===========================================================================//
//  Nathan Lucas
//  2015
//===========================================================================//

#include "utl/randomize.hpp"

#include <iostream>     //  std::cout, std::endl
#include <vector>       //  std::vector

namespace {   //-------------------------------------------------------------

void
print_vector(std::vector<int> const& vec)
{
  std::cout << "{ ";
  for (auto const& val : vec)
  {
    std::cout << val << " ";
  }
  std::cout << "}\n";
}

} // anonymous --------------------------------------------------------------


int
main(int argc, char* argv[])
{
  std::cout << "test utl::randomize...\n\n";

  std::vector<int> v { 0,1,2,3,4,5,6,7 };

  for (unsigned i = 0; i != 4; ++i)
  {
    std::vector<int> vv(v);
    utl::randomize(vv);
    print_vector(vv);
  }

  return 0;
}

//===========================================================================//
