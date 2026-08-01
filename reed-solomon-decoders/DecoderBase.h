#pragma once

#include "IErrorDecoderSchema.h"
#include "reed-solomon-codes/ReedSolomonBlockCodeParameters.h"

#include "container-helpers/ArrayExtensions.h"
#include "finite-fields/PolynomialsOverFieldAlgorithms.h"
#include "finite-fields-extensions/LagrangeInterpolation.h"
#include "reed-solomon-codes/Codeword.h"
#include "reed-solomon-codes/IEncoderSchema.h"
#include "reed-solomon-codes/Schema.h"

#include <algorithm>
#include <optional>

template<typename EncoderSchemaType, typename DecoderSchemaType, std::size_t n, std::size_t k, integer Prime, integer Exponent>
class DecoderBase
{
    static_assert( std::is_base_of_v<IEncoderSchema<EncoderSchemaType,n,k,Prime,Exponent>, EncoderSchemaType>, "EncoderSchemaType is not a child of desired interface class." );
    static_assert( std::is_base_of_v<IErrorDecoderSchema<DecoderSchemaType,n,k,Prime,Exponent>, DecoderSchemaType>, "DecoderSchemaType is not a child of desired interface class." );
    
    EncoderSchemaType encoder_schema;
    DecoderSchemaType decoder_schema;

    constexpr static std::size_t e{ GetReedSolomonParameters(n,k).e };
    static_assert( e > 0, "As polynomial lengths are template parameters we restrict our use cases to well defined ones." );

public:
    constexpr DecoderBase( const Schema<n, k, Prime, Exponent>& defining_schema )
        : encoder_schema{ defining_schema }
        , decoder_schema{ defining_schema }
    {}

    std::optional<Message<n, k, Prime, Exponent>> Decode( const Codeword<n, k, Prime, Exponent>& recieved_signal ) const
    {
        auto decode_res{ decoder_schema.Decode( recieved_signal ) };

        if( decode_res.has_value() )
        {
            return encoder_schema.PolynomialToMessage( decode_res.value() );
        }
        return std::nullopt;
    }
};

