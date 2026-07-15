#include "reed-solomon-codes-tmp/Codeword.h"

#include <vector>

#include "gtest/gtest.h"

template<std::size_t Prime, std::size_t Exponent> 
void introduce_error( ElementOfFiniteField<Prime, Exponent>& alphabet_entry )
{
    constexpr auto one{ ElementOfFiniteField<Prime, Exponent>::GetMultiplicativeInvarient() };
    ASSERT_NE( alphabet_entry, alphabet_entry + one );
    alphabet_entry = alphabet_entry + one;
}

template<std::size_t n, std::size_t k, std::size_t Prime, std::size_t Exponent> 
void introduce_any_errors( std::size_t error_count, Codeword<n, k, Prime, Exponent>& codeword )
{
    std::size_t starting_index{ 0 };
    for( std::size_t error_index{ starting_index }; error_index < starting_index + error_count; error_index++ )
    {
        introduce_error( codeword.at( error_index ) );
    }
}

template<std::size_t n, std::size_t k, std::size_t Prime, std::size_t Exponent> 
void introduce_errors( std::vector<std::size_t> indexes, Codeword<n, k, Prime, Exponent>& codeword )
{
    for( const auto index : indexes )
    {
        introduce_error( codeword.at( index ) );
    }
}

