#include "reed-solomon-codes/PolynomialsOverFiniteFieldOfSizePrimeToAPower.h"

#include "finite-fields-tests/test-data/IrriduciblePolynomial.h"

#include "gtest/gtest.h"

constexpr integer Prime{ 101 };
constexpr integer Exponent{ 2 };

TEST( TestDataVerifictaion, IrriducibleIsAsAssumed )
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

TEST( PolynomialOverFiniteFieldTests, Evaluation )
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
	
	const ElementOfFiniteField<Prime, Exponent> argument{
		PolynomialOverPrimeSizeFiniteField<Prime,1>{
			std::array<ElementOfFiniteFieldP<Prime>,PolynomialOverPrimeSizeFiniteField<Prime,1>::GetCapacity()>{
				ElementOfFiniteFieldP<Prime>{ 9 },
				ElementOfFiniteFieldP<Prime>{ 8 }
			} 
		},
		irriducible
	};

	const ElementOfFiniteField<Prime, Exponent> expected{
		PolynomialOverPrimeSizeFiniteField<Prime,1>{
			std::array<ElementOfFiniteFieldP<Prime>,PolynomialOverPrimeSizeFiniteField<Prime,1>::GetCapacity()>{
				ElementOfFiniteFieldP<Prime>{ 62 },
				ElementOfFiniteFieldP<Prime>{ 14 }
			} 
		},
		irriducible
	};

	const auto res = polynomial( argument );
	EXPECT_EQ( res, expected );
	for( std::size_t coefficient_index = 0; coefficient_index<res.value.coefficients.size(); coefficient_index++ )
	{
		EXPECT_EQ( res.value.coefficients.at( coefficient_index ).value, expected.value.coefficients.at( coefficient_index ).value ) << "Index: " << coefficient_index;
	}
}
