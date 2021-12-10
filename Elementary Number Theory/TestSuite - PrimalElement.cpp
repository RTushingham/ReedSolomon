
#define BOOST_TEST_MODULE My Test


#define BOOST_TEST_NO_MAIN
#define BOOST_TEST_ALTERNATIVE_INIT_API


#include <boost/test/included/unit_test.hpp>
#include <iostream>
namespace utf = boost::unit_test;

#include "PrimalElement.h"

#define RGTPrimesUpTo64 	{	2,	3,	5, 	7, 	11,	13,	17,	19,	23,	29,	31,	37,	41,	43,	47,	53,	59,	61	}
#define RGTPrimalElements 	{	1,	2, 	2, 	3, 	0, 	0, 	0, 	0, 	0, 	0, 	0, 	0, 	0, 	0, 	0, 	0, 	0, 	0	}

//	value returned from running values up to 61:	{	2,	2,	3,	2,	5,	2,	3,	2,	6,	3,	5,	2,	2,	2	}
//									Index:			{	11,	13,	17,	19,	23,	29,	31,	37,	41,	43,	47,	53,	59,	61	}

BOOST_AUTO_TEST_CASE(PrimalElements)
{
	//Do the values for IsPrimes match hard coded entries?
		//Scope: 	Primes from		2 to	61 (and therefore 64)
	std::array<int, 18> PrimesUpTo64 = RGTPrimesUpTo64;
	std::array<int, 18> PrimalElements = RGTPrimalElements;
	
	for(unsigned i=0; i<4; i++){
		//BOOST_TEST(NievePrimalElementofZp(PrimesUpTo64[i]) == PrimalElements[i]);
		BOOST_TEST(ToInvariantPrimalElementofZp(PrimesUpTo64[i]) == PrimalElements[i]);
	}
	
	// Do the hard coded entries actually have span =p-1?
		//Scope: 	Primes from		2 	to	7
	for(unsigned i=0; i<4; i++){
		BOOST_TEST(SpanofIndex(PrimalElements[i], PrimesUpTo64[i]).size() == (PrimesUpTo64[i]-1));
	}
	
	// Do the values of the function ToInvariantPrimalElementofZp actually have span =p-1?
		//Scope: 	Primes from		2 to	7
	for(unsigned i=0; i<4; i++){
		BOOST_TEST(SpanofIndex(ToInvariantPrimalElementofZp(PrimesUpTo64[i]), PrimesUpTo64[i]).size() == (PrimesUpTo64[i]-1));
	}
	
	// Do the unchecked values of the function ToInvariantPrimalElementofZp have span =p-1?
		//Scope: 	Primes from		2 to	61 (and therefore 64)
	for(unsigned i=4; i<PrimesUpTo64.size(); i++){
		BOOST_TEST(SpanofIndex(ToInvariantPrimalElementofZp(PrimesUpTo64[i]), PrimesUpTo64[i]).size() == (PrimesUpTo64[i]-1));
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

