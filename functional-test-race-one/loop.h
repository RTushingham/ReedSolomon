#pragma once

#include "CodeSchema.h"
#include "reed-solomon-decoders-tests/helpers/TestData.h"

#include "finite-fields-tests/binary-helpers/CharToElm.h"
#include "integer-packing-helpers/UIntAtLeast.h"

#include <bitset>
#include <fstream>
#include <vector>

using namespace TestCaseOne;

namespace
{
	std::bitset<Exponent> chars_to_bitset( char c, char c2 )
	{
		uint32_t a{(uint32_t)c};
		uint32_t a2{(uint32_t)c2};
		a2 <<= sizeof( sizeof(char) );

		u_atleast_t<Exponent> b1( a+a2 );

		return b1;
	}
}

std::vector<TestData<n, k, Exponent>> main_loop()
{
	std::fstream stream( R"(D:\ReedSolomon\functional-tests-file-based\text.txt)" );
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

    std::vector<TestData<n, k, Exponent>> outputs{};
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

		TestData<n, k, Exponent> new_output;

		new_output.message_seed = {
			next_codeword.at( 0 ),
			next_codeword.at( 1 ),
			next_codeword.at( 2 ),
			next_codeword.at( 3 )
		};

		// TODO - begin:
		//   - Move this into encoder util
		const std::array<ElementOfFiniteField<Prime, Exponent>,k> initializer{
			char_to_elm( chars_to_bitset( next_codeword.at( 0 ), next_codeword.at( 1 ) ) ),
			char_to_elm( chars_to_bitset( next_codeword.at( 2 ), next_codeword.at( 3 ) ) )
		};
		// TODO - end

		new_output.message = initializer;

		new_output.sent_codeword = 
			code.GenerateCodeword(
				PolynomialOverFiniteField<Prime,Exponent,k-1>{ 
					initializer 
				}
			);

		new_output.recived_block = new_output.sent_codeword;

		// TODO - begin:
		//   - Move this into util
		new_output.twiddled_bits.push_back( 0 );
		new_output.recived_block.blocks.at( 0 ) = ElementOfFiniteField<Prime,Exponent>::GetAdditionInvarient();		
		// TODO - end
		
		outputs.push_back( new_output );
	}

    return outputs;
}
