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
	//   Additionally, they have a multiplicative invariant, but it isn't useful for Reed Solomon codes.
	constexpr static PolynomialOverPrimeSizeFiniteField<Prime,MaxDegree> GetAdditionInvarient()
	{
		return PolynomialOverPrimeSizeFiniteField<Prime,MaxDegree>{ std::array<GFp, GetCapacity()>{ GFp::GetAdditionInvarient() } };
	}
	
	// In order to create a Finite Field of size p**k from polynomials over a Finite Filed of size p I need to have a modulo operator.
	//   This is because Finite Fileds of size p**k are polynomials over a Finite Field of size p modulo an irriducible polynomial of degree k+1 over a Finite Field of size p.
	// Additionally, in order to find MultiplicativeInverses in Finite Fileds of size p**k wwe need to use a variation of the Extended Euclidean Algorithm.
	//   My intended implementation of that algorithm uses this modulo operation.
	template<integer OtherMaxDegree>
	PolynomialOverPrimeSizeFiniteField<Prime,OtherMaxDegree-1> operator%(const PolynomialOverPrimeSizeFiniteField<Prime,OtherMaxDegree>& a) const
	{
		static_assert( OtherMaxDegree > 0, "" );
		
		// The modulo of 0 is undefined.
		if( a == PolynomialOverPrimeSizeFiniteField<Prime,OtherMaxDegree>::GetAdditionInvarient() )
		{
			throw;
		}
		
		// Due the a being an argument a.GetDegree cannot be a constant-expression.
		//   So, it can't be used in the return size to return less data.
		//   It can't be used to assign less data due to the multiplication within this function.
		// While finding a multiplicative inverse of an element of a Finite Fileds of size p**k this function will be used on polymonials of unknown degree.
		//   If we could assume that the degree of a was its MaxDegree then we could assign less data due to the multiplication in this function.
		//   However, the layers above this can't GetDegree to assign a smaller array and use that to pass a polynomial with smaller maxDegree to this.
		std::array<GFp, MaxDegree+OtherMaxDegree> running_remainder_coefficients{ GFp::GetAdditionInvarient() };
		for( std::size_t this_coefficients_index=0; this_coefficients_index < coefficients.size(); this_coefficients_index++ )
		{
			running_remainder_coefficients.at( this_coefficients_index ) = coefficients.at( this_coefficients_index );
		}
		PolynomialOverPrimeSizeFiniteField<Prime, MaxDegree+OtherMaxDegree-1> running_remainder{ running_remainder_coefficients };
		
		const auto a_leading_coefficient = a.coefficients.at( a.GetDegree() );
		
		while( running_remainder.GetDegree() >= a.GetDegree() )
		{
			std::array<GFp, MaxDegree> multiplying_factor_data{ 0 };
			
			multiplying_factor_data.at( running_remainder.GetDegree() - a.GetDegree() ) = running_remainder.coefficients.at( running_remainder.GetDegree() ) / a_leading_coefficient;
			
			PolynomialOverPrimeSizeFiniteField<Prime, MaxDegree-1> multiplying_factor{ multiplying_factor_data };
			
			running_remainder = running_remainder - ( multiplying_factor * a );
		}
		
		std::array<GFp, OtherMaxDegree> downsized_result_data;
		for( size_t downsize_result_index=0; downsize_result_index < OtherMaxDegree; downsize_result_index++ )
		{
			downsized_result_data.at(downsize_result_index) = running_remainder.coefficients.at(downsize_result_index);
		}
		
		return { downsized_result_data };
	}
};



