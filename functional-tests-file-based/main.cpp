#include "reed-solomon-decoders/BerlekampWelch.h"

#include "reed-solomon-codes/Code.h"
#include "reed-solomon-codes/Codeword.h"
#include "reed-solomon-codes/PolynomialsOverFiniteFieldOfSizePrimeToAPower.h"

#include <iostream>
#include <fstream>
#include <vector>
#include <string_view>

constexpr integer Prime{ 101 };
constexpr integer Exponent{ 2 };
constexpr std::size_t n{ 4 };
constexpr std::size_t k{ 2 };

namespace
{
	const ElementOfFiniteField<Prime, Exponent> argument_one{
		PolynomialOverPrimeSizeFiniteField<Prime,1>{
			std::array<ElementOfFiniteFieldP<Prime>,PolynomialOverPrimeSizeFiniteField<Prime,1>::GetCapacity()>{
				ElementOfFiniteFieldP<Prime>{ 9 },
				ElementOfFiniteFieldP<Prime>{ 8 }
			} 
		}
	};

	const ElementOfFiniteField<Prime, Exponent> argument_two{
		PolynomialOverPrimeSizeFiniteField<Prime,1>{
			std::array<ElementOfFiniteFieldP<Prime>,PolynomialOverPrimeSizeFiniteField<Prime,1>::GetCapacity()>{
				ElementOfFiniteFieldP<Prime>{ 10 },
				ElementOfFiniteFieldP<Prime>{ 11 }
			} 
		}
	};

	const ElementOfFiniteField<Prime, Exponent> argument_three{
		PolynomialOverPrimeSizeFiniteField<Prime,1>{
			std::array<ElementOfFiniteFieldP<Prime>,PolynomialOverPrimeSizeFiniteField<Prime,1>::GetCapacity()>{
				ElementOfFiniteFieldP<Prime>{ 12 },
				ElementOfFiniteFieldP<Prime>{ 13 }
			} 
		}
	};

	const ElementOfFiniteField<Prime, Exponent> argument_four{
		PolynomialOverPrimeSizeFiniteField<Prime,1>{
			std::array<ElementOfFiniteFieldP<Prime>,PolynomialOverPrimeSizeFiniteField<Prime,1>::GetCapacity()>{
				ElementOfFiniteFieldP<Prime>{ 14 },
				ElementOfFiniteFieldP<Prime>{ 15 }
			} 
		}
	};

	Code<n, k, Prime, Exponent> code{ std::array<ElementOfFiniteField<Prime, Exponent>,n>{ argument_one, argument_two, argument_three, argument_four } };
	const BerklekampWelchDecoder<n, k, Prime, Exponent> decoder{ code };
}

void main()
{
	std::fstream stream( R"(D:\ReedSolomon\functional-tests-file-based\text.txt)" );
	std::string text{};
	
	while( !stream.eof() )
	{
		std::string buffer{};
		stream >> buffer;
		text += buffer;
	}

	if( text.empty() )
	{
		std::cout << "Test invalid." << std::endl;
		return;
	}

	std::vector<Codeword<n, k, Prime, Exponent>> sent{};
	std::vector<Codeword<n, k, Prime, Exponent>> recieved{};
	for( int64_t index{0}; index<text.size(); index++ )
	{
		std::array<char,4> next_codeword{};
		bool b{false};
		for( std::size_t next_codeword_index{}; next_codeword_index<next_codeword.size(); next_codeword_index++ )
		{
			while( text.at(index)<=22 )
			{
				index++;
				if( ! (index<text.size()) )
				{
					b = true;
					break;
				}
			}
			if( b )
			{
				break;
			}

			next_codeword.at( next_codeword_index ) = text.at( index )-22;
		}
		if( b )
		{
			break;
		}

		const std::array<ElementOfFiniteField<Prime, Exponent>,k> initializer{
			ElementOfFiniteField<Prime, Exponent>{
				PolynomialOverPrimeSizeFiniteField<Prime,1>{ 
					std::array<ElementOfFiniteFieldP<Prime>,PolynomialOverPrimeSizeFiniteField<Prime,1>::GetCapacity()>{
						ElementOfFiniteFieldP<Prime>{ next_codeword.at( 0 ) },
						ElementOfFiniteFieldP<Prime>{ next_codeword.at( 1 ) }
					} 
				}
			},
			ElementOfFiniteField<Prime, Exponent>{
				PolynomialOverPrimeSizeFiniteField<Prime,1>{
					std::array<ElementOfFiniteFieldP<Prime>,PolynomialOverPrimeSizeFiniteField<Prime,1>::GetCapacity()>{
						ElementOfFiniteFieldP<Prime>{ next_codeword.at( 2 ) },
						ElementOfFiniteFieldP<Prime>{ next_codeword.at( 3 ) }
					} 
				}
			}
		};

		sent.push_back(
			code.GenerateCodeword(
				PolynomialOverFiniteField<Prime,Exponent,k-1>{ 
					initializer 
				}
			)
		);

		recieved.push_back(
			sent.back()
		);
		recieved.back().blocks.at( 0 ) = ElementOfFiniteField<Prime,Exponent>::GetAdditionInvarient();
	}

	for( int64_t run_index{0}; run_index < 10; run_index++ )
	{
		for( int64_t index{0}; index < recieved.size(); index++ )
		{
			if( sent.at( index ) != decoder.Decode( recieved.at( index ) ) )
			{
				std::cout << "Test failed." << std::endl;
				return;
			}
		}
	}

	std::cout << "Test passed." << std::endl;
}
