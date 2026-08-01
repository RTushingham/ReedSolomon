#pragma once

#include "reed-solomon-codes/Codeword.h"
#include "reed-solomon-codes/EncoderBase.h"
#include "reed-solomon-codes/IEncoderSchema.h"

template<typename RSSchema, typename EncoderSchema>
class EncoderSchemaTestTypes
{
    static_assert( std::is_base_of_v<IEncoderSchema<EncoderSchema,RSSchema::n,RSSchema::k,RSSchema::Prime,RSSchema::Exponent>, EncoderSchema>, "EncoderSchema is not a child of desired interface class." );
    
public:
    using m_RSSchema = RSSchema;

    using EncoderSchemaType = EncoderSchema;
};

