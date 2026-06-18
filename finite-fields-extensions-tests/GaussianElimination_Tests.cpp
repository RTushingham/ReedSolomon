#include "finite-fields-extensions/GaussianElimination.h"

#include "container-helpers/ArrayExtensions.h"
#include "finite-fields/FiniteFieldsOfSizePrimeToAPower.h"
#include "finite-fields-tests/test-data/IrriduciblePolynomial.h"

#include "gmock/gmock.h"
#include "gtest/gtest.h"

constexpr integer Prime{ 101 };
constexpr integer Exponent{ 2 };
constexpr std::size_t n{ 4 };

using ClassUnderTest = ElementaryMatrix<n, n+1, ElementOfFiniteField<Prime,Exponent>>;

namespace
{
	const ElementOfFiniteField<Prime, Exponent> a{
		PolynomialOverPrimeSizeFiniteField<Prime,1>{
			std::array<ElementOfFiniteFieldP<Prime>,PolynomialOverPrimeSizeFiniteField<Prime,1>::GetCoeffCount()>{
				ElementOfFiniteFieldP<Prime>{ 9 },
				ElementOfFiniteFieldP<Prime>{ 8 }
			} 
		}
	};
	const ElementOfFiniteField<Prime, Exponent> b{
		PolynomialOverPrimeSizeFiniteField<Prime,1>{
			std::array<ElementOfFiniteFieldP<Prime>,PolynomialOverPrimeSizeFiniteField<Prime,1>::GetCoeffCount()>{
				ElementOfFiniteFieldP<Prime>{ 62 },
				ElementOfFiniteFieldP<Prime>{ 14 }
			} 
		}
	};
}


TEST( GaussianEliminationTests, TrivialExample )
{
    ClassUnderTest matrix{ ElementOfFiniteField<Prime,Exponent>::GetAdditionInvarient() };

    std::array<std::size_t, matrix.RowCount()> expected{};
    for( std::size_t column_index{ 0 }; column_index<matrix.RowCount(); column_index++ )
    {
        matrix.Row( column_index ).at( column_index ) = a;
        expected.at( column_index ) = column_index;
    }
    
    const auto res{ GaussianElimination( matrix ) };
    
    EXPECT_THAT( res, ::testing::ContainerEq( expected ) );
}

TEST( GaussianEliminationTests, ReorderedExample )
{
    ClassUnderTest matrix{ ElementOfFiniteField<Prime,Exponent>::GetAdditionInvarient() };

    std::array<std::size_t, matrix.RowCount()> expected{};
    expected.at( 0 ) = 2;
    expected.at( 1 ) = 0;
    expected.at( 2 ) = 1;
    expected.at( 3 ) = 3;

    for( std::size_t column_index{ 0 }; column_index<matrix.RowCount(); column_index++ )
    {
        matrix.Row( expected.at( column_index ) ).at( column_index ) = a;
    }
    
    const auto res{ GaussianElimination( matrix ) };
    
    EXPECT_THAT( res, ::testing::ContainerEq( expected ) );
}

TEST( GaussianEliminationTests, ReorderedNonTrivialExample )
{
    ClassUnderTest matrix{ ElementOfFiniteField<Prime,Exponent>::GetAdditionInvarient() };

    std::array<std::size_t, matrix.RowCount()> expected{};
    expected.at( 0 ) = 2;
    expected.at( 1 ) = 0;
    expected.at( 2 ) = 1;
    expected.at( 3 ) = 3;

    for( std::size_t column_index{ 0 }; column_index<matrix.RowCount(); column_index++ )
    {
        matrix.Row( expected.at( column_index ) ).at( column_index ) = a;
    }
    for( std::size_t column_index{ 0 }; column_index<matrix.RowCount(); column_index++ )
    {
        matrix.Row( expected.at( column_index ) ).at( matrix.ColumnCount()-1 ) = b;
    }

    matrix.Row( 0 ).at( 1 ) = a;
    

    const auto res{ GaussianElimination( matrix ) };
    
    EXPECT_THAT( res, ::testing::ContainerEq( expected ) );

    EXPECT_TRUE( matrix.Row( 0 ).at( matrix.ColumnCount()-1 ).IsZero() );
}
