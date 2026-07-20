#pragma once

#include "reed-solomon-codes/IEncoderSchema.h"

#include <bitset>

template<typename EncoderSchemaType, typename DecoderSchemaType, std::size_t n, std::size_t k, integer Prime, integer Exponent>
class ErasureDecoderBase
{
    static_assert( std::is_base_of_v<IEncoderSchema<EncoderSchemaType,n,k,Prime,Exponent>, EncoderSchemaType>, "EncoderSchemaType is not a child of desired interface class." );

    static_assert( n-k > 0, "This config cannot correct any erasures." );

    EncoderSchemaType encoder_schema;
    DecoderSchemaType decoder_schema;

public:
    constexpr ErasureDecoderBase( const Schema<n, k, Prime, Exponent>& defining_schema, std::bitset<n> erasures )
        : encoder_schema{ defining_schema }
        , decoder_schema{ defining_schema, erasures }
    {
        if( erasures.count() > n-k )
            throw;
    }

    Message<n, k, Prime, Exponent> Decode( const std::array<ElementOfFiniteField<Prime,Exponent>, k>& recieved_signal ) const
    {
        return encoder_schema.PolynomialToMessage( decoder_schema.Decode( recieved_signal ) );
    }
};

