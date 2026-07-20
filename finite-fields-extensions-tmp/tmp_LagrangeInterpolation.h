#pragma once

#include "container-helpers/ArrayExtensions.h"
#include "finite-fields-tmp/ElementOfFiniteField_Poly.h"

#include <array>

template <std::size_t node_count, size_t Exponent>
class tmp_LagrangeInterpolation
{
    std::array<ElementOfFiniteField_Poly<node_count-1, Exponent>, node_count> legrange_basis{};

public:
    static constexpr std::array<ElementOfFiniteField_Poly<node_count-1, Exponent>, node_count> CreateLegrangeBasis( const std::array<ElementOfFiniteField<2,Exponent>, node_count>& nodes )
    {
        std::array<ElementOfFiniteField_Poly<node_count-1, Exponent>, node_count> legrange_basis{};

        ElementOfFiniteField_Poly<node_count-1, Exponent> setup_multiplyer{ std::array<ElementOfFiniteField<2,Exponent>, node_count>{} };
        setup_multiplyer.SetCoeff( ElementOfFiniteField<2,Exponent>::GetMultiplicativeInvarient(), 1 );
        
        for( std::size_t outer_node_index{ 0 }; outer_node_index < nodes.size(); outer_node_index++ )
        {
            legrange_basis.at( outer_node_index ) = ElementOfFiniteField_Poly<node_count-1, Exponent>::GetMultiplicativeInvarient();

            auto correcting_term{ ElementOfFiniteField<2,Exponent>::GetMultiplicativeInvarient() };
            
            for( const auto& inner_node : nodes )
            {
                if( nodes.at( outer_node_index ) != inner_node )
                {
                    setup_multiplyer.SetCoeff( ElementOfFiniteField<2,Exponent>::GetAdditionInvarient() - inner_node, 0 );
                    legrange_basis.at( outer_node_index ) = MultiplyUpToSameDegree( legrange_basis.at( outer_node_index ), setup_multiplyer );

                    correcting_term = correcting_term * ( nodes.at( outer_node_index ) - inner_node );
                }
            }
            
            legrange_basis.at( outer_node_index ) = ScalarMultiplication( legrange_basis.at( outer_node_index ), correcting_term.FindMultiplicativeInverse() );
        }

        return legrange_basis;
    }

    tmp_LagrangeInterpolation( const std::array<ElementOfFiniteField<2,Exponent>, node_count>& nodes )
        : legrange_basis{ CreateLegrangeBasis( nodes ) }
    {
        if( ! array_is_all_mutually_distinct( nodes ) )
        {
            throw;
        }
    }

    ElementOfFiniteField_Poly<node_count-1, Exponent> Interpolate( const std::array<ElementOfFiniteField<2,Exponent>, node_count>& values ) const
    {
        ElementOfFiniteField_Poly<node_count-1, Exponent> interpolated_polynomial{};

        for( std::size_t generator_element_index{ 0 }; generator_element_index < values.size(); generator_element_index++ )
        {
            interpolated_polynomial = interpolated_polynomial + ( ScalarMultiplication( legrange_basis.at( generator_element_index ), values.at( generator_element_index ) ) );
        }

        return interpolated_polynomial;
    }
};

