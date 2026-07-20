#include "CodeSchema.h"

#include "functional-tests/helpers/FormatTestData.h"
#include "functional-tests/helpers/LoadDataFromFile.h"

#include <iostream>

void main()
{
	std::vector<size_t> error_indexes{ 0, 1 };

	const auto text{ LoadDataFromFile( TestDataPaths::Large_File ) };

	const auto outputs{ FormatTestData<TestSchema>( text, error_indexes ) };

	// TODO:
	//   - Make constexpr
	const auto code{ TestSchema{}.encoder };
	const auto decoder{ TestSchema{}.decoder };

	for( int64_t run_index{0}; run_index < 1; run_index++ )
	{
		for( const auto& output : outputs )
		{
			const auto decode_res{ decoder.Decode( output.recived_signal ) };
			if( ! decode_res.has_value() || output.sent_codeword != code.GenerateCodeword( decode_res.value() ) )
			{
				std::cout << "Test failed. Seed: " << output.message_seed << std::endl;
				return;
			}
		}
	}

	std::cout << "Test passed." << std::endl;
}
