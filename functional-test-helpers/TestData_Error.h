#pragma once

#include "finite-fields/FiniteFieldsOfSizePrimeToAPower.h"

#include <string>
#include <vector>

template <typename TestTypes>
struct TestData_Error
{
	static_assert( TestTypes::m_RSSchema::Prime == 2 );

    std::string message_seed{};
    std::vector<std::size_t> twiddled_bits{};
    
    typename TestTypes::Message message{};
    typename TestTypes::Codeword sent_codeword{};
    typename TestTypes::Signal recived_signal{};
};

