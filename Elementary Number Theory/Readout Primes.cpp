
#include <iostream>

#include <vector>
using namespace std;

#include "Primes.h"

int main(int argc, char *argv[]) {
	
	std::vector<unsigned> Primes = VectorofPrimes(32767);
	
	for(unsigned j : Primes){
		cout << "Prime: " << j << endl;
	}
}
