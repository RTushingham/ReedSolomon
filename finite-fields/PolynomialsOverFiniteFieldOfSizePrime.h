#pragma once

#include "FiniteFieldsOfSizePrime.h"

#include "finite-fields/PolynomialsOverField.h"

template <integer Prime, integer MaxDegree>
using PolynomialOverPrimeSizeFiniteField = PolynomialOverField<MaxDegree, ElementOfFiniteFieldP<Prime>>;
