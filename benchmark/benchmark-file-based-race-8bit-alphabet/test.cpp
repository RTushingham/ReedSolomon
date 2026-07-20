#include "CodeSchema.h"

#include "functional-tests/helpers/FormatTestData.h"
#include "functional-tests/helpers/LoadDataFromFile.h"

#include "gtest/gtest.h"

// TODO - begin:
//   - Simplify
#include "reed-solomon-codes/EncoderBase.h"

namespace
{
	constexpr size_t e{ GetReedSolomonParameters( TestSchema::m_RSSchema::n, TestSchema::m_RSSchema::k ).e };
}
// TODO - end

TEST( BenchmarkValidityTests, AllDataDecodedCorrectly )
{
	std::vector<size_t> error_indexes{ 0, 1 };
	ASSERT_EQ( e, error_indexes.size() );

	const auto text{ LoadDataFromFile( TestDataPaths::Large_File ) };

	const auto outputs{ FormatTestData<TestSchema>( text, error_indexes ) };

	// TODO:
	//   - Make constexpr
	const auto code{ TestSchema{}.encoder };
	const auto decoder{ TestSchema{}.decoder };

	ASSERT_LT( 0, outputs.size() );
	ASSERT_EQ( 560533, outputs.size() );
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
