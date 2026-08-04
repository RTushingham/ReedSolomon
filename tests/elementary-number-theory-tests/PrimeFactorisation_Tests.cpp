#include "elementary-number-theory/PrimeFactorisation.h"

#include "gmock/gmock.h"
#include "gtest/gtest.h"

#include <vector>

namespace
{
	struct TestData{
		unsigned input{};
		PrimeFactorAndWeight expected{};
	};

	const std::vector<TestData> test_data{
		{  2, {  2, 1 } },
		{  3, {  3, 1 } },
		{  4, {  2, 2 } },
		{  5, {  5, 1 } },
		{  7, {  7, 1 } },
		{  8, {  2, 3 } },
		{  9, {  3, 2 } },
		{ 11, { 11, 1 } },
		{ 13, { 13, 1 } },
		{ 16, {  2, 4 } },
		{ 17, { 17, 1 } },
		{ 19, { 19, 1 } },
		{ 23, { 23, 1 } },
		{ 25, {  5, 2 } },
		{ 27, {  3, 3 } },
		{ 29, { 29, 1 } },
		{ 31, { 31, 1 } },
		{ 32, {  2, 5 } },
		{ 37, { 37, 1 } },
		{ 41, { 41, 1 } },
		{ 43, { 43, 1 } },
		{ 47, { 47, 1 } },
		{ 49, {  7, 2 } },
		{ 53, { 53, 1 } },
		{ 59, { 59, 1 } },
		{ 61, { 61, 1 } },
		{ 64, {  2, 6 } }
	};
}

TEST( PrimeFactorisation, WorksForAllNumbersWithOnePrimeFactor )
{
	EXPECT_THAT( test_data, ::testing::Not( ::testing::IsEmpty() ) );
	for( const auto& entry : test_data )
	{
		EXPECT_THAT( entry, ::testing::Field( &TestData::input,
			::testing::ResultOf( PrimeFactorisation_SingleFactor,
				::testing::AllOf( 
					::testing::Field( &PrimeFactorAndWeight::PrimeFactor, entry.expected.PrimeFactor ),
					::testing::Field( &PrimeFactorAndWeight::Weight, entry.expected.Weight )
				)
			)
		) );
	}
}

TEST( PrimeFactorisation, IsConstexpr )
{
	constexpr auto result{ PrimeFactorisation_SingleFactor( 8 ) };

	EXPECT_EQ( result.PrimeFactor, 2 );
	EXPECT_EQ( result.Weight, 3 );
}

