#pragma once

#include "finite-fields-polynomials/PolynomialsOverFiniteFieldOfSizePrimeToAPower.h"

#include "functional-tests/schemas/FamousRSSchemas.h"
#include "tests/finite-fields-tests/helpers/InitializerHelper.h"

#include <vector>

template<typename RSSchema>
class Po
{
    static_assert( false, "Template requires specialization." );
};

template<>
class Po<PrimePowerGF>
{
    static constexpr size_t n{ PrimePowerGF::n };
    static constexpr size_t k{ PrimePowerGF::k };
    static constexpr size_t Prime{ PrimePowerGF::Prime };
    static constexpr size_t Exponent{ PrimePowerGF::Exponent };

public:
    std::vector<PolynomialOverFiniteField<Prime,Exponent,k-1>> polynomials{ 
        PolynomialOverFiniteField<Prime,Exponent,k-1> 
        {
            std::array<ElementOfFiniteField<Prime, Exponent>, k>
            {
                ElementOfFiniteField<Prime, Exponent>{
                    (x_to( 4,0 ) + x_to( 5, 1 )).evaluate<PolynomialOverPrimeSizeFiniteField<Prime,Exponent-1>>()
                },
                ElementOfFiniteField<Prime, Exponent>{
                    (x_to( 7,0 ) + x_to( 6, 1 )).evaluate<PolynomialOverPrimeSizeFiniteField<Prime,Exponent-1>>()
                }
            } 
        },
        PolynomialOverFiniteField<Prime,Exponent,k-1> 
        {
            std::array<ElementOfFiniteField<Prime, Exponent>, k>
            {
                ElementOfFiniteField<Prime, Exponent>{
                    (x_to( 100,0 ) + x_to( 56, 1 )).evaluate<PolynomialOverPrimeSizeFiniteField<Prime,Exponent-1>>()
                },
                ElementOfFiniteField<Prime, Exponent>{
                    (x_to( 1,0 ) + x_to( 23, 1 )).evaluate<PolynomialOverPrimeSizeFiniteField<Prime,Exponent-1>>()
                }
            } 
        },
        PolynomialOverFiniteField<Prime,Exponent,k-1> 
        {
            std::array<ElementOfFiniteField<Prime, Exponent>, k>
            {
                ElementOfFiniteField<Prime, Exponent>{
                    (x_to( 0,0 ) + x_to( 0, 1 )).evaluate<PolynomialOverPrimeSizeFiniteField<Prime,Exponent-1>>()
                },
                ElementOfFiniteField<Prime, Exponent>{
                    (x_to( 0,0 ) + x_to( 0, 1 )).evaluate<PolynomialOverPrimeSizeFiniteField<Prime,Exponent-1>>()
                }
            } 
        },
        PolynomialOverFiniteField<Prime,Exponent,k-1> 
        {
            std::array<ElementOfFiniteField<Prime, Exponent>, k>
            {
                ElementOfFiniteField<Prime, Exponent>{
                    (x_to( 2,0 ) + x_to( 3, 1 )).evaluate<PolynomialOverPrimeSizeFiniteField<Prime,Exponent-1>>()
                },
                ElementOfFiniteField<Prime, Exponent>{
                    (x_to( 5,0 ) + x_to( 7, 1 )).evaluate<PolynomialOverPrimeSizeFiniteField<Prime,Exponent-1>>()
                }
            } 
        },
        PolynomialOverFiniteField<Prime,Exponent,k-1> 
        {
            std::array<ElementOfFiniteField<Prime, Exponent>, k>
            {
                ElementOfFiniteField<Prime, Exponent>{
                    (x_to( 11,0 ) + x_to( 13, 1 )).evaluate<PolynomialOverPrimeSizeFiniteField<Prime,Exponent-1>>()
                },
                ElementOfFiniteField<Prime, Exponent>{
                    (x_to( 17,0 ) + x_to( 19, 1 )).evaluate<PolynomialOverPrimeSizeFiniteField<Prime,Exponent-1>>()
                }
            } 
        },
        PolynomialOverFiniteField<Prime,Exponent,k-1> 
        {
            std::array<ElementOfFiniteField<Prime, Exponent>, k>
            {
                ElementOfFiniteField<Prime, Exponent>{
                    (x_to( 23,0 ) + x_to( 29, 1 )).evaluate<PolynomialOverPrimeSizeFiniteField<Prime,Exponent-1>>()
                },
                ElementOfFiniteField<Prime, Exponent>{
                    (x_to( 31,0 ) + x_to( 37, 1 )).evaluate<PolynomialOverPrimeSizeFiniteField<Prime,Exponent-1>>()
                }
            } 
        },
        PolynomialOverFiniteField<Prime,Exponent,k-1> 
        {
            std::array<ElementOfFiniteField<Prime, Exponent>, k>
            {
                ElementOfFiniteField<Prime, Exponent>{
                    (x_to( 41,0 ) + x_to( 43, 1 )).evaluate<PolynomialOverPrimeSizeFiniteField<Prime,Exponent-1>>()
                },
                ElementOfFiniteField<Prime, Exponent>{
                    (x_to( 47,0 ) + x_to( 53, 1 )).evaluate<PolynomialOverPrimeSizeFiniteField<Prime,Exponent-1>>()
                }
            } 
        }
    };
};

template<>
class Po<BinaryUint8GFUint32MessageUint64Codeword>
{
    static constexpr size_t n{ BinaryUint8GFUint32MessageUint64Codeword::n };
    static constexpr size_t k{ BinaryUint8GFUint32MessageUint64Codeword::k };
    static constexpr size_t Prime{ BinaryUint8GFUint32MessageUint64Codeword::Prime };
    static constexpr size_t Exponent{ BinaryUint8GFUint32MessageUint64Codeword::Exponent };

public:
    std::vector<PolynomialOverFiniteField<Prime,Exponent,k-1>> polynomials{ 
        PolynomialOverFiniteField<Prime,Exponent,k-1> 
        {
            std::array<ElementOfFiniteField<Prime, Exponent>, k>
            {
                ElementOfFiniteField<Prime, Exponent>{
                    ( x_to( 1,0 ) ).evaluate<PolynomialOverPrimeSizeFiniteField<Prime,Exponent-1>>()
                },
                ElementOfFiniteField<Prime, Exponent>{
                    ( x_to( 1,1 ) ).evaluate<PolynomialOverPrimeSizeFiniteField<Prime,Exponent-1>>()
                },
                ElementOfFiniteField<Prime, Exponent>{
                    ( x_to( 1,2 ) ).evaluate<PolynomialOverPrimeSizeFiniteField<Prime,Exponent-1>>()
                },
                ElementOfFiniteField<Prime, Exponent>{
                    ( x_to( 1,2 ) ).evaluate<PolynomialOverPrimeSizeFiniteField<Prime,Exponent-1>>()
                }
            } 
        },
        PolynomialOverFiniteField<Prime,Exponent,k-1> 
        {
            std::array<ElementOfFiniteField<Prime, Exponent>, k>
            {
                ElementOfFiniteField<Prime, Exponent>{
                    ( x_to( 1,4 ) ).evaluate<PolynomialOverPrimeSizeFiniteField<Prime,Exponent-1>>()
                },
                ElementOfFiniteField<Prime, Exponent>{
                    ( x_to( 1,5 ) ).evaluate<PolynomialOverPrimeSizeFiniteField<Prime,Exponent-1>>()
                },
                ElementOfFiniteField<Prime, Exponent>{
                    ( x_to( 1,6 ) ).evaluate<PolynomialOverPrimeSizeFiniteField<Prime,Exponent-1>>()
                },
                ElementOfFiniteField<Prime, Exponent>{
                    ( x_to( 1,7 ) ).evaluate<PolynomialOverPrimeSizeFiniteField<Prime,Exponent-1>>()
                }
            } 
        }
    };
};

template<>
class Po<BinaryUint16GFUint32MessageUint64Codeword>
{
    static constexpr size_t n{ BinaryUint16GFUint32MessageUint64Codeword::n };
    static constexpr size_t k{ BinaryUint16GFUint32MessageUint64Codeword::k };
    static constexpr size_t Prime{ BinaryUint16GFUint32MessageUint64Codeword::Prime };
    static constexpr size_t Exponent{ BinaryUint16GFUint32MessageUint64Codeword::Exponent };

public:
    std::vector<PolynomialOverFiniteField<Prime,Exponent,k-1>> polynomials{ 
        PolynomialOverFiniteField<Prime,Exponent,k-1> 
        {
            std::array<ElementOfFiniteField<Prime, Exponent>, k>
            {
                ElementOfFiniteField<Prime, Exponent>{
                    ( x_to( 1,0 ) ).evaluate<PolynomialOverPrimeSizeFiniteField<Prime,Exponent-1>>()
                },
                ElementOfFiniteField<Prime, Exponent>{
                    ( x_to( 1,1 ) ).evaluate<PolynomialOverPrimeSizeFiniteField<Prime,Exponent-1>>()
                }
            } 
        },
        PolynomialOverFiniteField<Prime,Exponent,k-1> 
        {
            std::array<ElementOfFiniteField<Prime, Exponent>, k>
            {
                ElementOfFiniteField<Prime, Exponent>{
                    ( x_to( 1,2 ) ).evaluate<PolynomialOverPrimeSizeFiniteField<Prime,Exponent-1>>()
                },
                ElementOfFiniteField<Prime, Exponent>{
                    ( x_to( 1,2 ) ).evaluate<PolynomialOverPrimeSizeFiniteField<Prime,Exponent-1>>()
                }
            } 
        },
        PolynomialOverFiniteField<Prime,Exponent,k-1> 
        {
            std::array<ElementOfFiniteField<Prime, Exponent>, k>
            {
                ElementOfFiniteField<Prime, Exponent>{
                    ( x_to( 1,4 ) ).evaluate<PolynomialOverPrimeSizeFiniteField<Prime,Exponent-1>>()
                },
                ElementOfFiniteField<Prime, Exponent>{
                    ( x_to( 1,5 ) ).evaluate<PolynomialOverPrimeSizeFiniteField<Prime,Exponent-1>>()
                }
            } 
        },
        PolynomialOverFiniteField<Prime,Exponent,k-1> 
        {
            std::array<ElementOfFiniteField<Prime, Exponent>, k>
            {
                ElementOfFiniteField<Prime, Exponent>{
                    ( x_to( 1,6 ) ).evaluate<PolynomialOverPrimeSizeFiniteField<Prime,Exponent-1>>()
                },
                ElementOfFiniteField<Prime, Exponent>{
                    ( x_to( 1,7 ) ).evaluate<PolynomialOverPrimeSizeFiniteField<Prime,Exponent-1>>()
                }
            } 
        }
    };
};

