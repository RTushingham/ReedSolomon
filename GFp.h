
#include "Elementary Number Theory\Typedef.h"
#include <vector.h>

class FiniteFieldp{
	integer NumberofElements;
	integer PrimeFactor;
	class Element;
	Element PrimalElement;
	
	
	FiniteField(int numberofelements){
		//if(!IsPrime(numberofelements)) throw
		
		PrimeFactorandWeightForThisFiniteField = PrimeFactorisation_SingleFactor(numberofelements);
		NumberofElements = numberofelements;
		
		Element = ElementsofFinitePrimeField<integer, NumberofElements>;
	}
	
	// std:array<int, m>
}

template <class myType, integer Prime>
Class ElementsofFinitePrimeField{
	myType value;
	
	ElementsofFiniteFields(myType InputValue){
		value = InputValue % Prime;
	}
	
	myType operator+(myType a, myType b){
		return ((a + b) % Prime);
	}
	myType operator-(myType a, myType B){
		return ((Prime + a - b) % Prime);
	}
	myType operator*(myType a, myType b){
		return ((a * b) % Prime);
	}
	myType MultiplicativeInverse(myType a){
		// a!=0 and Q.Size() <2.
		
		//if(a == 0) throw;
		
			// Is this the best data type?
		std::vector R;
		std::vector Q;
			// I probably only need to track R[Index], R[Index+1]
		
		R.push_back(Prime);
		R.push_back(a);
		
			// Can I adjust this so that all of the values are represented as their values in Zp?
			// If not can this overflow?
		
		unsigned Index = 0;
		while(R[Index+1] !=0){
			Q.push_back( R[Index]/R[Index+1] );
			R.push_back( R[Index] % R[Index+1]);
			Index++;
		}
		
		std::vector A;
		std::vector B;
			// I probably only need to track A[Index], A[Index-1], B[Index], and B[Index-1]
		
		// What do you do if Q.Size() < 2?
		
		A.push_back(1);
		B.push_back(-Q[0]);
		
		A.push_back(-Q[1]);			//	Can do this entirely recursively if I define A[-1] to be 0.
		B.push_back(Q[1]*Q[0]+1);	//	Can do this entirely recursively if I define B[-1] to be 1.
		
		Index = 2;
		while(R[Index] > 1){
			A.push_back( A[Index-2] - Q[Index]*A[Index-1] );	// 	if A[Index-2]*A[Index-1] < 0 and A[Index-2]<0 => A[Index] <0		if A[Index-2]*A[Index-1] < 0 and A[Index-2]>0 => A[Index]>0
			B.push_back( B[Index-2] - Q[Index]*B[Index-1] );	// 	if B[Index-2]*B[Index-1] < 0 and B[Index-2]<0 => B[Index] <0		if B[Index-2]*B[Index-1] < 0 and B[Index-2]>0 => B[Index]>0
			Index++;											// 		As A[0]*A[1] < 0 and A[0]>0 and B[0]*B[1] < 0 and B[0]<0 we can conclude that A[Index]*B[Index] <0 for all Index >= 0,
		}														//			which is a necessary condition for 1 = A[last]*a + B[last] as integers.
		
		return A[Index] % Prime;
	}
	myType operator/(myType a, myType b){
		//if(b == 0) throw;
		return(a*MultiplicativeInverse(b) % Prime);
	}
	bool operator==(myType a, myType b){
		return (a == b);
	}
}

/*
	find the inverse of n:
	
	1 = gcd(n, p)
		= ap + n
	
	1071 	= 	2	*	462	+	147
	462 	= 	3	*	147	+	21
	147		=	7	*	21	+	0
			=	7	*	21
	
	462 	= 	3	*	147	+	21
			= 	3	*	7	*	21	+	21
			=	22	*	21
	1071 	= 	2	*	462	+	147
			= 	2	*	22	*	21	+	7	*	21	+	0
			= 	51	*	21
	462		=	22	*	21
	
	gcd(n,p)
		=	
	
	51 - 2*22 = 7
	51 - 7*7 = 2
	7 - 3*2 = 1
	
	1 
	= 7 - 3*(51 - 7*7)
	= 3*51 - 49*7
	= 3*51 - 49*(51 - 44)
	= 49*44 - 46*51
	
	21
	= 21*1
	= 21*(49*44 - 46*51)
	= 21*(98*22 - 46*51)
	= 98*(21*22) - 46*(21*51)
	= 98*(462) - 46*(1071)
	
	gcd(n,p) = 1
	= m*n - k*p
	== m*n %p
	== (m%p)*n %p
	
	a = q0b + r0
	b = q1r0 + r1
	r0 = q2r1 + r2
	...
	
	r(n-2)	=	q(n)	*	r(n-1)	+	r(n)
	...
	
	r(M-3)	=	q(M-1)	*	r(M-2)	+	r(M-1)
			=	q(M-1)	*	r(M-2)	+	1
	
	r(M-2)	=	q(M)	*	r(M-1)	+	r(M)
			=	q(M)
	r(M) = 0
	r(M-1) = 1
	
	r(M-3)	=	q(M-1)	*	r(M-2)	+	1
	
	
	want to express Q(M-1)*r(M-2) in terms of na + kb
		= Q(M-1)*Q(M)	->Q(M) is explicit
	want to express r(M-3) in terms of na + kb
	
	r-2
	a = q0b + r0
	r-1
	b = q1r0 + r1
	r0 = q2r1 + r2
	
	r(n-2)	=	q(n)	*	r(n-1)	+	r(n)
	r(n-1)	=	q(n+1)	*	r(n)	+	r(n+1)
	
	r(n-2)	=	q(n)	*	r(n-1)	+	r(n)
			=	q(n)	*	(q(n+1)	*	r(n)	+	r(n+1))	+	1	*	r(n)
			=	q(n)	*	(q(n+1)	*	r(n)	+	r(n+1))	+	1	*	r(n)
			=	(q(n)	*	q(n+1)	+	1)	*	r(n)	+	q(n+1)	*	r(n+1)
	a		=	(q0		*	q1	+	1)	*	r0		+	q1	*	r1
	
	r(n-2)	=	(q(n)	*	q(n+1)	+	1)	*	r(n)	+	q(n+1)	*	r(n+1)
	
	r(n-3)	=	(q(n-1)	*	q(n)	+	1)	*	r(n-1)	+	q(n)	*	r(n)
	
	
	r(n-2)	=	q(n)	*	r(n-1)	+	r(n)
	r(n)	=	q(n+2)	*	r(n+1)	+	r(n+2)
	
	r(n-2)	=	q(n)	*	r(n-1)	+	r(n)
	
	---
	
	r(M-3)	=	q(M-1)	*	r(M-2)	+	r(M-1)
			=	q(M-1)	*	r(M-2)	+	1
	r(M-2)	=	q(M)	*	r(M-1)	+	r(M)
			=	q(M)	*	r(M-1)
			=:	a(M-2)	*	r(M-1)
	
	r(M-3)	=	q(M-1)	*	r(M-2)	+	r(M-1)
			=	q(M-1)	*	q(M)	*	r(M-1)	+	r(M-1)
			=	(q(M-1)	*	q(M)	+	1)		*	r(M-1)
	r(M-3)	=:	a(M-3)	*	r(M-1)
	
	let
	r(k)	=	a(k)	*	r(M-1)
	and
	r(k+1)	=	a(k+1)	*	r(M-1)
	
	r(k-1)	=	q(k+1)	*	r(k)	+	r(k+1)
			=	(q(k+1)	*	a(k)	*	r(M-1))	+	(a(k+1)	*	r(M-1))
			=	(q(k+1)	*	a(k)	+	a(k+1))	*	r(M-1)
			=	a(k-1) 	*	r(M-1)
	
	...
	
	n = a(0)
	
	
	---
	
	r-2
	a = q0b + r0
	r-1
	b = q1r0 + r1
	r0 = q2r1 + r2
	
	r0	=	a	-	q0	*	b
	
	r(k+2)	=	r(k)	
				-	q(k+2)	*	r(k+1)
	
	r(k+3)	=	r(k+1)	-	q(k+3)	*	r(k+2)
			=	r(k+1)	-	q(k+3)	*	(r(k)	-	q(k+2)	*	r(k+1))
			=	r(k+1)	*	1	+	q(k+3)	*	q(k+2)	*	r(k+1)	-	q(k+3)	*	r(k)
			=	r(k+1)	*	(1	+	q(k+3)	*	q(k+2))	-	q(k+3)	*	r(k)
	
			=	-	q(k+3)	*	r(k) 
				+ 	r(k+1)	*	(1	+	q(k+3)	*	q(k+2))
	
	
	r(M)	=:	A(M)	*	a
				+	B(M)	*	b
	
	r(0)	=	a	
				-	q(0)	*	b
			=	1	*	a
				+	(-q(0))	*	b
	1 		=: A(0)
	(-q(0))	=: B(0)
	
	r(1)	=	b	-	q(1)	r(0)
			=	b	+	(-q(1))	*	(a	+	(-q(0))	*	b)
			=	b	+	(-q(1))	*	a	+	(-q(1))	*	(-q(0))	*	b)
			=	(-q(1))	*	a
				+	(q(1)	*	q(0)	+	1)	*	b)
	(-q(1)) 					=: A(1)
	q(1)	*	q(0)	+	1	=: B(1)
	
	r(M+1)	=	r(M-1)	-	q(M+1)	*	r(M)
			=	(A(M-1)	*	a	+	B(M-1)	*	b)	
					+	(-q(M+1))	*	(A(M)	*	a	+	B(M)	*	b)
			=	A(M-1)	*	a	+	(-q(M+1))	*	A(M)	*	a
					+	B(M-1)	*	b	+	(-q(M+1))	*	B(M)	*	b
			=	a	*	(A(M-1)	+	(-q(M+1))	*	A(M))
					+	b	*	(B(M-1)	+	(-q(M+1))	*	B(M))
	A(M+1)	=	A(M-1)	+	(-q(M+1))	*	A(M)
	B(M+1)	=	B(M-1)	+	(-q(M+1))	*	B(M)
	
*/

