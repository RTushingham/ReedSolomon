#pragma once

#include "Serialize.h"
#include "Split.h"
#include "TestData_Erasure.h"

#include "integer-packing-helpers/UIntAtLeast.h"
#include "finite-fields/FiniteFieldsOfSizePrimeToAPower.h"

#include <algorithm>
#include <bitset>
#include <iterator>
#include <numeric>
#include <string_view>
#include <vector>

template <typename TestTypes>
std::vector<TestData_Erasure<TestTypes>> FormatTestData_Erasure( const std::string_view text, std::bitset<TestTypes::m_RSSchema::n> erasures )
{
	// TODO:
	//   - Tidy this up
	auto code{ TestTypes{ erasures }.encoder };

	constexpr size_t chars_per_message{ TestTypes::m_RSSchema::Exponent * TestTypes::m_RSSchema::k / (sizeof(char)*8) };
	const auto codeword_seeds{ Split_ToEvenSized( chars_per_message, text ) };

    std::vector<TestData_Erasure<TestTypes>> outputs{};
	for( const auto& next_codeword : codeword_seeds )
	{
		TestData_Erasure<TestTypes> new_output;

		new_output.message_seed = std::string{ next_codeword };

		new_output.message = serialize<TestTypes>( next_codeword );

		new_output.sent_codeword = 
			code.GenerateCodeword(
				new_output.message
			);

		// TODO - begin:
		//   - Move this into util
		//   - Test this
		size_t source_index{ 0 };
		std::copy_if( 
			new_output.sent_codeword.begin(), new_output.sent_codeword.end(),
			new_output.recived_signal.begin(),
			[ &source_index, erasures ]( auto ) { return false == erasures.test( source_index++ ); }
		);
		// TODO - end
		
		outputs.push_back( new_output );
	}

    return outputs;
}

