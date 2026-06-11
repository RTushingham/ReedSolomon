#pragma once

#include "elementary-mathematical-functions/IntegerPowers.h"

#include <vector>

std::vector<unsigned> AllPrimesUntil(unsigned upper_limit)
{
	if( upper_limit<2 )
		return{};

	std::vector<unsigned> Primes = {2};
	
	for(unsigned i = 3; i <= upper_limit; i++){
		bool PrimeFlag = true;
		
		// There may be some way to decude a priori if j < Primes.size() is an unnecessary check for all j
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
