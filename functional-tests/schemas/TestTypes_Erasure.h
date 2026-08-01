#pragma once

#include "reed-solomon-codes/Codeword.h"
#include "reed-solomon-codes/EncoderBase.h"
#include "reed-solomon-codes/IEncoderSchema.h"

#include "reed-solomon-decoders/ErasureDecoderBase.h"

#include <bitset>

template<typename RSSchema, typename EncoderSchema, typename DecoderSchema>
class TestTypes_Erasure
{
    static_assert( std::is_base_of_v<IEncoderSchema<EncoderSchema,RSSchema::n,RSSchema::k,RSSchema::Prime,RSSchema::Exponent>, EncoderSchema>, "EncoderSchema is not a child of desired interface class." );
    
public:
    using m_RSSchema = RSSchema;

    using Message = Message<RSSchema::n,RSSchema::k,RSSchema::Prime,RSSchema::Exponent>;
    using Codeword = Codeword<RSSchema::n,RSSchema::k,RSSchema::Prime,RSSchema::Exponent>;

    EncoderBase<EncoderSchema,RSSchema::n,RSSchema::k,RSSchema::Prime,RSSchema::Exponent> encoder;
    ErasureDecoderBase<EncoderSchema,DecoderSchema,RSSchema::n,RSSchema::k,RSSchema::Prime,RSSchema::Exponent> decoder;

    TestTypes_Erasure( std::bitset<RSSchema::n> erasures )
        : encoder{ RSSchema::schema }
        , decoder{ RSSchema::schema, erasures }
        {};
};

