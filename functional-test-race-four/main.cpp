#include "loop.h"

#include <iostream>

void main()
{
	const auto outputs{ main_loop() };
	if( outputs.size() == 0 )
	{
		std::cout << "Test setup failure. Messages count: " << outputs.size() << std::endl;
		return;
	}

	for( int64_t run_index{0}; run_index < 1; run_index++ )
	{
		for( const auto& output : outputs )
		{
			const auto decode_res{ decoder.Decode( output.recived_block ) };
			if( output.message != decode_res )
			{
				std::cout << "Test failed. Seed: " << output.message_seed << std::endl;
				return;
			}
		}
	}

	std::cout << "Test passed." << std::endl;
}
