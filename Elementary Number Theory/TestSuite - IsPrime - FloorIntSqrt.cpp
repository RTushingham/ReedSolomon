
#define BOOST_TEST_MODULE My Test Two


#define BOOST_TEST_NO_MAIN
#define BOOST_TEST_ALTERNATIVE_INIT_API


#include <boost/test/included/unit_test.hpp>
#include <iostream>
namespace utf = boost::unit_test;

#include "IsPrime.h"

#define RGTIfIndexPlusTwoIsPrime {1, 1, 1, 2, 2, 2, 2, 2, 3, 3, 3, 3, 3, 3, 3, 4, 4, 4, 4, 4, 4, 4, 4, 4, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 8}
#include <boost/math/special_functions/prime.hpp>

BOOST_AUTO_TEST_CASE(TestFloorIntSqrt)
{
	//Do the values for FloorIntSqrt match hard coded variables?
		//Scope:	1 to 	65024
	
	//Do the values for FloorIntSqrt act as an inverse function to floor(n**2)?
		//Scope:	1 to 	65024
	unsigned PreSquare;
	unsigned i;
	
	for(PreSquare = 1; PreSquare < 255; PreSquare++){
		unsigned i = (PreSquare-1);
		
		unsigned n;
		for(n = (PreSquare)*(PreSquare); n < (PreSquare+1)*(PreSquare+1); n++){
			BOOST_TEST(FloorIntSqrt(n) == PreSquare);
		}
	}
}


void make_use_of(char**)
{
  std::cout << "Using custom entry point..." << std::endl;
}

int main(int argc, char* argv[], char* envp[])
{
  make_use_of(envp);
  return utf::unit_test_main(init_unit_test, argc, argv);
}

