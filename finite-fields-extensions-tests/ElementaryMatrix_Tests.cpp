#include "finite-fields-extensions/ElementaryMatrix.h"

#include "finite-fields/FiniteFieldsOfSizePrimeToAPower.h"
#include "finite-fields-tests/test-data/IrriduciblePolynomial.h"

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

TEST( ElementaryMatrixTests, RowCount )
{
    const auto zero{ ElementOfFiniteField<Prime,Exponent>::GetAdditionInvarient() };
    ClassUnderTest matrix{ zero };

    EXPECT_EQ( matrix.RowCount(), n );
}

TEST( ElementaryMatrixTests, ColumnCount )
{
    const auto zero{ ElementOfFiniteField<Prime,Exponent>::GetAdditionInvarient() };
    ClassUnderTest matrix{ zero };

    EXPECT_EQ( matrix.ColumnCount(), n+1 );
}

TEST( ElementaryMatrixTests, DefaultInitializable )
{
    const auto zero{ ElementOfFiniteField<Prime,Exponent>::GetAdditionInvarient() };
    ClassUnderTest matrix{ zero };

    for( std::size_t row_index{ 0 }; row_index<n; row_index++ )
    {
        const auto& row{ matrix.Row( row_index ) };
        for( const auto& coeff : row )
        {
            EXPECT_EQ( coeff, zero );
        }
    }
}

TEST( ElementaryMatrixTests, CoefficientOverwriting )
{
    ClassUnderTest matrix{ ElementOfFiniteField<Prime,Exponent>::GetAdditionInvarient() };

    matrix.Row( 0 ).at( 0 ) = a;
    matrix.Row( 0 ).at( 1 ) = a;

    matrix.Row( 1 ).at( 0 ) = a;
    matrix.Row( 1 ).at( 1 ) = b;
    
    
    EXPECT_EQ( matrix.Row( 0 ).at( 0 ), a );
    EXPECT_EQ( matrix.Row( 0 ).at( 1 ), a );

    EXPECT_EQ( matrix.Row( 1 ).at( 0 ), a );
    EXPECT_EQ( matrix.Row( 1 ).at( 1 ), b );
}


TEST( ElementaryMatrixTests, RowSubtraction )
{
    ClassUnderTest matrix{ ElementOfFiniteField<Prime,Exponent>::GetAdditionInvarient() };

    matrix.Row( 0 ).at( 0 ) = a;
    matrix.Row( 0 ).at( 1 ) = a;

    matrix.Row( 1 ).at( 0 ) = a;
    matrix.Row( 1 ).at( 1 ) = b;


    matrix.SubtractRowByRow( 1, ElementOfFiniteField<Prime,Exponent>::GetMultiplicativeInvarient(), 0 );


    EXPECT_EQ( matrix.Row( 0 ).at( 0 ), a );
    EXPECT_EQ( matrix.Row( 0 ).at( 1 ), a );

    EXPECT_TRUE( matrix.Row( 1 ).at( 0 ).IsZero() );
    EXPECT_EQ( matrix.Row( 1 ).at( 1 ), b-a );
}

TEST( ElementaryMatrixTests, RowSubtractionUsingScalar )
{
    ClassUnderTest matrix{ ElementOfFiniteField<Prime,Exponent>::GetAdditionInvarient() };

    const auto one{ ElementOfFiniteField<Prime,Exponent>::GetMultiplicativeInvarient() };
    matrix.Row( 0 ).at( 0 ) = one;
    matrix.Row( 0 ).at( 1 ) = a;

    matrix.Row( 1 ).at( 0 ) = a;
    matrix.Row( 1 ).at( 1 ) = b;


    matrix.SubtractRowByRow( 1, a, 0 );


    EXPECT_EQ( matrix.Row( 0 ).at( 0 ), one );
    EXPECT_EQ( matrix.Row( 0 ).at( 1 ), a );

    EXPECT_TRUE( matrix.Row( 1 ).at( 0 ).IsZero() );
    EXPECT_TRUE( matrix.Row( 1 ).at( 0 ).IsZero() );
    EXPECT_EQ( matrix.Row( 1 ).at( 1 ), b-(a*a) );
}

