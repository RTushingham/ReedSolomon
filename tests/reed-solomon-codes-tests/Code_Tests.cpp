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
			std::array<ElementOfFiniteFieldP<Prime>,PolynomialOverPrimeSizeFiniteField<Prime,1>::GetCoeffCount()>{
				ElementOfFiniteFieldP<Prime>{ 9 },
				ElementOfFiniteFieldP<Prime>{ 8 }
			} 
		}
	};

	const ElementOfFiniteField<Prime, Exponent> argument_two{
		PolynomialOverPrimeSizeFiniteField<Prime,1>{
			std::array<ElementOfFiniteFieldP<Prime>,PolynomialOverPrimeSizeFiniteField<Prime,1>::GetCoeffCount()>{
				ElementOfFiniteFieldP<Prime>{ 10 },
				ElementOfFiniteFieldP<Prime>{ 11 }
			} 
		}
	};

	const ElementOfFiniteField<Prime, Exponent> argument_three{
		PolynomialOverPrimeSizeFiniteField<Prime,1>{
			std::array<ElementOfFiniteFieldP<Prime>,PolynomialOverPrimeSizeFiniteField<Prime,1>::GetCoeffCount()>{
				ElementOfFiniteFieldP<Prime>{ 12 },
				ElementOfFiniteFieldP<Prime>{ 13 }
			} 
		}
	};

	const ElementOfFiniteField<Prime, Exponent> argument_four{
		PolynomialOverPrimeSizeFiniteField<Prime,1>{
			std::array<ElementOfFiniteFieldP<Prime>,PolynomialOverPrimeSizeFiniteField<Prime,1>::GetCoeffCount()>{
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
	EXPECT_EQ( code.parameters.n, n );
	EXPECT_EQ( code.parameters.k, k );
	EXPECT_EQ( code.parameters.d, n-k+1 );
	EXPECT_EQ( code.parameters.e, (n-k)/2 );

	constexpr auto retVal{ GetReedSolomonParameters( n, k ) };
	EXPECT_EQ( code.parameters.n, retVal.n );
	EXPECT_EQ( code.parameters.k, retVal.k );
	EXPECT_EQ( code.parameters.e, retVal.e );
	EXPECT_EQ( code.parameters.e, retVal.e );
}
