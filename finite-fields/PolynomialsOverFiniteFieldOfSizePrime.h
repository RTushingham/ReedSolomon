#pragma once

#include "FiniteFieldsOfSizePrime.h"
#include "PolynomialsOverField.h"

template <integer Prime, integer MaxDegree>
using PolynomialOverPrimeSizeFiniteField = PolynomialOverField<MaxDegree, ElementOfFiniteFieldP<Prime>>;
