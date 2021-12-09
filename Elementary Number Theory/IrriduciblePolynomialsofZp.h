
IrriduciblePolynomialsinZpofdeg1(integer Prime, integer Degree){
	
	
	
}

IrriduciblePolynomialsinZpofdeg2(integer Prime){
	
	RunningPolynomial = PolynomialsoverZpofdegreen
	
	for(CoefficientOfDegreeOne=1; CoefficientOfDegreeOne<Prime; CoefficientOfDegreeOne++){
		for(CoefficientOfDegreeZero=0; CoefficientOfDegreeZero<Prime; CoefficientOfDegreeZero++){
			
			
		}
	}
	
}

ItteratorOverZpX(int Prime, int Degree){
	int max=Prime;
	for(unsigned Power=1; Power<Degree; Power++){
		max *= Prime
	}
	
	for(unsigned Index=1; Index<max; Index++){
		int remainder = 1;
		for(unsigned DegreeIndex=0; DegreeIndex<Degree && remainder!=0; DegreeIndex++){
			
			a[DegreeIndex] += remainder
			
			remainder = a[DegreeIndex]/Prime
			
			a[DegreeIndex] %= Prime
		}
	}
}


template <class myType, integer Prime, integer Degree>

// <std:array<integer, PrimeFactorandWeightForThisFiniteField.Weight>, PrimeFactorandWeightForThisFiniteField.PrimeFactor;

class PolynomialsoverZpofdegreen{
	std:array<integer, Degree+1> value;
	
	ElementsofFiniteFields(class std:array<integer, Degree+1> InputValue){
		for(integerindex i=0; i<=Degree; i++){
			value[i] = InputValue[i] % Prime;
		}
	}
	
	myType evaluate(class std:array<integer, Degree+1> Polynomial, int ValueofZp){
		int runningsum=0;
		int runningproduct=1;
		for(integerindex i=0; i<=Degree; i++){
			runningsum += (Polynomial[i] * runningproduct) % Prime;
			runningproduct *= ValueofZp;
		}
		return runningsum;
	}
	
	/*
	myType operator+(myType A, myType B){
		myType R;
		for(integerindex i=0; i<=Degree; i++){
			R[i] = (A[i] + B[i]) % Prime;
		}
		return R;
	}
	myType operator-(myType A, myType B){
		myType R;
		for(integerindex i=0; i<=Degree; i++){
			R[i] = (Prime + A[i] - B[i]) % Prime;
		}
		return R;
	}
	*/
	/*
	myType operator*(myType A, myType B){
		myType R;
		for(integerindex i=0; i<=Degree; i++){
			R[i] = (A[i] * B[i]) % Prime;
		}
		return R;
	}
	*/
	/*
	myType operator%(myType A, myType B){
		myType R;
		for(integerindex i=0; i<=Degree; i++){
			R[i] = (A[i] * B[i]) % Prime;
		}
		return R;
	}
	*/
	
	/*
	bool operator==(myType A, myType B){
		bool r=1;
		for(integerindex i=0; i<=Degree; i++){
			r = r & (A[i] == B[i]);
		}
		return r;
	}
	*/
}

