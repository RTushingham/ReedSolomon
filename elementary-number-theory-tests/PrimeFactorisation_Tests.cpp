#include "elementary-number-theory/PrimeFactorisation.h"

#include "gtest/gtest.h"

#include <array>

TEST( PrimeFactorisation, WorksForAllNumbersWithOnePrimeFactor )
{
	const std::array Inputs			{ 2, 3, 4, 5, 7, 8, 9, 11, 13, 16, 17, 19, 23, 25, 27, 29, 31, 32, 37, 41, 43, 47, 49, 53, 59, 61, 64 };
	const std::array PrimeFactors	{ 2, 3, 2, 5, 7, 2, 3, 11, 13,  2, 17, 19, 23,  5,  3, 29, 31,  2, 37, 41, 43, 47,  7, 53, 59, 61,  2 };
	const std::array Weights		{ 1, 1, 2, 1, 1, 3, 2,  1,  1,  4,  1,  1,  1,  2,  3,  1,  1,  5,  1,  1,  1,  1,  2,  1,  1,  1,  6 };

	for( std::size_t index; index<Inputs.size(); index++ )
	{
		const PrimeFactorAndWeight expected{ (unsigned)PrimeFactors.at(index), (unsigned)Weights.at(index) };
		const auto result{ PrimeFactorisation_SingleFactor( (unsigned)Inputs.at(index) ) };
		EXPECT_EQ( result.PrimeFactor, expected.PrimeFactor );
		EXPECT_EQ( result.Weight, expected.Weight );
	}
}
