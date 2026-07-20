#pragma once

#include "Serialize.h"
#include "Split.h"
#include "TestData_Error.h"

#include "integer-packing-helpers/UIntAtLeast.h"
#include "finite-fields/FiniteFieldsOfSizePrimeToAPower.h"

#include <bitset>
#include <string_view>
#include <vector>


template <typename TestTypes>
std::vector<TestData_Error<TestTypes>> FormatTestData( const std::string_view text, const std::vector<std::size_t>& error_indexes )
{
	auto code{ TestTypes{}.encoder };

	constexpr size_t chars_per_message{ TestTypes::m_RSSchema::Exponent * TestTypes::m_RSSchema::k / (sizeof(char)*8) };
	const auto codeword_seeds{ Split_ToEvenSized( chars_per_message, text ) };

    std::vector<TestData_Error<TestTypes>> outputs{};
	for( const auto& next_codeword : codeword_seeds )
	{
		TestData_Error<TestTypes> new_output;

		new_output.message_seed = std::string{ next_codeword };

		new_output.message = serialize<TestTypes>( next_codeword );

		new_output.sent_codeword = 
			code.GenerateCodeword(
				new_output.message
			);

		new_output.recived_signal = new_output.sent_codeword;

		for( const size_t index_to_twiddle : error_indexes )
		{
			new_output.recived_signal.at( index_to_twiddle ) = new_output.recived_signal.at( index_to_twiddle ) - ElementOfFiniteField<2,TestTypes::m_RSSchema::Exponent>::GetMultiplicativeInvarient();
		}
		new_output.twiddled_bits = error_indexes;
		
		outputs.push_back( new_output );
	}

    return outputs;
}

