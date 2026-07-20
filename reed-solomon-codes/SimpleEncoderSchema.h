#pragma once

#include "Schema.h"
#include "Codeword.h"
#include "IEncoderSchema.h"

#include "container-helpers/ArrayTransformation.h"
#include "cpp-helpers/Typedef.h"
#include "finite-fields/FiniteFieldsOfSizePrimeToAPower.h"
#include "finite-fields-polynomials/PolynomialsOverFiniteFieldOfSizePrimeToAPower.h"

template<std::size_t n, std::size_t k, integer Prime, integer Exponent>
class SimpleEncoderSchema : public IEncoderSchema<SimpleEncoderSchema<n,k,Prime,Exponent>,n,k,Prime,Exponent>
{
    const Schema<n,k,Prime,Exponent> schema;

public:
    PolynomialOverFiniteField<Prime,Exponent, k-1> MessageToPolynomial( const Message<n, k, Prime, Exponent>& message ) const
    {
        return { message };
    }

    Message<n, k, Prime, Exponent> PolynomialToMessage( const PolynomialOverFiniteField<Prime,Exponent, k-1>& polynomial ) const
    {
        Message<n, k, Prime, Exponent> message{};

        for( std::size_t generator_index{ 0 }; generator_index < message.size(); generator_index++ )
        {
            message.at( generator_index ) = polynomial.GetCoeff( generator_index );
        }

        return message;
    }

    SimpleEncoderSchema( const Schema<n,k,Prime,Exponent>& input_schema )
        : schema{ input_schema }
    {}
};

