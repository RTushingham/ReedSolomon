#include "finite-fields-tmp/tmp_FiniteFieldsOfSizePrimeToAPower.h"
#include "reed-solomon-codes-tmp/Code.h"
#include "reed-solomon-codes-tmp/Codeword.h"

#include <string>
#include <vector>

template<std::size_t n, std::size_t k, integer Prime, integer Exponent>
struct TestData
{
    std::string message_seed{};
    std::vector<std::size_t> twiddled_bits{};
    
    Message<n, k, 2, Exponent> message{};
    Codeword<n, k, 2, Exponent> sent_codeword{};
    Signal<n, k, 2, Exponent> recived_block{};
};
