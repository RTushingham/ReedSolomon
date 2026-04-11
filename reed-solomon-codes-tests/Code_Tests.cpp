#include "reed-solomon-codes/Code.h"

#include "gtest/gtest.h"

constexpr integer Prime{ 101 };
constexpr integer Exponent{ 2 };
constexpr std::size_t n{ 4 };
constexpr std::size_t k{ 1 };

namespace
{
	
	const ElementOfFiniteField<Prime, Exponent> argument_one{
		PolynomialOverPrimeSizeFiniteField<Prime,1>{
			std::array<ElementOfFiniteFieldP<Prime>,PolynomialOverPrimeSizeFiniteField<Prime,1>::GetCapacity()>{
				ElementOfFiniteFieldP<Prime>{ 9 },
				ElementOfFiniteFieldP<Prime>{ 8 }
			} 
		}
	};

	const ElementOfFiniteField<Prime, Exponent> argument_two{
		PolynomialOverPrimeSizeFiniteField<Prime,1>{
			std::array<ElementOfFiniteFieldP<Prime>,PolynomialOverPrimeSizeFiniteField<Prime,1>::GetCapacity()>{
				ElementOfFiniteFieldP<Prime>{ 10 },
				ElementOfFiniteFieldP<Prime>{ 11 }
			} 
		}
	};

	const ElementOfFiniteField<Prime, Exponent> argument_three{
		PolynomialOverPrimeSizeFiniteField<Prime,1>{
			std::array<ElementOfFiniteFieldP<Prime>,PolynomialOverPrimeSizeFiniteField<Prime,1>::GetCapacity()>{
				ElementOfFiniteFieldP<Prime>{ 12 },
				ElementOfFiniteFieldP<Prime>{ 13 }
			} 
		}
	};

	const ElementOfFiniteField<Prime, Exponent> argument_four{
		PolynomialOverPrimeSizeFiniteField<Prime,1>{
			std::array<ElementOfFiniteFieldP<Prime>,PolynomialOverPrimeSizeFiniteField<Prime,1>::GetCapacity()>{
				ElementOfFiniteFieldP<Prime>{ 14 },
				ElementOfFiniteFieldP<Prime>{ 15 }
			} 
		}
	};

	const std::array<ElementOfFiniteField<Prime, Exponent>,n> generators{ argument_one, argument_two, argument_three, argument_four };
	Code<n, k, Prime, Exponent> code{ std::array<ElementOfFiniteField<Prime, Exponent>,n>{ generators } };
}


TEST( CodeTests, BlockCodeParameters )
{
	EXPECT_EQ( code.n, n );
	EXPECT_EQ( code.k, k );
	EXPECT_EQ( code.hamming_distance, n-k+1 );
	EXPECT_EQ( code.e(), (code.hamming_distance -1)/2 );
	EXPECT_EQ( code.e(), (n-k)/2 );
}
