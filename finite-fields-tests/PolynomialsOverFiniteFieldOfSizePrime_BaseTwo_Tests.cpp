
#include "finite-fields/PolynomialsOverFiniteFieldOfSizePrime.h"

#include "gtest/gtest.h"

#include <bitset>

namespace
{
	constexpr integer Prime{ 2 };
}

TEST( PolynomialsOverPrimeFieldBaseTwoTests, GetCoeffAllZero )
{
	PolynomialOverPrimeSizeFiniteField<Prime,7> value{ 0 };
	EXPECT_TRUE( value.IsZero() );

	constexpr auto zero{ ElementOfFiniteFieldP<2>::GetAdditionInvarient() };
	for( std::size_t index{ 0 }; index < value.GetCoeffCount(); index++ )
	{
		const auto capture{ value.GetCoeff( index ) };
		EXPECT_EQ( zero, capture );
		EXPECT_TRUE( capture.IsZero() );
	}
}

TEST( PolynomialsOverPrimeFieldBaseTwoTests, GetCoeffAllOne )
{
	PolynomialOverPrimeSizeFiniteField<Prime,7> value{ (uint8_t)-1 };

	constexpr auto one{ ElementOfFiniteFieldP<2>::GetMultiplicativeInvarient() };
	for( std::size_t index{ 0 }; index < value.GetCoeffCount(); index++ )
	{
		const auto capture{ value.GetCoeff( index ) };
		EXPECT_EQ( one, capture );
		EXPECT_TRUE( capture.IsOne() );
	}
}

TEST( PolynomialsOverPrimeFieldBaseTwoTests, GetCoeffPredefined )
{
	std::bitset<PolynomialOverPrimeSizeFiniteField<Prime,7>::GetCoeffCount()> definition{ 0b10011 };

	PolynomialOverPrimeSizeFiniteField<Prime,7> value{ (uint8_t)definition.to_ullong() };

	for( std::size_t index{ 0 }; index < value.GetCoeffCount(); index++ )
	{
		const auto capture{ value.GetCoeff( index ) };
		if( definition.test( index ) )
		{
			EXPECT_TRUE( capture.IsOne() );
		}
		else
		{
			EXPECT_TRUE( capture.IsZero() );
		}
	}
}

//

TEST( PolynomialsOverPrimeFieldBaseTwoTests, SetCoeffAllZero )
{
	PolynomialOverPrimeSizeFiniteField<Prime,7> value{ (uint8_t)-1 };

	constexpr auto zero{ ElementOfFiniteFieldP<2>::GetAdditionInvarient() };
	for( std::size_t index{ 0 }; index < value.GetCoeffCount(); index++ )
	{
		value.SetCoeff( zero, index );
	}

	EXPECT_TRUE( value.IsZero() );
}

TEST( PolynomialsOverPrimeFieldBaseTwoTests, SetCoeffPredefined )
{

	std::bitset<PolynomialOverPrimeSizeFiniteField<Prime,7>::GetCoeffCount()> definition{ 0b1001010 };

	PolynomialOverPrimeSizeFiniteField<Prime,7> value{ (uint8_t)definition.to_ullong() };
	const auto initial_value{ value };

	ASSERT_FALSE( definition.test( 2 ) );

	constexpr auto one{ ElementOfFiniteFieldP<2>::GetMultiplicativeInvarient() };

	value.SetCoeff( one, 2 );

	auto expected_definition{ definition };
	expected_definition.set( 2 );
	PolynomialOverPrimeSizeFiniteField<Prime,7> expected{ (uint8_t)expected_definition.to_ullong() };

	EXPECT_EQ( value, expected );
}

//

TEST( PolynomialsOverPrimeFieldBaseTwoTests, MultiplyUpToSameDegreeTruncatesCorrectly )
{
	PolynomialOverPrimeSizeFiniteField<Prime,1> value{ (uint8_t)0b11 };

	PolynomialOverPrimeSizeFiniteField<Prime,1> expected{ (uint8_t)0b01 };

	EXPECT_EQ( value.MultiplyUpToSameDegree( value ), expected );
}

TEST( PolynomialsOverPrimeFieldBaseTwoTests, MultiplyUpToSameDegreeNoTruncationRequired )
{
	PolynomialOverPrimeSizeFiniteField<Prime,3> value{ (uint8_t)0b0011 };

	PolynomialOverPrimeSizeFiniteField<Prime,3> expected{ (uint8_t)0b0101 };

	EXPECT_EQ( value.MultiplyUpToSameDegree( value ), expected );
}

TEST( PolynomialsOverPrimeFieldBaseTwoTests, Multiplication )
{
	PolynomialOverPrimeSizeFiniteField<Prime,1> value{ (uint8_t)0b11 };

	PolynomialOverPrimeSizeFiniteField<Prime,2> expected{ (uint8_t)0b101 };

	EXPECT_EQ( value*value, expected );
}

//

TEST( PolynomialsOverPrimeFieldBaseTwoTests, ScalarMultiplication )
{
	PolynomialOverPrimeSizeFiniteField<Prime,3> value{ (uint8_t)0b0101 };

	constexpr auto zero{ ElementOfFiniteFieldP<2>::GetAdditionInvarient() };
	constexpr auto one{ ElementOfFiniteFieldP<2>::GetMultiplicativeInvarient() };

	EXPECT_EQ( value.ScalarMultiplication( one ), value );
	EXPECT_TRUE( value.ScalarMultiplication( zero ).IsZero() );
}

