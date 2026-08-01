#pragma once

#include "IErrorDecoderSchema.h"
#include "reed-solomon-codes/ReedSolomonBlockCodeParameters.h"

#include "container-helpers/ArrayExtensions.h"
#include "finite-fields/PolynomialsOverFieldAlgorithms.h"
#include "finite-fields-extensions/LagrangeInterpolation.h"
#include "reed-solomon-codes/Schema.h"
#include "reed-solomon-codes/Codeword.h"

#include <algorithm>
#include <optional>

template<std::size_t n, std::size_t k, integer Prime, integer Exponent>
class GeoDecoderSchema : public IErrorDecoderSchema<GeoDecoderSchema<n,k,Prime,Exponent>, n,k,Prime,Exponent>
{
    const LagrangeInterpolation<n, ElementOfFiniteField<Prime,Exponent>> interpolator;

    constexpr static std::size_t e{ GetReedSolomonParameters(n,k).e };
    static_assert( e > 0, "As polynomial lengths are template parameters we restrict our use cases to well defined ones." );

    static constexpr PolynomialOverFiniteField<Prime, Exponent, n> CreateInitialPolynomial( const Schema<n, k, Prime, Exponent>& defining_schema )
    {
        auto initial_term{ PolynomialOverFiniteField<Prime, Exponent, n>::GetMultiplicativeInvarient() };
        
        PolynomialOverFiniteField<Prime, Exponent, n> setup_multiplyer{};
        setup_multiplyer.SetCoeff( ElementOfFiniteField<Prime,Exponent>::GetMultiplicativeInvarient(), 1 );
        for( const auto& generator_element : defining_schema.generating_elements )
        {
            setup_multiplyer.SetCoeff( ElementOfFiniteField<Prime,Exponent>::GetAdditionInvarient() - generator_element, 0 );
            initial_term = initial_term.MultiplyUpToSameDegree( setup_multiplyer );
        }

        return initial_term;
    }

public:
    const PolynomialOverFiniteField<Prime, Exponent, n> m_initial_term;

    constexpr GeoDecoderSchema( const Schema<n, k, Prime, Exponent>& defining_schema )
        : m_initial_term{ CreateInitialPolynomial( defining_schema ) }
        , interpolator{ defining_schema.generating_elements }
    {}

    PolynomialOverFiniteField<Prime, Exponent, n-1> LagrangeInterpolation( const Signal<n, k, Prime, Exponent>& recieved_signal ) const
    {
        return interpolator.Interpolate( recieved_signal );
    }

    std::optional<PolynomialOverFiniteField<Prime, Exponent, k-1>> Decode( const Signal<n, k, Prime, Exponent>& recieved_signal ) const
    {
        auto interpolated_polynomial{ LagrangeInterpolation( recieved_signal ) };

        static_assert( k+e == n-e, "" );
        const auto eea_result{ ExtendedEuclideanAlgorithm( k+e-1, m_initial_term, interpolated_polynomial ) };

        auto longDivisionRes{ LongDivideBy( eea_result.remainder, eea_result.divisor_multiplyer ) };
        
        if( ! longDivisionRes.remainder.IsZero() )
        {
            // Decoder Error - must be at least hamming distance `>e` away from a codeword
            return std::nullopt;
        }

        return longDivisionRes.quotient.Downsize<k-1>();
    }
};
