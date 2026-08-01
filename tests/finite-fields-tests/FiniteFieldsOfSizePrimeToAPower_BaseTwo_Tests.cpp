#include "finite-fields/FiniteFieldsOfSizePrimeToAPower.h"

#include "gtest/gtest.h"

constexpr integer Exponent{ 2 };

TEST( BaseTwoFiniteFieldTests, PackingIsTight )
{
	EXPECT_EQ( (Exponent / 8) + 1, sizeof( ElementOfFiniteField<2, Exponent> ) );
}

