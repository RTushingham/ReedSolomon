
#define RGTPrimesDotHppDebugging 0

#if RGTPrimesDotHppDebugging
	#include <iostream>
#endif
#include <vector>
using namespace std;

std::vector<unsigned> VectorofPrimes(unsigned To){
	
	std::vector<unsigned> Primes = {2};
	bool PrimeFlag;
	unsigned i;
	
	for(i = 3; i <= To; i++){
		PrimeFlag = 1;
		
		for(unsigned j : Primes){
			if((i % j) == 0){
				PrimeFlag = 0;
			}
		}
		
		if(PrimeFlag){
			Primes.push_back(i);
		}
	}
	
	#if RGTPrimesDotHppDebugging
	for(unsigned j : Primes){
		cout << "Value: " << j << endl;
	}
	#endif
	
	return Primes;
}

std::vector<unsigned> SecondVectorofPrimes(unsigned To){
	
	std::vector<unsigned> Primes = {2};
	bool PrimeFlag;
	unsigned i;
	
	for(i = 3; i <= To; i++){
		PrimeFlag = 1;
		
		for(unsigned j = 0; (Primes[j]*Primes[j] <= i) and (Primes[j]*Primes[j] > Primes[j]) and (j < Primes.size()); j++){
			if((i % Primes[j]) == 0){
				PrimeFlag = 0;
			}
		}
		
		if(PrimeFlag){
			Primes.push_back(i);
		}
	}
	
	#if RGTPrimesDotHppDebugging
	for(unsigned j : Primes){
		cout << "Value: " << j << endl;
	}
	#endif
	
	return Primes;
}
