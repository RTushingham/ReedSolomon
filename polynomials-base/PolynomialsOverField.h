#pragma once

#include "cpp-helpers/Typedef.h"

#include <array>

template <integer MaxDegree, typename FieldElements>
class PolynomialOverField
{
	static_assert( MaxDegree >= 0, "" );
	
public:
	static constexpr size_t GetCapacity()
	{
		return MaxDegree+1;
	}
	std::array<FieldElements, GetCapacity()> coefficients;

	static constexpr size_t GetMaxDegree()
	{
		return MaxDegree;
	}
	constexpr integer GetDegree() const
	{
		for( size_t reverse_index = 0; reverse_index<coefficients.size(); reverse_index++ )
		{
			if( coefficients.at(coefficients.size() - 1 - reverse_index) != FieldElements::GetAdditionInvarient() )
			{
				return (integer)(coefficients.size() - 1 - reverse_index);
			}
		}
		
		return -1;
	}
	
	template<integer SmallerDegree>
	constexpr PolynomialOverField<SmallerDegree, FieldElements> Downsize() const
	{
		static_assert( SmallerDegree <= MaxDegree , "" );
		
		std::array<FieldElements, SmallerDegree+1> downsize_data{ FieldElements::GetAdditionInvarient() };
		for( size_t downsize_index=0; downsize_index < downsize_data.size(); downsize_index++ )
		{
			downsize_data.at(downsize_index) = coefficients.at(downsize_index);
		}
		
		return { downsize_data };
	}

	template<integer LargerDegree>
	constexpr PolynomialOverField<LargerDegree, FieldElements>Oversize() const
	{
		static_assert( LargerDegree >= MaxDegree, "" );
		
		std::array<FieldElements, LargerDegree+1> oversize_result_data{ FieldElements::GetAdditionInvarient() };
		for( size_t coefficient_index=0; coefficient_index < coefficients.size(); coefficient_index++ )
		{
			oversize_result_data.at(coefficient_index) = coefficients.at(coefficient_index);
		}
		
		return { oversize_result_data };
	}

public:
	constexpr PolynomialOverField( std::array<FieldElements, GetCapacity()> Input )
		: coefficients( Input )
	{};
	constexpr PolynomialOverField()
		: coefficients{}
	{};

	constexpr FieldElements operator()(const FieldElements& a) const
	{
		auto running_multiple = a;
		FieldElements running_result = coefficients.at( 0 );
		for( size_t coefficient_index =1; coefficient_index < coefficients.size(); coefficient_index++ )
		{
			running_result = running_result + ( coefficients.at( coefficient_index ) * running_multiple );
			running_multiple = running_multiple * a;
		}

		return running_result;
	}
	
	constexpr bool operator==(const PolynomialOverField<MaxDegree, FieldElements>& a) const
	{
		for( std::size_t index{ 0 }; index<coefficients.size(); index++ )
		{
			if( coefficients.at(index) != a.coefficients.at(index) )
				return false;
		}
		return true;
	}
	constexpr bool operator!=(const PolynomialOverField<MaxDegree, FieldElements>& a) const
	{
		return ! operator==(a);
	}
	
	constexpr PolynomialOverField<MaxDegree, FieldElements> operator+(const PolynomialOverField<MaxDegree, FieldElements>& a) const
	{
		std::array<FieldElements, GetCapacity()> new_coefficients{ FieldElements::GetAdditionInvarient() };
		
		for( size_t coefficient_index = 0; coefficient_index < new_coefficients.size(); coefficient_index++ )
		{
			new_coefficients.at(coefficient_index) = coefficients.at(coefficient_index) + a.coefficients.at(coefficient_index);
		}
		
		return { new_coefficients };
	}
	constexpr PolynomialOverField<MaxDegree, FieldElements> operator-(const PolynomialOverField<MaxDegree, FieldElements>& a) const
	{
		std::array<FieldElements, GetCapacity()> new_coefficients{ FieldElements::GetAdditionInvarient() };
		
		for( size_t coefficient_index = 0; coefficient_index < new_coefficients.size(); coefficient_index++ )
		{
			new_coefficients.at(coefficient_index) = coefficients.at(coefficient_index) - a.coefficients.at(coefficient_index);
		}
		
		return { new_coefficients };
	}
	
	template<integer OtherMaxDegree>
	constexpr PolynomialOverField<MaxDegree+OtherMaxDegree, FieldElements> operator*(const PolynomialOverField<OtherMaxDegree, FieldElements>& a) const
	{
		std::array<FieldElements, PolynomialOverField<MaxDegree+OtherMaxDegree, FieldElements>::GetCapacity()> new_coefficients{ FieldElements::GetAdditionInvarient() };
		
		for( size_t a_index = 0; a_index < a.coefficients.size(); a_index++ )
		{
			for( size_t this_index = 0; this_index < coefficients.size(); this_index++ )
			{
				new_coefficients.at( a_index + this_index ) = new_coefficients.at( a_index + this_index ) + ( a.coefficients.at( a_index ) * coefficients.at( this_index ) );
			}
		}
		
		return { new_coefficients };		
	}
	
	// Polynomials over prime sized Finite Field are a Ring.
	constexpr static PolynomialOverField<MaxDegree, FieldElements> GetAdditionInvarient()
	{
		return PolynomialOverField<MaxDegree, FieldElements>{ std::array<FieldElements, GetCapacity()>{ FieldElements::GetAdditionInvarient() } };
	}
	constexpr static PolynomialOverField<MaxDegree, FieldElements> GetMultiplicativeInvarient()
	{
		auto addition_invarient = GetAdditionInvarient();
		addition_invarient.coefficients.at( 0 ) = FieldElements::GetMultiplicativeInvarient();
		return addition_invarient;
	}
	
	template<integer DivisorMaxDegree>
	struct PolynomialLongDivisionRemainder
	{
		static_assert( DivisorMaxDegree > 0, "" );
		PolynomialOverField<MaxDegree-1, FieldElements> quotient{ PolynomialOverField<MaxDegree-1, FieldElements>::GetAdditionInvarient() };
		PolynomialOverField<DivisorMaxDegree-1, FieldElements> remainder{ PolynomialOverField<DivisorMaxDegree-1, FieldElements>::GetAdditionInvarient() };
	};
	
	// Additionally, in order to find MultiplicativeInverses in Finite Fileds of size p**k we need to use a variation of the Extended Euclidean Algorithm.
	//   My intended implementation of that algorithm uses polynomial long division.
	template<integer DivisorMaxDegree>
	constexpr PolynomialLongDivisionRemainder<DivisorMaxDegree> LongDivideBy( const PolynomialOverField<DivisorMaxDegree, FieldElements>& divisor ) const
	{
		static_assert( DivisorMaxDegree > 0, "" );
		
		// Long division by 0 is undefined.
		if( divisor == PolynomialOverField<DivisorMaxDegree, FieldElements>::GetAdditionInvarient() )
		{
			throw;
		}

		// Due the a being an argument a.GetDegree cannot be a constant-expression.
		//   So, it can't be used in the return size to return less data.
		//   It can't be used to assign less data due to the multiplication within this function.
		// While finding a multiplicative inverse of an element of a Finite Fileds of size p**k this function will be used on polymonials of unknown degree.
		//   If we could assume that the degree of a was its MaxDegree then we could assign less data due to the multiplication in this function.
		//   However, the layers above this can't GetDegree to assign a smaller array and use that to pass a polynomial with smaller maxDegree to this.
		PolynomialOverField<MaxDegree+DivisorMaxDegree-1, FieldElements> running_remainder{ Oversize<MaxDegree+DivisorMaxDegree-1>() };
		PolynomialOverField<MaxDegree-1, FieldElements> running_quotient{ PolynomialOverField<MaxDegree-1, FieldElements>::GetAdditionInvarient() };

		const auto divisor_leading_coefficient = divisor.coefficients.at( (std::size_t)(divisor.GetDegree()) );

		while( (running_remainder != PolynomialOverField<MaxDegree+DivisorMaxDegree-1, FieldElements>::GetAdditionInvarient()) && (running_remainder.GetDegree() >= divisor.GetDegree()) )
		{
			PolynomialOverField<MaxDegree-1, FieldElements> new_quotient{ PolynomialOverField<MaxDegree-1, FieldElements>::GetAdditionInvarient() };

			new_quotient.coefficients.at( (std::size_t)(running_remainder.GetDegree() - divisor.GetDegree()) ) = running_remainder.coefficients.at( (std::size_t)running_remainder.GetDegree() ) / divisor_leading_coefficient;

			running_remainder = running_remainder - ( new_quotient * divisor );
			running_quotient = running_quotient + new_quotient;
		}

		PolynomialLongDivisionRemainder<DivisorMaxDegree> result{};
		result.quotient = running_quotient;
		result.remainder = running_remainder.Downsize<DivisorMaxDegree-1>();
		return { result };
	}
	
	// In order to create a Finite Field of size p**k from polynomials over a Finite Filed of size p I need to have a modulo operator.
	//   This is because Finite Fileds of size p**k are polynomials over a Finite Field of size p modulo an irriducible polynomial of degree k+1 over a Finite Field of size p.
	template<integer OtherMaxDegree>
	constexpr PolynomialOverField<OtherMaxDegree-1, FieldElements> operator%(const PolynomialOverField<OtherMaxDegree, FieldElements>& a) const
	{
		return LongDivideBy( a ).remainder;
	}
};
