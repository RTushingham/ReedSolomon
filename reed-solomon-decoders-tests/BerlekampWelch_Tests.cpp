#include "reed-solomon-decoders/BerlekampWelch.h"
#include "reed-solomon-decoders/Geo.h"

#include "helpers/ErrorIntroduction.h"

#include "reed-solomon-codes/Code.h"
#include "reed-solomon-codes/Codeword.h"
#include "reed-solomon-codes/PolynomialsOverFiniteFieldOfSizePrimeToAPower.h"

#include "finite-fields-tests/helpers/InitializerHelper.h"

#include "gmock/gmock.h"
#include "gtest/gtest.h"

#include <vector>

constexpr integer Prime{ 101 };
constexpr integer Exponent{ 2 };
constexpr std::size_t n{ 4 };
constexpr std::size_t k{ 2 };

namespace
{
    std::vector<PolynomialOverFiniteField<Prime,Exponent,k-1>> polynomials
    { 
		PolynomialOverFiniteField<Prime,Exponent,k-1> 
        {
            std::array<ElementOfFiniteField<Prime, Exponent>, 2>
            {
                ElementOfFiniteField<Prime, Exponent>{
                    (x_to( 4,0 ) + x_to( 5, 1 )).evaluate<PolynomialOverPrimeSizeFiniteField<Prime,1>>()
                },
                ElementOfFiniteField<Prime, Exponent>{
                    (x_to( 7,0 ) + x_to( 6, 1 )).evaluate<PolynomialOverPrimeSizeFiniteField<Prime,1>>()
                }
            } 
        },
        PolynomialOverFiniteField<Prime,Exponent,k-1> 
        {
            std::array<ElementOfFiniteField<Prime, Exponent>, 2>
            {
                ElementOfFiniteField<Prime, Exponent>{
                    (x_to( 100,0 ) + x_to( 56, 1 )).evaluate<PolynomialOverPrimeSizeFiniteField<Prime,1>>()
                },
                ElementOfFiniteField<Prime, Exponent>{
                    (x_to( 1,0 ) + x_to( 23, 1 )).evaluate<PolynomialOverPrimeSizeFiniteField<Prime,1>>()
                }
            } 
        },
        PolynomialOverFiniteField<Prime,Exponent,k-1> 
        {
            std::array<ElementOfFiniteField<Prime, Exponent>, 2>
            {
                ElementOfFiniteField<Prime, Exponent>{
                    (x_to( 0,0 ) + x_to( 0, 1 )).evaluate<PolynomialOverPrimeSizeFiniteField<Prime,1>>()
                },
                ElementOfFiniteField<Prime, Exponent>{
                    (x_to( 0,0 ) + x_to( 0, 1 )).evaluate<PolynomialOverPrimeSizeFiniteField<Prime,1>>()
                }
            } 
        },
        PolynomialOverFiniteField<Prime,Exponent,k-1> 
        {
            std::array<ElementOfFiniteField<Prime, Exponent>, 2>
            {
                ElementOfFiniteField<Prime, Exponent>{
                    (x_to( 2,0 ) + x_to( 3, 1 )).evaluate<PolynomialOverPrimeSizeFiniteField<Prime,1>>()
                },
                ElementOfFiniteField<Prime, Exponent>{
                    (x_to( 5,0 ) + x_to( 7, 1 )).evaluate<PolynomialOverPrimeSizeFiniteField<Prime,1>>()
                }
            } 
        },
        PolynomialOverFiniteField<Prime,Exponent,k-1> 
        {
            std::array<ElementOfFiniteField<Prime, Exponent>, 2>
            {
                ElementOfFiniteField<Prime, Exponent>{
                    (x_to( 11,0 ) + x_to( 13, 1 )).evaluate<PolynomialOverPrimeSizeFiniteField<Prime,1>>()
                },
                ElementOfFiniteField<Prime, Exponent>{
                    (x_to( 17,0 ) + x_to( 19, 1 )).evaluate<PolynomialOverPrimeSizeFiniteField<Prime,1>>()
                }
            } 
        },
        PolynomialOverFiniteField<Prime,Exponent,k-1> 
        {
            std::array<ElementOfFiniteField<Prime, Exponent>, 2>
            {
                ElementOfFiniteField<Prime, Exponent>{
                    (x_to( 23,0 ) + x_to( 29, 1 )).evaluate<PolynomialOverPrimeSizeFiniteField<Prime,1>>()
                },
                ElementOfFiniteField<Prime, Exponent>{
                    (x_to( 31,0 ) + x_to( 37, 1 )).evaluate<PolynomialOverPrimeSizeFiniteField<Prime,1>>()
                }
            } 
        },
        PolynomialOverFiniteField<Prime,Exponent,k-1> 
        {
            std::array<ElementOfFiniteField<Prime, Exponent>, 2>
            {
                ElementOfFiniteField<Prime, Exponent>{
                    (x_to( 41,0 ) + x_to( 43, 1 )).evaluate<PolynomialOverPrimeSizeFiniteField<Prime,1>>()
                },
                ElementOfFiniteField<Prime, Exponent>{
                    (x_to( 47,0 ) + x_to( 53, 1 )).evaluate<PolynomialOverPrimeSizeFiniteField<Prime,1>>()
                }
            } 
        }
	};
	

	const ElementOfFiniteField<Prime, Exponent> argument_one{
        (x_to( 9,0 ) + x_to( 8, 1 )).evaluate<PolynomialOverPrimeSizeFiniteField<Prime,1>>()
	};
    
	const ElementOfFiniteField<Prime, Exponent> argument_two{
        (x_to( 10,0 ) + x_to( 11, 1 )).evaluate<PolynomialOverPrimeSizeFiniteField<Prime,1>>()
	};
    
	const ElementOfFiniteField<Prime, Exponent> argument_three{
        (x_to( 12,0 ) + x_to( 13, 1 )).evaluate<PolynomialOverPrimeSizeFiniteField<Prime,1>>()
	};
    
	const ElementOfFiniteField<Prime, Exponent> argument_four{
        (x_to( 14,0 ) + x_to( 15, 1 )).evaluate<PolynomialOverPrimeSizeFiniteField<Prime,1>>()
	};

	Code<n, k, Prime, Exponent> code{ std::array<ElementOfFiniteField<Prime, Exponent>,n>{ argument_one, argument_two, argument_three, argument_four } };
	const BerklekampWelchDecoder<n, k, Prime, Exponent> bw_decoder{ code };
	const GeoDecoder<n, k, Prime, Exponent> geo_decoder{ code };
	
	const std::array<ElementOfFiniteField<Prime, Exponent>,n>& generators{ code.generating_elements };
	constexpr std::size_t e = code.parameters.e;
}

TEST( DecoderTests, CodewordToCodewordRoundTripNoErrorCase )
{
    for( const auto& polynomial : polynomials )
    {
        const auto signal{ code.GenerateCodeword( polynomial ) };

        EXPECT_TRUE( bw_decoder.Decode( signal ).has_value() );
        EXPECT_EQ( signal, code.GenerateCodeword( bw_decoder.Decode( signal ).value() ) );

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
        
        EXPECT_TRUE( bw_decoder.Decode( signal ).has_value() );
        EXPECT_EQ( polynomial, bw_decoder.Decode( signal ).value() );
        
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
        
        EXPECT_FALSE( bw_decoder.Decode( signal ).has_value() );
        
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
        
        EXPECT_TRUE( bw_decoder.Decode( signal ).has_value() );
        EXPECT_NE( polynomial, bw_decoder.Decode( signal ).value() );

        EXPECT_TRUE( geo_decoder.Decode( signal ).has_value() );
        EXPECT_NE( polynomial, geo_decoder.Decode( signal ).value() );
    }
}

