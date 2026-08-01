#include "reed-solomon-codes/BlockCodeParameters.h"
#include "reed-solomon-codes/ReedSolomonBlockCodeParameters.h"

#include "functional-tests/schemas/FamousRSSchemas.h"

#include "gtest/gtest.h"

namespace
{
    template <typename T>
    class BlockCodeParameterTests : public testing::Test
    {
    public:
    };

    using BlockCodeParameterSchemas = testing::Types<
		BinaryUint8GFUint32MessageUint64Codeword,
		BinaryUint16GFUint32MessageUint64Codeword,
        PrimePowerGF
	>;

    TYPED_TEST_SUITE( BlockCodeParameterTests, BlockCodeParameterSchemas );
}

TYPED_TEST( BlockCodeParameterTests, PopulatesEFromNKandD )
{
	for( size_t d{ 0 }; d < TypeParam::n - TypeParam::k + 1; d++ )
	{
		const auto mds_params{ BlockCodeParameters::CreateFromBlockLengthMessageLengthHammingDistance( 
			TypeParam::n, 
			TypeParam::k, 
			d
		) };

		EXPECT_EQ( mds_params.n, TypeParam::n );
		EXPECT_EQ( mds_params.k, TypeParam::k );
		EXPECT_EQ( mds_params.d, d );
		EXPECT_EQ( mds_params.e, ( d - 1 ) / 2 );
	}
}

TYPED_TEST( BlockCodeParameterTests, ReedSolomonParametersReturnMDSParameters )
{
	const auto mds_params{ BlockCodeParameters::CreateFromBlockLengthMessageLengthHammingDistance( 
		TypeParam::n, 
		TypeParam::k, 
		TypeParam::n - TypeParam::k + 1
	) };

	constexpr auto retVal{ GetReedSolomonParameters( TypeParam::n, TypeParam::k ) };
	EXPECT_EQ( mds_params.n, retVal.n );
	EXPECT_EQ( mds_params.k, retVal.k );
	EXPECT_EQ( mds_params.e, retVal.e );
	EXPECT_EQ( mds_params.e, retVal.e );
}

