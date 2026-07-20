#include "loop.h"

#include <iostream>

void main()
{
	const auto outputs{ main_loop() };

	for( int64_t run_index{0}; run_index < 1; run_index++ )
	{
		for( const auto& output : outputs )
		{
			const auto decode_res{ decoder.Decode( output.recived_block ) };
			if( ! decode_res.has_value() || output.sent_codeword != code.GenerateCodeword( decode_res.value() ) )
			{
				std::cout << "Test failed. Seed: " << output.message_seed << std::endl;
				return;
			}
		}
	}

	std::cout << "Test passed." << std::endl;
}
