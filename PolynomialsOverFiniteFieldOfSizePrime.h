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
	
	using GFp = ElementOfFiniteFieldP<Prime>;

public:
	static constexpr size_t GetCapacity()
	{
		return MaxDegree+1;
	}
	std::array<GFp, GetCapacity()> coefficients;

public:
	PolynomialOverPrimeSizeFiniteField( std::array<GFp, GetCapacity()> Input )
		: coefficients( Input )
	{};
	
	constexpr bool operator==(const PolynomialOverPrimeSizeFiniteField<Prime,MaxDegree>& a) const
	{
		return coefficients == a.coefficients;
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
};

