#include "reed-solomon-codes/Schema.h"

#include "functional-tests/schemas/FamousRSSchemas.h"

#include "gtest/gtest.h"

#include <type_traits>

namespace
{
    template <typename T>
    class SchemaTests : public testing::Test
    {
    public:
    };

    using IEncoderSchemaImpls = testing::Types<
		BinaryUint8GFUint32MessageUint64Codeword,
		BinaryUint16GFUint32MessageUint64Codeword,
        PrimePowerGF
	>;

    TYPED_TEST_SUITE( SchemaTests, IEncoderSchemaImpls );
}

// Interface Tests

TYPED_TEST( SchemaTests, IsConstexprConstructable )
{
	// checking copy
	constexpr Schema<TypeParam::n, TypeParam::k, TypeParam::Prime, TypeParam::Exponent> copy{ TypeParam::schema };
}

TYPED_TEST( SchemaTests, IsLiteralType )
{
	constexpr bool is_literal_type{ 
		std::is_literal_type_v<
			Schema<TypeParam::n, TypeParam::k, TypeParam::Prime, TypeParam::Exponent>
		>
	};
	ASSERT_TRUE( is_literal_type );
}

// Functionality Tests
//   - These are trivial as this is just a wrapper around an array

// Safety Tests

TYPED_TEST( SchemaTests, ConstructorThrowsIfElementsAreNotDistinct )
{
	std::array<ElementOfFiniteField<TypeParam::Prime, TypeParam::Exponent>, TypeParam::n> array_of_1s{};
	for( auto& gen : array_of_1s )
	{
		gen = ElementOfFiniteField<TypeParam::Prime, TypeParam::Exponent>::GetMultiplicativeInvarient();
	}
	std::array<ElementOfFiniteField<TypeParam::Prime, TypeParam::Exponent>, TypeParam::n> array_of_0s{};
	for( auto& gen : array_of_0s )
	{
		gen = ElementOfFiniteField<TypeParam::Prime, TypeParam::Exponent>::GetAdditionInvarient();
	}
	
	// This is a workaround for the fact that on my version of GTest template parameters in EXPECT statements results in the error:
	//   "warning C4002: too many arguments"
	auto construction_lambda = []( const auto& gen )
	{
		return Schema<TypeParam::n, TypeParam::k, TypeParam::Prime, TypeParam::Exponent>{ gen };
	};

	EXPECT_ANY_THROW( construction_lambda( array_of_1s ) );
	EXPECT_ANY_THROW( construction_lambda( array_of_0s ) );
}

