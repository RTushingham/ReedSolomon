#pragma once

#include "container-helpers/ArrayExtensions.h"
#include "finite-fields-extensions-tmp/tmp_LagrangeInterpolation.h"
#include "finite-fields-tmp/ElementOfFiniteField_Poly_Algorithms.h"
#include "reed-solomon-codes/Codeword.h"
#include "reed-solomon-codes/ReedSolomonBlockCodeParameters.h"
#include "reed-solomon-codes-tmp/Code.h"

#include <algorithm>
#include <optional>

template<std::size_t n, std::size_t k, integer Prime, integer Exponent>
class GeoDecoder
{
    const Code<n, k, Prime, Exponent> schema;
    const tmp_LagrangeInterpolation<n,Exponent> interpolator;

    constexpr static std::size_t e{ GetReedSolomonParameters(n,k).e };
    static_assert( e > 0, "As polynomial lengths are template parameters we restrict our use cases to well defined ones." );

    static ElementOfFiniteField_Poly<n,Exponent> CreateInitialPolynomial( const Code<n, k, Prime, Exponent>& defining_schema )
    {
        auto initial_term{ ElementOfFiniteField_Poly<n,Exponent>::GetMultiplicativeInvarient() };
        
        ElementOfFiniteField_Poly<n,Exponent> setup_multiplyer{};
        setup_multiplyer.SetCoeff( ElementOfFiniteField<Prime,Exponent>::GetMultiplicativeInvarient(), 1 );
        for( const auto& generator_element : defining_schema.generating_elements )
        {
            setup_multiplyer.SetCoeff( ElementOfFiniteField<Prime,Exponent>::GetAdditionInvarient() - generator_element, 0 );
            initial_term = MultiplyUpToSameDegree( initial_term, setup_multiplyer );
        }

        return initial_term;
    }

public:
    const ElementOfFiniteField_Poly<n,Exponent> m_initial_term;

    constexpr GeoDecoder( const Code<n, k, Prime, Exponent>& defining_schema )
        : schema{ defining_schema }
        , m_initial_term{ CreateInitialPolynomial( defining_schema ) }
        , interpolator{ schema.generating_elements }
    {}

    ElementOfFiniteField_Poly<n-1,Exponent> LagrangeInterpolation( const Codeword<n, k, Prime, Exponent>& recieved_signal ) const
    {
        return interpolator.Interpolate( recieved_signal );
    }

    std::optional<Message<n, k, Prime, Exponent>> Decode( const Codeword<n, k, Prime, Exponent>& recieved_signal ) const
    {
        auto interpolated_polynomial{ LagrangeInterpolation( recieved_signal ) };

        // TODO:
        //   double check that works for all d paraties
        static_assert( k+e == n-e, "" );
        const auto eea_result{ tmp_ExtendedEuclideanAlgorithm( k+e-1, m_initial_term, interpolated_polynomial ) };

        auto longDivisionRes{ tmp_LongDivideBy( eea_result.remainder, eea_result.divisor_multiplyer ) };
        
        if( ! longDivisionRes.remainder.IsZero() )
        {
            // Decoder Error - must be at least hamming distance `>e` away from a codeword
            return std::nullopt;
        }

        return schema.PolynomialToMessage( longDivisionRes.quotient.Downsize<k-1>() );
    }
};
