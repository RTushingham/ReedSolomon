
#include "finite-fields-tmp/tmp_FiniteFieldsOfSizePrimeToAPower.h"
#include "finite-fields-tests/helpers/InitializerHelper.h"

#include "gtest/gtest.h"

constexpr integer Prime{ 2 };
constexpr integer Exponent{ 8 };
constexpr integer MaxDegree{ 3 };

namespace
{
	ElementOfFiniteField_Poly<MaxDegree,Exponent> a{
		std::array<ElementOfFiniteField<2, Exponent>,MaxDegree+1>{
			ElementOfFiniteField<2, Exponent>{
				( x_to( 1,1 ) + x_to( 1, 3 ) + x_to( 1, 5 ) ).evaluate<PolynomialOverPrimeSizeFiniteField<Prime,Exponent-1>>()
			},
			ElementOfFiniteField<2, Exponent>{
				( x_to( 1,1 ) + x_to( 1, 3 ) + x_to( 1, 5 ) ).evaluate<PolynomialOverPrimeSizeFiniteField<Prime,Exponent-1>>()
			},
			ElementOfFiniteField<2, Exponent>{
				( x_to( 1,1 ) + x_to( 1, 3 ) + x_to( 1, 5 ) ).evaluate<PolynomialOverPrimeSizeFiniteField<Prime,Exponent-1>>()
			},
			ElementOfFiniteField<2, Exponent>{
				( x_to( 1,1 ) + x_to( 1, 3 ) + x_to( 1, 5 ) ).evaluate<PolynomialOverPrimeSizeFiniteField<Prime,Exponent-1>>()
			}
		}
	};
	ElementOfFiniteField_Poly<MaxDegree,Exponent> b{
		std::array<ElementOfFiniteField<2, Exponent>,MaxDegree+1>{
			ElementOfFiniteField<2, Exponent>{
				( x_to( 1,0 ) + x_to( 1, 2 ) + x_to( 1, 5 ) ).evaluate<PolynomialOverPrimeSizeFiniteField<Prime,Exponent-1>>()
			},
			ElementOfFiniteField<2, Exponent>{
				( x_to( 1,0 ) + x_to( 1, 2 ) + x_to( 1, 5 ) ).evaluate<PolynomialOverPrimeSizeFiniteField<Prime,Exponent-1>>()
			},
			ElementOfFiniteField<2, Exponent>{
				( x_to( 1,0 ) + x_to( 1, 2 ) + x_to( 1, 5 ) ).evaluate<PolynomialOverPrimeSizeFiniteField<Prime,Exponent-1>>()
			},
			ElementOfFiniteField<2, Exponent>{
				( x_to( 1,0 ) + x_to( 1, 2 ) + x_to( 1, 5 ) ).evaluate<PolynomialOverPrimeSizeFiniteField<Prime,Exponent-1>>()
			}
		}
	};
	ElementOfFiniteField_Poly<MaxDegree,Exponent> sum_ab_expected{
		std::array<ElementOfFiniteField<2, Exponent>,MaxDegree+1>{
			ElementOfFiniteField<2, Exponent>{
				( x_to( 1,0 ) + x_to( 1,1 ) + x_to( 1, 2 ) + x_to( 1, 3 ) ).evaluate<PolynomialOverPrimeSizeFiniteField<Prime,Exponent-1>>()
			},
			ElementOfFiniteField<2, Exponent>{
				( x_to( 1,0 ) + x_to( 1,1 ) + x_to( 1, 2 ) + x_to( 1, 3 ) ).evaluate<PolynomialOverPrimeSizeFiniteField<Prime,Exponent-1>>()
			},
			ElementOfFiniteField<2, Exponent>{
				( x_to( 1,0 ) + x_to( 1,1 ) + x_to( 1, 2 ) + x_to( 1, 3 ) ).evaluate<PolynomialOverPrimeSizeFiniteField<Prime,Exponent-1>>()
			},
			ElementOfFiniteField<2, Exponent>{
				( x_to( 1,0 ) + x_to( 1,1 ) + x_to( 1, 2 ) + x_to( 1, 3 ) ).evaluate<PolynomialOverPrimeSizeFiniteField<Prime,Exponent-1>>()
			}
		}
	};
}

TEST( ExpressionTemplateTests, Addition )
{
	auto sum_ab_exptmp{ a+b };

	EXPECT_EQ( sum_ab_expected.GetCoeff( 0 ), sum_ab_exptmp.GetCoeff( 0 ) );

	for( size_t coeff_index{ 1 }; coeff_index < MaxDegree+1; coeff_index++ )
	{
		EXPECT_EQ( sum_ab_expected.GetCoeff( coeff_index ), sum_ab_exptmp.GetCoeff( coeff_index ) );
	}
}

TEST( ExpressionTemplateTests, AdditionEvaluation )
{
	auto sum_ab_exptmp{ a+b };

	ElementOfFiniteField_Poly<MaxDegree,Exponent> sum_ab{ sum_ab_exptmp };
	
	EXPECT_EQ( sum_ab, sum_ab_expected );
}

TEST( ExpressionTemplateTests, TrippleAddition )
{
	auto sum_abc_exptmp{ a+b+sum_ab_expected };

	const auto first_term{ sum_abc_exptmp.GetCoeff( 0 ) };
	EXPECT_TRUE( first_term.IsZero() );

	for( size_t coeff_index{ 1 }; coeff_index < MaxDegree+1; coeff_index++ )
	{
		EXPECT_TRUE( sum_abc_exptmp.GetCoeff( coeff_index ).IsZero() );
	}
}


TEST( ExpressionTemplateTests, ScalarMultiplication )
{
	ElementOfFiniteField<2, Exponent> scalar{
		( x_to( 1,2 ) + x_to( 1, 6 ) + x_to( 1, 7 ) ).evaluate<PolynomialOverPrimeSizeFiniteField<Prime,Exponent-1>>()
	};

	auto a_mul_scalar_exptmp{ ScalarMultiplication( a, scalar ) };

	EXPECT_EQ( a_mul_scalar_exptmp.GetCoeff( 0 ), a.GetCoeff( 0 ) * scalar );

	for( size_t coeff_index{ 1 }; coeff_index < MaxDegree+1; coeff_index++ )
	{
		EXPECT_EQ( a_mul_scalar_exptmp.GetCoeff( coeff_index ), a.GetCoeff( coeff_index ) * scalar );
	}
}


TEST( ExpressionTemplateTests, MultiplyUpToSameDegreeMulByZero )
{
	const auto zero{ a.GetAdditionInvarient() };

	auto a_mul_zero_exptmp{ MultiplyUpToSameDegree( a, zero ) };

	EXPECT_TRUE( a_mul_zero_exptmp.GetCoeff( 0 ).IsZero() );

	EXPECT_TRUE( a_mul_zero_exptmp.IsZero() );
}

TEST( ExpressionTemplateTests, MultiplyUpToSameDegreeMulByOne )
{
	const auto one{ a.GetMultiplicativeInvarient() };

	auto a_mul_one_exptmp{ MultiplyUpToSameDegree( a, one ) };

	EXPECT_EQ( a_mul_one_exptmp.GetCoeff( 0 ), a.GetCoeff( 0 ) );

	ElementOfFiniteField_Poly<MaxDegree,Exponent> a_mul_one{ a_mul_one_exptmp };
	EXPECT_EQ( a_mul_one, a );
}


TEST( ExpressionTemplateTests, MultiplyOperatorMulByZero )
{
	const auto zero{ a.GetAdditionInvarient() };

	auto a_mul_zero_exptmp{ a*zero };

	EXPECT_TRUE( a_mul_zero_exptmp.GetCoeff( 0 ).IsZero() );

	EXPECT_TRUE( a_mul_zero_exptmp.IsZero() );
}

TEST( ExpressionTemplateTests, MultiplyOperatorMulByOne )
{
	const auto one{ a.GetMultiplicativeInvarient() };

	auto a_mul_one_exptmp{ a * one };

	EXPECT_EQ( a_mul_one_exptmp.GetCoeff( 0 ), a.GetCoeff( 0 ) );

	ElementOfFiniteField_Poly<MaxDegree+MaxDegree,Exponent> a_mul_one{ a_mul_one_exptmp };
	// for( size_t a_coeff_index{ 0 }; a_coeff_index < a.GetCoeffCount(); a_coeff_index++ )
	for( size_t a_coeff_index{ 0 }; a_coeff_index < MaxDegree+1; a_coeff_index++ )
	{
		EXPECT_EQ( a_mul_one_exptmp.GetCoeff( a_coeff_index ), a.GetCoeff( a_coeff_index ) );
	}
	// for( size_t a_coeff_index{ a.GetCoeffCount() }; a_coeff_index < a_mul_one.GetCoeffCount(); a_coeff_index++ )
	for( size_t a_coeff_index{ MaxDegree+1 }; a_coeff_index < MaxDegree+MaxDegree+1; a_coeff_index++ )
	{
		EXPECT_TRUE( a_mul_one_exptmp.GetCoeff( a_coeff_index ).IsZero() );
	}
}

