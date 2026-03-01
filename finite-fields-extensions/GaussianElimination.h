#pragma once

#include "ElementaryMatrix.h"

#include "container-helpers/ArrayExtensions.h"

#include <array>

template<std::size_t row_count, std::size_t row_length, typename FieldElements>
std::array<std::size_t, row_count> GaussianElimination( ElementaryMatrix<row_count, row_length, FieldElements>& matrix, const FieldElements& addition_invarient )
{
    std::array<std::size_t, matrix.RowCount()> non_zero_row_index{};
	for( auto & a : non_zero_row_index )
	{
		a = (std::size_t)-1;
	}

    for( std::size_t round_index{ 0 }; round_index<matrix.RowCount(); round_index++ )
    {
        bool new_nonzero_leading_row_found{ false };
        for( std::size_t equation_index{ 0 }; equation_index<matrix.RowCount(); equation_index++ )
        {
            if( array_contains( non_zero_row_index, equation_index ) )
                continue;
            
            auto& eq = matrix.Row( round_index );
            
            if( eq.at( round_index ) != addition_invarient )
            {
                non_zero_row_index.at( round_index ) = equation_index;
                new_nonzero_leading_row_found = true;
                break;
            }
        }
        if( new_nonzero_leading_row_found == false )
        {
            throw;
        }

        const auto leading_non_zero_index{ non_zero_row_index.at( round_index ) };
        const auto& leading_v{ matrix.Row( leading_non_zero_index ).at( round_index ) };

        for( std::size_t equation_index{ 0 }; equation_index<matrix.RowCount(); equation_index++ )
        {
            if( equation_index == leading_non_zero_index )
                continue;
            
            const auto& target_v{ matrix.Row( equation_index ).at( non_zero_row_index.at( round_index ) ) };

            matrix.SubtractRowByRow( equation_index, target_v/leading_v, leading_non_zero_index );
        }
    }

    return non_zero_row_index;
}
