#pragma once

#include <array>

template<std::size_t row_count, std::size_t row_length, typename FieldElements>
class ElementaryMatrix
{
    std::array<std::array<FieldElements, row_length>, row_count> m_Matrix{};

public:
    constexpr ElementaryMatrix( const FieldElements& initializer )
        : m_Matrix{}
    {
        for( auto& equation : m_Matrix )
        {
            for( auto& coefficient : equation )
            {
                coefficient = initializer;
            }
        }
    }

    std::array<FieldElements, row_length>& Row( std::size_t index )
    {
        return m_Matrix.at( index );
    }
    static constexpr std::size_t RowCount()
    {
        return row_count;
    }
    static constexpr std::size_t ColumnCount()
    {
        return row_length;
    }

    void SubtractRowByRow( std::size_t target_index, FieldElements multiplyer, std::size_t source_index )
    {
        if( target_index == source_index )
            throw;
        
        const auto& source_row{ Row( source_index ) };
        auto& target_row{ Row( target_index ) };
        
        for( std::size_t index{ 0 }; index<target_row.size(); index++ )
        {
            target_row.at( index ) = target_row.at( index ) - ( source_row.at( index ) * multiplyer );
        }
    }

    void DivideRow( std::size_t target_index, FieldElements multiplyer )
    {
        auto& equation{ Row( target_index ) };
        
        for( auto& coeff : equation )
        {
            coeff = coeff / multiplyer;
        }
    }
};
