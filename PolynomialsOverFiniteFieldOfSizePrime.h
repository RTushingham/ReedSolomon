#pragma once

#include "FiniteFieldsOfSizePrime.h"

#include "Elementary Number Theory/Typedef.h"

#include <array>

// As part of building the ability to create any read solomon codes we need to create elements of finite fields (aka Galois Fields)
//   All finite fields are of the size p**k where p and k are positive integers, and p is a prime.
//   If k > 1 then the elements need to be expressable as polynomials modulo an irriducible polynomial over a finite filed of size p.
// In order to do that I need to be able to create polynomials over a finite filed of size p.
//   I would like to represent these as having a fixed maxium number of coefficients, as opposed to the normal mathematical notation.
//   As not all elements have multiplicative inverses, this is just a ring, so no division operation exists

template <integer Prime, integer MaxDegree>
class PolynomialOverPrimeSizeFiniteField
{
	// static_assert( IsPrime(Prime) );
	static_assert( MaxDegree >= 0, "" );
	
	// Galois Fields of size p
	using GFp = ElementOfFiniteFieldP<Prime>;

public:
	static constexpr size_t GetCapacity()
	{
		return MaxDegree+1;
	}
	std::array<GFp, GetCapacity()> coefficients;

	static constexpr size_t GetMaxDegree()
	{
		return MaxDegree;
	}
	constexpr size_t GetDegree() const
	{
		for( size_t coefficient_index = coefficients.size()-1; coefficient_index>=0; coefficient_index-- )
		{
			if( coefficients.at(coefficient_index) != GFp::GetAdditionInvarient() )
			{
				return coefficient_index;
			}
		}
		
		return (size_t)-1;
	}
	
	template<integer SmallerDegree>
	PolynomialOverPrimeSizeFiniteField<Prime,SmallerDegree>	Downsize() const
	{
		static_assert( SmallerDegree <= MaxDegree , "" );
		
		std::array<GFp, SmallerDegree+1> downsize_data;
		for( size_t downsize_index=0; downsize_index < downsize_data.size(); downsize_index++ )
		{
			downsize_data.at(downsize_index) = coefficients.at(downsize_index);
		}
		
		return { downsize_data };
	}

	template<integer LargerDegree>
	PolynomialOverPrimeSizeFiniteField<Prime,LargerDegree>Oversize() const
	{
		static_assert( LargerDegree >= MaxDegree, "" );
		
		std::array<GFp, LargerDegree+1> oversize_result_data;
		for( size_t coefficient_index=0; coefficient_index < coefficients.size(); coefficient_index++ )
		{
			oversize_result_data.at(coefficient_index) = coefficients.at(coefficient_index);
		}
		
		return { oversize_result_data };
	}

public:
	PolynomialOverPrimeSizeFiniteField( std::array<GFp, GetCapacity()> Input )
		: coefficients( Input )
	{};
	
	constexpr bool operator==(const PolynomialOverPrimeSizeFiniteField<Prime,MaxDegree>& a) const
	{
		return coefficients == a.coefficients;
	}
	constexpr bool operator!=(const PolynomialOverPrimeSizeFiniteField<Prime,MaxDegree>& a) const
	{
		return ! operator==(a);
	}
	
	constexpr PolynomialOverPrimeSizeFiniteField<Prime,MaxDegree> operator+(const PolynomialOverPrimeSizeFiniteField<Prime,MaxDegree>& a) const
	{
		std::array<GFp, GetCapacity()> new_coefficients{ GFp::GetAdditionInvarient() };
		
		for( size_t coefficient_index = 0; coefficient_index < new_coefficients.size(); coefficient_index++ )
		{
			new_coefficients.at(coefficient_index) = coefficients.at(coefficient_index) + a.coefficients.at(coefficient_index);
		}
		
		return { new_coefficients };
	}
	constexpr PolynomialOverPrimeSizeFiniteField<Prime,MaxDegree> operator-(const PolynomialOverPrimeSizeFiniteField<Prime,MaxDegree>& a) const
	{
		std::array<GFp, GetCapacity()> new_coefficients{ GFp::GetAdditionInvarient() };
		
		for( size_t coefficient_index = 0; coefficient_index < new_coefficients.size(); coefficient_index++ )
		{
			new_coefficients.at(coefficient_index) = coefficients.at(coefficient_index) - a.coefficients.at(coefficient_index);
		}
		
		return { new_coefficients };
	}
	
	template<integer OtherMaxDegree>
	constexpr PolynomialOverPrimeSizeFiniteField<Prime,MaxDegree+OtherMaxDegree> operator*(const PolynomialOverPrimeSizeFiniteField<Prime,OtherMaxDegree>& a) const
	{
		std::array<GFp, PolynomialOverPrimeSizeFiniteField<Prime,MaxDegree+OtherMaxDegree>::GetCapacity()> new_coefficients{ GFp::GetAdditionInvarient() };
		
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
	//   Additionally, they have a multiplicative invariant, but due to MaxDegree changing size isn't easy to use in this paradigm.
	constexpr static PolynomialOverPrimeSizeFiniteField<Prime,MaxDegree> GetAdditionInvarient()
	{
		return PolynomialOverPrimeSizeFiniteField<Prime,MaxDegree>{ std::array<GFp, GetCapacity()>{ GFp::GetAdditionInvarient() } };
	}
	
	template<integer DivisorMaxDegree>
	struct PolynomialLongDivisionRemainder
	{
		static_assert( DivisorMaxDegree > 0, "" );
		PolynomialOverPrimeSizeFiniteField<Prime,MaxDegree-1> quotient{ PolynomialOverPrimeSizeFiniteField<Prime,MaxDegree-1>::GetAdditionInvarient() };
		PolynomialOverPrimeSizeFiniteField<Prime,DivisorMaxDegree-1> remainder{ PolynomialOverPrimeSizeFiniteField<Prime,DivisorMaxDegree-1>::GetAdditionInvarient() };
	};
	
	// Additionally, in order to find MultiplicativeInverses in Finite Fileds of size p**k we need to use a variation of the Extended Euclidean Algorithm.
	//   My intended implementation of that algorithm uses polynomial long division.
	template<integer DivisorMaxDegree>
	constexpr PolynomialLongDivisionRemainder<DivisorMaxDegree> LongDivideBy( const PolynomialOverPrimeSizeFiniteField<Prime,DivisorMaxDegree>& divisor ) const
	{
		static_assert( DivisorMaxDegree > 0, "" );
		
		// Long division by 0 is undefined.
		if( divisor == PolynomialOverPrimeSizeFiniteField<Prime,DivisorMaxDegree>::GetAdditionInvarient() )
		{
			throw;
		}

		// Due the a being an argument a.GetDegree cannot be a constant-expression.
		//   So, it can't be used in the return size to return less data.
		//   It can't be used to assign less data due to the multiplication within this function.
		// While finding a multiplicative inverse of an element of a Finite Fileds of size p**k this function will be used on polymonials of unknown degree.
		//   If we could assume that the degree of a was its MaxDegree then we could assign less data due to the multiplication in this function.
		//   However, the layers above this can't GetDegree to assign a smaller array and use that to pass a polynomial with smaller maxDegree to this.
		PolynomialOverPrimeSizeFiniteField<Prime, MaxDegree+DivisorMaxDegree-1> running_remainder{ Oversize<MaxDegree+DivisorMaxDegree-1>() };
		PolynomialOverPrimeSizeFiniteField<Prime, MaxDegree-1> running_quotient{ PolynomialOverPrimeSizeFiniteField<Prime, MaxDegree-1>::GetAdditionInvarient() };

		const auto divisor_leading_coefficient = divisor.coefficients.at( divisor.GetDegree() );

		while( running_remainder.GetDegree() >= divisor.GetDegree() )
		{
			PolynomialOverPrimeSizeFiniteField<Prime, MaxDegree-1> new_quotient{ PolynomialOverPrimeSizeFiniteField<Prime, MaxDegree-1>::GetAdditionInvarient() };

			new_quotient.coefficients.at( running_remainder.GetDegree() - divisor.GetDegree() ) = running_remainder.coefficients.at( running_remainder.GetDegree() ) / divisor_leading_coefficient;

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
	constexpr PolynomialOverPrimeSizeFiniteField<Prime,OtherMaxDegree-1> operator%(const PolynomialOverPrimeSizeFiniteField<Prime,OtherMaxDegree>& a) const
	{
		return LongDivideBy( a ).remainder;
	}
};
