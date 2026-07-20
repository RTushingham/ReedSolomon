#include "reed-solomon-decoders-tmp/Geo.h"

#include "finite-fields-tmp/ElementOfFiniteField_Poly.h"
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
            EXPECT_EQ( l_i_res( code.generating_elements.at( generator_index ) ), signal.at( generator_index ) );
        }
    }
}

