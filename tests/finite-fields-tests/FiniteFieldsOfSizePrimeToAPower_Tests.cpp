
#include "finite-fields/FiniteFieldsOfSizePrimeToAPower.h"

#include "test-data/IrriduciblePolynomial.h"

#include "gtest/gtest.h"

#include <algorithm>
#include <array>
#include <type_traits>
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
		std::array<ElementOfFiniteFieldP<Prime>,PolynomialOverPrimeSizeFiniteField<Prime,2>::GetCoeffCount()>{
			ElementOfFiniteFieldP<Prime>{ -2 },
			ElementOfFiniteFieldP<Prime>{ 0 },
			ElementOfFiniteFieldP<Prime>{ 1 }
		} 
	};
	const auto& class_irriducible{ ElementOfFiniteField<Prime, Exponent>::irriducible_polynomial };
	ASSERT_EQ( class_irriducible, assumed ) << "This layer of indirection is so that expensive tests which verify irriducibility can be kept separate and only run if irriducible changes.";
}

TEST( ElementOfFiniteFieldTests, PackedTightlyWithRespectToValueSize )
{
	EXPECT_EQ( sizeof( ElementOfFiniteField<Prime, Exponent> ), Exponent * sizeof( ElementOfFiniteFieldP<Prime> ) );
}

TEST( ElementOfFiniteFieldTests, GetMultiplicativeInvarient )
{
	const auto initializer = PolynomialOverPrimeSizeFiniteField<Prime,1>{ 
		std::array<ElementOfFiniteFieldP<Prime>,PolynomialOverPrimeSizeFiniteField<Prime,1>::GetCoeffCount()>{
			ElementOfFiniteFieldP<Prime>{ 1 },
			ElementOfFiniteFieldP<Prime>{ 0 }
		}
	};

	const auto a = ElementOfFiniteField<Prime, Exponent>{
		initializer
	};

	const auto one = ElementOfFiniteField<Prime, Exponent>::GetMultiplicativeInvarient();

	EXPECT_EQ( one, a );
	EXPECT_TRUE( a.IsOne() );
}

TEST( ElementOfFiniteFieldTests, Inversion )
{
	const auto arbitrary = PolynomialOverPrimeSizeFiniteField<Prime,1>{ 
		std::array<ElementOfFiniteFieldP<Prime>,PolynomialOverPrimeSizeFiniteField<Prime,1>::GetCoeffCount()>{
			ElementOfFiniteFieldP<Prime>{ 46 },
			ElementOfFiniteFieldP<Prime>{ 99 }
		}
	};
	const auto unwound = ElementOfFiniteField<Prime, Exponent>{
		arbitrary
	};
	EXPECT_TRUE( (unwound/unwound).IsOne() );

	for( integer loop_index_0 = 0; loop_index_0<Prime; loop_index_0++ )
	{
		for( integer loop_index_1 = 0; loop_index_1<Prime; loop_index_1++ )
		{
			const auto initializer = PolynomialOverPrimeSizeFiniteField<Prime,1>{ 
				std::array<ElementOfFiniteFieldP<Prime>,PolynomialOverPrimeSizeFiniteField<Prime,1>::GetCoeffCount()>{
					ElementOfFiniteFieldP<Prime>{ loop_index_0 },
					ElementOfFiniteFieldP<Prime>{ loop_index_1 }
				}
			};

			const auto a = ElementOfFiniteField<Prime, Exponent>{
				initializer
			};

			if( a.IsZero() )
				continue;

			EXPECT_TRUE( (a/a).IsOne() );
		}
	}
}

TEST( ElementOfFiniteFieldTests, MultiplicationIsConstexpr )
{
	constexpr auto arbitrary = PolynomialOverPrimeSizeFiniteField<Prime,1>{ 
		std::array<ElementOfFiniteFieldP<Prime>,PolynomialOverPrimeSizeFiniteField<Prime,1>::GetCoeffCount()>{
			ElementOfFiniteFieldP<Prime>{ 46 },
			ElementOfFiniteFieldP<Prime>{ 99 }
		}
	};
	constexpr auto unwound = ElementOfFiniteField<Prime, Exponent>{
		arbitrary
	};
	constexpr auto inverse{ unwound*unwound };
	EXPECT_FALSE( inverse.IsZero() );
}

TEST( ElementOfFiniteFieldTests, InversionIsConstexpr )
{
	constexpr auto arbitrary = PolynomialOverPrimeSizeFiniteField<Prime,1>{ 
		std::array<ElementOfFiniteFieldP<Prime>,PolynomialOverPrimeSizeFiniteField<Prime,1>::GetCoeffCount()>{
			ElementOfFiniteFieldP<Prime>{ 46 },
			ElementOfFiniteFieldP<Prime>{ 99 }
		}
	};
	constexpr auto unwound = ElementOfFiniteField<Prime, Exponent>{
		arbitrary
	};
	constexpr auto inverse{ unwound.FindMultiplicativeInverse() };
	EXPECT_FALSE( inverse.IsZero() );
}

TEST( ElementOfFiniteFieldTests, ClassIsValueInstantiable )
{
	ElementOfFiniteField<Prime, Exponent> a{};

	const auto zero{ ElementOfFiniteField<Prime,Exponent>::GetAdditionInvarient() };
	EXPECT_EQ( a, zero );
}

TEST( ElementOfFiniteFieldTests, AdditionInvariantIsZero )
{
	const auto zero{ ElementOfFiniteField<Prime,Exponent>::GetAdditionInvarient() };

	EXPECT_TRUE( zero.IsZero() );
	EXPECT_FALSE( zero.IsOne() );
}

TEST( ElementOfFiniteFieldTests, MultiplicativeInvariantIsOne )
{
	auto one{ ElementOfFiniteField<Prime,Exponent>::GetMultiplicativeInvarient() };	

	EXPECT_FALSE( one.IsZero() );
	EXPECT_TRUE( one.IsOne() );
}

TEST( ElementOfFiniteFieldTests, AssignmentOverwritesValueInitialized )
{
	const auto zero{ ElementOfFiniteField<Prime,Exponent>::GetAdditionInvarient() };
	auto a{ ElementOfFiniteField<Prime,Exponent>::GetMultiplicativeInvarient() };

	a = zero;
	EXPECT_EQ( a, zero );
}

TEST( ElementOfFiniteFieldTests, Multiplication )
{
	ElementOfFiniteField<Prime, Exponent> a{
		PolynomialOverPrimeSizeFiniteField<Prime,1>{
			std::array<ElementOfFiniteFieldP<Prime>,PolynomialOverPrimeSizeFiniteField<Prime,1>::GetCoeffCount()>{
				ElementOfFiniteFieldP<Prime>{ 7 },
				ElementOfFiniteFieldP<Prime>{ 6 }
			} 
		}
	};


	const ElementOfFiniteField<Prime, Exponent> b{
		PolynomialOverPrimeSizeFiniteField<Prime,1>{
			std::array<ElementOfFiniteFieldP<Prime>,PolynomialOverPrimeSizeFiniteField<Prime,1>::GetCoeffCount()>{
				ElementOfFiniteFieldP<Prime>{ 9 },
				ElementOfFiniteFieldP<Prime>{ 8 }
			} 
		}
	};

	const ElementOfFiniteField<Prime, Exponent> ab_expected{
		PolynomialOverPrimeSizeFiniteField<Prime,1>{
			std::array<ElementOfFiniteFieldP<Prime>,PolynomialOverPrimeSizeFiniteField<Prime,1>::GetCoeffCount()>{
				ElementOfFiniteFieldP<Prime>{ 58 },
				ElementOfFiniteFieldP<Prime>{ 9 }
			} 
		}
	};

	EXPECT_EQ( a*b, ab_expected );
	

	const ElementOfFiniteField<Prime, Exponent> c{
		PolynomialOverPrimeSizeFiniteField<Prime,1>{
			std::array<ElementOfFiniteFieldP<Prime>,PolynomialOverPrimeSizeFiniteField<Prime,1>::GetCoeffCount()>{
				ElementOfFiniteFieldP<Prime>{ 10 },
				ElementOfFiniteFieldP<Prime>{ 11 }
			} 
		}
	};

	const ElementOfFiniteField<Prime, Exponent> ac_expected{
		PolynomialOverPrimeSizeFiniteField<Prime,1>{
			std::array<ElementOfFiniteFieldP<Prime>,PolynomialOverPrimeSizeFiniteField<Prime,1>::GetCoeffCount()>{
				ElementOfFiniteFieldP<Prime>{ 0 },
				ElementOfFiniteFieldP<Prime>{ 36 }
			} 
		}
	};

	EXPECT_EQ( a*c, ac_expected );
	

	const ElementOfFiniteField<Prime, Exponent> d{
		PolynomialOverPrimeSizeFiniteField<Prime,1>{
			std::array<ElementOfFiniteFieldP<Prime>,PolynomialOverPrimeSizeFiniteField<Prime,1>::GetCoeffCount()>{
				ElementOfFiniteFieldP<Prime>{ 12 },
				ElementOfFiniteFieldP<Prime>{ 13 }
			} 
		}
	};

	const ElementOfFiniteField<Prime, Exponent> ad_expected{
		PolynomialOverPrimeSizeFiniteField<Prime,1>{
			std::array<ElementOfFiniteFieldP<Prime>,PolynomialOverPrimeSizeFiniteField<Prime,1>::GetCoeffCount()>{
				ElementOfFiniteFieldP<Prime>{ 38 },
				ElementOfFiniteFieldP<Prime>{ 62 }
			} 
		}
	};

	EXPECT_EQ( a*d, ad_expected );
	

	const ElementOfFiniteField<Prime, Exponent> e{
		PolynomialOverPrimeSizeFiniteField<Prime,1>{
			std::array<ElementOfFiniteFieldP<Prime>,PolynomialOverPrimeSizeFiniteField<Prime,1>::GetCoeffCount()>{
				ElementOfFiniteFieldP<Prime>{ 14 },
				ElementOfFiniteFieldP<Prime>{ 15 }
			} 
		}
	};

	const ElementOfFiniteField<Prime, Exponent> ae_expected{
		PolynomialOverPrimeSizeFiniteField<Prime,1>{
			std::array<ElementOfFiniteFieldP<Prime>,PolynomialOverPrimeSizeFiniteField<Prime,1>::GetCoeffCount()>{
				ElementOfFiniteFieldP<Prime>{ 76 },
				ElementOfFiniteFieldP<Prime>{ 88 }
			} 
		}
	};

	EXPECT_EQ( a*e, ae_expected );
}

TEST( ElementOfFiniteFieldTests, Addition )
{
	ElementOfFiniteField<Prime, Exponent> a{
		PolynomialOverPrimeSizeFiniteField<Prime,1>{
			std::array<ElementOfFiniteFieldP<Prime>,PolynomialOverPrimeSizeFiniteField<Prime,1>::GetCoeffCount()>{
				ElementOfFiniteFieldP<Prime>{ 4 },
				ElementOfFiniteFieldP<Prime>{ 5 }
			} 
		}
	};


	const ElementOfFiniteField<Prime, Exponent> b{
		PolynomialOverPrimeSizeFiniteField<Prime,1>{
			std::array<ElementOfFiniteFieldP<Prime>,PolynomialOverPrimeSizeFiniteField<Prime,1>::GetCoeffCount()>{
				ElementOfFiniteFieldP<Prime>{ 58 },
				ElementOfFiniteFieldP<Prime>{ 9 }
			} 
		}
	};

	const ElementOfFiniteField<Prime, Exponent> ab_expected{
		PolynomialOverPrimeSizeFiniteField<Prime,1>{
			std::array<ElementOfFiniteFieldP<Prime>,PolynomialOverPrimeSizeFiniteField<Prime,1>::GetCoeffCount()>{
				ElementOfFiniteFieldP<Prime>{ 62 },
				ElementOfFiniteFieldP<Prime>{ 14 }
			} 
		}
	};

	EXPECT_EQ( a+b, ab_expected );
	

	const ElementOfFiniteField<Prime, Exponent> c{
		PolynomialOverPrimeSizeFiniteField<Prime,1>{
			std::array<ElementOfFiniteFieldP<Prime>,PolynomialOverPrimeSizeFiniteField<Prime,1>::GetCoeffCount()>{
				ElementOfFiniteFieldP<Prime>{ 0 },
				ElementOfFiniteFieldP<Prime>{ 36 }
			} 
		}
	};

	const ElementOfFiniteField<Prime, Exponent> ac_expected{
		PolynomialOverPrimeSizeFiniteField<Prime,1>{
			std::array<ElementOfFiniteFieldP<Prime>,PolynomialOverPrimeSizeFiniteField<Prime,1>::GetCoeffCount()>{
				ElementOfFiniteFieldP<Prime>{ 4 },
				ElementOfFiniteFieldP<Prime>{ 41 }
			} 
		}
	};

	EXPECT_EQ( a+c, ac_expected );
	

	const ElementOfFiniteField<Prime, Exponent> d{
		PolynomialOverPrimeSizeFiniteField<Prime,1>{
			std::array<ElementOfFiniteFieldP<Prime>,PolynomialOverPrimeSizeFiniteField<Prime,1>::GetCoeffCount()>{
				ElementOfFiniteFieldP<Prime>{ 38 },
				ElementOfFiniteFieldP<Prime>{ 62 }
			} 
		}
	};

	const ElementOfFiniteField<Prime, Exponent> ad_expected{
		PolynomialOverPrimeSizeFiniteField<Prime,1>{
			std::array<ElementOfFiniteFieldP<Prime>,PolynomialOverPrimeSizeFiniteField<Prime,1>::GetCoeffCount()>{
				ElementOfFiniteFieldP<Prime>{ 42 },
				ElementOfFiniteFieldP<Prime>{ 67 }
			} 
		}
	};

	EXPECT_EQ( a+d, ad_expected );
	

	const ElementOfFiniteField<Prime, Exponent> e{
		PolynomialOverPrimeSizeFiniteField<Prime,1>{
			std::array<ElementOfFiniteFieldP<Prime>,PolynomialOverPrimeSizeFiniteField<Prime,1>::GetCoeffCount()>{
				ElementOfFiniteFieldP<Prime>{ 76 },
				ElementOfFiniteFieldP<Prime>{ 88 }
			} 
		}
	};

	const ElementOfFiniteField<Prime, Exponent> ae_expected{
		PolynomialOverPrimeSizeFiniteField<Prime,1>{
			std::array<ElementOfFiniteFieldP<Prime>,PolynomialOverPrimeSizeFiniteField<Prime,1>::GetCoeffCount()>{
				ElementOfFiniteFieldP<Prime>{ 80 },
				ElementOfFiniteFieldP<Prime>{ 93 }
			} 
		}
	};

	EXPECT_EQ( a+e, ae_expected );
}

TEST( ElementOfFiniteFieldTests, IsLiteralType )
{
	constexpr bool is_literal_type{ std::is_literal_type_v<ElementOfFiniteField<Prime, Exponent>> };
	ASSERT_TRUE( is_literal_type );
}

TEST( ElementOfFiniteFieldTests, ArrayOfIsLiteralType )
{
	constexpr bool is_literal_type{ std::is_literal_type_v<std::array<ElementOfFiniteField<Prime,Exponent>, 4>> };
	ASSERT_TRUE( is_literal_type );
}

