#pragma once

#include "container-helpers/ArrayExtensions.h"
#include "cpp-helpers/Typedef.h"
#include "finite-fields/FiniteFieldsOfSizePrimeToAPower.h"

#include <array>

template<std::size_t n, std::size_t k, integer Prime, integer Exponent>
class Schema
{
public:
    const std::array<ElementOfFiniteField<Prime,Exponent>, n> generating_elements;
    
    Schema( const std::array<ElementOfFiniteField<Prime,Exponent>, n>& generators )
        : generating_elements{ generators }
    {
        if( array_contains( generators, ElementOfFiniteField<Prime,Exponent>::GetAdditionInvarient() ) )
        {
            throw;
        }

        if( false == array_is_all_mutually_distinct( generators ) )
        {
            throw;
        }
    }
};

