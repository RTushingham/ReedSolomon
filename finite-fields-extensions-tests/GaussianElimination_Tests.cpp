#include "finite-fields-extensions/GaussianElimination.h"

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
			std::array<ElementOfFiniteFieldP<Prime>,PolynomialOverPrimeSizeFiniteField<Prime,1>::GetCapacity()>{
				ElementOfFiniteFieldP<Prime>{ 9 },
				ElementOfFiniteFieldP<Prime>{ 8 }
			} 
		},
		irriducible
	};
	const ElementOfFiniteField<Prime, Exponent> b{
		PolynomialOverPrimeSizeFiniteField<Prime,1>{
			std::array<ElementOfFiniteFieldP<Prime>,PolynomialOverPrimeSizeFiniteField<Prime,1>::GetCapacity()>{
				ElementOfFiniteFieldP<Prime>{ 62 },
				ElementOfFiniteFieldP<Prime>{ 14 }
			} 
		},
		irriducible
	};
}


TEST( GaussianEliminationTests, TrivialExample )
{
    ClassUnderTest matrix{ ElementOfFiniteField<Prime,Exponent>::GetAdditionInvarient( irriducible ) };

    std::array<std::size_t, matrix.RowCount()> expected{};
    for( std::size_t column_index{ 0 }; column_index<matrix.RowCount(); column_index++ )
    {
        matrix.Row( column_index ).at( column_index ) = a;
        expected.at( column_index ) = column_index;
    }
    
    const auto res{ GaussianElimination( matrix, ElementOfFiniteField<Prime,Exponent>::GetAdditionInvarient( irriducible ) ) };
    
    EXPECT_THAT( res, ::testing::ContainerEq( expected ) );
}
