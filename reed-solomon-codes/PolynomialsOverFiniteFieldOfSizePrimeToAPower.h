#pragma once

#include "finite-fields/FiniteFieldsOfSizePrimeToAPower.h"
#include "polynomials-base/PolynomialsOverField.h"

template <integer Prime, integer Exponent, integer MaxDegree>
using PolynomialOverFiniteField = PolynomialOverField<MaxDegree,ElementOfFiniteField<Prime,Exponent>>;
