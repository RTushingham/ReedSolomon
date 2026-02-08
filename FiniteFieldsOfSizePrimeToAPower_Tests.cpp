#include "FiniteFieldsOfSizePrimeToAPower.h"

#include "test-data/IrriduciblePolynomial.h"

#include "gtest/gtest.h"

#include <algorithm>
#include <vector>

constexpr integer Prime{ 101 };
constexpr integer Exponent{ 2 };

TEST( TestDataVerifictaion, DegreeIsAppropriate )
{
	ASSERT_EQ( Exponent, irriducible.GetDegree() );
}
TEST( TestDataVerifictaion, ValueIsAsAssumed )
{
	const auto assumed = PolynomialOverPrimeSizeFiniteField<Prime,2>{ 
		std::array<ElementOfFiniteFieldP<Prime>,PolynomialOverPrimeSizeFiniteField<Prime,2>::GetCapacity()>{
			ElementOfFiniteFieldP<Prime>{ -2 },
			ElementOfFiniteFieldP<Prime>{ 0 },
			ElementOfFiniteFieldP<Prime>{ 1 }
		} 
	};
	ASSERT_EQ( irriducible, assumed ) << "This layer of indirection is so that expensive tests which verify irriducibility can be kept separate and only run if irriducible changes.";
}

TEST( ElementOfFiniteFieldTests, Construction )
{
	const auto initializer = PolynomialOverPrimeSizeFiniteField<Prime,2>{ 
		std::array<ElementOfFiniteFieldP<Prime>,PolynomialOverPrimeSizeFiniteField<Prime,2>::GetCapacity()>{
			ElementOfFiniteFieldP<Prime>{ 10 },
			ElementOfFiniteFieldP<Prime>{ 11 },
			ElementOfFiniteFieldP<Prime>{ 12 }
		} 
	};

	const auto a = ElementOfFiniteField<Prime, Exponent>{
		initializer,
		irriducible
	};

	const auto equivalent_value = PolynomialOverPrimeSizeFiniteField<Prime,1>{
		std::array<ElementOfFiniteFieldP<Prime>,PolynomialOverPrimeSizeFiniteField<Prime,1>::GetCapacity()>{
			ElementOfFiniteFieldP<Prime>{ 10 + 12 + 12 },
			ElementOfFiniteFieldP<Prime>{ 11 }
		} 
	};

	const auto expected = ElementOfFiniteField<Prime, Exponent>{
		equivalent_value,
		irriducible
	};
	
	EXPECT_EQ( a, expected );
}

TEST( ElementOfFiniteFieldTests, GetMultiplicativeInvarient )
{
	const auto initializer = PolynomialOverPrimeSizeFiniteField<Prime,1>{ 
		std::array<ElementOfFiniteFieldP<Prime>,PolynomialOverPrimeSizeFiniteField<Prime,1>::GetCapacity()>{
			ElementOfFiniteFieldP<Prime>{ 1 },
			ElementOfFiniteFieldP<Prime>{ 0 }
		}
	};

	const auto a = ElementOfFiniteField<Prime, Exponent>{
		initializer,
		irriducible
	};

	const auto one = ElementOfFiniteField<Prime, Exponent>::GetMultiplicativeInvarient( irriducible );

	EXPECT_EQ( one, a );
}

TEST( ElementOfFiniteFieldTests, Inversion )
{
	const auto one = ElementOfFiniteField<Prime, Exponent>::GetMultiplicativeInvarient( irriducible );

	const auto arbitrary = PolynomialOverPrimeSizeFiniteField<Prime,1>{ 
		std::array<ElementOfFiniteFieldP<Prime>,PolynomialOverPrimeSizeFiniteField<Prime,1>::GetCapacity()>{
			ElementOfFiniteFieldP<Prime>{ 46 },
			ElementOfFiniteFieldP<Prime>{ 99 }
		}
	};
	const auto unwound = ElementOfFiniteField<Prime, Exponent>{
		arbitrary,
		irriducible
	};
	EXPECT_EQ( unwound/unwound, one );

	for( integer loop_index_0 = 0; loop_index_0<Prime; loop_index_0++ )
	{
		for( integer loop_index_1 = 0; loop_index_1<Prime; loop_index_1++ )
		{
			const auto initializer = PolynomialOverPrimeSizeFiniteField<Prime,1>{ 
				std::array<ElementOfFiniteFieldP<Prime>,PolynomialOverPrimeSizeFiniteField<Prime,1>::GetCapacity()>{
					ElementOfFiniteFieldP<Prime>{ loop_index_0 },
					ElementOfFiniteFieldP<Prime>{ loop_index_1 }
				}
			};

			const auto a = ElementOfFiniteField<Prime, Exponent>{
				initializer,
				irriducible
			};

			if( a == a.GetAdditionInvarient() )
				continue;

			EXPECT_EQ( a/a, one );
		}
	}
}
