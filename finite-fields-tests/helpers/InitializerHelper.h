#pragma once

#include "finite-fields/PolynomialsOverField.h"

template <typename E1, typename E2>
class x_to_ref
{
    E1 first;
    E2 second;

public:
    constexpr x_to_ref( E1 f, E2 s )
        : first{ f }
        , second{ s }
    {}

    template <typename Other>
    constexpr x_to_ref<x_to_ref<E1,E2>,Other> operator+( Other a ) const
    {
        return { *this, a };
    }

    template <typename PolyType>
    constexpr void mod( PolyType& poly ) const
    {
        first.mod( poly );
        second.mod( poly );
    }

    template <typename PolyType>
    constexpr PolyType evaluate() const
    {
        PolyType poly{};
        mod( poly );
        return poly;
    }
};

template <typename StorageType>
class x_to
{
    StorageType construction_value;
    std::size_t coeff_index;

public:
    constexpr x_to( StorageType value, std::size_t index )
        : construction_value{ value }
        , coeff_index{ index }
    {}

    template <typename Other>
    constexpr x_to_ref<x_to,Other> operator+( Other a ) const
    {
        return { *this, a };
    }
    
    template <typename PolyType>
    constexpr void mod( PolyType& poly ) const
    {
        poly.SetCoeff( construction_value, coeff_index );
    }

    template <typename PolyType>
    constexpr PolyType evaluate() const
    {
        PolyType poly{};
        mod( poly );
        return poly;
    }
};
