
#include "finite-fields/IrriduciblePolynomialsOverFiniteFieldOfSizePrime.h"

#include "test-data/IrriduciblePolynomial.h"

#include "elementary-mathematical-functions/IntegerPowers.h"
#include "finite-fields/PolynomialsOverFieldAlgorithms.h"

#include "functional-tests/schemas/FamousRSSchemas.h"

#include "gtest/gtest.h"

#include <unordered_set>

TEST( irriduciblePolynomialGenerationTest, MatchesPrecalculated )
{
	constexpr const auto output = GetIrriduciblePolynomial<101, 2>();

	EXPECT_EQ( output, irriducible );
}

namespace
{
    using GetIrriduciblePolynomialSchemas = testing::Types<
		PrimePowerGF,
        BinaryUint8GFUint32MessageUint64Codeword,
        BinaryUint16GFUint32MessageUint64Codeword
	>;

    template <typename T>
    class GetIrriduciblePolynomialTests : public testing::Test
    {
	public:
    };

    TYPED_TEST_SUITE( GetIrriduciblePolynomialTests, GetIrriduciblePolynomialSchemas );
}

// Interface Tests

TYPED_TEST( GetIrriduciblePolynomialTests, IsConstexpr )
{
	constexpr auto irr_poly{ GetIrriduciblePolynomial<TypeParam::Prime, TypeParam::Exponent>() };
}

// Functionality Tests

TYPED_TEST( GetIrriduciblePolynomialTests, DegreeIsAsExpected )
{
	const auto irr_poly{ GetIrriduciblePolynomial<TypeParam::Prime, TypeParam::Exponent>() };

	EXPECT_EQ( TypeParam::Exponent, irr_poly.GetDegree() );
	EXPECT_EQ( TypeParam::Exponent + 1, irr_poly.GetCoeffCount() );
}

TYPED_TEST( GetIrriduciblePolynomialTests, IsIrriducibleBruteForce )
{
	const auto irr_poly{ GetIrriduciblePolynomial<TypeParam::Prime, TypeParam::Exponent>() };

	// For Test Verification
	std::unordered_set<size_t> degrees_tested{};

	for( uint64_t seed{ TypeParam::Prime }; seed < int_pow( TypeParam::Prime, TypeParam::Exponent ); seed++ )
	{
		PolynomialOverPrimeSizeFiniteField<TypeParam::Prime, TypeParam::Exponent> test_divisor{};
		for( size_t coeff_index{ 0 }; coeff_index < TypeParam::Exponent; coeff_index++ )
		{
			test_divisor.SetCoeff( ( seed / int_pow( TypeParam::Prime, coeff_index ) ) % TypeParam::Prime, coeff_index );
		}

		ASSERT_EQ( false, test_divisor.IsZero() );
		ASSERT_EQ( false, test_divisor.IsOne() );

		const auto result{ LongDivideBy( irr_poly, test_divisor ) };
		EXPECT_EQ( false, result.remainder.IsZero() ) << "Divisible to seed: " << seed;

		// For Test Verification - begin
		const auto current_degree{ test_divisor.GetDegree() };
		if( ! degrees_tested.count( current_degree ) )
		{
			degrees_tested.insert( current_degree );
		}
		// - end
	}

	// For Test Verification - begin
	EXPECT_EQ( 0, degrees_tested.count( 0 ) );
	EXPECT_EQ( 1, degrees_tested.count( 1 ) );
	EXPECT_EQ( TypeParam::Exponent - 1, degrees_tested.size() );
	// - end
}

