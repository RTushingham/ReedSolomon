
//	Can I change the input for BOOST_TEST() function to get the value of "To" used to generate the sets?

#define BOOST_TEST_MODULE My Test


#define BOOST_TEST_NO_MAIN
#define BOOST_TEST_ALTERNATIVE_INIT_API


#include <boost/test/included/unit_test.hpp>
#include <iostream>
namespace utf = boost::unit_test;

#include "Primes.h"
#include "IsPrime.h"

#define RGTPrimeUpTo64 {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61}

void TestIfSubsetandIfBiggerIsPrime(std::vector<unsigned> subset, std::vector<unsigned> superset, unsigned input){
	BOOST_TEST(subset.size() <= superset.size());
	if(subset.size() <= superset.size()){
		for(unsigned j = 0; j < subset.size(); j++){
			BOOST_TEST(subset[j] == superset[j]);
		}
		
		if(subset.size() < superset.size()){
			BOOST_TEST(subset.size()+1 == superset.size());
			if(subset.size()+1 == superset.size()){
				BOOST_TEST(input == input*SqrtIsPrime(input));
			}
		}else{
			BOOST_TEST(0 == input*SqrtIsPrime(input));
		}
	}
}

BOOST_AUTO_TEST_CASE(PrimesTests)
{
	int RGTTestMax = 8192;
	
	//	Do the entries in the Primes sets agree?
		//	Scope:	2 to	RGTTestMax == 8192
	{
	std::vector<unsigned> A,B;
	for(unsigned To=2; To<RGTTestMax; To++){
		A = VectorofPrimes(To);
		B = SecondVectorofPrimes(To);
		
		BOOST_TEST(A.size() == B.size());
		if(A.size() == B.size()){
			for(unsigned j = 0; j < A.size(); j++){
				BOOST_TEST(A[j] == B[j]);
			}
		}
	}
	}
	
	//	For all n<m is Primes(n) a subset of Primes(m)?
		//	This is tested by inductively, due to transitivity of the subset statement.
		//	(For computational simplicity the above could be unwound, and this could be added in there, but this is a test module, so CBA. I'll leave that up to the compiler.)
	//	Do the size of these sets increase if and only if they're going up to a prime number?
		//	If so do they only ever increase in size by one?
	//	Scope:	2 to	RGTTestMax == 8192
	{
	std::vector<unsigned> A,B;
	A = Primes(2);
	B = Primes(3);
	TestIfSubsetandIfBiggerIsPrime(A,B,3);
	
	for(unsigned To=4; To<RGTTestMax; To++){
		A = Primes(To);
		TestIfSubsetandIfBiggerIsPrime(B, A, To);
		To++;
		
		B = Primes(To);
		TestIfSubsetandIfBiggerIsPrime(A,B, To);
	}
	}
	
	
	//	Do the Primes sets match hard coded version?
		//	Scope: 	2 to	64
	std::vector<unsigned> VectorofPrimes_64 = VectorofPrimes(64);
	std::vector<unsigned> SecondVectorofPrimes_64 = SecondVectorofPrimes(64);
	
	std::array<unsigned, 18> PrimeUpTo64 = RGTPrimeUpTo64;
	for(unsigned i=0; i<PrimeUpTo64.size(); i++){
		BOOST_TEST(PrimeUpTo64[i] == VectorofPrimes_64[i]);
		BOOST_TEST(PrimeUpTo64[i] == SecondVectorofPrimes_64[i]);
	}
	//	From the previous tests we can conclude that for all inputs than or equal to 64 all of the values of Primes(input) are as we want them.
	
	
	//	Are all of the values in Primes(big) prime according to our nieve IsPrime function? 
		//	If so we can conluclude that for all inputs<big we have that Primes(inputs) is as desired.
	//	Scope: 	RGTTestMax
	std::vector<unsigned> Primes_RGTTestMax = Primes(RGTTestMax);
	for(unsigned i=0; i<Primes_RGTTestMax.size(); i++){
		BOOST_TEST(SqrtIsPrime(Primes_RGTTestMax[i]));
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

