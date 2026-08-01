#pragma once

#include "container-helpers/ArrayExtensions.h"
#include "cpp-helpers/Typedef.h"
#include "finite-fields-tmp/ElementOfFiniteField_Poly.h"
#include "reed-solomon-codes/Codeword.h"

#include <array>

template<std::size_t n, std::size_t k, integer Prime, integer Exponent>
class Code
{
public:
    const std::array<ElementOfFiniteField<Prime,Exponent>, n> generating_elements;

    Codeword<n, k, Prime, Exponent> GenerateCodeword( const Message<n, k, Prime, Exponent>& message ) const
    {
        Codeword<n, k, Prime, Exponent> blocks{};

        const ElementOfFiniteField_Poly_View<k-1,Exponent> generator_polynomial{ message };

        for( std::size_t block_index{ 0 }; block_index<blocks.size(); block_index++ )
        {
            blocks.at( block_index ) = generator_polynomial( generating_elements.at( block_index ) );
        }

        return blocks;
    }

    Message<n, k, Prime, Exponent> PolynomialToMessage( const ElementOfFiniteField_Poly<k-1,Exponent>& polynomial ) const
    {
        Message<n, k, Prime, Exponent> message{};

        for( std::size_t generator_index{ 0 }; generator_index < message.size(); generator_index++ )
        {
            message.at( generator_index ) = polynomial.GetCoeff( generator_index );
        }

        return message;
    }

    Code( const std::array<ElementOfFiniteField<Prime,Exponent>, n>& generators )
        : generating_elements{ generators }
    {
        // TODO:
        //   - Can 0 be an evaluation point?
        //       - Only element for which value == 0th coefficient
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
