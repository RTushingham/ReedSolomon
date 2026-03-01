#pragma once

#include "PolynomialsOverFiniteFieldOfSizePrime.h"

#include "cpp-helpers/Typedef.h"

// As part of building the ability to create any read solomon codes we need to create elements of finite fields (aka Galois Fields)
//   All finite fields are of the size p**k where p and k are positive integers, and p is a prime.
//   For k > 1 then the elements are polynomials over a finite field of size p modulo an irriducible polynomial over a finite filed of size p of degree k.

template <integer Prime, integer Exponent>
class ElementOfFiniteField
{
	// static_assert( IsPrime(Prime) );
	static_assert( Exponent > 0, "" );
	
	// // Polynomials over Galois Fields of size p
	// template<integer Degree>
	// using PolynomialOverPrimeSizeFiniteField<Prime,Degree> = PolynomialOverPrimeSizeFiniteField<Prime,Degree>;

	PolynomialOverPrimeSizeFiniteField<Prime,Exponent> irriducible_polynomial;	

public:
	PolynomialOverPrimeSizeFiniteField<Prime,Exponent-1> value;
	
public:
	template<integer OtherMaxDegree>
	constexpr ElementOfFiniteField<Prime,Exponent>( const PolynomialOverPrimeSizeFiniteField<Prime,OtherMaxDegree>& value, const PolynomialOverPrimeSizeFiniteField<Prime,Exponent>& irriducible_polynomial )
		: value { value % irriducible_polynomial }
		, irriducible_polynomial{ irriducible_polynomial }
	{
		// if( !IsIrriducible( irriducible_polynomial ) )
		// 	throw;
	}

	// Only used for value-initialization
	//   - leaves class in an error state.
	constexpr ElementOfFiniteField<Prime,Exponent>()
		: value{}
		, irriducible_polynomial{}
	{}
	
	constexpr ElementOfFiniteField<Prime,Exponent>& operator=(const ElementOfFiniteField<Prime,Exponent>& a){
		value = a.value;
		irriducible_polynomial = a.irriducible_polynomial;
		return *this;
	}
	
	constexpr bool operator==(const ElementOfFiniteField<Prime, Exponent>& a) const{
		return value == a.value && irriducible_polynomial == a.irriducible_polynomial;
	}
	constexpr bool operator!=(const ElementOfFiniteField<Prime, Exponent>& a) const
	{
		return ! operator==(a);
	}
	
	constexpr ElementOfFiniteField<Prime, Exponent> operator+(const ElementOfFiniteField<Prime, Exponent>& a) const{
		return {value + a.value, irriducible_polynomial};
	}
	constexpr ElementOfFiniteField<Prime, Exponent> operator-(const ElementOfFiniteField<Prime, Exponent>& a) const{
		return {value - a.value, irriducible_polynomial};
	}
	constexpr ElementOfFiniteField<Prime, Exponent> operator*(const ElementOfFiniteField<Prime, Exponent>& a) const{
		return {(value * a.value) % irriducible_polynomial, irriducible_polynomial};
	}

	constexpr ElementOfFiniteField<Prime, Exponent> FindMultiplicativeInverse() const
	{
	    if( value == value.GetAdditionInvarient() )
	    {
	        throw;
	    }

	    std::vector<PolynomialOverPrimeSizeFiniteField<Prime,Exponent>> remainders{ irriducible_polynomial, value.Oversize<Exponent>() };
	    std::vector<PolynomialOverPrimeSizeFiniteField<Prime,Exponent>> multiplying_factors{};
	    
	    PolynomialOverPrimeSizeFiniteField<Prime,Exponent> larger_remainder = remainders.at(0);
	    PolynomialOverPrimeSizeFiniteField<Prime,Exponent> smaller_remainder = remainders.at(1);
	    
	    while(remainders.back().GetDegree() > 0)
	    {
			const auto result = larger_remainder.LongDivideBy( smaller_remainder );

	        remainders.push_back( result.remainder.Oversize<Exponent>() );

			multiplying_factors.push_back( result.quotient.Oversize<Exponent>() );
	        
	        larger_remainder = smaller_remainder;
	        smaller_remainder = remainders.back();
	    }
	    
		const PolynomialOverPrimeSizeFiniteField<Prime, 0> final_correcting_factor( 
			std::array<ElementOfFiniteFieldP<Prime>, PolynomialOverPrimeSizeFiniteField<Prime, 0>::GetCapacity()>{
				smaller_remainder.coefficients.at( 0 ).FindMultiplicativeInverse()
			}
		);
 
	    std::vector<PolynomialOverPrimeSizeFiniteField<Prime, Exponent-1>> nMultiplyer{
			PolynomialOverPrimeSizeFiniteField<Prime, Exponent-1>::GetAdditionInvarient(), 
			PolynomialOverPrimeSizeFiniteField<Prime, Exponent-1>::GetMultiplicativeInvarient()
		};
	    
		// The final form of this algorithm fins two polynomains F and G such that:
		//   F*remainders[0] + G*remainders[1] = remainders.back() = a = F*irriducible_polynomial + G*value
		//  (where a isn element of GFp)
		// If g == G mod irriducible_polynomail then there is a polynomial H such that:
		//   a = F*irriducible_polynomial + (H*irriducible_polynomial + g)*value
		//     = (F + H*value)*irriducible_polynomial + g*value
		// So, g and G can both be used to find the multiplicative inverse of value.
		// Furthermore, because 
		//   nMultiplier[i+2] =  nMultiplier[i] - nMultiplier[i+1] * multiplying_factors[i]
		// We can store the result of nMultiplyer modulo irriducible_polynomial at each i and get a result 
		//   which equals the result we would have otherwise attained otherwise, just modulo irriducible_polynomial.
		//
		// Because the degree of G is at most the degree of irriducible_polynomial, it isn't necessary to call the modulo
		//   operation at each step, because we know we can store the coefficients within a known size.
		// However, at this stage I just want to create a version which works then refine later.
	    for( std::size_t multiplying_factors_index = 0; multiplying_factors_index<multiplying_factors.size(); multiplying_factors_index++ )
	    {
	        nMultiplyer.push_back( nMultiplyer.at(multiplying_factors_index) - ( nMultiplyer.at(multiplying_factors_index+1) * multiplying_factors.at(multiplying_factors_index) ) % irriducible_polynomial );
	    }

	    return ElementOfFiniteField<Prime, Exponent>{ nMultiplyer.back() * final_correcting_factor, irriducible_polynomial };
	}
	
	constexpr ElementOfFiniteField<Prime, Exponent> operator/(const ElementOfFiniteField<Prime, Exponent>& a) const{
		return (*this)*a.FindMultiplicativeInverse();
	}
	
	constexpr static ElementOfFiniteField<Prime, Exponent> GetAdditionInvarient( const PolynomialOverPrimeSizeFiniteField<Prime,Exponent>& irriducible_polynomial )
	{
		return ElementOfFiniteField<Prime, Exponent>( PolynomialOverPrimeSizeFiniteField<Prime,Exponent-1>::GetAdditionInvarient(), irriducible_polynomial );
	}
	constexpr ElementOfFiniteField<Prime, Exponent> GetAdditionInvarient() const
	{
		return GetAdditionInvarient( irriducible_polynomial );
	}
	constexpr static ElementOfFiniteField<Prime, Exponent> GetMultiplicativeInvarient( const PolynomialOverPrimeSizeFiniteField<Prime,Exponent>& irriducible_polynomial )
	{
		return ElementOfFiniteField<Prime, Exponent>{ PolynomialOverPrimeSizeFiniteField<Prime,Exponent-1>::GetMultiplicativeInvarient(), irriducible_polynomial };
	}
	constexpr ElementOfFiniteField<Prime, Exponent> GetMultiplicativeInvarient() const
	{
		return GetMultiplicativeInvarient( irriducible_polynomial );
	}
};

