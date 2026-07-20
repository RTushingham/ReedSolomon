#include "finite-fields-polynomials/PolynomialsOverFiniteFieldOfSizePrimeToAPower.h"

#include "tests/finite-fields-tests/helpers/InitializerHelper.h"

#include "gtest/gtest.h"

constexpr integer Prime{ 101 };
constexpr integer Exponent{ 2 };
constexpr integer MaxDegree{ 1 };

TEST( InitializerHelperTests, ConstructContexpr )
{
	const std::array<ElementOfFiniteField<Prime, Exponent>,MaxDegree+1> initializer{
		ElementOfFiniteField<Prime, Exponent>{
			PolynomialOverPrimeSizeFiniteField<Prime,1>{ 
				std::array<ElementOfFiniteFieldP<Prime>,PolynomialOverPrimeSizeFiniteField<Prime,1>::GetCoeffCount()>{
					ElementOfFiniteFieldP<Prime>{ 4 },
					ElementOfFiniteFieldP<Prime>{ 5 }
				} 
			}
		},
		ElementOfFiniteField<Prime, Exponent>{
			PolynomialOverPrimeSizeFiniteField<Prime,1>{
				std::array<ElementOfFiniteFieldP<Prime>,PolynomialOverPrimeSizeFiniteField<Prime,1>::GetCoeffCount()>{
					ElementOfFiniteFieldP<Prime>{ 7 },
					ElementOfFiniteFieldP<Prime>{ 6 }
				} 
			}
		}
	};

	PolynomialOverFiniteField<Prime,Exponent,MaxDegree> polynomial{ 
		initializer 
	};

	constexpr auto val{
		(
			x_to(
				( x_to( 4, 0 ) + x_to( 5, 1 ) ).evaluate<PolynomialOverPrimeSizeFiniteField<Prime,1>>(),
				0
			)
			+ x_to(
				( x_to( 7, 0 ) + x_to( 6, 1 ) ).evaluate<PolynomialOverPrimeSizeFiniteField<Prime,1>>(),
				1
			)
		).evaluate<PolynomialOverFiniteField<Prime,Exponent,MaxDegree>>()
	};
	
	EXPECT_EQ( polynomial, val );
}
