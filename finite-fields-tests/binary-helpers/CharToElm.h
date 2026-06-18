#pragma once

#include "finite-fields/FiniteFieldsOfSizePrimeToAPower.h"
#include "integer-packing-helpers/UIntAtLeast.h"

#include <bitset>

template<std::size_t Exponent>
ElementOfFiniteField<2, Exponent> char_to_elm( std::bitset<Exponent> seed )
{    
    ElementOfFiniteField<2, Exponent> out{};
    for( std::size_t bit_index{0}; bit_index < seed.size(); bit_index++ )
    {
        out.value.SetCoeff( seed.test( bit_index ), bit_index );
    }

    return out;
}
