#include "reed-solomon-codes/ReedSolomonBlockCodeParameters.h"
#include "reed-solomon-codes/SimpleEncoderSchema.h"
#include "reed-solomon-codes/SystematicEncoderSchema.h"
#include "reed-solomon-decoders/ErasureDecoderSchema.h"

#include "functional-tests/helpers/FormatTestData_Erasure.h"
#include "functional-tests/helpers/LoadDataFromFile.h"
#include "functional-tests/schemas/FamousRSSchemas.h"
#include "functional-tests/schemas/TestTypes_Erasure.h"

#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include <bitset>

namespace
{
    using AllBinaryFunctionalTestSchemas = testing::Types<
		TestTypes_Erasure<
			BinaryUint8GFUint32MessageUint64Codeword,
			SimpleEncoderSchema< BinaryUint8GFUint32MessageUint64Codeword::n,BinaryUint8GFUint32MessageUint64Codeword::k,BinaryUint8GFUint32MessageUint64Codeword::Prime,BinaryUint8GFUint32MessageUint64Codeword::Exponent >,
			ErasureDecoderSchema< BinaryUint8GFUint32MessageUint64Codeword::n,BinaryUint8GFUint32MessageUint64Codeword::k,BinaryUint8GFUint32MessageUint64Codeword::Prime,BinaryUint8GFUint32MessageUint64Codeword::Exponent >
		>,
		TestTypes_Erasure<
			BinaryUint8GFUint32MessageUint64Codeword,
			SystematicEncoderSchema< BinaryUint8GFUint32MessageUint64Codeword::n,BinaryUint8GFUint32MessageUint64Codeword::k,BinaryUint8GFUint32MessageUint64Codeword::Prime,BinaryUint8GFUint32MessageUint64Codeword::Exponent >,
			ErasureDecoderSchema< BinaryUint8GFUint32MessageUint64Codeword::n,BinaryUint8GFUint32MessageUint64Codeword::k,BinaryUint8GFUint32MessageUint64Codeword::Prime,BinaryUint8GFUint32MessageUint64Codeword::Exponent >
		>,
		TestTypes_Erasure<
			BinaryUint16GFUint32MessageUint64Codeword,
			SimpleEncoderSchema< BinaryUint16GFUint32MessageUint64Codeword::n,BinaryUint16GFUint32MessageUint64Codeword::k,BinaryUint16GFUint32MessageUint64Codeword::Prime,BinaryUint16GFUint32MessageUint64Codeword::Exponent >,
			ErasureDecoderSchema< BinaryUint16GFUint32MessageUint64Codeword::n,BinaryUint16GFUint32MessageUint64Codeword::k,BinaryUint16GFUint32MessageUint64Codeword::Prime,BinaryUint16GFUint32MessageUint64Codeword::Exponent >
		>,
		TestTypes_Erasure<
			BinaryUint16GFUint32MessageUint64Codeword,
			SystematicEncoderSchema< BinaryUint16GFUint32MessageUint64Codeword::n,BinaryUint16GFUint32MessageUint64Codeword::k,BinaryUint16GFUint32MessageUint64Codeword::Prime,BinaryUint16GFUint32MessageUint64Codeword::Exponent >,
			ErasureDecoderSchema< BinaryUint16GFUint32MessageUint64Codeword::n,BinaryUint16GFUint32MessageUint64Codeword::k,BinaryUint16GFUint32MessageUint64Codeword::Prime,BinaryUint16GFUint32MessageUint64Codeword::Exponent >
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

TYPED_TEST( FunctionalFileBaseTests, ErasuresAreCheckBits )
{
	constexpr size_t S{ GetReedSolomonParameters( TypeParam::m_RSSchema::n, TypeParam::m_RSSchema::k ).d - 1 };

	std::vector<size_t> erasure_indexes;
	erasure_indexes.resize( S );
	std::iota( erasure_indexes.begin(), erasure_indexes.end(), 0 );
	
	std::bitset<TypeParam::m_RSSchema::n> erasures{ 0 };
	for( const size_t index : erasure_indexes )
	{
		erasures.set( index );
	}
	ASSERT_EQ( S, erasures.count() );

	const auto outputs{ FormatTestData_Erasure<TypeParam>( text, erasures ) };

	const auto code{ TypeParam{ erasures }.encoder };
	const auto decoder{ TypeParam{ erasures }.decoder };

	ASSERT_LT( 0, outputs.size() );
	ASSERT_EQ( 12185, outputs.size() );
	for( const auto& output : outputs )
	{
		const auto decode_res{ decoder.Decode( output.recived_signal ) };
		EXPECT_EQ( output.sent_codeword, code.GenerateCodeword( decode_res ) ) << "Seed: \"" << output.message_seed << "\", Errors: " << std::endl;
	}
}

TYPED_TEST( FunctionalFileBaseTests, ErasuresAreMessageBits )
{
	constexpr size_t S{ GetReedSolomonParameters( TypeParam::m_RSSchema::n, TypeParam::m_RSSchema::k ).d - 1 };

	std::vector<size_t> erasure_indexes;
	erasure_indexes.resize( S );
	std::iota( erasure_indexes.begin(), erasure_indexes.end(), TypeParam::m_RSSchema::k );
	
	std::bitset<TypeParam::m_RSSchema::n> erasures{ 0 };
	for( const size_t index : erasure_indexes )
	{
		erasures.set( index );
	}
	ASSERT_EQ( S, erasures.count() );

	const auto outputs{ FormatTestData_Erasure<TypeParam>( text, erasures ) };

	const auto code{ TypeParam{ erasures }.encoder };
	const auto decoder{ TypeParam{ erasures }.decoder };

	ASSERT_LT( 0, outputs.size() );
	ASSERT_EQ( 12185, outputs.size() );
	for( const auto& output : outputs )
	{
		const auto decode_res{ decoder.Decode( output.recived_signal ) };
		EXPECT_EQ( output.sent_codeword, code.GenerateCodeword( decode_res ) ) << "Seed: \"" << output.message_seed << "\", Errors: " << std::endl;
	}
}

TYPED_TEST( FunctionalFileBaseTests, ErasuresAreArbitrary )
{
	constexpr size_t S{ GetReedSolomonParameters( TypeParam::m_RSSchema::n, TypeParam::m_RSSchema::k ).d - 1 };

	std::bitset<TypeParam::m_RSSchema::n> erasures{ 0 };
	for( size_t index{ 0 }; index < S; index++ )
	{
		// assumes 3 and n are coprime
		erasures.set( (3*index) % TypeParam::m_RSSchema::n );
	}
	ASSERT_EQ( S, erasures.count() );

	const auto outputs{ FormatTestData_Erasure<TypeParam>( text, erasures ) };

	const auto code{ TypeParam{ erasures }.encoder };
	const auto decoder{ TypeParam{ erasures }.decoder };

	ASSERT_LT( 0, outputs.size() );
	ASSERT_EQ( 12185, outputs.size() );
	for( const auto& output : outputs )
	{
		const auto decode_res{ decoder.Decode( output.recived_signal ) };
		EXPECT_EQ( output.sent_codeword, code.GenerateCodeword( decode_res ) ) << "Seed: \"" << output.message_seed << "\", Errors: " << std::endl;
	}
}

