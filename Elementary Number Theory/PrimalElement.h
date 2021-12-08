
#include "Typedef.h"
#include <vector>

#define RGTPrimesDotHppDebugging 0

#if RGTPrimesDotHppDebugging
	#include <iostream>
	using namespace std;
#endif

// The primal element "a" of a field F is a element of a filed such that {a**n | n is an natural number, excluding 0 } = F
// For finite fields of q elements this is equivalent to a**n != a**m for all ints n,m such that 0<n.m<q

// In general a field may have multiple primal elements, however for the purposes of generating FiniteFields, or ReedSolomon codes only one is needed.

// First I will generate this for the case of GF(p) where p is prime, so that I don't have to represent the values over aren't polynomials over its prime factor of degree greater than one.
int NievePrimalElementofZp(int PrimeInteger);
bool notcontains(std::vector<int> vector, int to, int find);


inline int PrimalElementofZp(int PrimeInteger){
	return NievePrimalElementofZp(PrimeInteger);
}

int NievePrimalElementofZp(int PrimeInteger){
	/*
	if(!IsPrime(PrimeInteger)){
		// throw
	}
	*/
	std::vector<int> SpanofIndex;
	SpanofIndex.resize(PrimeInteger-1);
	
	for(int IndexOverZp=1; IndexOverZp<PrimeInteger; IndexOverZp++){
		
		unsigned PowerIndex=0;
		SpanofIndex[PowerIndex] = IndexOverZp;
		
		while(notcontains(SpanofIndex, PowerIndex, SpanofIndex[PowerIndex]*IndexOverZp % PrimeInteger)){
			SpanofIndex[PowerIndex+1] = SpanofIndex[PowerIndex]*IndexOverZp % PrimeInteger;
			PowerIndex++;
		}
		
		if(PowerIndex == PrimeInteger-1){
			return IndexOverZp;
		}
	}
}

int ToInvariantPrimalElementofZp(int PrimeInteger){
	#if RGTPrimesDotHppDebugging
		cout << "ToInvariantPrimalElementofZp Called: " << PrimeInteger << endl;
		//cout << "Input IsPrime: " << IsPrime(PrimeInteger) << endl;
	#endif
	
	/*
	if(!IsPrime(PrimeInteger)){
		// throw
	}
	*/
	
	
	
	for(int IndexOverZp=1; IndexOverZp<PrimeInteger; IndexOverZp++){
		unsigned Power;
		int RunningProduct = IndexOverZp;
		
		#if RGTPrimesDotHppDebugging
			cout << "PreLoop: " << RunningProduct << endl;
		#endif
		
		for(Power=1; (Power<PrimeInteger) && (RunningProduct!=1); Power++){
			#if RGTPrimesDotHppDebugging
				cout << "InLoop: " << RunningProduct << ", Power: " << Power << endl;
			#endif
			RunningProduct = (RunningProduct*IndexOverZp) % PrimeInteger;
		}
		
		#if RGTPrimesDotHppDebugging
			cout << "AfterLoop: " << RunningProduct << ", Power: " << Power << endl;
		#endif
		
		if(Power == PrimeInteger-1){
			
			#if RGTPrimesDotHppDebugging
				cout << "Returning: " << IndexOverZp << endl;
			#endif
			
			return IndexOverZp;
		}
	}
}

std::vector<int> SpanofIndex(int ElementofField, int SizeofField){
	/*
	if(!IsPrime(PrimeInteger) and ElementofField<SizeofField and ElementofField>= 0){
		// throw
	}
	*/
	
	#if RGTPrimesDotHppDebugging
		cout << "SpanofIndex Called: " << ElementofField << ", " << SizeofField << endl;
	#endif
	
	std::vector<int> RunningSpan;
	RunningSpan.push_back(ElementofField);
	int RunningProduct = ElementofField;
	
	#if RGTPrimesDotHppDebugging
		cout << "PreLoop: " << ElementofField << ", Power: " << 1 << endl;
	#endif
	
	for(unsigned Power=2; (Power<SizeofField) && (RunningProduct!=1); Power++){
		RunningProduct = (RunningProduct*ElementofField) % SizeofField;
		RunningSpan.push_back(RunningProduct);
		
		#if RGTPrimesDotHppDebugging
			cout << "InLoop: " << RunningProduct << ", Power: " << Power << endl;
		#endif
	}
	return RunningSpan;
}

bool notcontains(std::vector<int> vector, int to, int find){
	for(unsigned index=0; index<to; index++){
		if(vector[index] == find){
			return 0;
		}
	}
	return 1;
}

