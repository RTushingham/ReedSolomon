#include "CodeSchema.h"

#include "functional-tests/helpers/FormatTestData_Erasure.h"
#include "functional-tests/helpers/LoadDataFromFile.h"

#include "gtest/gtest.h"

// TODO - begin:
//   - Simplify
#include "reed-solomon-codes/EncoderBase.h"

namespace
{
	constexpr size_t S{ GetReedSolomonParameters( TestSchema::m_RSSchema::n, TestSchema::m_RSSchema::k ).d - 1 };
}
// TODO - end

TEST( BenchmarkValidityTests, AllDataDecodedCorrectly )
{
	const auto text{ LoadDataFromFile( TestDataPaths::Large_File ) };

	std::vector<size_t> erasure_indexes{ 0, 1, 2, 3 };
	ASSERT_EQ( S, erasure_indexes.size() );

	std::bitset<TestSchema::m_RSSchema::n> erasures{ 0 };
	for( const size_t index : erasure_indexes )
	{
		erasures.set( index );
	}

	const auto outputs{ FormatTestData_Erasure<TestSchema>( text, erasures ) };

	// TODO:
	//   - Make constexpr
	const auto code{ TestSchema{ erasures }.encoder };
	const auto decoder{ TestSchema{ erasures }.decoder };

	ASSERT_LT( 0, outputs.size() );
	ASSERT_EQ( 560533, outputs.size() );
	for( const auto& output : outputs )
	{
		const auto decode_res{ decoder.Decode( output.recived_signal ) };
		EXPECT_EQ( output.sent_codeword, code.GenerateCodeword( decode_res ) ) << "Seed: \"" << output.message_seed << "\", Errors: " << std::endl;
	}
}
