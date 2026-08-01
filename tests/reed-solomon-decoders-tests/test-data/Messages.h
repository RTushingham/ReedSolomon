#pragma once

#include "functional-tests/schemas/FamousRSSchemas.h"
#include "tests/finite-fields-tests/binary-helpers/CharToElm.h"
#include "tests/reed-solomon-codes-tests/helpers/BlockCodeOverFiniteFieldSchema.h"

#include <vector>

template<typename RSSchema>
class Msgs
{
    static_assert( false, "Template requires specialization." );
};

template<>
class Msgs<BinaryUint8GFUint32MessageUint64Codeword>
{
    static constexpr size_t Exponent{ BinaryUint8GFUint32MessageUint64Codeword::Exponent };

public:
    // These are specific messages which previous versions failed to decode.
    std::vector<typename BlockCodeOverFiniteFieldSchema<BinaryUint8GFUint32MessageUint64Codeword>::Message> messages
    {
        {
            char_to_elm<Exponent>( (uint8_t)-1 ),
            char_to_elm<Exponent>( (uint8_t)-1 ),
            char_to_elm<Exponent>( (uint8_t)-1 ),
            char_to_elm<Exponent>( (uint8_t)-1 )
        },
        {
            char_to_elm<Exponent>( (uint8_t)0b10000000 ),
            char_to_elm<Exponent>( (uint8_t)0b10001110 ),
            char_to_elm<Exponent>( (uint8_t)0b00010101 ),
            char_to_elm<Exponent>( (uint8_t)0b11010001 )
        },
        {
            char_to_elm<Exponent>( (uint8_t)0b00000101 ),
            char_to_elm<Exponent>( (uint8_t)0b00000010 ),
            char_to_elm<Exponent>( (uint8_t)0b11100001 ),
            char_to_elm<Exponent>( (uint8_t)0b11110111 )
        },
        {
            char_to_elm<Exponent>( (uint8_t)0b00110000 ),
            char_to_elm<Exponent>( (uint8_t)0b01101110 ),
            char_to_elm<Exponent>( (uint8_t)0b11101110 ),
            char_to_elm<Exponent>( (uint8_t)0b10001110 )
        },
        {
            char_to_elm<Exponent>( (uint8_t)0b01100001 ),
            char_to_elm<Exponent>( (uint8_t)0b10101101 ),
            char_to_elm<Exponent>( (uint8_t)0b00110101 ),
            char_to_elm<Exponent>( (uint8_t)0b10100001 )
        },
        {
            char_to_elm<Exponent>( (uint8_t)0b11011000 ),
            char_to_elm<Exponent>( (uint8_t)0b11111110 ),
            char_to_elm<Exponent>( (uint8_t)0b11111101 ),
            char_to_elm<Exponent>( (uint8_t)0b00110100 )
        },
        {
            char_to_elm<Exponent>( (uint8_t)0b01000010 ),
            char_to_elm<Exponent>( (uint8_t)0b00011001 ),
            char_to_elm<Exponent>( (uint8_t)0b11010110 ),
            char_to_elm<Exponent>( (uint8_t)0b11110011 )
        },
        {
            char_to_elm<Exponent>( (uint8_t)86 ),
            char_to_elm<Exponent>( (uint8_t)12 ),
            char_to_elm<Exponent>( (uint8_t)255 ),
            char_to_elm<Exponent>( (uint8_t)32 )
        },
        {
            char_to_elm<Exponent>( (uint8_t)53 ),
            char_to_elm<Exponent>( (uint8_t)7 ),
            char_to_elm<Exponent>( (uint8_t)112 ),
            char_to_elm<Exponent>( (uint8_t)187 )
        },
        {
            char_to_elm<Exponent>( 0 ),
            char_to_elm<Exponent>( 0 ),
            char_to_elm<Exponent>( 0 ),
            char_to_elm<Exponent>( 0 )
        },
        {
            char_to_elm<Exponent>( 'c' ),
            char_to_elm<Exponent>( 'h' ),
            char_to_elm<Exponent>( ',' ),
            char_to_elm<Exponent>( 'o' )
        }
    };
};

