#include "loop.h"

#include "gtest/gtest.h"

TEST( FileBasedBenchmarkTest, TestCase )
{
	const auto outputs{ main_loop() };

	for( int64_t run_index{0}; run_index < 1; run_index++ )
	{
		ASSERT_LT( 0, outputs.size() );
		for( const auto& output : outputs )
		{
			const auto decode_res{ decoder.Decode( output.recived_block ) };
			EXPECT_TRUE( decode_res.has_value() ) << "Seed: \"" << output.message_seed << "\", Errors: " << std::endl;
			if( decode_res.has_value() )
			{
				EXPECT_EQ( output.sent_codeword, code.GenerateCodeword( decode_res.value() ) ) << "Seed: \"" << output.message_seed << "\", Errors: " << std::endl;
			}
		}
	}
}
