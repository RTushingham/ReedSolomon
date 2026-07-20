#pragma once

#include "reed-solomon-codes/Codeword.h"
#include "reed-solomon-codes/EncoderBase.h"
#include "reed-solomon-codes/IEncoderSchema.h"
#include "reed-solomon-decoders/DecoderBase.h"
#include "reed-solomon-decoders/IErrorDecoderSchema.h"

template<typename RSSchema, typename EncoderSchema, typename DecoderSchema>
class TestTypes
{
    static_assert( std::is_base_of_v<IEncoderSchema<EncoderSchema,RSSchema::n,RSSchema::k,RSSchema::Prime,RSSchema::Exponent>, EncoderSchema>, "EncoderSchema is not a child of desired interface class." );
    static_assert( std::is_base_of_v<IErrorDecoderSchema<DecoderSchema,RSSchema::n,RSSchema::k,RSSchema::Prime,RSSchema::Exponent>, DecoderSchema>, "DecoderSchema is not a child of desired interface class." );
    // TODO:
    //   - Static assert RSSchema for the CRT types
    
public:
    using m_RSSchema = RSSchema;

    using Signal = Signal<RSSchema::n,RSSchema::k,RSSchema::Prime,RSSchema::Exponent>;
    using Codeword = Codeword<RSSchema::n,RSSchema::k,RSSchema::Prime,RSSchema::Exponent>;
    using Message = Message<RSSchema::n,RSSchema::k,RSSchema::Prime,RSSchema::Exponent>;

    EncoderBase<EncoderSchema,RSSchema::n,RSSchema::k,RSSchema::Prime,RSSchema::Exponent> encoder;
    DecoderBase<EncoderSchema,DecoderSchema,RSSchema::n,RSSchema::k,RSSchema::Prime,RSSchema::Exponent> decoder;

    TestTypes()
        : encoder{ RSSchema{}.schema.generating_elements }
        , decoder{ RSSchema{}.schema }
        {};
};

