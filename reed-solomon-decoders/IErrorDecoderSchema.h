#pragma once

#include "finite-fields-polynomials/PolynomialsOverFiniteFieldOfSizePrimeToAPower.h"
#include "reed-solomon-codes/Codeword.h"

#include "cpp-helpers/Typedef.h"

#include <optional>

template<typename E, std::size_t n, std::size_t k, integer Prime, integer Exponent>
class IErrorDecoderSchema
{
public:
    std::optional<PolynomialOverFiniteField<Prime,Exponent, k-1>> Decode( const Signal<n, k, Prime, Exponent>& recieved_signal ) const
    {
        return static_cast<E const&>( *this ).Decode( recieved_signal );
    }
};

