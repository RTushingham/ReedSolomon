#pragma once

#include "integer-packing-helpers/UIntAtLeast.h"
#include "finite-fields/FiniteFieldsOfSizePrimeToAPower.h"

#include <bitset>
#include <string_view>

namespace Details
{
    template <typename RSSchema>
    std::bitset<RSSchema::Exponent> chars_to_bitset( std::string_view chars )
    {
        static_assert( RSSchema::Prime == 2 );

        u_atleast_t<RSSchema::Exponent> running_xor{};

        constexpr std::size_t char_count{ RSSchema::Exponent / (sizeof(char)*8) };
        for( size_t chars_index{ 0 }; chars_index < char_count; chars_index++ )
        {
            auto tmp{ (u_atleast_t<RSSchema::Exponent>)chars.at( chars_index ) };
            tmp <<= chars_index * (sizeof(char)*8);
            running_xor += tmp;
        }

        return running_xor;
    }

    template <typename RSSchema>
    ElementOfFiniteField<2, RSSchema::Exponent> bitset_to_elm( std::bitset<RSSchema::Exponent> seed )
    {
        static_assert( RSSchema::Prime == 2 );

        ElementOfFiniteField<2, RSSchema::Exponent> out{};

        for( std::size_t bit_index{0}; bit_index < seed.size(); bit_index++ )
        {
            out.value.SetCoeff( seed.test( bit_index ), bit_index );
        }

        return out;
    }
}

template <typename RSSchema>
ElementOfFiniteField<2, RSSchema::Exponent> serialize_element( std::string_view chars )
{
    static_assert( RSSchema::Prime == 2 );
    
    return Details::bitset_to_elm<RSSchema>( Details::chars_to_bitset<RSSchema>( chars ) );
}

template <typename TestTypes>
typename TestTypes::Message serialize( std::string_view message_seed )
{
    TestTypes::Message message{};
    
    constexpr size_t chars_per_element{ TestTypes::m_RSSchema::Exponent / (sizeof(char)*8) };
    for( size_t a{ 0 }; a < TestTypes::m_RSSchema::k; a++ )
    {
        message.at( a ) = serialize_element<TestTypes::m_RSSchema>( std::string_view(message_seed.data()+(chars_per_element*a), chars_per_element ) );
    }

    return message;
}
		
