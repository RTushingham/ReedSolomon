#include "finite-fields/PolynomialsOverFiniteFieldOfSizePrime.h"

#include "polynomials-base-tests/helpers/InitializerHelper.h"

#include "gtest/gtest.h"

constexpr integer Prime{ 101 };

TEST( InitializerHelperTests, EvaluationOneTerm )
{
	auto a_first_term{
		( x_to( 10,0 ) ).evaluate<PolynomialOverPrimeSizeFiniteField<Prime,2>>()
	};

	PolynomialOverPrimeSizeFiniteField<Prime,2> base{};
	x_to( 10, 0 ).mod( base );
	
	EXPECT_EQ( a_first_term, base );
}

TEST( InitializerHelperTests, EvaluationMultipleTerms )
{
	auto a_first_term{
		( x_to( 10,0 ) + x_to( 12,2 ) ).evaluate<PolynomialOverPrimeSizeFiniteField<Prime,2>>()
	};

	PolynomialOverPrimeSizeFiniteField<Prime,2> base{};
	( x_to( 10, 0 ) + x_to( 12, 2 ) ).mod( base );
	
	EXPECT_EQ( a_first_term, base );
}

TEST( InitializerHelperTests, ConstructContexpr )
{
	auto a_first_term{
		( x_to( 10,0 ) + x_to( 11,1 ) + x_to( 12,2 ) ).evaluate<PolynomialOverPrimeSizeFiniteField<Prime,2>>()
	};

	constexpr auto val{ ( x_to( 10, 0 ) + x_to( 12, 2 ) + x_to( 11, 1 ) ).evaluate<PolynomialOverPrimeSizeFiniteField<Prime,2>>() };
	
	EXPECT_EQ( a_first_term, val );
}
