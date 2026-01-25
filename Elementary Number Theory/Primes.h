#pragma once

constexpr unsigned int_pow(unsigned base, unsigned exponent)
{
	return exponent == 0 ? 1 : base*int_pow(base,exponent-1);
}

#include <vector>

using namespace std;

std::vector<unsigned> AllPrimesUntil(unsigned upper_limit)
{
	if( upper_limit<2 )
		return{};

	std::vector<unsigned> Primes = {2};
	
	for(unsigned i = 3; i <= upper_limit; i++){
		bool PrimeFlag = true;
		
		// there may be some theorem somewhere which we could apply to decude that j < Primes.size() is an unnecessary check
		for(unsigned j = 0; (Primes[j]*Primes[j] <= i) && (Primes[j]*Primes[j] > Primes[j]) && (j < Primes.size()); j++){
			if((i % Primes[j]) == 0){
				PrimeFlag = false;
				break;
			}
		}
		
		if(PrimeFlag){
			Primes.push_back(i);
		}
	}
	
	return Primes;
}
