#include "loop.h"

#include <iostream>

void main()
{
	const auto outputs{ main_loop() };

	for( int64_t run_index{0}; run_index < 10; run_index++ )
	{
		for( int64_t index{0}; index < outputs.recieved.size(); index++ )
		{
			const auto decode_res{ decoder.Decode( outputs.recieved.at( index ) ) };
			if(! decode_res.has_value() || outputs.sent.at( index ) != code.GenerateCodeword( decode_res.value() ) )
			{
				std::cout << "Test failed." << std::endl;
				return;
			}
		}
	}

	std::cout << "Test passed." << std::endl;
}
