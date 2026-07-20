#include "finite-fields-extensions/LagrangeInterpolation.h"

#include "container-helpers/ArrayExtensions.h"
#include "finite-fields-tests/helpers/InitializerHelper.h"
#include "finite-fields-polynomials/PolynomialsOverFiniteFieldOfSizePrimeToAPower.h"

#include "gmock/gmock.h"
#include "gtest/gtest.h"

#include <vector>

namespace
{
    constexpr integer Prime{ 101 };
    constexpr integer Exponent{ 2 };
    constexpr std::size_t n{ 4 };
    constexpr std::size_t k{ 2 };

    std::vector<std::array<ElementOfFiniteField<Prime, Exponent>, n>> basis_or_values
    { 
        std::array<ElementOfFiniteField<Prime, Exponent>, n>
        {
            ElementOfFiniteField<Prime, Exponent>{
                (x_to( 4,0 ) + x_to( 5, 1 )).evaluate<PolynomialOverPrimeSizeFiniteField<Prime,1>>()
            },
            ElementOfFiniteField<Prime, Exponent>{
                (x_to( 7,0 ) + x_to( 6, 1 )).evaluate<PolynomialOverPrimeSizeFiniteField<Prime,1>>()
            },
            ElementOfFiniteField<Prime, Exponent>{
                (x_to( 8,0 ) + x_to( 9, 1 )).evaluate<PolynomialOverPrimeSizeFiniteField<Prime,1>>()
            },
            ElementOfFiniteField<Prime, Exponent>{
                (x_to( 11,0 ) + x_to( 10, 1 )).evaluate<PolynomialOverPrimeSizeFiniteField<Prime,1>>()
            }
        },
        std::array<ElementOfFiniteField<Prime, Exponent>, n>
        {
            ElementOfFiniteField<Prime, Exponent>{
                (x_to( 100,0 ) + x_to( 56, 1 )).evaluate<PolynomialOverPrimeSizeFiniteField<Prime,1>>()
            },
            ElementOfFiniteField<Prime, Exponent>{
                (x_to( 1,0 ) + x_to( 23, 1 )).evaluate<PolynomialOverPrimeSizeFiniteField<Prime,1>>()
            },
            ElementOfFiniteField<Prime, Exponent>{
                (x_to( 34,0 ) + x_to( 17, 1 )).evaluate<PolynomialOverPrimeSizeFiniteField<Prime,1>>()
            },
            ElementOfFiniteField<Prime, Exponent>{
                (x_to( 2,0 ) + x_to( 63, 1 )).evaluate<PolynomialOverPrimeSizeFiniteField<Prime,1>>()
            }
        },
        std::array<ElementOfFiniteField<Prime, Exponent>, n>
        {
            ElementOfFiniteField<Prime, Exponent>{
                (x_to( 2,0 ) + x_to( 3, 1 )).evaluate<PolynomialOverPrimeSizeFiniteField<Prime,1>>()
            },
            ElementOfFiniteField<Prime, Exponent>{
                (x_to( 5,0 ) + x_to( 7, 1 )).evaluate<PolynomialOverPrimeSizeFiniteField<Prime,1>>()
            },
            ElementOfFiniteField<Prime, Exponent>{
                (x_to( 11,0 ) + x_to( 13, 1 )).evaluate<PolynomialOverPrimeSizeFiniteField<Prime,1>>()
            },
            ElementOfFiniteField<Prime, Exponent>{
                (x_to( 17,0 ) + x_to( 19, 1 )).evaluate<PolynomialOverPrimeSizeFiniteField<Prime,1>>()
            }
        },
        std::array<ElementOfFiniteField<Prime, Exponent>, n>
        {
            ElementOfFiniteField<Prime, Exponent>{
                (x_to( 11,0 ) + x_to( 13, 1 )).evaluate<PolynomialOverPrimeSizeFiniteField<Prime,1>>()
            },
            ElementOfFiniteField<Prime, Exponent>{
                (x_to( 17,0 ) + x_to( 19, 1 )).evaluate<PolynomialOverPrimeSizeFiniteField<Prime,1>>()
            },
            ElementOfFiniteField<Prime, Exponent>{
                (x_to( 23,0 ) + x_to( 29, 1 )).evaluate<PolynomialOverPrimeSizeFiniteField<Prime,1>>()
            },
            ElementOfFiniteField<Prime, Exponent>{
                (x_to( 31,0 ) + x_to( 37, 1 )).evaluate<PolynomialOverPrimeSizeFiniteField<Prime,1>>()
            }
        },
        std::array<ElementOfFiniteField<Prime, Exponent>, n>
        {
            ElementOfFiniteField<Prime, Exponent>{
                (x_to( 23,0 ) + x_to( 29, 1 )).evaluate<PolynomialOverPrimeSizeFiniteField<Prime,1>>()
            },
            ElementOfFiniteField<Prime, Exponent>{
                (x_to( 31,0 ) + x_to( 37, 1 )).evaluate<PolynomialOverPrimeSizeFiniteField<Prime,1>>()
            },
            ElementOfFiniteField<Prime, Exponent>{
                (x_to( 2,0 ) + x_to( 18, 1 )).evaluate<PolynomialOverPrimeSizeFiniteField<Prime,1>>()
            },
            ElementOfFiniteField<Prime, Exponent>{
                (x_to( 42,0 ) + x_to( 87, 1 )).evaluate<PolynomialOverPrimeSizeFiniteField<Prime,1>>()
            }
        },
        std::array<ElementOfFiniteField<Prime, Exponent>, n>
        {
            ElementOfFiniteField<Prime, Exponent>{
                (x_to( 41,0 ) + x_to( 43, 1 )).evaluate<PolynomialOverPrimeSizeFiniteField<Prime,1>>()
            },
            ElementOfFiniteField<Prime, Exponent>{
                (x_to( 47,0 ) + x_to( 53, 1 )).evaluate<PolynomialOverPrimeSizeFiniteField<Prime,1>>()
            },
            ElementOfFiniteField<Prime, Exponent>{
                (x_to( 47,0 ) + x_to( 43, 1 )).evaluate<PolynomialOverPrimeSizeFiniteField<Prime,1>>()
            },
            ElementOfFiniteField<Prime, Exponent>{
                (x_to( 41,0 ) + x_to( 53, 1 )).evaluate<PolynomialOverPrimeSizeFiniteField<Prime,1>>()
            }
        }
	};
	
    std::vector<std::array<ElementOfFiniteField<Prime, Exponent>, n>> values_only{
        std::array<ElementOfFiniteField<Prime, Exponent>, n>
        {
            ElementOfFiniteField<Prime, Exponent>{
                (x_to( 0,0 ) + x_to( 0,1 )).evaluate<PolynomialOverPrimeSizeFiniteField<Prime,1>>()
            },
            ElementOfFiniteField<Prime, Exponent>{
                (x_to( 0,0 ) + x_to( 0,1 )).evaluate<PolynomialOverPrimeSizeFiniteField<Prime,1>>()
            },
            ElementOfFiniteField<Prime, Exponent>{
                (x_to( 0,0 ) + x_to( 0,1 )).evaluate<PolynomialOverPrimeSizeFiniteField<Prime,1>>()
            },
            ElementOfFiniteField<Prime, Exponent>{
                (x_to( 0,0 ) + x_to( 0,1 )).evaluate<PolynomialOverPrimeSizeFiniteField<Prime,1>>()
            }
        },
        std::array<ElementOfFiniteField<Prime, Exponent>, n>
        {
            ElementOfFiniteField<Prime, Exponent>{
                (x_to( 2,0 ) + x_to( 3,1 )).evaluate<PolynomialOverPrimeSizeFiniteField<Prime,1>>()
            },
            ElementOfFiniteField<Prime, Exponent>{
                (x_to( 4,0 ) + x_to( 6,1 )).evaluate<PolynomialOverPrimeSizeFiniteField<Prime,1>>()
            },
            ElementOfFiniteField<Prime, Exponent>{
                (x_to( 1,0 ) + x_to( 1,1 )).evaluate<PolynomialOverPrimeSizeFiniteField<Prime,1>>()
            },
            ElementOfFiniteField<Prime, Exponent>{
                (x_to( 1,0 ) + x_to( 1,1 )).evaluate<PolynomialOverPrimeSizeFiniteField<Prime,1>>()
            }
        }
    };
}

TEST( LagrangeInterpolationTests, DataIsValid )
{
    for( const auto& group : basis_or_values )
    {
        EXPECT_TRUE( array_is_all_mutually_distinct( group ) );
    }
    EXPECT_THAT( basis_or_values, ::testing::Not( ::testing::IsEmpty() ) );
    EXPECT_THAT( values_only, ::testing::Not( ::testing::IsEmpty() ) );
}

TEST( LagrangeInterpolationTests, BasisIsSetUpCorrectly )
{
    for( const auto& basis : basis_or_values )
    {
        const auto legrage_basis{ LagrangeInterpolation<n, ElementOfFiniteField<Prime,Exponent>>::CreateLegrangeBasis( basis ) };

        for( std::size_t basis_index{ 0 }; basis_index < basis.size(); basis_index++ )
        {
            for( const auto& other_basis_element : basis )
            {
                if( other_basis_element != basis.at( basis_index ) )
                {
                    EXPECT_TRUE( legrage_basis.at( basis_index )( other_basis_element ).IsZero() );
                }
                else
                {
                    EXPECT_TRUE( legrage_basis.at( basis_index )( other_basis_element ).IsOne() );
                }
            }
        }
    }
}

TEST( LagrangeInterpolationTests, LegrangeInterpolationWorks )
{
    for( const auto& basis : basis_or_values )
    {
        LagrangeInterpolation<n, ElementOfFiniteField<Prime,Exponent>> interpolator{ basis };

        for( const auto& values : basis_or_values )
        {
            const auto l_i_res{ interpolator.Interpolate( values ) };

            for( std::size_t basis_index{ 0 }; basis_index < basis.size(); basis_index++ )
            {
                EXPECT_EQ( l_i_res( basis.at( basis_index ) ), values.at( basis_index ) );
            }
        }

        for( const auto& values : values_only )
        {
            const auto l_i_res{ interpolator.Interpolate( values ) };

            for( std::size_t basis_index{ 0 }; basis_index < basis.size(); basis_index++ )
            {
                EXPECT_EQ( l_i_res( basis.at( basis_index ) ), values.at( basis_index ) );
            }
        }
    }
}

