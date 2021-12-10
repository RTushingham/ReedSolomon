
#define BOOST_TEST_MODULE My Test


#define BOOST_TEST_NO_MAIN
#define BOOST_TEST_ALTERNATIVE_INIT_API


#include <boost/test/included/unit_test.hpp>
#include <iostream>
namespace utf = boost::unit_test;

#include "IsPrime.h"

#define RGTIfIndexIsPrime {0, 0, 1, 1, 0, 1, 0, 1, 0, 0, 0, 1, 0, 1, 0, 0, 0, 1, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0}

BOOST_AUTO_TEST_CASE(IsPrimes)
{
	//Do all of the IsPrimes functions agree?
		//scope:	0 to	INT_Max == 32767
	unsigned i;
	for(i=0; i<32767; i++){
		BOOST_TEST(IsPrime(i) == SetCompareIsPrime(i));
		BOOST_TEST(IsPrime(i) == NieveIsPrime(i));
		BOOST_TEST(IsPrime(i) == HeuristicIsPrime(i));
		BOOST_TEST(IsPrime(i) == SqrtIsPrime(i));
	}
	
	//Do the values for IsPrimes match hard coded entries?
		//Scope: 	0 to	64
	std::array<bool, 65> IfNIsPrime = RGTIfIndexIsPrime;
	for(i=0; i<IfNIsPrime.size(); i++){
		BOOST_TEST(IfNIsPrime[i] == IsPrime(i));
		BOOST_TEST(IfNIsPrime[i] == SetCompareIsPrime(i));
		BOOST_TEST(IfNIsPrime[i] == NieveIsPrime(i));
		BOOST_TEST(IfNIsPrime[i] == HeuristicIsPrime(i));
		BOOST_TEST(IfNIsPrime[i] == SqrtIsPrime(i));
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

