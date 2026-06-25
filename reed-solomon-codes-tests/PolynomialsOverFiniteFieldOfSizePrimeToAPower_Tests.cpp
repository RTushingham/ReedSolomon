#include "reed-solomon-codes/PolynomialsOverFiniteFieldOfSizePrimeToAPower.h"

#include "finite-fields-tests/test-data/IrriduciblePolynomial.h"
#include "polynomials-base-tests/helpers/InitializerHelper.h"

#include "gtest/gtest.h"

constexpr integer Prime{ 101 };
constexpr integer Exponent{ 2 };

namespace
{
	constexpr integer MaxDegree = 1;

	const std::array<ElementOfFiniteField<Prime, Exponent>,MaxDegree+1> initializer{
		ElementOfFiniteField<Prime, Exponent>{
			( x_to(  4,0 ) + x_to(  5, 1 ) ).evaluate<PolynomialOverPrimeSizeFiniteField<Prime,1>>()
		},
		ElementOfFiniteField<Prime, Exponent>{
			( x_to(  7,0 ) + x_to(  6, 1 ) ).evaluate<PolynomialOverPrimeSizeFiniteField<Prime,1>>()
		}
	};

	PolynomialOverFiniteField<Prime,Exponent,MaxDegree> polynomial{ 
		initializer 
	};
}


TEST( TestDataVerifictaion, IrriducibleIsAsAssumed )
{
	const auto assumed{
		( x_to( -2,0 ) + x_to(  1, 2 ) ).evaluate<PolynomialOverPrimeSizeFiniteField<Prime,2>>()
	};
	ASSERT_EQ( irriducible, assumed ) << "This layer of indirection is so that expensive tests which verify irriducibility can be kept separate and only run if irriducible changes.";
}

TEST( PolynomialOverFiniteFieldTests, EvaluationOne )
{
	const ElementOfFiniteField<Prime, Exponent> argument{
		( x_to(  9,0 ) + x_to(  8, 1 ) ).evaluate<PolynomialOverPrimeSizeFiniteField<Prime,1>>()
	};

	const ElementOfFiniteField<Prime, Exponent> expected{
		( x_to( 62,0 ) + x_to( 14, 1 ) ).evaluate<PolynomialOverPrimeSizeFiniteField<Prime,1>>()
	};

	EXPECT_EQ( polynomial( argument ), expected );
}

TEST( PolynomialOverFiniteFieldTests, EvaluationTwo )
{
	const ElementOfFiniteField<Prime, Exponent> argument{
		( x_to( 10,0 ) + x_to( 11, 1 ) ).evaluate<PolynomialOverPrimeSizeFiniteField<Prime,1>>()
	};

	const ElementOfFiniteField<Prime, Exponent> expected{
		( x_to(  4,0 ) + x_to( 41, 1 ) ).evaluate<PolynomialOverPrimeSizeFiniteField<Prime,1>>()
	};

	EXPECT_EQ( polynomial( argument ), expected );
}

TEST( PolynomialOverFiniteFieldTests, EvaluationThree )
{
	const ElementOfFiniteField<Prime, Exponent> argument{
		( x_to( 12,0 ) + x_to( 13, 1 ) ).evaluate<PolynomialOverPrimeSizeFiniteField<Prime,1>>()
	};

	const ElementOfFiniteField<Prime, Exponent> expected{
		( x_to( 42,0 ) + x_to( 67, 1 ) ).evaluate<PolynomialOverPrimeSizeFiniteField<Prime,1>>()
	};

	EXPECT_EQ( polynomial( argument ), expected );
}

TEST( PolynomialOverFiniteFieldTests, EvaluationFour )
{
	const ElementOfFiniteField<Prime, Exponent> argument{
		( x_to( 14,0 ) + x_to( 15, 1 ) ).evaluate<PolynomialOverPrimeSizeFiniteField<Prime,1>>()
	};

	const ElementOfFiniteField<Prime, Exponent> expected{
		( x_to( 80,0 ) + x_to( 93, 1 ) ).evaluate<PolynomialOverPrimeSizeFiniteField<Prime,1>>()
	};

	EXPECT_EQ( polynomial( argument ), expected );
}

TEST( PolynomialsOverPrimeFieldTests, LongDivision )
{
	PolynomialOverFiniteField<Prime,Exponent,MaxDegree> c
	{
        std::array<ElementOfFiniteField<Prime, Exponent>, MaxDegree+1>
        {
            ElementOfFiniteField<Prime, Exponent>{
                (x_to( 11,0 ) + x_to( 13, 1 )).evaluate<PolynomialOverPrimeSizeFiniteField<Prime,1>>()
            },
            ElementOfFiniteField<Prime, Exponent>{
                (x_to( 17,0 ) + x_to( 19, 1 )).evaluate<PolynomialOverPrimeSizeFiniteField<Prime,1>>()
            }
        }
	};
	constexpr auto zero{ PolynomialOverFiniteField<Prime,Exponent,MaxDegree+1>::GetAdditionInvarient() };

	EXPECT_TRUE( LongDivideBy( zero, c ).remainder.IsZero() );
	EXPECT_TRUE( LongDivideBy( zero, c ).quotient.IsZero() );
}
