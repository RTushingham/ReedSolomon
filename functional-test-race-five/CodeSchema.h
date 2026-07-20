#pragma once

#include "reed-solomon-decoders-tmp/Geo.h"

#include "finite-fields-tmp/ElementOfFiniteField_Poly_Algorithms.h"

#include "reed-solomon-codes-tmp/Code.h"
#include "reed-solomon-codes-tmp/Codeword.h"

#include "finite-fields-tests/helpers/InitializerHelper.h"

namespace TestCaseFive
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
