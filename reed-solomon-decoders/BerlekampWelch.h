#pragma once

#include "DecoderBase.h"
#include "BerlekampWelchSchema.h"

#include "reed-solomon-codes/SimpleEncoderSchema.h"

template<std::size_t n, std::size_t k, integer Prime, integer Exponent>
using BerklekampWelchDecoder = DecoderBase<SimpleEncoderSchema<n,k,Prime,Exponent>, BerlekampWelchSchema<n,k,Prime,Exponent>, n,k,Prime,Exponent>;

