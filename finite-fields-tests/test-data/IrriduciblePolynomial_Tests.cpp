#include "IrriduciblePolynomial.h"

#include "gtest/gtest.h"

#include <algorithm>
#include <vector>

namespace
{
	constexpr integer Prime{ 101 };
}

TEST( TestDataVerifictaion, IsIrriducible )
{
	std::array<ElementOfFiniteFieldP<Prime>,Prime> squares;

	for( std::size_t index=0; index<Prime; index++ )
	{
		squares[index] = ElementOfFiniteFieldP<Prime>{ (integer)index } * ElementOfFiniteFieldP<Prime>{ (integer)index };
	}

	std::vector<ElementOfFiniteFieldP<Prime>> nonSquares;
	for( unsigned index=0; index<Prime; index++ )
	{
		if( squares.end() == std::find( squares.begin(), squares.end(), ElementOfFiniteFieldP<Prime>( index ) ) )
		{
			nonSquares.push_back( ElementOfFiniteFieldP<Prime>( index ) );
		}
	}

	std::vector<ElementOfFiniteFieldP<Prime>> expected{ 2,3,7,8,10,11,12,15,18,26,27,28,29,32,34,35,38,39,40,41,42,44,46,48,50,51,53,55,57,59,60,61,62,63,66,67,69,72,73,74,75,83,86,89,90,91,93,94,98,99 };
	EXPECT_EQ( nonSquares, expected );

	std::vector<PolynomialOverPrimeSizeFiniteField<Prime,2>> irriducibles;
	for( const auto nonSquare : nonSquares )
	{
		irriducibles.push_back(
			PolynomialOverPrimeSizeFiniteField<Prime,2>{
				std::array<ElementOfFiniteFieldP<Prime>,PolynomialOverPrimeSizeFiniteField<Prime,2>::GetCapacity()>{
					ElementOfFiniteFieldP<Prime>{ -nonSquare.value },
					ElementOfFiniteFieldP<Prime>{ 0 },
					ElementOfFiniteFieldP<Prime>{ 1 }
				} 
			}
		);
	}

	for( std::size_t index=0; index<Prime; index++ )
	{
		const PolynomialOverPrimeSizeFiniteField<Prime,1> normalised_poly{
			std::array<ElementOfFiniteFieldP<Prime>,PolynomialOverPrimeSizeFiniteField<Prime,1>::GetCapacity()>{
				ElementOfFiniteFieldP<Prime>{ (integer)index },
				ElementOfFiniteFieldP<Prime>{ 1 }
			} 
		};

		for( const auto i : irriducibles )
		{
			EXPECT_FALSE(
				i.LongDivideBy( normalised_poly ).remainder.IsZero()
			) << "polynomial of the form X^2 - " << Prime - i.Coeff(0).value << " is not irriducible. This contradicts Lang [1984, p. 331, Theorem 9.1]." ;
		}
	}

	const bool irriducibles_contains_test_poly{ irriducibles.end() != std::find( irriducibles.begin(), irriducibles.end(), irriducible ) };
	EXPECT_TRUE( irriducibles_contains_test_poly );
}
