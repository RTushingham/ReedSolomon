#include "PolynomialsOverFiniteFieldOfSizePrime.h"

#include <iostream>

constexpr integer Prime{ 101 };

template<integer p, integer d>
std::string Print( const PolynomialOverPrimeSizeFiniteField<p,d> polynomial )
{
	std::string output{};
	bool first{ true };
	for( const auto& coefficient : polynomial.coefficients ){
		if( !first )
			output += std::string( ", " );
		output += std::string( std::to_string( coefficient.value ) );
		first = false;
	}
	
	return output;
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
			ElementOfFiniteFieldP<Prime>{ 7 },
			ElementOfFiniteFieldP<Prime>{ 9 }
		} 
	};
	PolynomialOverPrimeSizeFiniteField<Prime,1> c{ 
		std::array<ElementOfFiniteFieldP<Prime>,PolynomialOverPrimeSizeFiniteField<Prime,1>::GetCapacity()>{
			ElementOfFiniteFieldP<Prime>{ 2 },
			ElementOfFiniteFieldP<Prime>{ 3 }
		} 
	};
	
	std::cout << Print( a + b ) << std::endl;
	std::cout << "Expected:" << std::endl;
	std::cout << Print( 
		PolynomialOverPrimeSizeFiniteField<Prime,2>{ 
			std::array<ElementOfFiniteFieldP<Prime>,PolynomialOverPrimeSizeFiniteField<Prime,2>::GetCapacity()>{
				ElementOfFiniteFieldP<Prime>{ 15 },
				ElementOfFiniteFieldP<Prime>{ 18 },
				ElementOfFiniteFieldP<Prime>{ 21 }
			} 
		} 
	) << std::endl;
	std::cout << std::endl;
	
	std::cout << Print( a - b ) << std::endl;
	std::cout << "Expected:" << std::endl;
	std::cout << Print( 
		PolynomialOverPrimeSizeFiniteField<Prime,2>{ 
			std::array<ElementOfFiniteFieldP<Prime>,PolynomialOverPrimeSizeFiniteField<Prime,2>::GetCapacity()>{
				ElementOfFiniteFieldP<Prime>{ 5 },
				ElementOfFiniteFieldP<Prime>{ 4 },
				ElementOfFiniteFieldP<Prime>{ 3 }
			} 
		} 
	) << std::endl;
	std::cout << std::endl;
	
	std::cout << Print( a * c ) << std::endl;
	std::cout << "Expected:" << std::endl;
	std::cout << Print( 
		PolynomialOverPrimeSizeFiniteField<Prime,3>{ 
			std::array<ElementOfFiniteFieldP<Prime>,PolynomialOverPrimeSizeFiniteField<Prime,3>::GetCapacity()>{
				ElementOfFiniteFieldP<Prime>{ 20 },
				ElementOfFiniteFieldP<Prime>{ 52 },
				ElementOfFiniteFieldP<Prime>{ 57 },
				ElementOfFiniteFieldP<Prime>{ 36 }
			} 
		} 
	) << std::endl;
	std::cout << std::endl;
	
	
	PolynomialOverPrimeSizeFiniteField<Prime,0> x{ 
		std::array<ElementOfFiniteFieldP<Prime>,PolynomialOverPrimeSizeFiniteField<Prime,0>::GetCapacity()>{
			ElementOfFiniteFieldP<Prime>{ 12 }/ElementOfFiniteFieldP<Prime>{ 9 }
		} 
	};
	std::cout << Print( a % b ) << std::endl;
	std::cout << "Expected:" << std::endl;
	std::cout << Print( a - (x*b) ) << std::endl;
	std::cout << std::endl;
	
	
	PolynomialOverPrimeSizeFiniteField<Prime,1> y{ 
		std::array<ElementOfFiniteFieldP<Prime>,PolynomialOverPrimeSizeFiniteField<Prime,1>::GetCapacity()>{
			ElementOfFiniteFieldP<Prime>{ 1 },
			ElementOfFiniteFieldP<Prime>{ 4 }
		} 
	};
	std::cout << Print( a % c ) << std::endl;
	std::cout << "Expected:" << std::endl;
	std::cout << Print( 
		PolynomialOverPrimeSizeFiniteField<Prime,0>{ 
			std::array<ElementOfFiniteFieldP<Prime>,PolynomialOverPrimeSizeFiniteField<Prime,0>::GetCapacity()>{
				ElementOfFiniteFieldP<Prime>{ 8 }
			} 
		} 
	) << std::endl;
	std::cout << "Verification:" << std::endl;
	std::cout << Print( a - (y*c) ) << std::endl;
	std::cout << std::endl;
	
	std::cout << Print( c % a ) << std::endl;
	std::cout << "Expected:" << std::endl;
	std::cout << Print( c ) << std::endl;
}

