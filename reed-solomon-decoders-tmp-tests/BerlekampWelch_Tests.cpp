
#include "reed-solomon-decoders-tmp/Geo.h"

#include "helpers/ErrorIntroduction.h"

#include "finite-fields-tmp/tmp_FiniteFieldsOfSizePrimeToAPower.h"
#include "reed-solomon-codes-tmp/Code.h"
#include "reed-solomon-codes-tmp/Codeword.h"

#include "finite-fields-tests/helpers/InitializerHelper.h"

#include "gmock/gmock.h"
#include "gtest/gtest.h"

#include <vector>

namespace
{
    constexpr integer Prime{ 2 };
    constexpr integer Exponent{ 8 };
    constexpr std::size_t n{ 4 };
    constexpr std::size_t k{ 2 };

    std::vector<ElementOfFiniteField_Poly<k-1,Exponent>> polynomials{ 
		ElementOfFiniteField_Poly<k-1,Exponent> 
        {
            std::array<ElementOfFiniteField<Prime, Exponent>, k>
            {
                ElementOfFiniteField<Prime, Exponent>{
                    ( x_to( 1,0 ) + x_to( 1,1 ) ).evaluate<PolynomialOverPrimeSizeFiniteField<Prime,Exponent-1>>()
                },
                ElementOfFiniteField<Prime, Exponent>{
                    ( x_to( 1,1 ) + x_to( 1,2 ) ).evaluate<PolynomialOverPrimeSizeFiniteField<Prime,Exponent-1>>()
                }
            } 
        },
        ElementOfFiniteField_Poly<k-1,Exponent> 
        {
            std::array<ElementOfFiniteField<Prime, Exponent>, k>
            {
                ElementOfFiniteField<Prime, Exponent>{
                    ( x_to( 1,2 ) + x_to( 1,3 ) ).evaluate<PolynomialOverPrimeSizeFiniteField<Prime,Exponent-1>>()
                },
                ElementOfFiniteField<Prime, Exponent>{
                    ( x_to( 1,3 ) + x_to( 1,4 ) ).evaluate<PolynomialOverPrimeSizeFiniteField<Prime,Exponent-1>>()
                }
            } 
        },
        ElementOfFiniteField_Poly<k-1,Exponent> 
        {
            std::array<ElementOfFiniteField<Prime, Exponent>, k>
            {
                ElementOfFiniteField<Prime, Exponent>{
                    ( x_to( 1,0 ) + x_to( 1,2 ) ).evaluate<PolynomialOverPrimeSizeFiniteField<Prime,Exponent-1>>()
                },
                ElementOfFiniteField<Prime, Exponent>{
                    ( x_to( 1,1 ) + x_to( 1,4 ) ).evaluate<PolynomialOverPrimeSizeFiniteField<Prime,Exponent-1>>()
                }
            } 
        },
        ElementOfFiniteField_Poly<k-1,Exponent> 
        {
            std::array<ElementOfFiniteField<Prime, Exponent>, k>
            {
                ElementOfFiniteField<Prime, Exponent>{
                    ( x_to( 1,2 ) + x_to( 1,6 ) ).evaluate<PolynomialOverPrimeSizeFiniteField<Prime,Exponent-1>>()
                },
                ElementOfFiniteField<Prime, Exponent>{
                    ( x_to( 1,3 ) + x_to( 1,0 ) ).evaluate<PolynomialOverPrimeSizeFiniteField<Prime,Exponent-1>>()
                }
            } 
        },
        ElementOfFiniteField_Poly<k-1,Exponent> 
        {
            std::array<ElementOfFiniteField<Prime, Exponent>, k>
            {
                ElementOfFiniteField<Prime, Exponent>{
                    ( x_to( 1,2 ) + x_to( 1,3 ) ).evaluate<PolynomialOverPrimeSizeFiniteField<Prime,Exponent-1>>()
                },
                ElementOfFiniteField<Prime, Exponent>{
                    ( x_to( 1,5 ) + x_to( 1,7 ) ).evaluate<PolynomialOverPrimeSizeFiniteField<Prime,Exponent-1>>()
                }
            } 
        },
        ElementOfFiniteField_Poly<k-1,Exponent> 
        {
            std::array<ElementOfFiniteField<Prime, Exponent>, k>
            {
                ElementOfFiniteField<Prime, Exponent>{
                    ( x_to( 1,3 ) + x_to( 1,5 ) ).evaluate<PolynomialOverPrimeSizeFiniteField<Prime,Exponent-1>>()
                },
                ElementOfFiniteField<Prime, Exponent>{
                    ( x_to( 1,1 ) + x_to( 1,3 ) ).evaluate<PolynomialOverPrimeSizeFiniteField<Prime,Exponent-1>>()
                }
            } 
        },
        ElementOfFiniteField_Poly<k-1,Exponent> 
        {
            std::array<ElementOfFiniteField<Prime, Exponent>, k>
            {
                ElementOfFiniteField<Prime, Exponent>{
                    ( x_to( 0,0 ) + x_to( 0,1 ) ).evaluate<PolynomialOverPrimeSizeFiniteField<Prime,Exponent-1>>()
                },
                ElementOfFiniteField<Prime, Exponent>{
                    ( x_to( 0,0 ) + x_to( 0,1 ) ).evaluate<PolynomialOverPrimeSizeFiniteField<Prime,Exponent-1>>()
                }
            } 
        },
        ElementOfFiniteField_Poly<k-1,Exponent> 
        {
            std::array<ElementOfFiniteField<Prime, Exponent>, k>
            {
                ElementOfFiniteField<Prime, Exponent>{
                    ( x_to( 0,0 ) + x_to( 0,1 ) ).evaluate<PolynomialOverPrimeSizeFiniteField<Prime,Exponent-1>>()
                },
                ElementOfFiniteField<Prime, Exponent>{
                    ( x_to( 0,0 ) + x_to( 0,1 ) ).evaluate<PolynomialOverPrimeSizeFiniteField<Prime,Exponent-1>>()
                }
            } 
        }
	};

	const ElementOfFiniteField<Prime, Exponent> argument_one{
        ( x_to( 1,0 ) + x_to( 1,1 ) ).evaluate<PolynomialOverPrimeSizeFiniteField<Prime,Exponent-1>>()
	};
    
	const ElementOfFiniteField<Prime, Exponent> argument_two{
        ( x_to( 1,1 ) + x_to( 1,2 ) ).evaluate<PolynomialOverPrimeSizeFiniteField<Prime,Exponent-1>>()
	};
    
	const ElementOfFiniteField<Prime, Exponent> argument_three{
        ( x_to( 1,2 ) + x_to( 1,3 ) ).evaluate<PolynomialOverPrimeSizeFiniteField<Prime,Exponent-1>>()
	};
    
	const ElementOfFiniteField<Prime, Exponent> argument_four{
        ( x_to( 1,3 ) + x_to( 1,4 ) ).evaluate<PolynomialOverPrimeSizeFiniteField<Prime,Exponent-1>>()
	};

	Code<n, k, Prime, Exponent> code{ 
        std::array<ElementOfFiniteField<Prime, Exponent>,n>{ 
            argument_one, 
            argument_two, 
            argument_three,
            argument_four 
        } 
    };

	const GeoDecoder<n, k, Prime, Exponent> geo_decoder{ code };
	
	const std::array<ElementOfFiniteField<Prime, Exponent>,n>& generators{ code.generating_elements };
	constexpr std::size_t e = code.parameters.e;
}

TEST( DecoderTests, CodewordToCodewordRoundTripNoErrorCase )
{
    for( const auto& polynomial : polynomials )
    {
        const auto signal{ code.GenerateCodeword( polynomial ) };

        EXPECT_TRUE( geo_decoder.Decode( signal ).has_value() );
        EXPECT_EQ( signal, code.GenerateCodeword( geo_decoder.Decode( signal ).value() ) );
    }
}

TEST( DecoderTests, CodewordToCodewordRoundTripOneErrorCase )
{
    for( const auto& polynomial : polynomials )
    {
        EXPECT_TRUE( code.parameters.e >= 1 );

        auto signal{ code.GenerateCodeword( polynomial ) };

        introduce_any_errors( 1, signal );
        
        EXPECT_TRUE( geo_decoder.Decode( signal ).has_value() );
        EXPECT_EQ( polynomial, geo_decoder.Decode( signal ).value() );
    }
}

TEST( DecoderTests, CodewordToCodewordRoundTripUnrecoverableSituation )
{
    for( const auto& polynomial : polynomials )
    {
        EXPECT_TRUE( code.parameters.e < 2 );
        EXPECT_TRUE( code.parameters.d - code.parameters.e >= 2 );
        
        auto signal{ code.GenerateCodeword( polynomial ) };
        
        // There is no guarantee that these are actually unrecoverable
        introduce_any_errors( 2, signal );
        
        EXPECT_FALSE( geo_decoder.Decode( signal ).has_value() );
    }
}

TEST( DecoderTests, CodewordToCodewordRoundTripIncorrectlyRecovered )
{
    for( const auto& polynomial : polynomials )
    {
        EXPECT_TRUE( code.parameters.d % 2 == 1 );
        EXPECT_TRUE( code.parameters.e < 2 );

        auto signal{ code.GenerateCodeword( polynomial ) };
        
        introduce_any_errors( 3, signal );
        
        EXPECT_TRUE( geo_decoder.Decode( signal ).has_value() );
        EXPECT_NE( polynomial, geo_decoder.Decode( signal ).value() );
    }
}

