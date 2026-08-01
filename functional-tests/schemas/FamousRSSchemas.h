#pragma once

#include "cpp-helpers/Typedef.h"
#include "reed-solomon-codes/Schema.h"

#include "finite-fields-polynomials/PolynomialsOverFiniteFieldOfSizePrimeToAPower.h"

#include "tests/finite-fields-tests/helpers/InitializerHelper.h"

class BinaryUint8GFUint32MessageUint64Codeword
{
public:
    static constexpr integer Prime{ 2 };
    static constexpr integer Exponent{ 8 };
    static constexpr std::size_t k{ 4 };
    static constexpr std::size_t n{ 8 };

    static constexpr Schema<n, k, Prime, Exponent> schema{
        []() -> Schema<n, k, Prime, Exponent> {
            ElementOfFiniteField<Prime, Exponent> argument_one{
                x_to( 1,0 ).evaluate<PolynomialOverPrimeSizeFiniteField<Prime, Exponent-1>>()
            };

            ElementOfFiniteField<Prime, Exponent> argument_two{
                x_to( 1,1 ).evaluate<PolynomialOverPrimeSizeFiniteField<Prime, Exponent-1>>()
            };

            ElementOfFiniteField<Prime, Exponent> argument_three{
                x_to( 1,2 ).evaluate<PolynomialOverPrimeSizeFiniteField<Prime, Exponent-1>>()
            };

            ElementOfFiniteField<Prime, Exponent> argument_four{
                x_to( 1,3 ).evaluate<PolynomialOverPrimeSizeFiniteField<Prime, Exponent-1>>()
            };

            ElementOfFiniteField<Prime, Exponent> argument_five{
                x_to( 1,4 ).evaluate<PolynomialOverPrimeSizeFiniteField<Prime, Exponent-1>>()
            };

            ElementOfFiniteField<Prime, Exponent> argument_six{
                x_to( 1,5 ).evaluate<PolynomialOverPrimeSizeFiniteField<Prime, Exponent-1>>()
            };

            ElementOfFiniteField<Prime, Exponent> argument_seven{
                x_to( 1,6 ).evaluate<PolynomialOverPrimeSizeFiniteField<Prime, Exponent-1>>()
            };

            ElementOfFiniteField<Prime, Exponent> argument_eight{
                x_to( 1,7 ).evaluate<PolynomialOverPrimeSizeFiniteField<Prime, Exponent-1>>()
            };

            return { std::array<ElementOfFiniteField<Prime, Exponent>, n>{ argument_one, argument_two, argument_three, argument_four, argument_five, argument_six, argument_seven, argument_eight } };
        }() // NOTE - invoke immediately
    };
};

class BinaryUint16GFUint32MessageUint64Codeword
{
public:
    static constexpr integer Prime{ 2 };
    static constexpr integer Exponent{ 16 };
    static constexpr size_t k{ 2 };
    static constexpr size_t n{ 4 };

	static constexpr Schema<n, k, Prime, Exponent> schema{
        []() -> Schema<n, k, Prime, Exponent> {
            ElementOfFiniteField<Prime, Exponent> argument_one{
                x_to( 1,0 ).evaluate<PolynomialOverPrimeSizeFiniteField<Prime,Exponent-1>>()
            };

            ElementOfFiniteField<Prime, Exponent> argument_two{
                x_to( 1,1 ).evaluate<PolynomialOverPrimeSizeFiniteField<Prime,Exponent-1>>()
            };

            ElementOfFiniteField<Prime, Exponent> argument_three{
                x_to( 1,2 ).evaluate<PolynomialOverPrimeSizeFiniteField<Prime,Exponent-1>>()
            };

            ElementOfFiniteField<Prime, Exponent> argument_four{
                x_to( 1,3 ).evaluate<PolynomialOverPrimeSizeFiniteField<Prime,Exponent-1>>()
            };

            return{ std::array<ElementOfFiniteField<Prime, Exponent>,n>{ argument_one, argument_two, argument_three, argument_four } };
        }() // NOTE - invoke immediately
    };
};

class PrimePowerGF
{
public:
    static constexpr integer Prime{ 101 };
    static constexpr integer Exponent{ 2 };
    static constexpr std::size_t n{ 4 };
    static constexpr std::size_t k{ 2 };

    static constexpr Schema<n, k, Prime, Exponent> schema{
        []() -> Schema<n, k, Prime, Exponent> {
            ElementOfFiniteField<Prime, Exponent> argument_one{
                PolynomialOverPrimeSizeFiniteField<Prime,Exponent-1>{
                    std::array<ElementOfFiniteFieldP<Prime>,Exponent>{
                        ElementOfFiniteFieldP<Prime>{ 9 },
                        ElementOfFiniteFieldP<Prime>{ 8 }
                    } 
                }
            };

            ElementOfFiniteField<Prime, Exponent> argument_two{
                PolynomialOverPrimeSizeFiniteField<Prime,Exponent-1>{
                    std::array<ElementOfFiniteFieldP<Prime>,Exponent>{
                        ElementOfFiniteFieldP<Prime>{ 10 },
                        ElementOfFiniteFieldP<Prime>{ 11 }
                    } 
                }
            };

            ElementOfFiniteField<Prime, Exponent> argument_three{
                PolynomialOverPrimeSizeFiniteField<Prime,Exponent-1>{
                    std::array<ElementOfFiniteFieldP<Prime>,Exponent>{
                        ElementOfFiniteFieldP<Prime>{ 12 },
                        ElementOfFiniteFieldP<Prime>{ 13 }
                    } 
                }
            };

            ElementOfFiniteField<Prime, Exponent> argument_four{
                PolynomialOverPrimeSizeFiniteField<Prime,Exponent-1>{
                    std::array<ElementOfFiniteFieldP<Prime>,Exponent>{
                        ElementOfFiniteFieldP<Prime>{ 14 },
                        ElementOfFiniteFieldP<Prime>{ 15 }
                    } 
                }
            };

            return std::array<ElementOfFiniteField<Prime, Exponent>, n>{ argument_one, argument_two, argument_three, argument_four };
        }() // NOTE - invoke immediately
    };
};

