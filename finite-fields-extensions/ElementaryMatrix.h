#pragma once

#include <array>

template<std::size_t rows, std::size_t columns, typename FieldElements>
class ElementaryMatrix
{
    std::array<std::array<FieldElements, columns>, rows> m_Matrix{};

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

    std::array<FieldElements, columns>& Row( std::size_t index )
    {
        return m_Matrix.at( index );
    }
    const std::array<FieldElements, columns>& Row( std::size_t index ) const
    {
        return m_Matrix.at( index );
    }
    static constexpr std::size_t RowCount()
    {
        return rows;
    }
    static constexpr std::size_t ColumnCount()
    {
        return columns;
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
};
