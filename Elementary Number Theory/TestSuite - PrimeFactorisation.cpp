
#define BOOST_TEST_MODULE My Test


#define BOOST_TEST_NO_MAIN
#define BOOST_TEST_ALTERNATIVE_INIT_API


#include <boost/test/included/unit_test.hpp>
#include <iostream>
namespace utf = boost::unit_test;

#include "PrimeFactorisation.h"

#define RGTSinglePrimeFactorValueUpTo64 		{	2, 3, 4, 5, 7, 8, 9, 11, 13, 16, 17, 19, 23, 25, 27, 29, 31, 32, 37, 41, 43, 47, 49, 53, 59, 61, 64}
#define RGTPrimeFactorsUpTo64					{	2, 3, 2, 5, 7, 2, 3, 11, 13,  2, 17, 19, 23,  5,  3, 29, 31,  2, 37, 41, 43, 47,  7, 53, 59, 61,  2}
#define RGTFactorWeightUpTo64					{	1, 1, 2, 1, 1, 3, 2,  1,  1,  4,  1,  1,  1,  2,  3,  1,  1,  5,  1,  1,  1,  1,  2,  1,  1,  1,  6}
#define NumberofInputs							27

//												{	6,10,12,14,15,18,20,21,22,24,26,28,30,33,34,35,36,38,39,40,42,44,45,46,48,50,51,52,54,55,56,57,58,60,62,63}

BOOST_AUTO_TEST_CASE(PrimeFactorisationTests)
{
	//Do the Primes sets match hard coded version?
		//Scope: 	2 to	64
	{
	std::array<int, NumberofInputs> Value 	= RGTSinglePrimeFactorValueUpTo64;
	std::array<int, NumberofInputs> Factor 	= RGTPrimeFactorsUpTo64;
	std::array<int, NumberofInputs> Weight 	= RGTFactorWeightUpTo64;
	
	for(unsigned Index; Index<NumberofInputs; Index++){
		BOOST_TEST( PrimeFactorisation_SingleFactor(Value[Index]).PrimeFactor == Factor[Index]);
		BOOST_TEST( PrimeFactorisation_SingleFactor(Value[Index]).Weight == Weight[Index]);
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

