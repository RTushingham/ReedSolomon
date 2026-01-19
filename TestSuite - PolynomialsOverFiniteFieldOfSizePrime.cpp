#include "PolynomialsOverFiniteFieldOfSizePrime.h"

#include <iostream>

constexpr integer Prime{ 101 };

template<integer p, integer d>
Print( const PolynomialOverPrimeSizeFiniteField<p,d>& polynomial )
{
	for( const auto& coefficient : polynomial.coefficients ){
		std::cout << coefficient.value << ", ";
	}
	std::cout << std::endl;
}

int main()
{
	PolynomialOverPrimeSizeFiniteField<Prime,2> a{ 
		std::array<ElementOfFiniteFieldP<Prime>,PolynomialOverPrimeSizeFiniteField<Prime,2>::GetCapacity()>{
			ElementOfFiniteFieldP<Prime>{ 10 },
			ElementOfFiniteFieldP<Prime>{ 11 },
			ElementOfFiniteFieldP<Prime>{ 12 }
		} 
	};
	PolynomialOverPrimeSizeFiniteField<Prime,2> b{ 
		std::array<ElementOfFiniteFieldP<Prime>,PolynomialOverPrimeSizeFiniteField<Prime,2>::GetCapacity()>{
			ElementOfFiniteFieldP<Prime>{ 5 },
			ElementOfFiniteFieldP<Prime>{ 6 },
			ElementOfFiniteFieldP<Prime>{ 7 }
		} 
	};
	PolynomialOverPrimeSizeFiniteField<Prime,1> c{ 
		std::array<ElementOfFiniteFieldP<Prime>,PolynomialOverPrimeSizeFiniteField<Prime,1>::GetCapacity()>{
			ElementOfFiniteFieldP<Prime>{ 2 },
			ElementOfFiniteFieldP<Prime>{ 3 }
		} 
	};
	
	Print( a + b );
	Print( a - b );
	Print( a * c );
}

