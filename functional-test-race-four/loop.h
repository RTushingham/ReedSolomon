#pragma once

#include "CodeSchema.h"

#include "finite-fields-tests/binary-helpers/CharToElm.h"
#include "integer-packing-helpers/UIntAtLeast.h"

#include <bitset>
#include <fstream>
#include <vector>

using namespace TestCaseTwo;

std::vector<Erasure_TestData> main_loop()
{
	std::fstream stream( R"(D:\ReedSolomon\functional-test-data\erasure-correcting\text.txt)" );
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

    std::vector<Erasure_TestData> outputs{};
	for( int64_t index{0}; index<text.size(); index++ )
	{
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

		Erasure_TestData new_output;

		new_output.message_seed = {
			next_codeword.at( 0 ),
			next_codeword.at( 1 ),
			next_codeword.at( 2 ),
			next_codeword.at( 3 )
		};

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
		
		for( std::size_t target_index{ 0 }, source_index{ 0 }; target_index < new_output.recived_block.size() && source_index < new_output.sent_codeword.size(); source_index++ )
		{
			if( false == Erasures.test( source_index ) )
			{
				new_output.recived_block.at( target_index ) = new_output.sent_codeword.at( source_index );
				target_index++;
			}
		}

		outputs.push_back( new_output );
	}

    return outputs;
}
