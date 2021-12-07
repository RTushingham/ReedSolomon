
#define BOOST_TEST_MODULE My Test


#define BOOST_TEST_NO_MAIN
#define BOOST_TEST_ALTERNATIVE_INIT_API


#include <boost/test/included/unit_test.hpp>
#include <iostream>
namespace utf = boost::unit_test;

#include "Primes.h"
//#define RGTSinglePrimeFactorPrimeFactorsUpTo64 {{2, {2, 1}}, {3, {3, 1}}, {4, {2, 2}}, {5, {5, 1}}, {7, {7, 1}}, {8, {2, 3}}, {9, {3, 2}}, {11, {11, 1}},  {13, {13, 1}}, {16, {2, 4}}, {19, {19, 1}}, {23, {23, 1}}, {25, {5, 2}}, {27, {3, 3}}, {29, {29, 1}}, {31, {31, 1}}, {32, {2, 5}}, {37, {37, 1}}, {41, {41, 1}}, {43, {43, 1}}, {47, {47, 1}}, {49, {7, 2}}, {53, {53, 1}}, {59, {59, 1}}, {61, {61, 1}}, {64, {2, 6}}

BOOST_AUTO_TEST_CASE(PrimeFactorisationTests)
{
	
	//Do the Primes sets match hard coded version?
		//Scope: 	2 to	64
	
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

