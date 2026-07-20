#include "CodeSchema.h"

#include "functional-tests/helpers/FormatTestData_Erasure.h"
#include "functional-tests/helpers/LoadDataFromFile.h"

#include <iostream>

void main()
{
	std::vector<size_t> erasure_indexes{ 0, 1, 2, 3 };
	std::bitset<TestSchema::m_RSSchema::n> erasures{ 0 };
	for( const size_t index : erasure_indexes )
	{
		erasures.set( index );
	}

	const auto text{ LoadDataFromFile( TestDataPaths::Large_File ) };

	const auto outputs{ FormatTestData_Erasure<TestSchema>( text, erasures ) };

	// TODO:
	//   - Make constexpr
	const auto code{ TestSchema{ erasures }.encoder };
	const auto decoder{ TestSchema{ erasures }.decoder };

	for( int64_t run_index{0}; run_index < 1; run_index++ )
	{
		for( const auto& output : outputs )
		{
			const auto decode_res{ decoder.Decode( output.recived_signal ) };
			if( output.sent_codeword != code.GenerateCodeword( decode_res ) )
			{
				std::cout << "Test failed. Seed: " << output.message_seed << std::endl;
				return;
			}
		}
	}

	std::cout << "Test passed." << std::endl;
}
