#pragma once

#include "container-helpers/ArrayTransformation.h"
#include "finite-fields-extensions/LagrangeInterpolation.h"
#include "reed-solomon-codes/ErasureCode.h"

#include <bitset>

template<std::size_t n, std::size_t k, integer Prime, integer Exponent>
class ErasureDecoder
{
    static_assert( n-k > 0, "This config cannot correct any erasures." );

    const ErasureCode<n, k, Prime, Exponent> schema;

    LagrangeInterpolation<k, ElementOfFiniteField<Prime,Exponent>> first_k_non_erasure_generators_interpolator{};

public:
    constexpr ErasureDecoder( const ErasureCode<n, k, Prime, Exponent>& defining_schema, std::bitset<n> erasures )
        : schema{ defining_schema }
        , first_k_non_erasure_generators_interpolator{ CopyIf<ElementOfFiniteField<Prime,Exponent>, k, n>( defining_schema.generating_elements, erasures ) }
    {
        if( erasures.count() > n-k )
            throw;
    }

    std::array<ElementOfFiniteField<2, Exponent>, k> Decode( const std::array<ElementOfFiniteField<Prime,Exponent>, k>& recieved_signal ) const
    {
        auto poly{ first_k_non_erasure_generators_interpolator.Interpolate( recieved_signal ) };

        std::array<ElementOfFiniteField<2, Exponent>, k> arry{};
        for( std::size_t generator_index{ 0 }; generator_index < arry.size(); generator_index++ )
        {
            arry.at( generator_index ) = poly( schema.generating_elements.at( generator_index ) );
        }

        return arry;
    }
};
