#pragma once

#include "finite-fields/FiniteFieldsOfSizePrimeToAPower.h"

#include <array>
#include <string>
#include <vector>

template <typename TestTypes>
struct TestData_Erasure
{
	static_assert( TestTypes::m_RSSchema::Prime == 2 );

    std::string message_seed{};
    std::vector<std::size_t> recieved_indexes{};
    
    typename TestTypes::Message message{};
    typename TestTypes::Codeword sent_codeword{};
    std::array<ElementOfFiniteField<TestTypes::m_RSSchema::Prime,TestTypes::m_RSSchema::Exponent>, TestTypes::m_RSSchema::k> recived_signal{};
};

