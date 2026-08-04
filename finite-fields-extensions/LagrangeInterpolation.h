#pragma once

#include "container-helpers/ArrayExtensions.h"
#include "finite-fields/PolynomialsOverField.h"

#include <array>

template <std::size_t node_count, typename FieldElements>
class LagrangeInterpolation
{
    static_assert( node_count > 1, "Currently do not support node_count == 1 case." );

    std::array<PolynomialOverField<node_count-1, FieldElements>, node_count> legrange_basis{};

public:
    static constexpr std::array<PolynomialOverField<node_count-1, FieldElements>, node_count> CreateLegrangeBasis( const std::array<FieldElements, node_count>& nodes )
    {
        std::array<PolynomialOverField<node_count-1, FieldElements>, node_count> legrange_basis{};

        PolynomialOverField<node_count-1, FieldElements> setup_multiplyer{};
        setup_multiplyer.SetCoeff( FieldElements::GetMultiplicativeInvarient(), 1 );
        
        for( std::size_t outer_node_index{ 0 }; outer_node_index < nodes.size(); outer_node_index++ )
        {
            legrange_basis.at( outer_node_index ) = PolynomialOverField<node_count-1, FieldElements>::GetMultiplicativeInvarient();

            auto correcting_term{ FieldElements::GetMultiplicativeInvarient() };
            
            for( const auto& inner_node : nodes )
            {
                if( nodes.at( outer_node_index ) != inner_node )
                {
                    setup_multiplyer.SetCoeff( FieldElements::GetAdditionInvarient() - inner_node, 0 );
                    legrange_basis.at( outer_node_index ) = legrange_basis.at( outer_node_index ).MultiplyUpToSameDegree( setup_multiplyer );

                    correcting_term = correcting_term * ( nodes.at( outer_node_index ) - inner_node );
                }
            }
            
            legrange_basis.at( outer_node_index ) = legrange_basis.at( outer_node_index ).ScalarMultiplication( correcting_term.FindMultiplicativeInverse() );
        }

        return legrange_basis;
    }

    constexpr LagrangeInterpolation( const std::array<FieldElements, node_count>& nodes )
        : legrange_basis{ CreateLegrangeBasis( nodes ) }
    {
        if( ! array_is_all_mutually_distinct( nodes ) )
        {
            throw;
        }
    }

    constexpr PolynomialOverField<node_count-1, FieldElements> Interpolate( const std::array<FieldElements, node_count>& values ) const
    {
        PolynomialOverField<node_count-1, FieldElements> interpolated_polynomial{};

        for( std::size_t generator_element_index{ 0 }; generator_element_index < values.size(); generator_element_index++ )
        {
            interpolated_polynomial = interpolated_polynomial + ( legrange_basis.at( generator_element_index ).ScalarMultiplication( values.at( generator_element_index ) ) );
        }

        return interpolated_polynomial;
    }
};

