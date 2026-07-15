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
		
		PolynomialOverField<SmallerDegree, FieldElements> output{};

		for( size_t downsize_index=0; downsize_index < output.GetCoeffCount(); downsize_index++ )
		{
			output.SetCoeff( GetCoeff( downsize_index ), downsize_index );
		}
		
		return output;
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

	constexpr PolynomialOverField<MaxDegree-1, FieldElements> MultiplicationExcessTerms( const PolynomialOverField<MaxDegree, FieldElements>& a ) const
	{
		auto return_value{ PolynomialOverField<MaxDegree-1, FieldElements>::GetAdditionInvarient() };
		
		for( size_t a_index = 1; a_index < a.GetCoeffCount(); a_index++ )
		{
			for( size_t this_index = GetCoeffCount() - a_index; this_index < GetCoeffCount(); this_index++ )
			{
				return_value.SetCoeff( return_value.GetCoeff( a_index + this_index - GetCoeffCount() ) + ( a.GetCoeff( a_index ) * GetCoeff( this_index ) ), a_index + this_index - GetCoeffCount() );
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

