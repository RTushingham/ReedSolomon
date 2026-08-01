#pragma once

#include "BlockCodeParameters.h"

constexpr BlockCodeParameters GetReedSolomonParameters( std::size_t n, std::size_t k )
{
    return BlockCodeParameters::CreateFromBlockLengthMessageLengthHammingDistance(
        n,
        k,
        n-k+1
    );
}

