#pragma once

#include "finite-fields/FiniteFieldsOfSizePrimeToAPower.h"
#include "finite-fields/PolynomialsOverField.h"

template <integer Prime, integer Exponent, integer MaxDegree>
using PolynomialOverFiniteField = PolynomialOverField<MaxDegree,ElementOfFiniteField<Prime,Exponent>>;
