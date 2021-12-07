
#define BOOST_TEST_MODULE My Test


#define BOOST_TEST_NO_MAIN
#define BOOST_TEST_ALTERNATIVE_INIT_API


#include <boost/test/included/unit_test.hpp>
#include <iostream>
namespace utf = boost::unit_test;

#include "IsPrime.h"

#define RGTIfIndexPlusTwoIsPrime {1, 1, 0, 1, 0, 1, 0, 0, 0, 1, 0, 1, 0, 0, 0, 1, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0}

BOOST_AUTO_TEST_CASE(IsPrimes)
{
	bool dummyboolean;
	
	//Do all of the IsPrimes functions agree?
		//scope:	2 to	64
	BOOST_TEST(IsPrime(2) == 1);
	
	unsigned i;
	for(i=2; i<64; i++){
		dummyboolean = IsPrime(i) == FastIsPrime(i);
		dummyboolean = dummyboolean && (FastIsPrime(i) == SqrtIsPrime(i));
		BOOST_TEST(dummyboolean);
	}
	
	
	//Do the values for IsPrimes match hard coded entries?
		//Scope: 	2 to	64
	std::array<bool, 63> IfNPlusTwoIsPrime = RGTIfIndexPlusTwoIsPrime;
	for(i=2; i<IfNPlusTwoIsPrime.size()+1; i++){
		dummyboolean = (IsPrime(i) == IfNPlusTwoIsPrime[i-2]);
		dummyboolean = dummyboolean && (IsPrime(i) == FastIsPrime(i));
		dummyboolean = dummyboolean && (FastIsPrime(i) == SqrtIsPrime(i));
		BOOST_TEST(dummyboolean);
	}
	
	//Do the values for IsPrimes match the values in boost/math/special_functions/prime.hpp?
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

