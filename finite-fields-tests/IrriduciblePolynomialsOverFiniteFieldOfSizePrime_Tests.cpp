
#include "finite-fields/IrriduciblePolynomialsOverFiniteFieldOfSizePrime.h"

#include "finite-fields/PolynomialsOverFieldAlgorithms.h"
#include "test-data/IrriduciblePolynomial.h"

#include "gtest/gtest.h"

TEST( irriduciblePolynomialGenerationTest, MatchesPrecalculated )
{
	constexpr const auto output = GetIrriduciblePolynomial<101, 2>();

	EXPECT_EQ( output, irriducible );
}

TEST( irriduciblePolynomialGenerationTest, Slow )
{
	constexpr const auto output = GetIrriduciblePolynomial<101, 27>();

	// haven't calculated this yet
	EXPECT_NE( output, irriducible.Oversize<27>() );
}

//

#include <bitset>

TEST( irriduciblePolynomialGenerationTest, RaceOneSetupTest )
{
	constexpr const auto irr_poly_candidate{ GetIrriduciblePolynomial<2, 8>() };

	PolynomialOverPrimeSizeFiniteField<2,8> test_divisor{};

	constexpr auto zero{ PolynomialOverPrimeSizeFiniteField<2,8 - 1>::GetAdditionInvarient() };
	for( uint64_t seed{ 2 }; seed < 32; seed++ )
	{
		std::bitset<8+1> bitset{ seed };
		for( std::size_t coeff_index{ 0 }; coeff_index < test_divisor.GetCoeffCount(); coeff_index++ )
		{
			test_divisor.SetCoeff( bitset.test( coeff_index ), coeff_index );
		}

		const auto result{ LongDivideBy( irr_poly_candidate, test_divisor ) };
		EXPECT_NE( result.remainder, zero ) << "Divisible to seed: " << seed;
	}
}

TEST( irriduciblePolynomialGenerationTest, RaceTwoSetupTest )
{
	constexpr const auto irr_poly_candidate{ GetIrriduciblePolynomial<2, 16>() };

	PolynomialOverPrimeSizeFiniteField<2,16> test_divisor{};

	constexpr auto zero{ PolynomialOverPrimeSizeFiniteField<2,16 - 1>::GetAdditionInvarient() };
	for( uint64_t seed{ 2 }; seed < 512; seed++ )
	{
		std::bitset<16+1> bitset{ seed };
		for( std::size_t coeff_index{ 0 }; coeff_index < test_divisor.GetCoeffCount(); coeff_index++ )
		{
			test_divisor.SetCoeff( bitset.test( coeff_index ), coeff_index );
		}

		const auto result{ LongDivideBy( irr_poly_candidate, test_divisor ) };
		EXPECT_NE( result.remainder, zero ) << "Divisible to seed: " << seed;
	}
}

