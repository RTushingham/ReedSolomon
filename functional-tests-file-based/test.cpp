#include "loop.h"

#include "gtest/gtest.h"

TEST( FileBasedBenchmarkTest, TestCase )
{
	const auto outputs{ main_loop() };

	for( int64_t run_index{0}; run_index < 10; run_index++ )
	{
		for( int64_t index{0}; index < outputs.recieved.size(); index++ )
		{
			if( outputs.sent.at( index ) != decoder.Decode( outputs.recieved.at( index ) ) )
			{
				std::cout << "Test failed." << std::endl;
				return;
			}
		}
	}

	std::cout << "Test passed." << std::endl;
}
