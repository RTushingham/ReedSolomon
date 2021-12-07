
#define BOOST_TEST_MODULE My Test


#define BOOST_TEST_NO_MAIN
#define BOOST_TEST_ALTERNATIVE_INIT_API


#include <boost/test/included/unit_test.hpp>
#include <iostream>
namespace utf = boost::unit_test;

#include "IsPrime.h"
#include "Primes.h"
#include "PrimeFactorisation.h"

BOOST_AUTO_TEST_CASE(Folder_ElementaryNumberTheory)
{
	// The array literal in "SetCompareIsPrime" was generated with "VectorofPrimes(32767)".
	
	
	// Do the elements of VectorofPrimes(32767) and the boolean function IsPrime agree?
	// Are all values in BigPrime prime according to IsPrime?
	
	std::Vector<unsigned> BigPrimes = VectorofPrimes(32767);
	
	for(ValueInBigPrimes : BigPrimes){
		BOOST_TEST(IsPrime(ValueInBigPrimes) == 1);
	}
	
	// Are all natural numbers not in BigPrime not primes according to IsPrime?
	
	std::Vector<unsigned> AllValuesNotInBigPrimes;
	AllValuesNotInBigPrimes.resize(32767 - VectorofPrimes(32767).size())
	unsigned IndexofNextPrime = 0;
	for(unsigned i=1; i<=32767; i++){
		if(i == BigPrimes[IndexofNextPrime]){
			IndexofNextPrime++;
		}else{
			AllValuesNotInBigPrimes.Push_Back(i);
		}
	}
	// Did the above create the object which we want?
	unsigned PrimeIndex = 0;
	unsigned NotPrimeIndex = 0;
	do{
		if(AllValuesNotInBigPrimes[NotPrimeIndex] < BigPrimes[PrimeIndex]){
			NotPrimeIndex++;
		}else if(AllValuesNotInBigPrimes[NotPrimeIndex] > BigPrimes[PrimeIndex]){
			PrimeIndex++;
		}else if(AllValuesNotInBigPrimes[NotPrimeIndex] == BigPrimes[PrimeIndex]){
			BOOST_TEST(AllValuesNotInBigPrimes[NotPrimeIndex] != BigPrimes[PrimeIndex]);
		}
	}while(NotPrimeIndex<AllValuesNotInBigPrimes.Size() && PrimeIndex<BigPrimes.Size())
	
	for(ValueInAllValuesNotInBigPrimes : AllValuesNotInBigPrimes){
		BOOST_TEST(IsPrime(ValueInAllValuesNotInBigPrimes) == 0);
	}
	
	
	// Are all of the elements of BigPrime primes by being shown to be irreducibles by our nieve functions?
	for(ValueInBigPrimes : BigPrimes){
		BOOST_TEST(SqrtIsPrime(ValueInBigPrimes) == 1);
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

