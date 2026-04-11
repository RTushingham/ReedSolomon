#pragma once

#include "BlockCodeParameters.h"
#include "Codeword.h"
#include "PolynomialsOverFiniteFieldOfSizePrimeToAPower.h"

#include "cpp-helpers/Typedef.h"
#include "finite-fields/FiniteFieldsOfSizePrimeToAPower.h"

#include <array>

template<std::size_t n, std::size_t k, integer Prime, integer Exponent>
class Code
{
public:
    const std::array<ElementOfFiniteField<Prime,Exponent>, n> generating_elements;

    Codeword<n, k, Prime, Exponent> GenerateCodeword( const PolynomialOverFiniteField<Prime,Exponent,k>& generator_polynomial ) const
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

    constexpr static BlockCodeParameters parameters{ 
        BlockCodeParameters::CreateFromBlockLengthMessageLengthHammingDistance(
            n,
            k,
            n-k+1
        )
    };
    constexpr static std::size_t n{ parameters.n };
    constexpr static std::size_t k{ parameters.k };
    constexpr static std::size_t hamming_distance{ parameters.d };

    constexpr static std::size_t e()
    {
        return parameters.e;
    }
};
