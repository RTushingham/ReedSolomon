#include "loop.h"

#include "gtest/gtest.h"

TEST( FileBasedBenchmarkTest, TestCase )
{
	const auto outputs{ main_loop() };

	for( int64_t index{0}; index < outputs.recieved.size(); index++ )
	{
		const auto decode_res{ decoder.Decode( outputs.recieved.at( index ) ) };
		EXPECT_TRUE( decode_res.has_value() );
		if( decode_res.has_value() )
		{
			EXPECT_EQ( outputs.sent.at( index ), code.GenerateCodeword( decode_res.value() ) );
		}
	}
}
