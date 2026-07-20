#pragma once

#include "DecoderBase.h"
#include "GeoDecoderSchema.h"

#include "reed-solomon-codes/SimpleEncoderSchema.h"

template<std::size_t n, std::size_t k, integer Prime, integer Exponent>
using GeoDecoder = DecoderBase<SimpleEncoderSchema<n,k,Prime,Exponent>, GeoDecoderSchema<n,k,Prime,Exponent>, n,k,Prime,Exponent>;

