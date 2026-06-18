#include "reed-solomon-codes/Code.h"
#include "reed-solomon-codes/Codeword.h"
#include "reed-solomon-codes/PolynomialsOverFiniteFieldOfSizePrimeToAPower.h"

#include <string>
#include <vector>

template<std::size_t n, std::size_t k, integer Exponent>
struct TestData
{
    std::string message_seed{};
    std::vector<std::size_t> twiddled_bits{};
    
    PolynomialOverFiniteField<2, Exponent, k-1> message{};
    Codeword<n, k, 2, Exponent> sent_codeword{ std::array<ElementOfFiniteField<2, Exponent>, n>{} };
    Codeword<n, k, 2, Exponent> recived_block{ std::array<ElementOfFiniteField<2, Exponent>, n>{} };
};
