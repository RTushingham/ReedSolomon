#pragma once

#include "BlockCodeParameters.h"
#include "Codeword.h"
#include "PolynomialsOverFiniteFieldOfSizePrimeToAPower.h"

#include "cpp-helpers/Typedef.h"
#include "finite-fields/FiniteFieldsOfSizePrimeToAPower.h"

#include <array>

constexpr static BlockCodeParameters GetReedSolomonParameters( std::size_t n, std::size_t k )
{
    return BlockCodeParameters::CreateFromBlockLengthMessageLengthHammingDistance(
        n,
        k,
        n-k+1
    );
}

template<std::size_t n, std::size_t k, integer Prime, integer Exponent>
class Code
{
public:
    const std::array<ElementOfFiniteField<Prime,Exponent>, n> generating_elements;

    Codeword<n, k, Prime, Exponent> GenerateCodeword( const PolynomialOverFiniteField<Prime,Exponent,k-1>& generator_polynomial ) const
    {
        std::array<ElementOfFiniteField<Prime,Exponent>, n> blocks{};

        for( std::size_t block_index{ 0 }; block_index<blocks.size(); block_index++ )
        {
            blocks.at( block_index ) = generator_polynomial( generating_elements.at( block_index ) );
        }

        return Codeword<n, k, Prime, Exponent>{ blocks };
    }

    Code( const std::array<ElementOfFiniteField<Prime,Exponent>, n>& generators )
        : generating_elements{ generators }
    {}

    constexpr static BlockCodeParameters parameters{ GetReedSolomonParameters(n,k) };
};
