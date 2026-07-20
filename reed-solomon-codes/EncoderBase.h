#pragma once

#include "BlockCodeParameters.h"
#include "Codeword.h"
#include "IEncoderSchema.h"
#include "Schema.h"
#include "SystematicEncoderSchema.h"

#include "container-helpers/ArrayExtensions.h"
#include "cpp-helpers/Typedef.h"
#include "finite-fields/FiniteFieldsOfSizePrimeToAPower.h"
#include "finite-fields-polynomials/PolynomialsOverFiniteFieldOfSizePrimeToAPower.h"

#include <array>

constexpr static BlockCodeParameters GetReedSolomonParameters( std::size_t n, std::size_t k )
{
    return BlockCodeParameters::CreateFromBlockLengthMessageLengthHammingDistance(
        n,
        k,
        n-k+1
    );
}

template<std::size_t n, std::size_t k, integer Prime, integer Exponent>
void PolynomialToCodeword( const std::array<ElementOfFiniteField<Prime,Exponent>, n>& generating_elements, Codeword<n, k, Prime, Exponent>& blocks, size_t start_index, const PolynomialOverFiniteField<Prime,Exponent,k-1>& generator_polynomial )
{
    for( std::size_t block_index{ start_index }; block_index < blocks.size(); block_index++ )
    {
        blocks.at( block_index ) = generator_polynomial( generating_elements.at( block_index ) );
    }
}

template<typename EncoderSchemaType, std::size_t n, std::size_t k, integer Prime, integer Exponent>
class EncoderBase
{
    static_assert( std::is_base_of_v<IEncoderSchema<EncoderSchemaType,n,k,Prime,Exponent>, EncoderSchemaType>, "EncoderSchemaType is not a child of desired interface class." );

public:
    const std::array<ElementOfFiniteField<Prime,Exponent>, n> generating_elements;

    const EncoderSchemaType encoder_schema;

    Codeword<n, k, Prime, Exponent> GenerateCodeword( const Message<n, k, Prime, Exponent>& message ) const
    {
        Codeword<n, k, Prime, Exponent> blocks{};

        std::size_t first_empty_block_index{ 0 };

        if constexpr ( std::is_same_v<EncoderSchemaType, SystematicEncoderSchema<n,k,Prime,Exponent>> )
        {
            for( std::size_t block_index{ 0 }; block_index < k; block_index++ )
            {
                blocks.at( block_index ) = message.at( block_index );
            }

            first_empty_block_index = k;
        }

        PolynomialToCodeword<n, k, Prime, Exponent>( generating_elements, blocks, first_empty_block_index, encoder_schema.MessageToPolynomial( message ) );

        return blocks;
    }

    Message<n, k, Prime, Exponent> PolynomialToMessage( const PolynomialOverFiniteField<Prime,Exponent,k-1>& polynomial ) const
    {
        return encoder_schema.PolynomialToMessage( polynomial );
    }

    EncoderBase( const std::array<ElementOfFiniteField<Prime,Exponent>, n>& generators )
        : generating_elements{ generators }
        , encoder_schema{ Schema<n, k, Prime, Exponent>{ generators } }
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

    constexpr static BlockCodeParameters parameters{ GetReedSolomonParameters(n,k) };
};

