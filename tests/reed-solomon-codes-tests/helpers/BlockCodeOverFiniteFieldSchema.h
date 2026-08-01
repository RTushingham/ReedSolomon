#pragma once

#include "reed-solomon-codes/Codeword.h"

template<typename RSSchema>
class BlockCodeOverFiniteFieldSchema
{
public:
    using Signal = Signal<RSSchema::n,RSSchema::k,RSSchema::Prime,RSSchema::Exponent>;
    using Codeword = Codeword<RSSchema::n,RSSchema::k,RSSchema::Prime,RSSchema::Exponent>;
    using Message = Message<RSSchema::n,RSSchema::k,RSSchema::Prime,RSSchema::Exponent>;
};

