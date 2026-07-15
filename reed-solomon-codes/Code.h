#pragma once

#include "EncoderBase.h"
#include "SimpleEncoderSchema.h"

template<std::size_t n, std::size_t k, integer Prime, integer Exponent>
using Code = EncoderBase<SimpleEncoderSchema<n,k,Prime,Exponent>, n,k,Prime,Exponent>;

