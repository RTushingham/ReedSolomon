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

TEST( GaussianEliminationTests, ReorderedExample )
{
    ClassUnderTest matrix{ ElementOfFiniteField<Prime,Exponent>::GetAdditionInvarient( irriducible ) };

    std::array<std::size_t, matrix.RowCount()> expected{};
    expected.at( 0 ) = 2;
    expected.at( 1 ) = 0;
    expected.at( 2 ) = 1;
    expected.at( 3 ) = 3;

    for( std::size_t column_index{ 0 }; column_index<matrix.RowCount(); column_index++ )
    {
        matrix.Row( expected.at( column_index ) ).at( column_index ) = a;
    }
    
    const auto res{ GaussianElimination( matrix, ElementOfFiniteField<Prime,Exponent>::GetAdditionInvarient( irriducible ) ) };
    
    EXPECT_THAT( res, ::testing::ContainerEq( expected ) );
}

TEST( GaussianEliminationTests, ReorderedNonTrivialExample )
{
    ClassUnderTest matrix{ ElementOfFiniteField<Prime,Exponent>::GetAdditionInvarient( irriducible ) };

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
    

    const auto res{ GaussianElimination( matrix, ElementOfFiniteField<Prime,Exponent>::GetAdditionInvarient( irriducible ) ) };
    
    EXPECT_THAT( res, ::testing::ContainerEq( expected ) );

    const auto zero{ ElementOfFiniteField<Prime,Exponent>::GetAdditionInvarient( irriducible ) };
    EXPECT_EQ( matrix.Row( 0 ).at( matrix.ColumnCount()-1 ), zero );
}

#include "reed-solomon-codes/PolynomialsOverFiniteFieldOfSizePrimeToAPower.h"

#include <algorithm>

namespace
{
	constexpr integer MaxDegree = 1;

	const std::array<ElementOfFiniteField<Prime, Exponent>,MaxDegree+1> initializer{
		ElementOfFiniteField<Prime, Exponent>{
			PolynomialOverPrimeSizeFiniteField<Prime,1>{ 
				std::array<ElementOfFiniteFieldP<Prime>,PolynomialOverPrimeSizeFiniteField<Prime,1>::GetCapacity()>{
					ElementOfFiniteFieldP<Prime>{ 4 },
					ElementOfFiniteFieldP<Prime>{ 5 }
				} 
			},
			irriducible
		},
		ElementOfFiniteField<Prime, Exponent>{
			PolynomialOverPrimeSizeFiniteField<Prime,1>{
				std::array<ElementOfFiniteFieldP<Prime>,PolynomialOverPrimeSizeFiniteField<Prime,1>::GetCapacity()>{
					ElementOfFiniteFieldP<Prime>{ 7 },
					ElementOfFiniteFieldP<Prime>{ 6 }
				} 
			},
			irriducible
		}
	};

	PolynomialOverFiniteField<Prime,Exponent,MaxDegree> polynomial{ 
		initializer 
	};
	
	const ElementOfFiniteField<Prime, Exponent> argument_one{
		PolynomialOverPrimeSizeFiniteField<Prime,1>{
			std::array<ElementOfFiniteFieldP<Prime>,PolynomialOverPrimeSizeFiniteField<Prime,1>::GetCapacity()>{
				ElementOfFiniteFieldP<Prime>{ 9 },
				ElementOfFiniteFieldP<Prime>{ 8 }
			} 
		},
		irriducible
	};

	const ElementOfFiniteField<Prime, Exponent> argument_two{
		PolynomialOverPrimeSizeFiniteField<Prime,1>{
			std::array<ElementOfFiniteFieldP<Prime>,PolynomialOverPrimeSizeFiniteField<Prime,1>::GetCapacity()>{
				ElementOfFiniteFieldP<Prime>{ 10 },
				ElementOfFiniteFieldP<Prime>{ 11 }
			} 
		},
		irriducible
	};

	const ElementOfFiniteField<Prime, Exponent> argument_three{
		PolynomialOverPrimeSizeFiniteField<Prime,1>{
			std::array<ElementOfFiniteFieldP<Prime>,PolynomialOverPrimeSizeFiniteField<Prime,1>::GetCapacity()>{
				ElementOfFiniteFieldP<Prime>{ 12 },
				ElementOfFiniteFieldP<Prime>{ 13 }
			} 
		},
		irriducible
	};

	const ElementOfFiniteField<Prime, Exponent> argument_four{
		PolynomialOverPrimeSizeFiniteField<Prime,1>{
			std::array<ElementOfFiniteFieldP<Prime>,PolynomialOverPrimeSizeFiniteField<Prime,1>::GetCapacity()>{
				ElementOfFiniteFieldP<Prime>{ 14 },
				ElementOfFiniteFieldP<Prime>{ 15 }
			} 
		},
		irriducible
	};

	void SetMatrixWithStartParameters( ClassUnderTest& matrix, std::size_t assumed_error_value, std::size_t max_error_value, const std::vector<ElementOfFiniteField<Prime,Exponent>>& revieced_signal, const std::vector<ElementOfFiniteField<Prime,Exponent>>& generating_elements )
	{
		// layout = e0, e1, ..., e(e-1), q0, ..., q(e+k), "const"
		//   ->
		// layout = q0, ..., q(e+k), e0, ..., e(e-1), "const"

		//   In particular as e=0 in this case:
		// layout = q0, ..., q(k), 0, ..., 0, 0, ..., 0, "const"

		for( std::size_t row_index{ 0 }; row_index<matrix.RowCount(); row_index++ )
		{
			const auto& a{ generating_elements.at( row_index ) };
			auto& row{ matrix.Row( row_index ) };
			
			std::size_t coeff_count{ 0 };
			auto running_product{ ElementOfFiniteField<Prime,Exponent>::GetMultiplicativeInvarient( irriducible ) };
			while( coeff_count <= MaxDegree + assumed_error_value )
			{
				row.at( coeff_count ) = running_product;
				running_product = running_product * a;
				coeff_count++;
			}

			running_product = ElementOfFiniteField<Prime,Exponent>::GetAdditionInvarient( irriducible ) - ElementOfFiniteField<Prime,Exponent>::GetMultiplicativeInvarient( irriducible );
			running_product = running_product * revieced_signal.at( row_index );

			coeff_count = max_error_value+MaxDegree + 1;
			// so that const is at end
			coeff_count += max_error_value-assumed_error_value;
			while( coeff_count <= max_error_value+MaxDegree + max_error_value + 1 )
			{
				row.at( coeff_count ) = running_product;
				running_product = running_product * a;
				coeff_count++;
			}
		}
	}

	// allow matrix to be const?
	bool SSEHasAtLeastOneSolution( const std::array<std::size_t, n>& rows_for_leading_non_zeros, ClassUnderTest& matrix )
	{
		for( std::size_t row_index{ 0 }; row_index<rows_for_leading_non_zeros.size(); row_index++ )
		{
			if( false == array_contains( rows_for_leading_non_zeros, row_index ) )
			{
				// wrong - you check this for all of the things no in here...
				if( matrix.Row( row_index ).at( matrix.ColumnCount()-1 ) != ElementOfFiniteField<Prime,Exponent>::GetAdditionInvarient( irriducible ) )
				{
					// no possible solution
					return false;
				}
			}
		}

		return true;
	}

	bool SSEHasFiniteNumberOfSolutions( std::size_t assumed_error_value, std::size_t max_error_value, const std::array<std::size_t, n>& rows_for_leading_non_zeros, ClassUnderTest& matrix )
	{
		const auto all_zero_row_count{ std::count( rows_for_leading_non_zeros.begin(), rows_for_leading_non_zeros.end(), (std::size_t)-1 ) };

		return all_zero_row_count == 2*(max_error_value - assumed_error_value);
	}

    struct DecodeResult
    {
        PolynomialOverFiniteField<Prime, Exponent, MaxDegree + (n-MaxDegree)/2> generator{};
        PolynomialOverFiniteField<Prime, Exponent, (n-MaxDegree)/2> error_polynomial{};
    };

	DecodeResult GetPolynomialsFromMatrix( ClassUnderTest& matrix, std::size_t error_value, std::size_t max_error_value, const std::array<std::size_t, n>& res )
	{
		constexpr auto zero{ ElementOfFiniteField<Prime,Exponent>::GetAdditionInvarient( irriducible ) };

		DecodeResult result{};
		// layout = e0, e1, ..., e(e-1), q0, ..., q(e+k), "const"
		//   ->
		// layout = q0, ..., q(e+k), e0, ..., e(e-1), "const"

		//   In particular as e=0 in this case:
		// layout = q0, ..., q(k), 0, ..., 0, 0, ..., 0, "const"

		//   In the solved case for each row we have:
		// a*q0 + "const" = 0
		// c*q1 + "const" = 0
		//   ...

		// a*q0 + "const" = 0
		//   =>
		// q0 = (0-"const")/a

		std::size_t coeff_count{ 0 };
		while( coeff_count <= MaxDegree + error_value )
		{
			result.generator.coefficients.at( coeff_count ) = ( zero - matrix.Row( res.at(coeff_count) ).at( matrix.ColumnCount()-1 ) ) / matrix.Row( res.at(coeff_count) ).at( coeff_count );
			coeff_count++;
		}

		coeff_count = max_error_value+MaxDegree + 1;
		// so that const is at end
		coeff_count += max_error_value-error_value;
		std::size_t e_coeff_index{ 0 };
		while( coeff_count <= max_error_value+MaxDegree + max_error_value )
		{
			result.error_polynomial.coefficients.at( e_coeff_index ) = ( zero - matrix.Row( res.at(coeff_count) ).at( matrix.ColumnCount()-1 ) ) / matrix.Row( res.at(coeff_count) ).at( coeff_count );
			coeff_count++;
			e_coeff_index++;
		}
		result.error_polynomial.coefficients.at( e_coeff_index ) = ElementOfFiniteField<Prime,Exponent>::GetMultiplicativeInvarient( irriducible );

		return result;
	}
}

TEST( GaussianEliminationBerlekampWelchTests, Example )
{
    ClassUnderTest matrix{ ElementOfFiniteField<Prime,Exponent>::GetAdditionInvarient( irriducible ) };
	constexpr std::size_t e = 1;

	std::vector<ElementOfFiniteField<Prime, Exponent>> generators{};
	generators.push_back( argument_one );
	generators.push_back( argument_two );
	generators.push_back( argument_three );
	generators.push_back( argument_four );
	
	std::vector<ElementOfFiniteField<Prime, Exponent>> signals{};
	signals.push_back( polynomial( generators.at( 0 ) ) );
	signals.push_back( polynomial( generators.at( 1 ) ) );
	signals.push_back( polynomial( generators.at( 2 ) ) );
	signals.push_back( polynomial( generators.at( 0 ) ) );

	SetMatrixWithStartParameters( matrix, e, e, signals, generators );

    const auto res{ GaussianElimination( matrix, ElementOfFiniteField<Prime,Exponent>::GetAdditionInvarient( irriducible ) ) };

	EXPECT_FALSE( array_contains( res, (std::size_t)-1 ) ) << "This system is solvabled";
	EXPECT_EQ( true, SSEHasAtLeastOneSolution( res, matrix ) );
	EXPECT_EQ( true, SSEHasFiniteNumberOfSolutions( e, e, res, matrix ) );
}

TEST( GaussianEliminationBerlekampWelchTests, NoErrorExample )
{
    ClassUnderTest matrix{ ElementOfFiniteField<Prime,Exponent>::GetAdditionInvarient( irriducible ) };
	constexpr std::size_t e = 1;

	std::vector<ElementOfFiniteField<Prime, Exponent>> generators{};
	generators.push_back( argument_one );
	generators.push_back( argument_two );
	generators.push_back( argument_three );
	generators.push_back( argument_four );
	
	std::vector<ElementOfFiniteField<Prime, Exponent>> signals{};
	signals.push_back( polynomial( generators.at( 0 ) ) );
	signals.push_back( polynomial( generators.at( 1 ) ) );
	signals.push_back( polynomial( generators.at( 2 ) ) );
	signals.push_back( polynomial( generators.at( 3 ) ) );

	SetMatrixWithStartParameters( matrix, e, e, signals, generators );

    const auto res{ GaussianElimination( matrix, ElementOfFiniteField<Prime,Exponent>::GetAdditionInvarient( irriducible ) ) };

	EXPECT_TRUE( array_contains( res, (std::size_t)-1 ) ) << "This system is not solvable";
	EXPECT_EQ( true, SSEHasAtLeastOneSolution( res, matrix ) );
	EXPECT_EQ( false, SSEHasFiniteNumberOfSolutions( e, e, res, matrix ) );
}

TEST( GaussianEliminationBerlekampWelchTests, ExampleWhereHadToShrinkPolynomialSize )
{
    ClassUnderTest matrix{ ElementOfFiniteField<Prime,Exponent>::GetAdditionInvarient( irriducible ) };
	constexpr std::size_t e = 1;

	std::vector<ElementOfFiniteField<Prime, Exponent>> generators{};
	generators.push_back( argument_one );
	generators.push_back( argument_two );
	generators.push_back( argument_three );
	generators.push_back( argument_four );
	
	std::vector<ElementOfFiniteField<Prime, Exponent>> signals{};
	signals.push_back( polynomial( generators.at( 0 ) ) );
	signals.push_back( polynomial( generators.at( 1 ) ) );
	signals.push_back( polynomial( generators.at( 2 ) ) );
	signals.push_back( polynomial( generators.at( 3 ) ) );

	SetMatrixWithStartParameters( matrix, 0, e, signals, generators );

	const auto zero{ ElementOfFiniteField<Prime,Exponent>::GetAdditionInvarient( irriducible ) };
    const auto res{ GaussianElimination( matrix, zero ) };

	EXPECT_NE( res.at( 0 ), (std::size_t)-1 );
	EXPECT_NE( res.at( MaxDegree ), (std::size_t)-1 );
	EXPECT_EQ( res.at( 2 ), (std::size_t)-1 );
	EXPECT_EQ( res.at( 3 ), (std::size_t)-1 );
	
	EXPECT_EQ( matrix.Row( 2 ).at( 4 ), zero );
	EXPECT_EQ( matrix.Row( 3 ).at( 4 ), zero );
	
	EXPECT_EQ( true, SSEHasAtLeastOneSolution( res, matrix ) );
	EXPECT_EQ( true, SSEHasFiniteNumberOfSolutions( 0, e, res, matrix ) );

	// a*q0 + b*e0 = 0
	// c*q1 + d*e0 = 0

	// e0 := 1
	//   => 
	// a*q0 + b = 0
	// c*q1 + d = 0

	// a*q0 + b = 0
	// q0 = (0-b)/a
	const auto Q_zero{ ( zero - matrix.Row( res.at(0) ).at( 4 ) ) / matrix.Row( res.at(0) ).at( 0 ) };
	const auto Q_one{ ( zero - matrix.Row( res.at(MaxDegree) ).at( 4 ) ) / matrix.Row( res.at(MaxDegree) ).at( MaxDegree ) };

	EXPECT_EQ( polynomial.coefficients.at( 0 ), Q_zero );
	EXPECT_EQ( polynomial.coefficients.at( 1 ), Q_one );

	auto polys{ GetPolynomialsFromMatrix( matrix, 0, e, res ) };
 
	EXPECT_EQ( polys.generator.coefficients.at( 0 ), Q_zero );
	EXPECT_EQ( polys.generator.coefficients.at( 1 ), Q_one );
}
