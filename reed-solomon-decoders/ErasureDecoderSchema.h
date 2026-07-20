#pragma once

#include "container-helpers/ArrayTransformation.h"
#include "finite-fields-extensions/LagrangeInterpolation.h"

#include <bitset>

template<std::size_t n, std::size_t k, integer Prime, integer Exponent>
class ErasureDecoderSchema
{
    static_assert( n-k > 0, "This config cannot correct any erasures." );

    LagrangeInterpolation<k, ElementOfFiniteField<Prime,Exponent>> first_k_non_erasure_generators_interpolator{};

public:
    constexpr ErasureDecoderSchema( const Schema<n, k, Prime, Exponent>& defining_schema, std::bitset<n> erasures )
        : first_k_non_erasure_generators_interpolator{ CopyIf<ElementOfFiniteField<Prime,Exponent>, k, n>( defining_schema.generating_elements, erasures ) }
    {
        if( erasures.count() > n-k )
            throw;
    }

    PolynomialOverFiniteField<Prime,Exponent,k-1> Decode( const std::array<ElementOfFiniteField<Prime,Exponent>, k>& recieved_signal ) const
    {
        return first_k_non_erasure_generators_interpolator.Interpolate( recieved_signal );
    }
};

