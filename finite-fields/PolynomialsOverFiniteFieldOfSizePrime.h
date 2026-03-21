#pragma once

#include "FiniteFieldsOfSizePrime.h"

#include "polynomials-base/PolynomialsOverField.h"

// As part of building the ability to create any read solomon codes we need to create elements of finite fields (aka Galois Fields)
//   All finite fields are of the size p**k where p and k are positive integers, and p is a prime.
//   If k > 1 then the elements need to be expressable as polynomials modulo an irriducible polynomial over a finite filed of size p.
// In order to do that I need to be able to create polynomials over a finite filed of size p.
//   I would like to represent these as having a fixed maxium number of coefficients, as opposed to the normal mathematical notation.
//   As not all elements have multiplicative inverses, this is just a ring, so no division operation exists

template <integer Prime, integer MaxDegree>
using PolynomialOverPrimeSizeFiniteField = PolynomialOverField<MaxDegree, ElementOfFiniteFieldP<Prime>>;
