#pragma once

#include "cpp-helpers/Sentinal.h"
#include "cpp-helpers/Typedef.h"

#include <array>

template <integer MaxDegree, typename FieldElements>
class PolynomialOverField
{
	static_assert( MaxDegree >= 0, "" );

public:
	static constexpr size_t GetCoeffCount()
	{
		return MaxDegree+1;
	}
	static constexpr size_t GetMaxDegree()
	{
		return MaxDegree;
	}

private:
	std::array<FieldElements, GetCoeffCount()> coefficients;
	
public:
	constexpr FieldElements GetCoeff( std::size_t index ) const
	{
		return coefficients.at( index );
	}
	constexpr void SetCoeff( const FieldElements& value, std::size_t index )
	{
		coefficients.at( index ) = value;
	}

	constexpr Sentinal<size_t, size_t, (size_t)-1> tmp_GetDegree() const
	{
		for( size_t reverse_index = 0; reverse_index < GetCoeffCount(); reverse_index++ )
		{
			if( ! GetCoeff( GetMaxDegree() - reverse_index ).IsZero() )
			{
				return (GetMaxDegree() - reverse_index);
			}
		}
		
		return (size_t)-1;
	}
	constexpr DefaultSentinal<FieldElements> Coeff_Safe( Sentinal<size_t, size_t, (size_t)-1> degree ) const
	{
		if( degree.has_value() )
		{
			return { GetCoeff( degree.value() )};
		}
		
		return { DefaultSentinal<FieldElements>{} };
	}
	
	constexpr integer GetDegree() const
	{
		for( size_t reverse_index = 0; reverse_index < GetCoeffCount(); reverse_index++ )
		{
			if( ! GetCoeff( GetMaxDegree() - reverse_index ).IsZero() )
			{
				return (integer)(GetMaxDegree() - reverse_index);
			}
		}
		
		return -1;
	}
	
	template<integer SmallerDegree>
	constexpr PolynomialOverField<SmallerDegree, FieldElements> Downsize() const
	{
		static_assert( SmallerDegree <= MaxDegree , "Downsize cannot increase the size of a polynomial." );
		
		std::array<FieldElements, SmallerDegree+1> downsize_data{ FieldElements::GetAdditionInvarient() };
		for( size_t downsize_index=0; downsize_index < downsize_data.size(); downsize_index++ )
		{
			downsize_data.at( downsize_index ) = GetCoeff( downsize_index );
		}
		
		return { downsize_data };
	}
	template<integer LargerDegree>
	constexpr PolynomialOverField<LargerDegree, FieldElements> Oversize() const
	{
		static_assert( LargerDegree >= MaxDegree, "Oversize cannot decrease the size of a polynomial." );

		PolynomialOverField<LargerDegree, FieldElements> oversized{};

		for( size_t coefficient_index{ 0 }; coefficient_index < GetCoeffCount(); coefficient_index++ )
		{
			oversized.SetCoeff( GetCoeff( coefficient_index ), coefficient_index );
		}
		
		return oversized;
	}
	template<integer OtherDegree>
	constexpr PolynomialOverField<OtherDegree, FieldElements> ToSize() const
	{
		PolynomialOverField<OtherDegree, FieldElements> output{};

		const size_t a{ GetCoeffCount() > output.GetCoeffCount() ? output.GetCoeffCount() : GetCoeffCount() };

		for( size_t coefficient_index{ 0 }; coefficient_index < a; coefficient_index++ )
		{
			output.SetCoeff( GetCoeff( coefficient_index ), coefficient_index );
		}
		
		return output;
	}
	template<>
	constexpr PolynomialOverField<MaxDegree, FieldElements> ToSize() const
	{
		return *this;
	}

	constexpr PolynomialOverField( std::array<FieldElements, GetCoeffCount()> Input )
		: coefficients( Input )
	{};
	constexpr PolynomialOverField()
		: coefficients{}
	{};

	constexpr FieldElements operator()(const FieldElements& a) const
	{
		auto running_result = GetCoeff( GetMaxDegree() );

		for( size_t coeff_index = GetMaxDegree()-1; coeff_index != (size_t)-1; coeff_index-- )
		{
			running_result = ( running_result * a ) + GetCoeff( coeff_index );
		}

		return running_result;
	}
	
	constexpr bool operator==(const PolynomialOverField<MaxDegree, FieldElements>& a) const
	{
		return coefficients == a.coefficients;
	}
	constexpr bool operator!=(const PolynomialOverField<MaxDegree, FieldElements>& a) const
	{
		return ! operator==(a);
	}
	
	constexpr static PolynomialOverField<MaxDegree, FieldElements> GetAdditionInvarient()
	{
		return PolynomialOverField<MaxDegree, FieldElements>{ std::array<FieldElements, GetCoeffCount()>{ FieldElements::GetAdditionInvarient() } };
	}
	constexpr bool IsZero() const
	{
		for( const auto& coef : coefficients )
		{
			if( !coef.IsZero() )
			{
				return false;
			}
		}
		return true;
	}
	constexpr static PolynomialOverField<MaxDegree, FieldElements> GetMultiplicativeInvarient()
	{
		auto addition_invarient = GetAdditionInvarient();
		addition_invarient.SetCoeff( FieldElements::GetMultiplicativeInvarient(), 0 );
		return addition_invarient;
	}
	constexpr bool IsOne() const
	{
		if( ! GetCoeff( 0 ).IsOne() )
		{
			return false;
		}
		for( std::size_t index{ 1 }; index < GetCoeffCount(); index++ )
		{
			if( ! GetCoeff( index ).IsZero() )
			{
				return false;
			}
		}
		return true;
	}

	constexpr PolynomialOverField<MaxDegree, FieldElements> operator+(const PolynomialOverField<MaxDegree, FieldElements>& a) const
	{
		auto return_value{ GetAdditionInvarient() };
		
		for( size_t coefficient_index = 0; coefficient_index < GetCoeffCount(); coefficient_index++ )
		{
			return_value.SetCoeff( GetCoeff( coefficient_index ) + a.GetCoeff( coefficient_index ), coefficient_index );
		}
		
		return return_value;
	}
	constexpr PolynomialOverField<MaxDegree, FieldElements> operator-(const PolynomialOverField<MaxDegree, FieldElements>& a) const
	{
		auto return_value{ GetAdditionInvarient() };

		for( size_t coefficient_index = 0; coefficient_index < GetCoeffCount(); coefficient_index++ )
		{
			return_value.SetCoeff( GetCoeff( coefficient_index ) - a.GetCoeff( coefficient_index ), coefficient_index );
		}
		
		return return_value;
	}

	constexpr PolynomialOverField<MaxDegree, FieldElements> MultiplyUpToSameDegree( const PolynomialOverField<MaxDegree, FieldElements>& a ) const
	{
		auto return_value{ PolynomialOverField<MaxDegree, FieldElements>::GetAdditionInvarient() };
		
		for( size_t a_index = 0; a_index < a.GetCoeffCount(); a_index++ )
		{
			for( size_t this_index = 0; this_index < GetCoeffCount() - a_index; this_index++ )
			{
				return_value.SetCoeff( return_value.GetCoeff( a_index + this_index ) + ( a.GetCoeff( a_index ) * GetCoeff( this_index ) ), a_index + this_index );
			}
		}

		return return_value;
	}

	constexpr PolynomialOverField<MaxDegree, FieldElements> ScalarMultiplication( const FieldElements& scalar ) const
	{
		auto return_value{ GetAdditionInvarient() };
		
		for( size_t index = 0; index < GetCoeffCount(); index++ )
		{
			return_value.SetCoeff( GetCoeff( index ) * scalar, index );
		}
	
		return return_value;
	}

	template<integer OtherMaxDegree>
	constexpr PolynomialOverField<MaxDegree+OtherMaxDegree, FieldElements> operator*( const PolynomialOverField<OtherMaxDegree, FieldElements>& a ) const
	{
		auto return_value{ PolynomialOverField<MaxDegree+OtherMaxDegree, FieldElements>::GetAdditionInvarient() };
		
		for( size_t a_index = 0; a_index < a.GetCoeffCount(); a_index++ )
		{
			for( size_t this_index = 0; this_index < GetCoeffCount(); this_index++ )
			{
				return_value.SetCoeff( return_value.GetCoeff( a_index + this_index ) + ( a.GetCoeff( a_index ) * GetCoeff( this_index ) ), a_index + this_index );
			}
		}
		
		return return_value;
	}
};


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
	std::size_t stopping_degree,
	const PolynomialOverField<LargerMaxDegree, FieldElements>& larger_term,
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

