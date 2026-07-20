#include "finite-fields-extensions-tmp/tmp_LagrangeInterpolation.h"

#include "container-helpers/ArrayExtensions.h"
#include "tests/finite-fields-tests/helpers/InitializerHelper.h"

#include "gmock/gmock.h"
#include "gtest/gtest.h"

#include <vector>

namespace
{
    constexpr integer Exponent{ 8 };
    constexpr std::size_t n{ 4 };
    constexpr std::size_t k{ 2 };

    std::vector<std::array<ElementOfFiniteField<2, Exponent>, n>> basis_or_values
    { 
        std::array<ElementOfFiniteField<2, Exponent>, n>
        {
            ElementOfFiniteField<2, Exponent>{
                ( x_to( 1,0 ) + x_to( 1,1 ) ).evaluate<PolynomialOverPrimeSizeFiniteField<2,Exponent-1>>()
            },
            ElementOfFiniteField<2, Exponent>{
                ( x_to( 1,1 ) + x_to( 1,2 ) ).evaluate<PolynomialOverPrimeSizeFiniteField<2,Exponent-1>>()
            },
            ElementOfFiniteField<2, Exponent>{
                ( x_to( 1,2 ) + x_to( 1,3 ) ).evaluate<PolynomialOverPrimeSizeFiniteField<2,Exponent-1>>()
            },
            ElementOfFiniteField<2, Exponent>{
                ( x_to( 1,3 ) + x_to( 1,4 ) ).evaluate<PolynomialOverPrimeSizeFiniteField<2,Exponent-1>>()
            }
        },
        std::array<ElementOfFiniteField<2, Exponent>, n>
        {
            ElementOfFiniteField<2, Exponent>{
                ( x_to( 1,0 ) + x_to( 1,2 ) ).evaluate<PolynomialOverPrimeSizeFiniteField<2,Exponent-1>>()
            },
            ElementOfFiniteField<2, Exponent>{
                ( x_to( 1,1 ) + x_to( 1,4 ) ).evaluate<PolynomialOverPrimeSizeFiniteField<2,Exponent-1>>()
            },
            ElementOfFiniteField<2, Exponent>{
                ( x_to( 1,2 ) + x_to( 1,6 ) ).evaluate<PolynomialOverPrimeSizeFiniteField<2,Exponent-1>>()
            },
            ElementOfFiniteField<2, Exponent>{
                ( x_to( 1,3 ) + x_to( 1,0 ) ).evaluate<PolynomialOverPrimeSizeFiniteField<2,Exponent-1>>()
            }
        },
        std::array<ElementOfFiniteField<2, Exponent>, n>
        {
            ElementOfFiniteField<2, Exponent>{
                ( x_to( 1,2 ) + x_to( 1,3 ) ).evaluate<PolynomialOverPrimeSizeFiniteField<2,Exponent-1>>()
            },
            ElementOfFiniteField<2, Exponent>{
                ( x_to( 1,5 ) + x_to( 1,7 ) ).evaluate<PolynomialOverPrimeSizeFiniteField<2,Exponent-1>>()
            },
            ElementOfFiniteField<2, Exponent>{
                ( x_to( 1,3 ) + x_to( 1,5 ) ).evaluate<PolynomialOverPrimeSizeFiniteField<2,Exponent-1>>()
            },
            ElementOfFiniteField<2, Exponent>{
                ( x_to( 1,1 ) + x_to( 1,3 ) ).evaluate<PolynomialOverPrimeSizeFiniteField<2,Exponent-1>>()
            }
        }
	};
	
    std::vector<std::array<ElementOfFiniteField<2, Exponent>, n>> values_only{
        std::array<ElementOfFiniteField<2, Exponent>, n>
        {
            ElementOfFiniteField<2, Exponent>{
                ( x_to( 0,0 ) + x_to( 0,1 ) ).evaluate<PolynomialOverPrimeSizeFiniteField<2,Exponent-1>>()
            },
            ElementOfFiniteField<2, Exponent>{
                ( x_to( 0,0 ) + x_to( 0,1 ) ).evaluate<PolynomialOverPrimeSizeFiniteField<2,Exponent-1>>()
            },
            ElementOfFiniteField<2, Exponent>{
                ( x_to( 0,0 ) + x_to( 0,1 ) ).evaluate<PolynomialOverPrimeSizeFiniteField<2,Exponent-1>>()
            },
            ElementOfFiniteField<2, Exponent>{
                ( x_to( 0,0 ) + x_to( 0,1 ) ).evaluate<PolynomialOverPrimeSizeFiniteField<2,Exponent-1>>()
            }
        }
    };
}

TEST( tmp_LagrangeInterpolationTests, DataIsValid )
{
    for( const auto& group : basis_or_values )
    {
        EXPECT_TRUE( array_is_all_mutually_distinct( group ) );
    }
    EXPECT_THAT( basis_or_values, ::testing::Not( ::testing::IsEmpty() ) );
    EXPECT_THAT( values_only, ::testing::Not( ::testing::IsEmpty() ) );
}

TEST( tmp_LagrangeInterpolationTests, BasisIsSetUpCorrectly )
{
    for( const auto& basis : basis_or_values )
    {
        const auto legrage_basis{ tmp_LagrangeInterpolation<n, Exponent>::CreateLegrangeBasis( basis ) };

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

TEST( tmp_LagrangeInterpolationTests, LegrangeInterpolationWorks )
{
    for( const auto& basis : basis_or_values )
    {
        tmp_LagrangeInterpolation<n, Exponent> interpolator{ basis };

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

