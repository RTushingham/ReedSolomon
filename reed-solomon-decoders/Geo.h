#pragma once

#include "container-helpers/ArrayExtensions.h"
#include "finite-fields-extensions/GaussianElimination.h"
#include "finite-fields-extensions/LagrangeInterpolation.h"
#include "reed-solomon-codes/Code.h"
#include "reed-solomon-codes/Codeword.h"

#include <algorithm>
#include <optional>

template<std::size_t n, std::size_t k, integer Prime, integer Exponent>
class GeoDecoder
{
    const Code<n, k, Prime, Exponent> schema;
    const LagrangeInterpolation<n, ElementOfFiniteField<Prime,Exponent>> interpolator;

    constexpr static std::size_t e{ GetReedSolomonParameters(n,k).e };
    static_assert( e > 0, "As polynomial lengths are template parameters we restrict our use cases to well defined ones." );

    static PolynomialOverFiniteField<Prime, Exponent, n> CreateInitialPolynomial( const Code<n, k, Prime, Exponent>& defining_schema )
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

    constexpr GeoDecoder( const Code<n, k, Prime, Exponent>& defining_schema )
        : schema{ defining_schema }
        , m_initial_term{ CreateInitialPolynomial( defining_schema ) }
        , interpolator{ schema.generating_elements }
    {}

    PolynomialOverFiniteField<Prime, Exponent, n-1> LagrangeInterpolation( const Codeword<n, k, Prime, Exponent>& recieved_signal ) const
    {
        return interpolator.Interpolate( recieved_signal.blocks );
    }

    std::optional<PolynomialOverFiniteField<Prime,Exponent,k-1>> Decode( const Codeword<n, k, Prime, Exponent>& recieved_signal ) const
    {
        auto initial_term{ m_initial_term };
        
        auto interpolated_polynomial{ LagrangeInterpolation( recieved_signal ) };

        static_assert( k+e == n-e, "" );
        const auto eea_result{ ExtendedEuclideanAlgorithm( k+e-1, initial_term, interpolated_polynomial ) };

        auto longDivisionRes{ eea_result.remainder.LongDivideBy( eea_result.divisor_multiplyer ) };
        
        if( ! longDivisionRes.remainder.IsZero() )
        {
            // Decoder Error - must be at least hamming distance `>e` away from a codeword
            return std::nullopt;
        }

        return longDivisionRes.quotient.Downsize<k-1>();
    }
};
