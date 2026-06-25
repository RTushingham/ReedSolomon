#pragma once

#include "BlockCodeParameters.h"
#include "Codeword.h"
#include "PolynomialsOverFiniteFieldOfSizePrimeToAPower.h"

#include "container-helpers/ArrayExtensions.h"
#include "cpp-helpers/Typedef.h"
#include "finite-fields/FiniteFieldsOfSizePrimeToAPower.h"
#include "finite-fields-extensions/LagrangeInterpolation.h"

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
class ErasureCode
{
    static_assert( n-k > 0, "Cannot correct any erasures." );

    static constexpr std::array<ElementOfFiniteField<Prime,Exponent>, k> CopyFirstKElements( const std::array<ElementOfFiniteField<Prime,Exponent>, n>& source )
    {
        std::array<ElementOfFiniteField<Prime,Exponent>, k> first_k_generators{};
        for( std::size_t index{ 0 }; index < k; index++ )
        {
            first_k_generators.at( index ) = source.at( index );
        }
        return first_k_generators;
    }
    
public:
    const std::array<ElementOfFiniteField<Prime,Exponent>, n> generating_elements;
    
    const LagrangeInterpolation<k, ElementOfFiniteField<Prime,Exponent>> interpolator;

    Codeword<n, k, Prime, Exponent> GenerateCodeword( const std::array<ElementOfFiniteField<Prime,Exponent>, k>& generator ) const
    {
        std::array<ElementOfFiniteField<Prime,Exponent>, n> blocks{};

        const auto generator_polynomial{ interpolator.Interpolate( generator ) };

        for( std::size_t block_index{ 0 }; block_index < blocks.size(); block_index++ )
        {
            blocks.at( block_index ) = generator_polynomial( generating_elements.at( block_index ) );
        }

        return Codeword<n, k, Prime, Exponent>{ blocks };
    }

    ErasureCode( const std::array<ElementOfFiniteField<Prime,Exponent>, n>& generators )
        : generating_elements{ generators }
        , interpolator{ CopyFirstKElements( generators ) }
    {
        if( array_contains( generators, ElementOfFiniteField<Prime,Exponent>::GetAdditionInvarient() ) )
        {
            throw;
        }

        if( false == array_is_all_mutually_distinct( generators ) )
        {
            throw;
        }
    }

    constexpr static BlockCodeParameters parameters{ GetReedSolomonParameters(n,k) };
};
