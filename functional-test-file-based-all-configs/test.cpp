#include "reed-solomon-codes/SimpleEncoderSchema.h"
#include "reed-solomon-codes/SystematicEncoderSchema.h"
#include "reed-solomon-decoders/GeoDecoderSchema.h"

#include "functional-test-helpers/FormatTestData.h"
#include "functional-test-helpers/LoadDataFromFile.h"
#include "functional-test-schemas/FamousRSSchemas.h"
#include "functional-test-schemas/TestTypes.h"

#include "gtest/gtest.h"
#include "gmock/gmock.h"

namespace
{
    using AllBinaryFunctionalTestSchemas = testing::Types<
		TestTypes<
			BinaryUint8GFUint32MessageUint64Codeword,
			SimpleEncoderSchema< BinaryUint8GFUint32MessageUint64Codeword::n,BinaryUint8GFUint32MessageUint64Codeword::k,BinaryUint8GFUint32MessageUint64Codeword::Prime,BinaryUint8GFUint32MessageUint64Codeword::Exponent >,
			GeoDecoderSchema< BinaryUint8GFUint32MessageUint64Codeword::n,BinaryUint8GFUint32MessageUint64Codeword::k,BinaryUint8GFUint32MessageUint64Codeword::Prime,BinaryUint8GFUint32MessageUint64Codeword::Exponent >
		>,
		TestTypes<
			BinaryUint8GFUint32MessageUint64Codeword,
			SystematicEncoderSchema< BinaryUint8GFUint32MessageUint64Codeword::n,BinaryUint8GFUint32MessageUint64Codeword::k,BinaryUint8GFUint32MessageUint64Codeword::Prime,BinaryUint8GFUint32MessageUint64Codeword::Exponent >,
			GeoDecoderSchema< BinaryUint8GFUint32MessageUint64Codeword::n,BinaryUint8GFUint32MessageUint64Codeword::k,BinaryUint8GFUint32MessageUint64Codeword::Prime,BinaryUint8GFUint32MessageUint64Codeword::Exponent >
		>,
		TestTypes<
			BinaryUint16GFUint32MessageUint64Codeword,
			SimpleEncoderSchema< BinaryUint16GFUint32MessageUint64Codeword::n,BinaryUint16GFUint32MessageUint64Codeword::k,BinaryUint16GFUint32MessageUint64Codeword::Prime,BinaryUint16GFUint32MessageUint64Codeword::Exponent >,
			GeoDecoderSchema< BinaryUint16GFUint32MessageUint64Codeword::n,BinaryUint16GFUint32MessageUint64Codeword::k,BinaryUint16GFUint32MessageUint64Codeword::Prime,BinaryUint16GFUint32MessageUint64Codeword::Exponent >
		>,
		TestTypes<
			BinaryUint16GFUint32MessageUint64Codeword,
			SystematicEncoderSchema< BinaryUint16GFUint32MessageUint64Codeword::n,BinaryUint16GFUint32MessageUint64Codeword::k,BinaryUint16GFUint32MessageUint64Codeword::Prime,BinaryUint16GFUint32MessageUint64Codeword::Exponent >,
			GeoDecoderSchema< BinaryUint16GFUint32MessageUint64Codeword::n,BinaryUint16GFUint32MessageUint64Codeword::k,BinaryUint16GFUint32MessageUint64Codeword::Prime,BinaryUint16GFUint32MessageUint64Codeword::Exponent >
		>
	>;

    template <typename T>
    class FunctionalFileBaseTests : public testing::Test
    {
	public:
		const std::string text{ LoadDataFromFile( TestDataPaths::Small_File ) };
    };

    TYPED_TEST_SUITE( FunctionalFileBaseTests, AllBinaryFunctionalTestSchemas );
}

#include "reed-solomon-codes/EncoderBase.h"

#include <numeric>

TYPED_TEST( FunctionalFileBaseTests, TestCase )
{
	constexpr size_t e{ GetReedSolomonParameters( TypeParam::m_RSSchema::n, TypeParam::m_RSSchema::k ).e };

	std::vector<size_t> error_indexes;
	error_indexes.resize( e );
	std::iota( error_indexes.begin(), error_indexes.end(), 0 );
	
	ASSERT_EQ( e, error_indexes.size() );
	ASSERT_THAT( error_indexes, ::testing::Not( ::testing::IsEmpty() ) );
	ASSERT_THAT( error_indexes, ::testing::Each( ::testing::Ge( 0 ) ) );
	ASSERT_THAT( error_indexes, ::testing::Each( ::testing::Lt( TypeParam::m_RSSchema::n ) ) );
	
	const auto outputs{ FormatTestData<TypeParam>( text, error_indexes ) };

	const auto code{ TypeParam{}.encoder };
	const auto decoder{ TypeParam{}.decoder };

	ASSERT_LT( 0, outputs.size() );
	ASSERT_EQ( 12185, outputs.size() );
	for( const auto& output : outputs )
	{
		const auto decode_res{ decoder.Decode( output.recived_signal ) };
		EXPECT_TRUE( decode_res.has_value() ) << "Seed: \"" << output.message_seed << "\", Errors: " << std::endl;
		if( decode_res.has_value() )
		{
			EXPECT_EQ( output.sent_codeword, code.GenerateCodeword( decode_res.value() ) ) << "Seed: \"" << output.message_seed << "\", Errors: " << std::endl;
		}
	}
}

