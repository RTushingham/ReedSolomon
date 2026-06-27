#pragma once

#include "reed-solomon-decoders/ErasureDecoder.h"

#include "reed-solomon-codes/ErasureCode.h"
#include "reed-solomon-codes/Codeword.h"
#include "reed-solomon-codes/PolynomialsOverFiniteFieldOfSizePrimeToAPower.h"

#include "finite-fields-tests/helpers/InitializerHelper.h"

#include <bitset>

namespace TestCaseTwo
{
    constexpr integer Prime{ 2 };
    constexpr integer Exponent{ 8 };
    constexpr std::size_t k{ 4 };
    constexpr std::size_t n{ 8 };

	const ElementOfFiniteField<Prime, Exponent> argument_one{
		x_to( 1,0 ).evaluate<PolynomialOverPrimeSizeFiniteField<Prime,Exponent-1>>()
	};

	const ElementOfFiniteField<Prime, Exponent> argument_two{
		x_to( 1,1 ).evaluate<PolynomialOverPrimeSizeFiniteField<Prime,Exponent-1>>()
	};

	const ElementOfFiniteField<Prime, Exponent> argument_three{
		x_to( 1,2 ).evaluate<PolynomialOverPrimeSizeFiniteField<Prime,Exponent-1>>()
	};

	const ElementOfFiniteField<Prime, Exponent> argument_four{
		x_to( 1,3 ).evaluate<PolynomialOverPrimeSizeFiniteField<Prime,Exponent-1>>()
	};

	const ElementOfFiniteField<Prime, Exponent> argument_five{
		x_to( 1,4 ).evaluate<PolynomialOverPrimeSizeFiniteField<Prime,Exponent-1>>()
	};

	const ElementOfFiniteField<Prime, Exponent> argument_six{
		x_to( 1,5 ).evaluate<PolynomialOverPrimeSizeFiniteField<Prime,Exponent-1>>()
	};

	const ElementOfFiniteField<Prime, Exponent> argument_seven{
		x_to( 1,6 ).evaluate<PolynomialOverPrimeSizeFiniteField<Prime,Exponent-1>>()
	};

	const ElementOfFiniteField<Prime, Exponent> argument_eight{
		x_to( 1,7 ).evaluate<PolynomialOverPrimeSizeFiniteField<Prime,Exponent-1>>()
	};

	ErasureCode<n, k, Prime, Exponent> code{ std::array<ElementOfFiniteField<Prime, Exponent>,n>{ argument_one, argument_two, argument_three, argument_four, argument_five, argument_six, argument_seven, argument_eight } };
	constexpr std::bitset<n> Erasures{ 0b11001001 };
	const ErasureDecoder<n, k, Prime, Exponent> decoder{ code, Erasures };

	struct Erasure_TestData
	{
		std::string message_seed{};
		
		std::array<ElementOfFiniteField<2, Exponent>, k> message{};

		Codeword<n, k, 2, Exponent> sent_codeword{ std::array<ElementOfFiniteField<2, Exponent>, n>{} };
		std::array<ElementOfFiniteField<2, Exponent>, k> recived_block{};
	};
}
