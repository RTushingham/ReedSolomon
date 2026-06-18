#pragma once

#include <cstdint>
#include <type_traits>

template<size_t bits>
class u_atleast
{
    static_assert( bits <= 64 );
public:
    using type = std::conditional_t<
        bits <= 8,
        uint8_t,
            std::conditional_t<
            bits <= 16,
            uint16_t,
                std::conditional_t<
                bits <= 32,
                uint32_t,
                uint64_t
                >
            >
        >;
};

template<size_t bits>
using u_atleast_t = typename u_atleast<bits>::type;
