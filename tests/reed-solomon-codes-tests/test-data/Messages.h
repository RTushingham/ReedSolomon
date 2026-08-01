#pragma once

#include "reed-solomon-codes/Codeword.h"
#include "finite-fields-polynomials/PolynomialsOverFiniteFieldOfSizePrimeToAPower.h"

#include "functional-tests/schemas/FamousRSSchemas.h"
#include "tests/finite-fields-tests/binary-helpers/CharToElm.h"
#include "tests/finite-fields-tests/helpers/InitializerHelper.h"

#include <vector>

template<typename RSSchema>
class Msgs
{
    static_assert( false, "Template requires specialization." );
};

template<>
class Msgs<BinaryUint16GFUint32MessageUint64Codeword>
{
    static constexpr size_t n{ BinaryUint16GFUint32MessageUint64Codeword::n };
    static constexpr size_t k{ BinaryUint16GFUint32MessageUint64Codeword::k };
    static constexpr size_t Prime{ BinaryUint16GFUint32MessageUint64Codeword::Prime };
    static constexpr size_t Exponent{ BinaryUint16GFUint32MessageUint64Codeword::Exponent };

public:
    // These are specific messages which previous versions failed to decode.
    std::vector<Message<n, k, Prime, Exponent>> messages
    {
        std::array<ElementOfFiniteField<Prime, Exponent>, k>
        {
            ElementOfFiniteField<Prime, Exponent>{
                ( x_to( 1,0 ) + x_to( 1,1 ) ).evaluate<PolynomialOverPrimeSizeFiniteField<Prime,Exponent-1>>()
            },
            ElementOfFiniteField<Prime, Exponent>{
                ( x_to( 1,1 ) + x_to( 1,2 ) ).evaluate<PolynomialOverPrimeSizeFiniteField<Prime,Exponent-1>>()
            }
        },
        std::array<ElementOfFiniteField<Prime, Exponent>, k>
        {
            ElementOfFiniteField<Prime, Exponent>{
                ( x_to( 1,2 ) + x_to( 1,3 ) ).evaluate<PolynomialOverPrimeSizeFiniteField<Prime,Exponent-1>>()
            },
            ElementOfFiniteField<Prime, Exponent>{
                ( x_to( 1,3 ) + x_to( 1,4 ) ).evaluate<PolynomialOverPrimeSizeFiniteField<Prime,Exponent-1>>()
            }
        },
        std::array<ElementOfFiniteField<Prime, Exponent>, k>
        {
            ElementOfFiniteField<Prime, Exponent>{
                ( x_to( 1,0 ) + x_to( 1,2 ) ).evaluate<PolynomialOverPrimeSizeFiniteField<Prime,Exponent-1>>()
            },
            ElementOfFiniteField<Prime, Exponent>{
                ( x_to( 1,1 ) + x_to( 1,4 ) ).evaluate<PolynomialOverPrimeSizeFiniteField<Prime,Exponent-1>>()
            }
        },
        std::array<ElementOfFiniteField<Prime, Exponent>, k>
        {
            ElementOfFiniteField<Prime, Exponent>{
                ( x_to( 1,2 ) + x_to( 1,6 ) ).evaluate<PolynomialOverPrimeSizeFiniteField<Prime,Exponent-1>>()
            },
            ElementOfFiniteField<Prime, Exponent>{
                ( x_to( 1,3 ) + x_to( 1,0 ) ).evaluate<PolynomialOverPrimeSizeFiniteField<Prime,Exponent-1>>()
            }
        },
        std::array<ElementOfFiniteField<Prime, Exponent>, k>
        {
            ElementOfFiniteField<Prime, Exponent>{
                ( x_to( 1,2 ) + x_to( 1,3 ) ).evaluate<PolynomialOverPrimeSizeFiniteField<Prime,Exponent-1>>()
            },
            ElementOfFiniteField<Prime, Exponent>{
                ( x_to( 1,5 ) + x_to( 1,7 ) ).evaluate<PolynomialOverPrimeSizeFiniteField<Prime,Exponent-1>>()
            }
        },
        std::array<ElementOfFiniteField<Prime, Exponent>, k>
        {
            ElementOfFiniteField<Prime, Exponent>{
                ( x_to( 1,3 ) + x_to( 1,5 ) ).evaluate<PolynomialOverPrimeSizeFiniteField<Prime,Exponent-1>>()
            },
            ElementOfFiniteField<Prime, Exponent>{
                ( x_to( 1,1 ) + x_to( 1,3 ) ).evaluate<PolynomialOverPrimeSizeFiniteField<Prime,Exponent-1>>()
            }
        },
        std::array<ElementOfFiniteField<Prime, Exponent>, k>
        {
            ElementOfFiniteField<Prime, Exponent>{
                ( x_to( 0,0 ) + x_to( 0,1 ) ).evaluate<PolynomialOverPrimeSizeFiniteField<Prime,Exponent-1>>()
            },
            ElementOfFiniteField<Prime, Exponent>{
                ( x_to( 0,0 ) + x_to( 0,1 ) ).evaluate<PolynomialOverPrimeSizeFiniteField<Prime,Exponent-1>>()
            }
        },
        std::array<ElementOfFiniteField<Prime, Exponent>, k>
        {
            ElementOfFiniteField<Prime, Exponent>{
                ( x_to( 0,0 ) + x_to( 0,1 ) ).evaluate<PolynomialOverPrimeSizeFiniteField<Prime,Exponent-1>>()
            },
            ElementOfFiniteField<Prime, Exponent>{
                ( x_to( 0,0 ) + x_to( 0,1 ) ).evaluate<PolynomialOverPrimeSizeFiniteField<Prime,Exponent-1>>()
            }
        }
    };
};

