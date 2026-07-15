#pragma once

#include "CodeSchema.h"
#include "reed-solomon-decoders-tests/helpers/TestData.h"

#include "finite-fields-tests/binary-helpers/CharToElm.h"
#include "integer-packing-helpers/UIntAtLeast.h"

#include <bitset>
#include <fstream>
#include <vector>

using namespace TestCaseTwo;

std::vector<TestData<n, k, Prime, Exponent>> main_loop()
{
	std::fstream stream( R"(D:\ReedSolomon\functional-test-data\error-correcting\text.txt)" );
	std::string text{};

	if( !stream.is_open() )
	{
		throw std::exception( "Test invalid." );
	}
	
	while( !stream.eof() )
	{
		std::string buffer{};
		stream >> buffer;
		text += buffer;
	}

	if( text.empty() )
	{
		throw std::exception( "Test invalid." );
	}

    std::vector<TestData<n, k, Prime, Exponent>> outputs{};
	for( int64_t index{0}; index<text.size(); index++ )
	{
		// TODO:
		//   - Make this into splitter/span thing
		std::array<char,4> next_codeword{};
		bool b{false};
		for( std::size_t next_codeword_index{}; next_codeword_index<next_codeword.size(); next_codeword_index++ )
		{
			index++;

			if( ! (index<text.size()) )
			{
				b = true;
				break;
			}
			if( b )
			{
				break;
			}

			next_codeword.at( next_codeword_index ) = text.at( index );
		}
		if( b )
		{
			break;
		}

		TestData<n, k, Prime, Exponent> new_output;

		new_output.message_seed = {
			next_codeword.at( 0 ),
			next_codeword.at( 1 ),
			next_codeword.at( 2 ),
			next_codeword.at( 3 )
		};

		// TODO:
		//   - Move this into encoder util
		const std::array<ElementOfFiniteField<Prime, Exponent>,k> initializer{
			char_to_elm<Exponent>( next_codeword.at( 0 ) ),
			char_to_elm<Exponent>( next_codeword.at( 1 ) ),
			char_to_elm<Exponent>( next_codeword.at( 2 ) ),
			char_to_elm<Exponent>( next_codeword.at( 3 ) )
		};

		new_output.message = initializer;

		new_output.sent_codeword = 
			code.GenerateCodeword(
				initializer
			);

		new_output.recived_block = new_output.sent_codeword;

		// TODO:
		//   - Move this into util
		new_output.twiddled_bits.push_back( 6 );
		new_output.recived_block.at( 6 ) = ElementOfFiniteField<Prime,Exponent>::GetAdditionInvarient();
		new_output.twiddled_bits.push_back( 7 );
		new_output.recived_block.at( 7 ) = ElementOfFiniteField<Prime,Exponent>::GetAdditionInvarient();
		
		outputs.push_back( new_output );
	}

    return outputs;
}
