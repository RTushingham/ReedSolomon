#pragma once

#include "EncoderBase.h"
#include "SystematicEncoderSchema.h"

template<std::size_t n, std::size_t k, integer Prime, integer Exponent>
using ErasureCode = EncoderBase<SystematicEncoderSchema<n,k,Prime,Exponent>, n,k,Prime,Exponent>;

