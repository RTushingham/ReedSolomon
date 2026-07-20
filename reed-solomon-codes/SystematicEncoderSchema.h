#pragma once

#include "Schema.h"
#include "Codeword.h"
#include "IEncoderSchema.h"

#include "container-helpers/ArrayTransformation.h"
#include "cpp-helpers/Typedef.h"
#include "finite-fields/FiniteFieldsOfSizePrimeToAPower.h"
#include "finite-fields-extensions/LagrangeInterpolation.h"
#include "finite-fields-polynomials/PolynomialsOverFiniteFieldOfSizePrimeToAPower.h"

template<std::size_t n, std::size_t k, integer Prime, integer Exponent>
class SystematicEncoderSchema : public IEncoderSchema<SystematicEncoderSchema<n,k,Prime,Exponent>,n,k,Prime,Exponent>
{
    const Schema<n,k,Prime,Exponent> schema;
    
    const LagrangeInterpolation<k, ElementOfFiniteField<Prime,Exponent>> interpolator;

public:
    PolynomialOverFiniteField<Prime,Exponent, k-1> MessageToPolynomial( const Message<n, k, Prime, Exponent>& message ) const
    {
        return interpolator.Interpolate( message );
    }

    Message<n, k, Prime, Exponent> PolynomialToMessage( const PolynomialOverFiniteField<Prime,Exponent, k-1>& polynomial ) const
    {
        Message<n, k, Prime, Exponent> message{};

        for( std::size_t generator_index{ 0 }; generator_index < message.size(); generator_index++ )
        {
            message.at( generator_index ) = polynomial( schema.generating_elements.at( generator_index ) );
        }

        return message;
    }

    SystematicEncoderSchema( const Schema<n,k,Prime,Exponent>& input_schema )
        : schema{ input_schema }
        , interpolator{ CopyFirstKElements<ElementOfFiniteField<Prime,Exponent>, k, n>( input_schema.generating_elements ) }
    {}
};

