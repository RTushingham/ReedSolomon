#include "reed-solomon-codes/PolynomialsOverFiniteFieldOfSizePrimeToAPower.h"

#include "finite-fields-tests/test-data/IrriduciblePolynomial.h"

#include "gtest/gtest.h"

constexpr integer Prime{ 101 };
constexpr integer Exponent{ 2 };

namespace
{
	constexpr integer MaxDegree = 1;

	const std::array<ElementOfFiniteField<Prime, Exponent>,MaxDegree+1> initializer{
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

	PolynomialOverFiniteField<Prime,Exponent,MaxDegree> polynomial{ 
		initializer 
	};
}


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
	const ElementOfFiniteField<Prime, Exponent> argument{
		PolynomialOverPrimeSizeFiniteField<Prime,1>{
			std::array<ElementOfFiniteFieldP<Prime>,PolynomialOverPrimeSizeFiniteField<Prime,1>::GetCapacity()>{
				ElementOfFiniteFieldP<Prime>{ 9 },
				ElementOfFiniteFieldP<Prime>{ 8 }
			} 
		}
	};

	const ElementOfFiniteField<Prime, Exponent> expected{
		PolynomialOverPrimeSizeFiniteField<Prime,1>{
			std::array<ElementOfFiniteFieldP<Prime>,PolynomialOverPrimeSizeFiniteField<Prime,1>::GetCapacity()>{
				ElementOfFiniteFieldP<Prime>{ 62 },
				ElementOfFiniteFieldP<Prime>{ 14 }
			} 
		}
	};

	EXPECT_EQ( polynomial( argument ), expected );
}

TEST( PolynomialOverFiniteFieldTests, b )
{
	const ElementOfFiniteField<Prime, Exponent> argument{
		PolynomialOverPrimeSizeFiniteField<Prime,1>{
			std::array<ElementOfFiniteFieldP<Prime>,PolynomialOverPrimeSizeFiniteField<Prime,1>::GetCapacity()>{
				ElementOfFiniteFieldP<Prime>{ 10 },
				ElementOfFiniteFieldP<Prime>{ 11 }
			} 
		}
	};

	const ElementOfFiniteField<Prime, Exponent> expected{
		PolynomialOverPrimeSizeFiniteField<Prime,1>{
			std::array<ElementOfFiniteFieldP<Prime>,PolynomialOverPrimeSizeFiniteField<Prime,1>::GetCapacity()>{
				ElementOfFiniteFieldP<Prime>{ 4 },
				ElementOfFiniteFieldP<Prime>{ 41 }
			} 
		}
	};

	EXPECT_EQ( polynomial( argument ), expected );
}

TEST( PolynomialOverFiniteFieldTests, c )
{
	const ElementOfFiniteField<Prime, Exponent> argument{
		PolynomialOverPrimeSizeFiniteField<Prime,1>{
			std::array<ElementOfFiniteFieldP<Prime>,PolynomialOverPrimeSizeFiniteField<Prime,1>::GetCapacity()>{
				ElementOfFiniteFieldP<Prime>{ 12 },
				ElementOfFiniteFieldP<Prime>{ 13 }
			} 
		}
	};

	const ElementOfFiniteField<Prime, Exponent> expected{
		PolynomialOverPrimeSizeFiniteField<Prime,1>{
			std::array<ElementOfFiniteFieldP<Prime>,PolynomialOverPrimeSizeFiniteField<Prime,1>::GetCapacity()>{
				ElementOfFiniteFieldP<Prime>{ 42 },
				ElementOfFiniteFieldP<Prime>{ 67 }
			} 
		}
	};

	EXPECT_EQ( polynomial( argument ), expected );
}

TEST( PolynomialOverFiniteFieldTests, d )
{
	const ElementOfFiniteField<Prime, Exponent> argument{
		PolynomialOverPrimeSizeFiniteField<Prime,1>{
			std::array<ElementOfFiniteFieldP<Prime>,PolynomialOverPrimeSizeFiniteField<Prime,1>::GetCapacity()>{
				ElementOfFiniteFieldP<Prime>{ 14 },
				ElementOfFiniteFieldP<Prime>{ 15 }
			} 
		}
	};

	const ElementOfFiniteField<Prime, Exponent> expected{
		PolynomialOverPrimeSizeFiniteField<Prime,1>{
			std::array<ElementOfFiniteFieldP<Prime>,PolynomialOverPrimeSizeFiniteField<Prime,1>::GetCapacity()>{
				ElementOfFiniteFieldP<Prime>{ 80 },
				ElementOfFiniteFieldP<Prime>{ 93 }
			} 
		}
	};

	EXPECT_EQ( polynomial( argument ), expected );
}
