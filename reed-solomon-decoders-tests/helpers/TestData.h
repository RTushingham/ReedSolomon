#include "reed-solomon-codes/Code.h"
#include "reed-solomon-codes/Codeword.h"
#include "reed-solomon-codes/PolynomialsOverFiniteFieldOfSizePrimeToAPower.h"

#include <string>
#include <vector>

template<std::size_t n, std::size_t k, integer Prime, integer Exponent>
struct TestData
{
    std::string message_seed{};
    std::vector<std::size_t> twiddled_bits{};
    
    Message<n, k, Prime, Exponent> message{};
    Codeword<n, k, Prime, Exponent> sent_codeword{ };
    Signal<n, k, Prime, Exponent> recived_block{ };
};
