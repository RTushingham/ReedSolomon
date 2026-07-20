#include "reed-solomon-decoders/BerlekampWelch.h"

#include "finite-fields-polynomials/PolynomialsOverFiniteFieldOfSizePrimeToAPower.h"
#include "reed-solomon-codes/Code.h"
#include "reed-solomon-codes/Codeword.h"

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
			std::array<ElementOfFiniteFieldP<Prime>,PolynomialOverPrimeSizeFiniteField<Prime,1>::GetCoeffCount()>{
				ElementOfFiniteFieldP<Prime>{ 9 },
				ElementOfFiniteFieldP<Prime>{ 8 }
			} 
		}
	};

	const ElementOfFiniteField<Prime, Exponent> argument_two{
		PolynomialOverPrimeSizeFiniteField<Prime,1>{
			std::array<ElementOfFiniteFieldP<Prime>,PolynomialOverPrimeSizeFiniteField<Prime,1>::GetCoeffCount()>{
				ElementOfFiniteFieldP<Prime>{ 10 },
				ElementOfFiniteFieldP<Prime>{ 11 }
			} 
		}
	};

	const ElementOfFiniteField<Prime, Exponent> argument_three{
		PolynomialOverPrimeSizeFiniteField<Prime,1>{
			std::array<ElementOfFiniteFieldP<Prime>,PolynomialOverPrimeSizeFiniteField<Prime,1>::GetCoeffCount()>{
				ElementOfFiniteFieldP<Prime>{ 12 },
				ElementOfFiniteFieldP<Prime>{ 13 }
			} 
		}
	};

	const ElementOfFiniteField<Prime, Exponent> argument_four{
		PolynomialOverPrimeSizeFiniteField<Prime,1>{
			std::array<ElementOfFiniteFieldP<Prime>,PolynomialOverPrimeSizeFiniteField<Prime,1>::GetCoeffCount()>{
				ElementOfFiniteFieldP<Prime>{ 14 },
				ElementOfFiniteFieldP<Prime>{ 15 }
			} 
		}
	};

	// TODO:
	//   - Template thes?
    const Schema<n, k, Prime, Exponent> schema{ std::array<ElementOfFiniteField<Prime, Exponent>,n>{ argument_one, argument_two, argument_three, argument_four } };

	Code<n, k, Prime, Exponent> code{ schema.generating_elements };
	const BerklekampWelchDecoder<n, k, Prime, Exponent> decoder{ schema };
}

struct TestOutputs
{
	std::vector<Codeword<n, k, Prime, Exponent>> sent{};
	std::vector<Codeword<n, k, Prime, Exponent>> recieved{};
};

TestOutputs main_loop()
{
	std::fstream stream( R"(D:\ReedSolomon\functional-tests\data\error-correcting\text.txt)" );
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

    TestOutputs outputs{};
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
					std::array<ElementOfFiniteFieldP<Prime>,PolynomialOverPrimeSizeFiniteField<Prime,1>::GetCoeffCount()>{
						ElementOfFiniteFieldP<Prime>{ next_codeword.at( 0 ) },
						ElementOfFiniteFieldP<Prime>{ next_codeword.at( 1 ) }
					} 
				}
			},
			ElementOfFiniteField<Prime, Exponent>{
				PolynomialOverPrimeSizeFiniteField<Prime,1>{
					std::array<ElementOfFiniteFieldP<Prime>,PolynomialOverPrimeSizeFiniteField<Prime,1>::GetCoeffCount()>{
						ElementOfFiniteFieldP<Prime>{ next_codeword.at( 2 ) },
						ElementOfFiniteFieldP<Prime>{ next_codeword.at( 3 ) }
					} 
				}
			}
		};

		outputs.sent.push_back(
			code.GenerateCodeword(
				initializer
			)
		);

		outputs.recieved.push_back(
			outputs.sent.back()
		);
		outputs.recieved.back().at( 0 ) = ElementOfFiniteField<Prime,Exponent>::GetAdditionInvarient();
	}

    return outputs;
}
