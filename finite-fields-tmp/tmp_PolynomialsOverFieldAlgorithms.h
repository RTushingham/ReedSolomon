#pragma once

#include "tmp_FiniteFieldsOfSizePrimeToAPower.h"

#include "cpp-helpers/Sentinal.h"
#include "cpp-helpers/Typedef.h"

#include <array>

template<std::size_t NumeratorMaxDegree, std::size_t DivisorMaxDegree, std::size_t Exponent>
struct tmp_PolynomialLongDivisionRemainder
{
	static_assert( DivisorMaxDegree > 0, "" );
	ElementOfFiniteField_Poly<NumeratorMaxDegree-1, Exponent> quotient{ ElementOfFiniteField_Poly<NumeratorMaxDegree-1, Exponent>::GetAdditionInvarient() };
	ElementOfFiniteField_Poly<DivisorMaxDegree-1, Exponent> remainder{ ElementOfFiniteField_Poly<DivisorMaxDegree-1, Exponent>::GetAdditionInvarient() };
};

template<std::size_t OpFormMaxDegree, std::size_t Exponent>
constexpr tmp_PolynomialLongDivisionRemainder<OpFormMaxDegree, OpFormMaxDegree, Exponent> tmp_LongDivideBy_Internal(
	Sentinal<size_t, size_t, (size_t)-1> remainder_degree,
	DefaultSentinal<ElementOfFiniteField<2,Exponent>> remainder_leading_coefficient,
	const ElementOfFiniteField_Poly<OpFormMaxDegree - 1, Exponent>& numerator,
	// These following two terms only needed for the equal degree case
	const size_t divisor_degree,
	const ElementOfFiniteField<2,Exponent> divisor_leading_coefficient,
	// This only needs to be equal because CauchyCrossProduct demands same degree
	const ElementOfFiniteField_Poly<OpFormMaxDegree - 1, Exponent>& divisor
)
{
	tmp_PolynomialLongDivisionRemainder<OpFormMaxDegree, OpFormMaxDegree, Exponent> result{};

	ElementOfFiniteField_Poly<OpFormMaxDegree-1, Exponent> running_remainder{ numerator };
	auto running_quotient{ ElementOfFiniteField_Poly<OpFormMaxDegree-1, Exponent>::GetAdditionInvarient() };

	const auto inverse_of_divisor_leading_coefficient{ divisor_leading_coefficient.FindMultiplicativeInverse() };

	while( remainder_degree.has_value() && ( remainder_degree.value() >= divisor_degree ) )
	{
		auto new_quotient{ ElementOfFiniteField_Poly<OpFormMaxDegree-1, Exponent>::GetAdditionInvarient() };

		new_quotient.SetCoeff( remainder_leading_coefficient.value() * inverse_of_divisor_leading_coefficient, remainder_degree.value() - divisor_degree );

		running_remainder = running_remainder - ( MultiplyUpToSameDegree( new_quotient, divisor ) );
		running_quotient = running_quotient + new_quotient;

		remainder_degree = running_remainder.tmp_GetDegree();
		remainder_leading_coefficient = running_remainder.Coeff_Safe( remainder_degree );
	}

	result.quotient = running_quotient;
	result.remainder = running_remainder;
	return { result };
}

// This is bugged when the difference in actual degree == NumeratorMaxDegree
template<std::size_t NumeratorMaxDegree, std::size_t DivisorMaxDegree, std::size_t Exponent>
constexpr tmp_PolynomialLongDivisionRemainder<NumeratorMaxDegree, NumeratorMaxDegree, Exponent> tmp_LongDivideBy( const ElementOfFiniteField_Poly<NumeratorMaxDegree, Exponent>& numerator, const ElementOfFiniteField_Poly<DivisorMaxDegree, Exponent>& divisor )
{
	static_assert( DivisorMaxDegree > 0, "" );
	static_assert( NumeratorMaxDegree >= DivisorMaxDegree, "To focus code maintainance time I am restricting ovvered use cases. NumeratorMaxDegree isn't actualy degree, so this unsupported case can be non-trivial." );

	const auto divisor_degree{ divisor.tmp_GetDegree() };
	if( !divisor_degree.has_value() )
	{
		// Long division by 0 is undefined.
		throw;
	}
	const auto divisor_leading_coefficient = divisor.GetCoeff( divisor_degree.value() );

	auto remainder_degree{ numerator.tmp_GetDegree() };
	auto remainder_leading_coefficient{ numerator.Coeff_Safe( remainder_degree ) };

	auto old_result{ tmp_LongDivideBy_Internal<NumeratorMaxDegree,Exponent>( 
		remainder_degree,
		remainder_leading_coefficient,
		numerator.Downsize<NumeratorMaxDegree-1>(),
		divisor_degree.value(),
		divisor_leading_coefficient,
		divisor.ToSize<NumeratorMaxDegree-1>()
	) };

	if constexpr( DivisorMaxDegree == NumeratorMaxDegree )
	{
		return old_result;
	}
	else
	{
		tmp_PolynomialLongDivisionRemainder<NumeratorMaxDegree,NumeratorMaxDegree,Exponent> result{};
		result.quotient = old_result.quotient;
		result.remainder = old_result.remainder.ToSize<NumeratorMaxDegree-1>();

		return result;
	}
}


template<std::size_t LargerMaxDegree, std::size_t SmalerMaxDegree, std::size_t Exponent>
struct tmp_EEAResult
{
	ElementOfFiniteField_Poly<SmalerMaxDegree, Exponent> remainder{};
	ElementOfFiniteField_Poly<LargerMaxDegree-1, Exponent> divisor_multiplyer{};
};

template<std::size_t LargerMaxDegree, std::size_t Exponent>
static constexpr tmp_EEAResult<LargerMaxDegree, LargerMaxDegree-1, Exponent> tmp_ExtendedEuclideanAlgorithm(
	// Returns coefficients in the Bézout's identity when remainder is of stopping_degree or lower. 
	std::size_t stopping_degree,
	const ElementOfFiniteField_Poly<LargerMaxDegree, Exponent>& larger_term,
	// To focus impl.
	const ElementOfFiniteField_Poly<LargerMaxDegree-1, Exponent>& smaller_term
)
{
	tmp_EEAResult<LargerMaxDegree,LargerMaxDegree-1, Exponent> result{};

	auto first_nMultiplyer{ ElementOfFiniteField_Poly<LargerMaxDegree-1, Exponent>::GetAdditionInvarient() };
	result.divisor_multiplyer = ElementOfFiniteField_Poly<LargerMaxDegree-1, Exponent>::GetMultiplicativeInvarient();
	
	ElementOfFiniteField_Poly<LargerMaxDegree-1, Exponent> larger_remainder{ larger_term.Downsize<LargerMaxDegree-1>() };
	result.remainder = smaller_term;

	auto larger_remainder_degree{ larger_term.tmp_GetDegree() };
	auto larger_remainder_leading_term{ larger_term.Coeff_Safe( larger_remainder_degree ) };
	auto smaller_remainder_degree{ result.remainder.tmp_GetDegree() };
	
	while( smaller_remainder_degree.has_value() && smaller_remainder_degree.value() > stopping_degree )
	{
		const auto long_div_res = tmp_LongDivideBy_Internal<LargerMaxDegree, Exponent>( 
			larger_remainder_degree,
			larger_remainder_leading_term,
			larger_remainder,
			smaller_remainder_degree.value(),
			result.remainder.GetCoeff( smaller_remainder_degree.value() ),
			result.remainder
		);

		const ElementOfFiniteField_Poly<LargerMaxDegree-1, Exponent> new_nMultiplyer{ 
			first_nMultiplyer - MultiplyUpToSameDegree( result.divisor_multiplyer, long_div_res.quotient )
		};
		
		larger_remainder = result.remainder;
		result.remainder = long_div_res.remainder;

		larger_remainder_degree = larger_remainder.tmp_GetDegree();
		larger_remainder_leading_term = larger_remainder.Coeff_Safe( larger_remainder_degree );
		smaller_remainder_degree = result.remainder.tmp_GetDegree();

		first_nMultiplyer = result.divisor_multiplyer;
		result.divisor_multiplyer = new_nMultiplyer;
	}
	
	return result;
}

