
#define BOOST_TEST_MODULE My Test


#define BOOST_TEST_NO_MAIN
#define BOOST_TEST_ALTERNATIVE_INIT_API


#include <boost/test/included/unit_test.hpp>
#include <iostream>
namespace utf = boost::unit_test;

#include "Primes.h"

#define RGTPrimeUpTo64 {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61}
//A.push_back(65);
BOOST_AUTO_TEST_CASE(IsPrimes)
{
	int To = 64;
	//Do the Primes functions agree?
		//scope:	2 to	To
	
	std::vector<unsigned> A = VectorofPrimes(To);
	std::vector<unsigned> B = SecondVectorofPrimes(To);
	
	for(unsigned j = 0; j < A.size(); j++){
		if(A[j] != B[j]){
			BOOST_TEST(A[j] == B[j]);
		}	
	}
	for(unsigned j = 0; j < B.size(); j++){
		if(B[j] != A[j]){
			BOOST_TEST(B[j] == A[j]);
		}	
	}
	
		//Is this comparison method valid?
	
	
	std::vector<unsigned> VectorofPrimes_64 = VectorofPrimes(64);
	std::vector<unsigned> SecondVectorofPrimes_64 = SecondVectorofPrimes(64);
	
	//Do the Primes sets match hard coded version?
		//Scope: 	2 to	64
	std::array<bool, 18> PrimeUpTo64 = RGTPrimeUpTo64;
	for(i=2; i<PrimeUpTo64.size()+1; i++){
		BOOST_TEST(VectorofPrimes_64[i] == PrimeUpTo64[i]);
		BOOST_TEST(SecondVectorofPrimes_64[i] == PrimeUpTo64[i]);
	}
	
	//Do the values for IsPrimes match the values in boost/math/special_functions/prime.hpp?
	
	//Do they also pass these tests when we vary the number it's going up to? (If To is 7 do they include 7?)
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

