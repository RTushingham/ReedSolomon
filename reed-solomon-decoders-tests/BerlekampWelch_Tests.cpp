#include "reed-solomon-decoders/BerlekampWelch.h"

#include "reed-solomon-codes/Code.h"
#include "reed-solomon-codes/Codeword.h"
#include "reed-solomon-codes/PolynomialsOverFiniteFieldOfSizePrimeToAPower.h"

#include "gmock/gmock.h"
#include "gtest/gtest.h"

constexpr integer Prime{ 101 };
constexpr integer Exponent{ 2 };
constexpr std::size_t n{ 4 };
constexpr std::size_t k{ 2 };

namespace
{
	const std::array<ElementOfFiniteField<Prime, Exponent>,k> initializer{
		ElementOfFiniteField<Prime, Exponent>{
			PolynomialOverPrimeSizeFiniteField<Prime,1>{ 
				std::array<ElementOfFiniteFieldP<Prime>,PolynomialOverPrimeSizeFiniteField<Prime,1>::GetCapacity()>{
					ElementOfFiniteFieldP<Prime>{ 4 },
					ElementOfFiniteFieldP<Prime>{ 5 }
				} 
			}
		},
		ElementOfFiniteField<Prime, Exponent>{
			PolynomialOverPrimeSizeFiniteField<Prime,1>{
				std::array<ElementOfFiniteFieldP<Prime>,PolynomialOverPrimeSizeFiniteField<Prime,1>::GetCapacity()>{
					ElementOfFiniteFieldP<Prime>{ 7 },
					ElementOfFiniteFieldP<Prime>{ 6 }
				} 
			}
		}
	};

	PolynomialOverFiniteField<Prime,Exponent,k-1> polynomial{ 
		initializer 
	};
	

	const ElementOfFiniteField<Prime, Exponent> argument_one{
		PolynomialOverPrimeSizeFiniteField<Prime,1>{
			std::array<ElementOfFiniteFieldP<Prime>,PolynomialOverPrimeSizeFiniteField<Prime,1>::GetCapacity()>{
				ElementOfFiniteFieldP<Prime>{ 9 },
				ElementOfFiniteFieldP<Prime>{ 8 }
			} 
		}
	};

	const ElementOfFiniteField<Prime, Exponent> argument_two{
		PolynomialOverPrimeSizeFiniteField<Prime,1>{
			std::array<ElementOfFiniteFieldP<Prime>,PolynomialOverPrimeSizeFiniteField<Prime,1>::GetCapacity()>{
				ElementOfFiniteFieldP<Prime>{ 10 },
				ElementOfFiniteFieldP<Prime>{ 11 }
			} 
		}
	};

	const ElementOfFiniteField<Prime, Exponent> argument_three{
		PolynomialOverPrimeSizeFiniteField<Prime,1>{
			std::array<ElementOfFiniteFieldP<Prime>,PolynomialOverPrimeSizeFiniteField<Prime,1>::GetCapacity()>{
				ElementOfFiniteFieldP<Prime>{ 12 },
				ElementOfFiniteFieldP<Prime>{ 13 }
			} 
		}
	};

	const ElementOfFiniteField<Prime, Exponent> argument_four{
		PolynomialOverPrimeSizeFiniteField<Prime,1>{
			std::array<ElementOfFiniteFieldP<Prime>,PolynomialOverPrimeSizeFiniteField<Prime,1>::GetCapacity()>{
				ElementOfFiniteFieldP<Prime>{ 14 },
				ElementOfFiniteFieldP<Prime>{ 15 }
			} 
		}
	};

	Code<n, k, Prime, Exponent> code{ std::array<ElementOfFiniteField<Prime, Exponent>,n>{ argument_one, argument_two, argument_three, argument_four } };
	const BerklekampWelchDecoder<n, k, Prime, Exponent> decoder{ code };
	
	const std::array<ElementOfFiniteField<Prime, Exponent>,n>& generators{ code.generating_elements };
	constexpr std::size_t e = code.parameters.e;
}

TEST( BerlekampWelchTests, NoErrorCase )
{
	const auto signal{ code.GenerateCodeword( polynomial ) };

	EXPECT_EQ( signal, decoder.Decode( signal ) );
}

TEST( BerlekampWelchTests, OneErrorCase )
{
	EXPECT_TRUE( code.parameters.e >= 1 );

	auto signal{ code.GenerateCodeword( polynomial ) };
	
	const auto zero{ ElementOfFiniteField<Prime, Exponent>::GetAdditionInvarient() };
	ASSERT_NE( signal.blocks.at( 0 ), zero );
	signal.blocks.at( 0 ) = zero;

	EXPECT_EQ( code.GenerateCodeword( polynomial ), decoder.Decode( signal ) );
}

TEST( BerlekampWelchTests, UnrecoverableSituation )
{
	EXPECT_TRUE( code.parameters.e < 2 );

	auto signal{ code.GenerateCodeword( polynomial ) };
	
	const auto zero{ ElementOfFiniteField<Prime, Exponent>::GetAdditionInvarient() };
	ASSERT_NE( signal.blocks.at( 0 ), zero );
	ASSERT_NE( signal.blocks.at( 1 ), zero );
	signal.blocks.at( 0 ) = zero;
	signal.blocks.at( 1 ) = zero;

	EXPECT_NE( code.GenerateCodeword( polynomial ), decoder.Decode( signal ) );
}

/// Internals

TEST( BerlekampWelchInternalsTests, Example )
{
    ElementaryMatrix<n, n+1, ElementOfFiniteField<Prime,Exponent>> matrix{ ElementOfFiniteField<Prime,Exponent>::GetAdditionInvarient() };

	Codeword<n, k, Prime, Exponent> signals{
		std::array<ElementOfFiniteField<Prime, Exponent>,n>{ 
			polynomial( generators.at( 0 ) ),
			polynomial( generators.at( 1 ) ),
			polynomial( generators.at( 2 ) ),
			polynomial( generators.at( 0 ) )
		}
	};
	
	decoder.SetMatrixWithStartParameters( matrix, e, signals );

    const auto res{ GaussianElimination( matrix ) };

	EXPECT_FALSE( array_contains( res, (std::size_t)-1 ) ) << "This system is solvabled";
	EXPECT_EQ( true, decoder.SSEHasAtLeastOneSolution( matrix, res ) );
	EXPECT_EQ( true, decoder.SSEHasFiniteNumberOfSolutions( matrix, e, res ) );
}

TEST( BerlekampWelchInternalsTests, NoErrorExample )
{
	ElementaryMatrix<n, n+1, ElementOfFiniteField<Prime,Exponent>> matrix{ ElementOfFiniteField<Prime,Exponent>::GetAdditionInvarient() };
	
	Codeword<n, k, Prime, Exponent> signals{
		std::array<ElementOfFiniteField<Prime, Exponent>,n>{ 
			polynomial( generators.at( 0 ) ),
			polynomial( generators.at( 1 ) ),
			polynomial( generators.at( 2 ) ),
			polynomial( generators.at( 3 ) )
		}
	};
	
	decoder.SetMatrixWithStartParameters( matrix, e, signals );
	
    const auto res{ GaussianElimination( matrix ) };
	
	EXPECT_TRUE( array_contains( res, (std::size_t)-1 ) ) << "This system is not solvable";
	EXPECT_EQ( true, decoder.SSEHasAtLeastOneSolution( matrix, res ) );
	EXPECT_EQ( false, decoder.SSEHasFiniteNumberOfSolutions( matrix, e, res ) );
}

TEST( BerlekampWelchInternalsTests, ExampleWhereHadToShrinkPolynomialSize )
{
    ElementaryMatrix<n, n+1, ElementOfFiniteField<Prime,Exponent>> matrix{ ElementOfFiniteField<Prime,Exponent>::GetAdditionInvarient() };

	Codeword<n, k, Prime, Exponent> signals{
		std::array<ElementOfFiniteField<Prime, Exponent>,n>{ 
			polynomial( generators.at( 0 ) ),
			polynomial( generators.at( 1 ) ),
			polynomial( generators.at( 2 ) ),
			polynomial( generators.at( 3 ) )
		}
	};
	decoder.SetMatrixWithStartParameters( matrix, 0, signals );

    const auto res{ GaussianElimination( matrix ) };

	constexpr std::size_t MaxDegree = 1;

	EXPECT_NE( res.at( 0 ), (std::size_t)-1 );
	EXPECT_NE( res.at( MaxDegree ), (std::size_t)-1 );
	EXPECT_EQ( res.at( 2 ), (std::size_t)-1 );
	EXPECT_EQ( res.at( 3 ), (std::size_t)-1 );
	
	const auto zero{ ElementOfFiniteField<Prime,Exponent>::GetAdditionInvarient() };
	EXPECT_EQ( matrix.Row( 2 ).at( 4 ), zero );
	EXPECT_EQ( matrix.Row( 3 ).at( 4 ), zero );
	
	EXPECT_EQ( true, decoder.SSEHasAtLeastOneSolution( matrix, res ) );
	EXPECT_EQ( true, decoder.SSEHasFiniteNumberOfSolutions( matrix, 0, res ) );

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

	auto polys{ decoder.GetPolynomialsFromMatrix( matrix, 0, res ) };
 
	EXPECT_EQ( polys.generator.coefficients.at( 0 ), Q_zero );
	EXPECT_EQ( polys.generator.coefficients.at( 1 ), Q_one );

	auto longDivisionRes{ polys.generator.LongDivideBy( polys.error_polynomial ) };

	const auto poly_zero{ PolynomialOverFiniteField<Prime,Exponent,0>::GetAdditionInvarient() };
	EXPECT_EQ( longDivisionRes.remainder, poly_zero );
}
