#pragma once

#include "Codeword.h"

#include "cpp-helpers/Typedef.h"
#include "finite-fields/FiniteFieldsOfSizePrimeToAPower.h"
#include "finite-fields-polynomials/PolynomialsOverFiniteFieldOfSizePrimeToAPower.h"

template<typename E, std::size_t n, std::size_t k, integer Prime, integer Exponent>
class IEncoderSchema
{
public:
    PolynomialOverFiniteField<Prime,Exponent, k-1> MessageToPolynomial( const Message<n, k, Prime, Exponent>& message ) const
    {
        return static_cast<E const&>( *this ).MessageToPolynomial( message );
    }

    Message<n, k, Prime, Exponent> PolynomialToMessage( const PolynomialOverFiniteField<Prime,Exponent, k-1>& polynomial ) const
    {
        return static_cast<E const&>( *this ).PolynomialToMessage( polynomial );
    }
};

