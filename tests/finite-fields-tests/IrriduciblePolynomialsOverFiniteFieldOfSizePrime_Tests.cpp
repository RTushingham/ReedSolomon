
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

/*
TEST( irriduciblePolynomialGenerationTest, BruteForcePolyFindingForRaceOne )
{
	constexpr auto zero{ PolynomialOverPrimeSizeFiniteField<2,8 - 1>::GetAdditionInvarient() };
	
	PolynomialOverPrimeSizeFiniteField<2,8> test_divisor{};

	for( std::size_t mid_in_coeff{ 1 }; mid_in_coeff < 8; mid_in_coeff++ )
	{
		PolynomialOverPrimeSizeFiniteField<2,8> irr_poly_candidate{};
		irr_poly_candidate.Coeff( 0 ) = 1;
		irr_poly_candidate.Coeff( 2 ) = 1;
		irr_poly_candidate.Coeff( mid_in_coeff ) = 1;
		irr_poly_candidate.Coeff( 4 ) = 1;
		irr_poly_candidate.Coeff( 8 ) = 1;

		bool found_it{ true };
		for( uint64_t seed{ 2 }; seed < 32; seed++ )
		{
			std::bitset<8+1> bitset{ seed };
			for( std::size_t coeff_index{ 0 }; coeff_index < test_divisor.GetCoeffCount(); coeff_index++ )
			{
				test_divisor.Coeff( coeff_index ) = bitset.test( coeff_index );
			}

			const auto result{ irr_poly_candidate.LongDivideBy( test_divisor ) };
			if( zero == result.remainder )
			{
				found_it = false;
			}
		}

		EXPECT_FALSE( found_it ) << "Found it with mid_in_coeff: " << mid_in_coeff;
	}
}

TEST( irriduciblePolynomialGenerationTest, BruteForcePolyFindingForRaceTwo )
{
	constexpr auto zero{ PolynomialOverPrimeSizeFiniteField<2,16 - 1>::GetAdditionInvarient() };

	PolynomialOverPrimeSizeFiniteField<2,16> test_divisor{};

	for( std::size_t mid_in_coeff{ 1 }; mid_in_coeff < 16; mid_in_coeff++ )
	{
		PolynomialOverPrimeSizeFiniteField<2,16> irr_poly_candidate{};
		irr_poly_candidate.Coeff( 0 ) = 1;
		irr_poly_candidate.Coeff( 1 ) = 1;
		irr_poly_candidate.Coeff( mid_in_coeff ) = 1;
		irr_poly_candidate.Coeff( 12 ) = 1;
		irr_poly_candidate.Coeff( 16 ) = 1;

		bool found_it{ true };
		for( uint64_t seed{ 2 }; seed < 512; seed++ )
		{
			std::bitset<16+1> bitset{ seed };
			for( std::size_t coeff_index{ 0 }; coeff_index < test_divisor.GetCoeffCount(); coeff_index++ )
			{
				test_divisor.Coeff( coeff_index ) = bitset.test( coeff_index );
			}

			const auto result{ irr_poly_candidate.LongDivideBy( test_divisor ) };
			if( zero == result.remainder )
			{
				found_it = false;
			}
		}

		EXPECT_FALSE( found_it ) << "Found it with mid_in_coeff: " << mid_in_coeff;
	}
}
*/

/*

#include "tests/finite-fields-tests/helpers/InitializerHelper.h"

TEST( ElementOfFiniteFieldTests, InversionForTestCaseOne )
{
	for( integer loop_index_0 = 0; loop_index_0<2; loop_index_0++ )
	{
		for( integer loop_index_1 = 0; loop_index_1<2; loop_index_1++ )
		{
			const auto initializer = PolynomialOverPrimeSizeFiniteField<2,1>{ 
				std::array<ElementOfFiniteFieldP<Prime>,PolynomialOverPrimeSizeFiniteField<Prime,1>::GetCoeffCount()>{
					ElementOfFiniteFieldP<Prime>{ loop_index_0 },
					ElementOfFiniteFieldP<Prime>{ loop_index_1 }
				}
			};

			
			const auto a = ElementOfFiniteField<2, 16>{};
			a.value.Coeff(  )

			if( a.IsZero() )
				continue;

			EXPECT_TRUE( (a/a).IsOne() );
		}
	}
}

TEST( ElementOfFiniteFieldTests, InversionForTestCaseTwo )
{
	const auto arbitrary = PolynomialOverPrimeSizeFiniteField<Prime,1>{ 
		std::array<ElementOfFiniteFieldP<Prime>,PolynomialOverPrimeSizeFiniteField<Prime,1>::GetCoeffCount()>{
			ElementOfFiniteFieldP<Prime>{ 46 },
			ElementOfFiniteFieldP<Prime>{ 99 }
		}
	};
	const auto unwound = ElementOfFiniteField<Prime, Exponent>{
		arbitrary
	};
	EXPECT_TRUE( (unwound/unwound).IsOne() );

	for( integer loop_index_0 = 0; loop_index_0<Prime; loop_index_0++ )
	{
		for( integer loop_index_1 = 0; loop_index_1<Prime; loop_index_1++ )
		{
			const auto initializer = PolynomialOverPrimeSizeFiniteField<Prime,1>{ 
				std::array<ElementOfFiniteFieldP<Prime>,PolynomialOverPrimeSizeFiniteField<Prime,1>::GetCoeffCount()>{
					ElementOfFiniteFieldP<Prime>{ loop_index_0 },
					ElementOfFiniteFieldP<Prime>{ loop_index_1 }
				}
			};

			const auto a = ElementOfFiniteField<Prime, Exponent>{
				initializer
			};

			if( a.IsZero() )
				continue;

			EXPECT_TRUE( (a/a).IsOne() );
		}
	}
}
*/
