#include "finite-fields/FiniteFieldsOfSizePrimeToAPower.h"

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

TEST( ElementOfFiniteFieldTests, ClassIsValueInstantiable )
{
	ElementOfFiniteField<Prime, Exponent> a{};

	const auto zero{ ElementOfFiniteField<Prime,Exponent>::GetAdditionInvarient( irriducible ) };
	EXPECT_NE( a, zero );
}

TEST( ElementOfFiniteFieldTests, AssignmentOverwritesValueInitialized )
{
	const auto zero{ ElementOfFiniteField<Prime,Exponent>::GetAdditionInvarient( irriducible ) };
	ElementOfFiniteField<Prime, Exponent> a{};

	a = zero;
	EXPECT_EQ( a, zero );
}

TEST( ElementOfFiniteFieldTests, AdditionInvarientHelperConstexpr )
{
	constexpr auto zero{ ElementOfFiniteField<Prime,Exponent>::GetAdditionInvarient( irriducible ) };
}

TEST( ElementOfFiniteFieldTests, InversionForAnyIrriducible )
{
	std::vector<ElementOfFiniteFieldP<Prime>> nonSquares{ 2,3,7,8,10,11,12,15,18,26,27,28,29,32,34,35,38,39,40,41,42,44,46,48,50,51,53,55,57,59,60,61,62,63,66,67,69,72,73,74,75,83,86,89,90,91,93,94,98,99 };
	
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

	unsigned testCount{ 0 };

	for( const auto poly : irriducibles )
	{
		const auto one = ElementOfFiniteField<Prime, Exponent>::GetMultiplicativeInvarient( poly );

		for( integer loop_index_0 = 0; loop_index_0<Prime; loop_index_0++ )
		{
			for( integer loop_index_1 = 0; loop_index_1<Prime; loop_index_1++ )
			{
				testCount++;

				const auto initializer = PolynomialOverPrimeSizeFiniteField<Prime,1>{ 
					std::array<ElementOfFiniteFieldP<Prime>,PolynomialOverPrimeSizeFiniteField<Prime,1>::GetCapacity()>{
						ElementOfFiniteFieldP<Prime>{ loop_index_0 },
						ElementOfFiniteFieldP<Prime>{ loop_index_1 }
					}
				};

				const auto a = ElementOfFiniteField<Prime, Exponent>{
					initializer,
					poly
				};

				if( a == a.GetAdditionInvarient() )
					continue;

				EXPECT_EQ( a/a, one );
			}
		}
	}

	EXPECT_EQ( testCount, irriducibles.size()*Prime*Prime );
}

	