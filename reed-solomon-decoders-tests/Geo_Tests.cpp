#include "reed-solomon-decoders/Geo.h"

#include "finite-fields-tests/helpers/InitializerHelper.h"
#include "reed-solomon-codes/PolynomialsOverFiniteFieldOfSizePrimeToAPower.h"

#include "gmock/gmock.h"
#include "gtest/gtest.h"

#include <vector>

namespace
{
    constexpr integer Prime{ 101 };
    constexpr integer Exponent{ 2 };
    constexpr std::size_t n{ 4 };
    constexpr std::size_t k{ 2 };

    std::vector<PolynomialOverFiniteField<Prime,Exponent,k-1>> polynomials{ 
		PolynomialOverFiniteField<Prime,Exponent,k-1> 
        {
            std::array<ElementOfFiniteField<Prime, Exponent>, k>
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
            std::array<ElementOfFiniteField<Prime, Exponent>, k>
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
            std::array<ElementOfFiniteField<Prime, Exponent>, k>
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
            std::array<ElementOfFiniteField<Prime, Exponent>, k>
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
            std::array<ElementOfFiniteField<Prime, Exponent>, k>
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
            std::array<ElementOfFiniteField<Prime, Exponent>, k>
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
            std::array<ElementOfFiniteField<Prime, Exponent>, k>
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

	Code<n, k, Prime, Exponent> code{ 
        std::array<ElementOfFiniteField<Prime, Exponent>,n>{ 
            argument_one, 
            argument_two, 
            argument_three,
            argument_four 
        } 
    };

	const GeoDecoder<n, k, Prime, Exponent> geo_decoder{ code };
}


TEST( GeoInternalsTests, InitialTermIsAsExpected )
{
    EXPECT_EQ( geo_decoder.m_initial_term.GetDegree(), code.generating_elements.size() );
    for( const auto& generator : code.generating_elements )
    {
        EXPECT_TRUE( geo_decoder.m_initial_term( generator ).IsZero() );
    }
}

TEST( GeoInternalsTests, LegrangeInterpolationWorks )
{
    for( const auto& polynomial : polynomials )
    {
        const auto signal{ code.GenerateCodeword( polynomial ) };
        const auto l_i_res{ geo_decoder.LagrangeInterpolation( signal ) };

        for( std::size_t generator_index{ 0 }; generator_index < code.generating_elements.size(); generator_index++ )
        {
            EXPECT_EQ( l_i_res( code.generating_elements.at( generator_index ) ), signal.blocks.at( generator_index ) );
        }
    }
}

