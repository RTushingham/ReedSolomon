#pragma once

#include "PolynomialsOverField.h"

template<std::size_t NumeratorMaxDegree, std::size_t DivisorMaxDegree, typename FieldElements>
struct PolynomialLongDivisionRemainder
{
	static_assert( DivisorMaxDegree > 0, "" );
	PolynomialOverField<NumeratorMaxDegree-1, FieldElements> quotient{ PolynomialOverField<NumeratorMaxDegree-1, FieldElements>::GetAdditionInvarient() };
	PolynomialOverField<DivisorMaxDegree-1, FieldElements> remainder{ PolynomialOverField<DivisorMaxDegree-1, FieldElements>::GetAdditionInvarient() };
};

template<std::size_t OpFormMaxDegree, typename FieldElements>
constexpr PolynomialLongDivisionRemainder<OpFormMaxDegree, OpFormMaxDegree, FieldElements> LongDivideBy_Internal(
	Sentinal<size_t, size_t, (size_t)-1> remainder_degree,
	DefaultSentinal<FieldElements> remainder_leading_coefficient,
	const PolynomialOverField<OpFormMaxDegree - 1, FieldElements>& numerator,
	// These following two terms only needed for the equal degree case
	const size_t divisor_degree,
	const FieldElements divisor_leading_coefficient,
	// This only needs to be equal because CauchyCrossProduct demands same degree
	const PolynomialOverField<OpFormMaxDegree - 1, FieldElements>& divisor
)
{
	PolynomialLongDivisionRemainder<OpFormMaxDegree, OpFormMaxDegree, FieldElements> result{};

	PolynomialOverField<OpFormMaxDegree-1, FieldElements> running_remainder{ numerator };
	auto running_quotient{ PolynomialOverField<OpFormMaxDegree-1, FieldElements>::GetAdditionInvarient() };

	const auto inverse_of_divisor_leading_coefficient{ divisor_leading_coefficient.FindMultiplicativeInverse() };

	while( remainder_degree.has_value() && ( remainder_degree.value() >= divisor_degree ) )
	{
		auto new_quotient{ PolynomialOverField<OpFormMaxDegree-1, FieldElements>::GetAdditionInvarient() };

		new_quotient.SetCoeff( remainder_leading_coefficient.value() * inverse_of_divisor_leading_coefficient, remainder_degree.value() - divisor_degree );

		running_remainder = running_remainder - ( new_quotient.MultiplyUpToSameDegree( divisor ) );
		running_quotient = running_quotient + new_quotient;

		remainder_degree = running_remainder.tmp_GetDegree();
		remainder_leading_coefficient = running_remainder.Coeff_Safe( remainder_degree );
	}

	result.quotient = running_quotient;
	result.remainder = running_remainder;
	return { result };
}

// This is bugged when the difference in actual degree == NumeratorMaxDegree
template<std::size_t NumeratorMaxDegree, std::size_t DivisorMaxDegree, typename FieldElements>
constexpr PolynomialLongDivisionRemainder<NumeratorMaxDegree, NumeratorMaxDegree, FieldElements> LongDivideBy( const PolynomialOverField<NumeratorMaxDegree, FieldElements>& numerator, const PolynomialOverField<DivisorMaxDegree, FieldElements>& divisor )
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

	auto old_result{ LongDivideBy_Internal<NumeratorMaxDegree,FieldElements>( 
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
		PolynomialLongDivisionRemainder<NumeratorMaxDegree,NumeratorMaxDegree,FieldElements> result{};
		result.quotient = old_result.quotient;
		result.remainder = old_result.remainder.ToSize<NumeratorMaxDegree-1>();

		return result;
	}
}


template<std::size_t LargerMaxDegree, std::size_t SmalerMaxDegree, typename FieldElements>
struct EEAResult
{
	PolynomialOverField<SmalerMaxDegree, FieldElements> remainder{};
	PolynomialOverField<LargerMaxDegree-1, FieldElements> divisor_multiplyer{};
};

template<std::size_t LargerMaxDegree, typename FieldElements>
static constexpr EEAResult<LargerMaxDegree, LargerMaxDegree-1, FieldElements> ExtendedEuclideanAlgorithm(
	// Returns coefficients in the Bézout's identity when remainder is of stopping_degree or lower. 
	std::size_t stopping_degree,
	const PolynomialOverField<LargerMaxDegree, FieldElements>& larger_term,
	// To focus impl.
	const PolynomialOverField<LargerMaxDegree-1, FieldElements>& smaller_term
)
{
	EEAResult<LargerMaxDegree,LargerMaxDegree-1, FieldElements> result{};

	auto first_nMultiplyer{ PolynomialOverField<LargerMaxDegree-1, FieldElements>::GetAdditionInvarient() };
	result.divisor_multiplyer = PolynomialOverField<LargerMaxDegree-1, FieldElements>::GetMultiplicativeInvarient();
	
	auto larger_remainder{ larger_term.Downsize<LargerMaxDegree-1>() };
	result.remainder = smaller_term;

	auto larger_remainder_degree{ larger_term.tmp_GetDegree() };
	auto larger_remainder_leading_term{ larger_term.Coeff_Safe( larger_remainder_degree ) };
	auto smaller_remainder_degree{ result.remainder.tmp_GetDegree() };
	
	while( smaller_remainder_degree.has_value() && smaller_remainder_degree.value() > stopping_degree )
	{
		const auto long_div_res = LongDivideBy_Internal<LargerMaxDegree, FieldElements>( 
			larger_remainder_degree,
			larger_remainder_leading_term,
			larger_remainder,
			smaller_remainder_degree.value(),
			result.remainder.GetCoeff( smaller_remainder_degree.value() ),
			result.remainder
		);

		const PolynomialOverField<LargerMaxDegree-1, FieldElements> new_nMultiplyer{ 
			first_nMultiplyer - result.divisor_multiplyer.MultiplyUpToSameDegree( long_div_res.quotient )
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

