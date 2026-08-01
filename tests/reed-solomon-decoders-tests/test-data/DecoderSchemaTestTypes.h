#pragma once

#include "reed-solomon-codes/Codeword.h"
#include "reed-solomon-decoders/DecoderBase.h"
#include "reed-solomon-decoders/IErrorDecoderSchema.h"

template<typename RSSchema, typename DecoderSchema>
class DecoderSchemaTestTypes
{
    static_assert( std::is_base_of_v<IErrorDecoderSchema<DecoderSchema,RSSchema::n,RSSchema::k,RSSchema::Prime,RSSchema::Exponent>, DecoderSchema>, "DecoderSchema is not a child of desired interface class." );
    
public:
    using m_RSSchema = RSSchema;

    using DecoderSchemaType = DecoderSchema;
};

