
struct PrimeFactorandWeightPair{
	unsigned PrimeFactor;
	unsigned Weight;
};

#include "Primes.h"
#include "IsPrime.h"
#include <vector>
#include <array>
using namespace std;

Std::Vector<struct PrimeFactorandWeightPair> PrimeFactorisation_Primes(unsigned n){
		// I want this to be by value.
	
	Std::Vector<struct PrimeFactorandWeightPair> ReturnValue;
	IndexPrimes = VectorofPrimes(FloorIntSqrt(n));
	unsigned runningproduct = 1;
	
	For(unsigned i=0; i<VectorofPrimes.size()); i++){
		
		if(n % (runningproduct*VectorofPrimes[i]) == 0){
			PrimeFactorandWeightPair DummyPrimeFactorandWeightPair;
			
			DummyPrimeFactorandWeightPair.PrimeFactor = VectorofPrimes[i];
			DummyPrimeFactorandWeightPair.Weight = 0;
			
			do{
				runningproduct *= VectorofPrimes[i];
				DummyPrimeFactorandWeightPair.Weight++;
			}while(n % (runningproduct * VectorofPrimes[i]) == 0)
			
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

Std::Vector<struct PrimeFactorandWeightPair> PrimeFactorisation_Nieve(unsigned n){
		// I want this to be by value.
	
	Std::Vector<struct PrimeFactorandWeightPair> ReturnValue;
	unsigned runningproduct = 1;
	
	For(unsigned i=2; i<FloorIntSqrt(n)); i++){ // If n is a composite
		
		if(n % (runningproduct * i) == 0){
			PrimeFactorandWeightPair DummyPrimeFactorandWeightPair;
			
			DummyPrimeFactorandWeightPair.PrimeFactor = i;
			DummyPrimeFactorandWeightPair.Weight = 0;
			
			do{
				runningproduct *= i;
				DummyPrimeFactorandWeightPair.Weight++;
			}while(n % (runningproduct*i) == 0)
			
			ReturnValue.push_back(DummyPrimeFactorandWeightPair);
		}
	}
	if(n != runningproduct){	// If n was prime.
		DummyPrimeFactorandWeightPair.PrimeFactor = n;
		DummyPrimeFactorandWeightPair.Weight = 1;
		ReturnValue.push_back(DummyPrimeFactorandWeightPair);
	}
}

Std::Vector<struct PrimeFactorandWeightPair> PrimeFactorisation_DeducePrimes(unsigned n){
	
}



struct PrimeFactorandWeightPair PrimeFactorisation_SingleFactor(unsigned n){
		// n has to be an integer >1 and <NMax.
	
	IndexPrimes = VectorofPrimes(FloorIntSqrt(n));
			// Is this too slow?
	
	For(unsigned i=0; i<VectorofPrimes.size()); i++){
		if(n % VectorofPrimes[i] == 0){
			unsigned divisor = VectorofPrimes[i];
			
			PrimeFactorandWeightPair DummyPrimeFactorandWeightPair;
			DummyPrimeFactorandWeightPair.PrimeFactor = VectorofPrimes[i];
			
			DummyPrimeFactorandWeightPair.Weight = 1;
			while(n % (divisor*VectorofPrimes[i]) == 0){
				divisor = divisor*VectorofPrimes[i];
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
