#pragma once

#include "FiniteFieldsOfSizePrime.h"

#include "polynomials-base/PolynomialsOverField.h"

template <integer Prime, integer MaxDegree>
using PolynomialOverPrimeSizeFiniteField = PolynomialOverField<MaxDegree, ElementOfFiniteFieldP<Prime>>;
