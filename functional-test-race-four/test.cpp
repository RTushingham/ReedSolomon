#include "loop.h"

#include "gtest/gtest.h"

TEST( FileBasedBenchmarkTest, TestCase )
{
	const auto outputs{ main_loop() };
	ASSERT_LT( 0, outputs.size() );

	for( int64_t run_index{0}; run_index < 1; run_index++ )
	{
		for( const auto& output : outputs )
		{
			const auto decode_res{ decoder.Decode( output.recived_block ) };
			EXPECT_EQ( output.message, decode_res ) << "Seed: \"" << output.message_seed << "\"";
		}
	}
}
