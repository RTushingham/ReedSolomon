
#include <math.h>

bool IsPrime(unsigned i){
	for(unsigned j=2; j<i; j++){
		if(i % j == 0){
			return 0;
		}
	}		
	return 1;
}

bool FastIsPrime(unsigned i){
	for(unsigned j=2; j <= i>>1; j++){
		if(i % j == 0){
			return 0;
		}
	}
	return 1;
}

int FloorIntSqrt(unsigned i){
	float dummyfloat = i;
	dummyfloat = sqrt(dummyfloat);
	dummyfloat = floor(dummyfloat);
	unsigned dummyint = dummyfloat;
	return dummyint;
}

bool SqrtIsPrime(unsigned i){
	for(unsigned j=2; j <= FloorIntSqrt(i); j++){
		if(i % j == 0){
			return 0;
		}
	}
	return 1;
}

