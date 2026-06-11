#include "finite-fields/PolynomialsOverFiniteFieldOfSizePrime.h"

#include "polynomials-base/InitializerHelper.h"

#include "gtest/gtest.h"

constexpr integer Prime{ 101 };

TEST( InitializerHelperTests, EvaluationOneTerm )
{
	PolynomialOverPrimeSizeFiniteField<Prime,2> a_first_term{ 
		std::array<ElementOfFiniteFieldP<Prime>,PolynomialOverPrimeSizeFiniteField<Prime,2>::GetCapacity()>{
			ElementOfFiniteFieldP<Prime>{ 10 },
			ElementOfFiniteFieldP<Prime>{ 0 },
			ElementOfFiniteFieldP<Prime>{ 0 }
		} 
	};

	PolynomialOverPrimeSizeFiniteField<Prime,2> base{};
	x_to( 10, 0 ).mod( base );
	
	EXPECT_EQ( a_first_term, base );
}

TEST( InitializerHelperTests, EvaluationMultipleTerms )
{
	PolynomialOverPrimeSizeFiniteField<Prime,2> a_first_term{ 
		std::array<ElementOfFiniteFieldP<Prime>,PolynomialOverPrimeSizeFiniteField<Prime,2>::GetCapacity()>{
			ElementOfFiniteFieldP<Prime>{ 10 },
			ElementOfFiniteFieldP<Prime>{ 0 },
			ElementOfFiniteFieldP<Prime>{ 12 }
		} 
	};

	PolynomialOverPrimeSizeFiniteField<Prime,2> base{};
	( x_to( 10, 0 ) + x_to( 12, 2 ) ).mod( base );
	
	EXPECT_EQ( a_first_term, base );
}

TEST( InitializerHelperTests, ConstructContexpr )
{
	PolynomialOverPrimeSizeFiniteField<Prime,2> a_first_term{ 
		std::array<ElementOfFiniteFieldP<Prime>,PolynomialOverPrimeSizeFiniteField<Prime,2>::GetCapacity()>{
			ElementOfFiniteFieldP<Prime>{ 10 },
			ElementOfFiniteFieldP<Prime>{ 11 },
			ElementOfFiniteFieldP<Prime>{ 12 }
		} 
	};

	constexpr auto val{ ( x_to( 10, 0 ) + x_to( 12, 2 ) + x_to( 11, 1 ) ).evaluate<PolynomialOverPrimeSizeFiniteField<Prime,2>>() };
	
	EXPECT_EQ( a_first_term, val );
}
