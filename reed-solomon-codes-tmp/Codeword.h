#pragma once

#include "cpp-helpers/Typedef.h"
#include "finite-fields/FiniteFieldsOfSizePrimeToAPower.h"

#include <array>

template<size_t n, size_t k, integer Prime, integer Exponent>
using Signal = std::array<ElementOfFiniteField<Prime,Exponent>, n>;

template<size_t n, size_t k, integer Prime, integer Exponent>
using Codeword = Signal<n, k, Prime, Exponent>;

template<size_t n, size_t k, integer Prime, integer Exponent>
using Message = std::array<ElementOfFiniteField<Prime,Exponent>, k>;

