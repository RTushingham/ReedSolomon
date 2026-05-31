#pragma once

#include "cpp-helpers/Typedef.h"
#include "finite-fields/FiniteFieldsOfSizePrimeToAPower.h"

#include <array>

template<std::size_t n, std::size_t k, integer Prime, integer Exponent>
class Codeword
{
public:
    std::array<ElementOfFiniteField<Prime,Exponent>, n> blocks;

    Codeword( const std::array<ElementOfFiniteField<Prime,Exponent>, n>& blocks )
        : blocks{ blocks }
    {}

    constexpr bool operator==( const Codeword& other ) const
    {
        return blocks == other.blocks;
    }
	constexpr bool operator!=( const Codeword& a ) const
	{
		return ! operator==(a);
	}
};
