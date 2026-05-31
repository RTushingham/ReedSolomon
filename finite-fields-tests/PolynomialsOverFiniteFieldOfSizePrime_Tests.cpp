#include "finite-fields/PolynomialsOverFiniteFieldOfSizePrime.h"

#include "gtest/gtest.h"

constexpr integer Prime{ 101 };

PolynomialOverPrimeSizeFiniteField<Prime,2> a{ 
	std::array<ElementOfFiniteFieldP<Prime>,PolynomialOverPrimeSizeFiniteField<Prime,2>::GetCapacity()>{
		ElementOfFiniteFieldP<Prime>{ 10 },
		ElementOfFiniteFieldP<Prime>{ 11 },
		ElementOfFiniteFieldP<Prime>{ 12 }
	} 
};
PolynomialOverPrimeSizeFiniteField<Prime,2> b{ 
	std::array<ElementOfFiniteFieldP<Prime>,PolynomialOverPrimeSizeFiniteField<Prime,2>::GetCapacity()>{
		ElementOfFiniteFieldP<Prime>{ 5 },
		ElementOfFiniteFieldP<Prime>{ 7 },
		ElementOfFiniteFieldP<Prime>{ 9 }
	} 
};

TEST( PolynomialsOverPrimeFieldTests, Addition )
{
	const auto expected = PolynomialOverPrimeSizeFiniteField<Prime,2>{ 
		std::array<ElementOfFiniteFieldP<Prime>,PolynomialOverPrimeSizeFiniteField<Prime,2>::GetCapacity()>{
			ElementOfFiniteFieldP<Prime>{ 15 },
			ElementOfFiniteFieldP<Prime>{ 18 },
			ElementOfFiniteFieldP<Prime>{ 21 }
		} 
	};

	EXPECT_EQ( a + b, expected );
}

TEST( PolynomialsOverPrimeFieldTests, Subtraction )
{
	const auto expected = PolynomialOverPrimeSizeFiniteField<Prime,2>{ 
		std::array<ElementOfFiniteFieldP<Prime>,PolynomialOverPrimeSizeFiniteField<Prime,2>::GetCapacity()>{
			ElementOfFiniteFieldP<Prime>{ 5 },
			ElementOfFiniteFieldP<Prime>{ 4 },
			ElementOfFiniteFieldP<Prime>{ 3 }
		} 
	}; 

	EXPECT_EQ( a - b, expected );
}

PolynomialOverPrimeSizeFiniteField<Prime,1> c{ 
	std::array<ElementOfFiniteFieldP<Prime>,PolynomialOverPrimeSizeFiniteField<Prime,1>::GetCapacity()>{
		ElementOfFiniteFieldP<Prime>{ 2 },
		ElementOfFiniteFieldP<Prime>{ 3 }
	}
};

TEST( PolynomialsOverPrimeFieldTests, Multiplication )
{
	const auto expected = PolynomialOverPrimeSizeFiniteField<Prime,3>{ 
		std::array<ElementOfFiniteFieldP<Prime>,PolynomialOverPrimeSizeFiniteField<Prime,3>::GetCapacity()>{
			ElementOfFiniteFieldP<Prime>{ 20 },
			ElementOfFiniteFieldP<Prime>{ 52 },
			ElementOfFiniteFieldP<Prime>{ 57 },
			ElementOfFiniteFieldP<Prime>{ 36 }
		} 
	};

	EXPECT_EQ( a * c, expected );
}

TEST( PolynomialsOverPrimeFieldTests, Modulo )
{
	const auto abQuotient = PolynomialOverPrimeSizeFiniteField<Prime,0>{ 
		std::array<ElementOfFiniteFieldP<Prime>,PolynomialOverPrimeSizeFiniteField<Prime,0>::GetCapacity()>{
			ElementOfFiniteFieldP<Prime>{ 12 }/ElementOfFiniteFieldP<Prime>{ 9 }
		} 
	};
	EXPECT_EQ( (a % b).Oversize<2>(), a - ( abQuotient * b ) );

	const auto acQuotient = PolynomialOverPrimeSizeFiniteField<Prime,1>{ 
		std::array<ElementOfFiniteFieldP<Prime>,PolynomialOverPrimeSizeFiniteField<Prime,1>::GetCapacity()>{
			ElementOfFiniteFieldP<Prime>{ 1 },
			ElementOfFiniteFieldP<Prime>{ 4 }
		} 
	};
	const auto acRemainder = PolynomialOverPrimeSizeFiniteField<Prime,0>{ 
		std::array<ElementOfFiniteFieldP<Prime>,PolynomialOverPrimeSizeFiniteField<Prime,0>::GetCapacity()>{
			ElementOfFiniteFieldP<Prime>{ 8 }
		} 
	};
	EXPECT_EQ( a % c, acRemainder );
	EXPECT_EQ( (a % c).Oversize<2>(), a - ( acQuotient * c ) );

	EXPECT_EQ( c % a, c );
}

TEST( PolynomialsOverPrimeFieldTests, ClassIsConstexprInstantiable )
{
	constexpr PolynomialOverPrimeSizeFiniteField<Prime,0> const_expr{ 
		std::array<ElementOfFiniteFieldP<Prime>,PolynomialOverPrimeSizeFiniteField<Prime,0>::GetCapacity()>{
			ElementOfFiniteFieldP<Prime>{ 12 }/ElementOfFiniteFieldP<Prime>{ 9 }
		} 
	};
}

TEST( PolynomialsOverPrimeFieldTests, ValueInitializable )
{
	PolynomialOverPrimeSizeFiniteField<Prime,0> val_init{};

	const auto zero{ PolynomialOverPrimeSizeFiniteField<Prime,0>::GetAdditionInvarient() };
	EXPECT_EQ( val_init, zero );
}

TEST( PolynomialsOverPrimeFieldTests, AdditionInvarientHelperConstexpr )
{
	constexpr auto zero{ PolynomialOverPrimeSizeFiniteField<Prime,0>::GetAdditionInvarient() };
}

TEST( PolynomialsOverPrimeFieldTests, AdditionInvariantIsZero )
{
	const auto zero{ PolynomialOverPrimeSizeFiniteField<Prime,2>::GetAdditionInvarient() };

	EXPECT_TRUE( zero.IsZero() );
	EXPECT_FALSE( zero.IsOne() );
}

TEST( PolynomialsOverPrimeFieldTests, MultiplicativeInvariantIsOne )
{
	auto one{ PolynomialOverPrimeSizeFiniteField<Prime,2>::GetMultiplicativeInvarient() };	

	EXPECT_FALSE( one.IsZero() );
	EXPECT_TRUE( one.IsOne() );
}
