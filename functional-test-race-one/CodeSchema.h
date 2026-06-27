#pragma once

#include "reed-solomon-decoders/Geo.h"

#include "reed-solomon-codes/Code.h"
#include "reed-solomon-codes/Codeword.h"
#include "reed-solomon-codes/PolynomialsOverFiniteFieldOfSizePrimeToAPower.h"

#include "finite-fields-tests/helpers/InitializerHelper.h"

namespace TestCaseOne
{
    constexpr integer Prime{ 2 };
    constexpr integer Exponent{ 16 };
    constexpr std::size_t k{ 2 };
    constexpr std::size_t n{ 4 };

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

	Code<n, k, Prime, Exponent> code{ std::array<ElementOfFiniteField<Prime, Exponent>,n>{ argument_one, argument_two, argument_three, argument_four } };
	const GeoDecoder<n, k, Prime, Exponent> decoder{ code };
}
