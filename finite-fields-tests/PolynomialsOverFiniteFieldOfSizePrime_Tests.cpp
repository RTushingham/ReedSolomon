
#include "finite-fields/PolynomialsOverFiniteFieldOfSizePrime.h"

#include "finite-fields-tests/helpers/InitializerHelper.h"

#include "gtest/gtest.h"

namespace
{
	constexpr integer Prime{ 101 };

	PolynomialOverPrimeSizeFiniteField<Prime,2> a{
		( x_to( 10,0 ) + x_to( 11, 1 ) + x_to( 12, 2 ) ).evaluate<PolynomialOverPrimeSizeFiniteField<Prime,2>>()
	};
	PolynomialOverPrimeSizeFiniteField<Prime,2> b{ 
		( x_to(  5,0 ) + x_to(  7, 1 ) + x_to(  9, 2 ) ).evaluate<PolynomialOverPrimeSizeFiniteField<Prime,2>>()
	};
}

TEST( PolynomialsOverPrimeFieldTests, Addition )
{
	const auto expected{
		( x_to( 15,0 ) + x_to( 18, 1 ) + x_to( 21, 2 ) ).evaluate<PolynomialOverPrimeSizeFiniteField<Prime,2>>()
	};

	EXPECT_EQ( a + b, expected );
}

TEST( PolynomialsOverPrimeFieldTests, Subtraction )
{
	const auto expected{
		( x_to(  5,0 ) + x_to(  4, 1 ) + x_to(  3, 2 ) ).evaluate<PolynomialOverPrimeSizeFiniteField<Prime,2>>()
	};

	EXPECT_EQ( a - b, expected );
}

namespace
{
	PolynomialOverPrimeSizeFiniteField<Prime,1> c{ 
		std::array<ElementOfFiniteFieldP<Prime>,PolynomialOverPrimeSizeFiniteField<Prime,1>::GetCoeffCount()>{
			ElementOfFiniteFieldP<Prime>{ 2 },
			ElementOfFiniteFieldP<Prime>{ 3 }
		}
	};
}

TEST( PolynomialsOverPrimeFieldTests, Multiplication )
{
	const auto expected = PolynomialOverPrimeSizeFiniteField<Prime,3>{ 
		std::array<ElementOfFiniteFieldP<Prime>,PolynomialOverPrimeSizeFiniteField<Prime,3>::GetCoeffCount()>{
			ElementOfFiniteFieldP<Prime>{ 20 },
			ElementOfFiniteFieldP<Prime>{ 52 },
			ElementOfFiniteFieldP<Prime>{ 57 },
			ElementOfFiniteFieldP<Prime>{ 36 }
		} 
	};

	EXPECT_EQ( a * c, expected );
}

TEST( PolynomialsOverPrimeFieldTests, MultiplicationUpToSameDegree )
{
	const auto expected = PolynomialOverPrimeSizeFiniteField<Prime,2>{ 
		std::array<ElementOfFiniteFieldP<Prime>,PolynomialOverPrimeSizeFiniteField<Prime,2>::GetCoeffCount()>{
			ElementOfFiniteFieldP<Prime>{ 50 },
			ElementOfFiniteFieldP<Prime>{ 24 },
			ElementOfFiniteFieldP<Prime>{ 25 }
		} 
	};

	EXPECT_EQ( a.MultiplyUpToSameDegree( b ), expected );
}

namespace
{
	const PolynomialOverPrimeSizeFiniteField<Prime,0> abQuotient{
 		std::array<ElementOfFiniteFieldP<Prime>,PolynomialOverPrimeSizeFiniteField<Prime,0>::GetCoeffCount()>{
 			ElementOfFiniteFieldP<Prime>{ 12 }/ElementOfFiniteFieldP<Prime>{ 9 }
 		} 
 	};

	const auto acQuotient{
		( x_to(  1,0 ) + x_to(  4,1 ) ).evaluate<PolynomialOverPrimeSizeFiniteField<Prime,1>>()
	};
	const auto acRemainder{
		( x_to(  8,0 ) ).evaluate<PolynomialOverPrimeSizeFiniteField<Prime,0>>()
	};
}

TEST( PolynomialsOverPrimeFieldTests, LongDivision )
{
	EXPECT_EQ( LongDivideBy( a, c ).remainder, acRemainder.Oversize<1>() );
	EXPECT_EQ( LongDivideBy( a, c ).quotient, acQuotient );
	
	EXPECT_EQ( LongDivideBy( a, b ).quotient, abQuotient.Oversize<1>() );
	EXPECT_EQ( a, LongDivideBy( a, b ).remainder.Oversize<2>() + ( LongDivideBy( a, b ).quotient.Downsize<0>() * b ) );

	constexpr auto zero{ PolynomialOverPrimeSizeFiniteField<Prime,2>::GetAdditionInvarient() };

	EXPECT_TRUE( LongDivideBy( zero, c ).remainder.IsZero() );
	EXPECT_TRUE( LongDivideBy( zero, c ).quotient.IsZero() );
}

TEST( PolynomialsOverPrimeFieldTests, LongDivisionMaxPossibleQuotientSize )
{
	const auto d{
		( x_to(  5,0 ) ).evaluate<PolynomialOverPrimeSizeFiniteField<Prime,2>>()
	};

	ASSERT_TRUE( a.tmp_GetDegree().has_value() );
	ASSERT_TRUE( d.tmp_GetDegree().has_value() );
	ASSERT_EQ( a.GetMaxDegree(), a.tmp_GetDegree().value() - d.tmp_GetDegree().value() ) << "Test case aims at case where quotient is a big as theoretically possible.";

	// TODO:
	//   - Fix this
	//       - ATM this case never comes up. Long division is only used for % irr_poly or in
	// const auto a_div_d_result{ a.LongDivideBy( d ) };
	// EXPECT_EQ( a, ( d*a_div_d_result.quotient ).ToSize<a.GetMaxDegree()>() + a_div_d_result.remainder.ToSize<a.GetMaxDegree()>() );
}

TEST( PolynomialsOverPrimeFieldTests, ClassIsConstexprInstantiable )
{
	constexpr PolynomialOverPrimeSizeFiniteField<Prime,0> const_expr{ 
		std::array<ElementOfFiniteFieldP<Prime>,PolynomialOverPrimeSizeFiniteField<Prime,0>::GetCoeffCount()>{
			ElementOfFiniteFieldP<Prime>{ 12 }/ElementOfFiniteFieldP<Prime>{ 9 }
		} 
	};
}

TEST( PolynomialsOverPrimeFieldTests, ValueInitializable )
{
	PolynomialOverPrimeSizeFiniteField<Prime,0> val_init{};

	const auto zero{ PolynomialOverPrimeSizeFiniteField<Prime,0>::GetAdditionInvarient() };
	EXPECT_EQ( val_init, zero );
}

TEST( PolynomialsOverPrimeFieldTests, AdditionInvarientHelperConstexpr )
{
	constexpr auto zero{ PolynomialOverPrimeSizeFiniteField<Prime,0>::GetAdditionInvarient() };
}

TEST( PolynomialsOverPrimeFieldTests, AdditionInvariantIsZero )
{
	const auto zero{ PolynomialOverPrimeSizeFiniteField<Prime,2>::GetAdditionInvarient() };

	EXPECT_TRUE( zero.IsZero() );
	EXPECT_FALSE( zero.IsOne() );
}

TEST( PolynomialsOverPrimeFieldTests, MultiplicativeInvariantIsOne )
{
	auto one{ PolynomialOverPrimeSizeFiniteField<Prime,2>::GetMultiplicativeInvarient() };	

	EXPECT_FALSE( one.IsZero() );
	EXPECT_TRUE( one.IsOne() );
}
