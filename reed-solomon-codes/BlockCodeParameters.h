#pragma once

#include <cstddef>

struct BlockCodeParameters
{
    const std::size_t n{0};
    const std::size_t k{0};
    const std::size_t d{0};
    const std::size_t e{0};

    constexpr BlockCodeParameters( std::size_t n, std::size_t k, std::size_t d, std::size_t e )
        : n{n}
        , k{k}
        , d{d}
        , e{e}
    {};
    
    constexpr static BlockCodeParameters CreateFromBlockLengthMessageLengthHammingDistance( std::size_t blockLength, std::size_t messageLength, std::size_t hammingDistance )
    {
        return BlockCodeParameters( blockLength, messageLength, hammingDistance, (hammingDistance-1)/2 );
    };
};
