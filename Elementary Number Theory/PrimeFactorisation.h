
struct PrimeFactorandWeightPair{
	unsigned PrimeFactor;
	unsigned Weight;
};

#include "Primes.h"
#include "IsPrime.h"
#include <vector>
#include <array>
using namespace std;

struct PrimeFactorandWeightPair PrimeFactorisation_SingleFactor(unsigned n){
		// n has to be an integer >1 and <NMax.
	
	std::vector<unsigned> IndexPrimes = VectorofPrimes(FloorIntSqrt(n));
			// Is this too slow?
	
	for(unsigned i=0; i<IndexPrimes.size(); i++){
		if(n % IndexPrimes[i] == 0){
			unsigned divisor = IndexPrimes[i];
			
			PrimeFactorandWeightPair DummyPrimeFactorandWeightPair;
			DummyPrimeFactorandWeightPair.PrimeFactor = IndexPrimes[i];
			
			DummyPrimeFactorandWeightPair.Weight = 1;
			while(n % (divisor*IndexPrimes[i]) == 0){
				divisor = divisor*IndexPrimes[i];
				DummyPrimeFactorandWeightPair.Weight++;
			}
			if(n == divisor){
				return DummyPrimeFactorandWeightPair;
			}
				// else { Multiple Prime Factors }
		}
	}

	PrimeFactorandWeightPair DummyPrimeFactorandWeightPair;	
	DummyPrimeFactorandWeightPair.PrimeFactor = n;
	DummyPrimeFactorandWeightPair.Weight = 1;
	return DummyPrimeFactorandWeightPair;
}


std::vector<struct PrimeFactorandWeightPair> PrimeFactorisation_Primes(unsigned n){
		// I want this to be by value.
	
	std::vector<struct PrimeFactorandWeightPair> ReturnValue;
	std::vector<unsigned> IndexPrimes = VectorofPrimes(FloorIntSqrt(n));
	unsigned runningproduct = 1;
	PrimeFactorandWeightPair DummyPrimeFactorandWeightPair;
	
	for(unsigned i=0; i<IndexPrimes.size(); i++){
		
		if(n % (runningproduct*IndexPrimes[i]) == 0){
			DummyPrimeFactorandWeightPair.PrimeFactor = IndexPrimes[i];
			DummyPrimeFactorandWeightPair.Weight = 0;
			
			do{
				runningproduct *= IndexPrimes[i];
				DummyPrimeFactorandWeightPair.Weight++;
			}while(n % (runningproduct * IndexPrimes[i]) == 0);
			
			ReturnValue.push_back(DummyPrimeFactorandWeightPair);
			
		}
	}
	if(n != runningproduct){
		DummyPrimeFactorandWeightPair.PrimeFactor = n;
		DummyPrimeFactorandWeightPair.Weight = 1;
		ReturnValue.push_back(DummyPrimeFactorandWeightPair);
	}
	
	return ReturnValue;
}

std::vector<struct PrimeFactorandWeightPair> PrimeFactorisation_Nieve(unsigned n){
		// I want this to be by value.
	
	std::vector<struct PrimeFactorandWeightPair> ReturnValue;
	unsigned runningproduct = 1;
	PrimeFactorandWeightPair DummyPrimeFactorandWeightPair;
	
	for(unsigned i=2; i<FloorIntSqrt(n); i++){ // If n is a composite
		
		if(n % (runningproduct * i) == 0){
			DummyPrimeFactorandWeightPair.PrimeFactor = i;
			DummyPrimeFactorandWeightPair.Weight = 0;
			
			do{
				runningproduct *= i;
				DummyPrimeFactorandWeightPair.Weight++;
			}while(n % (runningproduct*i) == 0);
			
			ReturnValue.push_back(DummyPrimeFactorandWeightPair);
		}
	}
	if(n != runningproduct){	// If n was prime.
		DummyPrimeFactorandWeightPair.PrimeFactor = n;
		DummyPrimeFactorandWeightPair.Weight = 1;
		ReturnValue.push_back(DummyPrimeFactorandWeightPair);
	}
}

/*
std::vector<struct PrimeFactorandWeightPair> PrimeFactorisation_DeducePrimes(unsigned n){
	
}
*/
