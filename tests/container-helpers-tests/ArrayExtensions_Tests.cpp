#include "container-helpers/ArrayExtensions.h"

#include "gtest/gtest.h"

// ArrayEqualsTests

TEST( ArrayEqualsTests, FunctionIsConstexpr )
{
	constexpr std::array<int, 3> a{ 0,1,2 };
	constexpr std::array<int, 3> b{ 0,1,3 };

	constexpr bool a_eq_b{ array_equals( a, b ) };
	EXPECT_EQ( false, a_eq_b );
}

TEST( ArrayEqualsTests, ValuesAreCorrect )
{
	constexpr std::array<int, 3> a{ 0,1,2 };
	constexpr std::array<int, 3> b{ 0,1,3 };

	EXPECT_EQ( false, array_equals( a, b ) );
	EXPECT_EQ( true, array_equals( a, a ) );
	EXPECT_EQ( true, array_equals( b, b ) );
}

#include "finite-fields/FiniteFieldsOfSizePrime.h"

TEST( ArrayEqualsTests, PrimeFieldIsConstexpr )
{
	constexpr std::array<ElementOfFiniteFieldP<101>, 3> a{};
	constexpr std::array<ElementOfFiniteFieldP<101>, 3> b{};

	constexpr bool a_eq_b{ array_equals( a, b ) };
	EXPECT_EQ( true, a_eq_b );
}

TEST( ArrayEqualsTests, SizeTwoPrimeFieldIsConstexpr )
{
	constexpr std::array<ElementOfFiniteFieldP<2>, 3> a{};
	constexpr std::array<ElementOfFiniteFieldP<2>, 3> b{};

	constexpr bool a_eq_b{ array_equals( a, b ) };
	EXPECT_EQ( true, a_eq_b );
}

