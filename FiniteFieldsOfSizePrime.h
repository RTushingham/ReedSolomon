#include "Elementary Number Theory/Typedef.h"

#include <vector>

// As part of building the ability to create any read solomon codes we need to create elements of finite fields (aka Galois Fields)
//   All finite fields are of the size p**k where p and k are positive integers, and p is a prime.
//   If k > 1 then the elements need to be expressable as polynomials modulo an irriducible polynomial over a finite filed of size p.
// In order to do that I need to start off with finite fields of size p.
//   This is just integers modulo p.

template <integer Prime>
class ElementOfFiniteFieldP
{
	// static_assert( IsPrime(Prime) );
	
public:
	integer value;
	
public:
	constexpr ElementOfFiniteFieldP(integer InputValue)
		: value { ( (InputValue % Prime) + Prime) % Prime}
	{};
	
	constexpr ElementOfFiniteFieldP()
		: ElementOfFiniteFieldP( (integer)0 )
	{};
	
	constexpr bool operator==(const ElementOfFiniteFieldP<Prime>& a) const{
		return ( value + a.value) % Prime;
	}
	
	constexpr ElementOfFiniteFieldP<Prime> operator+(const ElementOfFiniteFieldP<Prime>& a) const{
		return ( value + a.value) % Prime;
	}
	constexpr ElementOfFiniteFieldP<Prime> operator-(const ElementOfFiniteFieldP<Prime>& a) const{
		return (Prime - a.value + value) % Prime;
	}
	constexpr ElementOfFiniteFieldP<Prime> operator*(const ElementOfFiniteFieldP<Prime>& a) const{
		return ((value * a.value) % Prime);
	}
	
	ElementOfFiniteFieldP<Prime> FindMultiplicativeInverse() const
	{
		// This is necessary for Fp to be a field
		//   For all n such that 0 < n < p, we have that n and p are coprime.
		//   Because they are coprime the Greatest Common Denominator is 1.
		//   Using the Extended Euclidean Algorithm we can find an a and b such that a*p + b*n = 1.
		//   Which is equivalent to 1 = a*p + (-b)n which implies (-b)n = 1 modulo p
		//   So ( -b % p ) will be multiplicative inverse of n within this finite field.
		
		if( value==0 )
		{
			throw;
		}
		
		std::vector<integer> remainders{ Prime, value };
		std::vector<integer> multiplying_factors{};
		
		integer larger_remainder = remainders.at(0);
		integer smaller_remainder = remainders.at(1);
		do
		{
			remainders.push_back( larger_remainder % smaller_remainder );
			multiplying_factors.push_back( larger_remainder / smaller_remainder );
			
			larger_remainder = smaller_remainder;
			smaller_remainder = remainders.back();
		}
		while(remainders.back() != 0);
		
		// I'm going to track things in the form:
		//   pMultiplyer[i]*p + nMultiplyer[i]*n = remainder[i]  (where this is valid from i=0 onwards)
		// Proved that doing so is valid can be done by induction.
		//   Finding the solution is equivalent to providing this explanation.
		//
		// We have the initial values because 
		//   p = remainder[0]  <=>  1*p + 0*n = remainder[0]
		//   n = remainder[1]  <=>  0*p + 1*n = remainder[1]
		std::vector<integer> pMultiplyer{ 1, 0 };
		std::vector<integer> nMultiplyer{ 0, 1 };
		//
		// Because for all i >= 0
		//   remainders[i] = remainders[i+1] * multiplying_factors[i] + remainders[i+2]
		// and if for all k < i+2
		//   pMultiplyer[k]*p + nMultiplyer[k]*n = remainder[k]  (where this is valid from i=0 onwards)
		// we get
		//   pMultiplyer[i]*p + nMultiplyer[i]*n = ( pMultiplyer[i+1]*p + nMultiplyer[i+1]*n ) * multiplying_factors[i] + remainders[i+2]
		//    <=>
		//   (pMultiplyer[i] - pMultiplyer[i+1]*multiplying_factors[i])*p + (nMultiplyer[i] - nMultiplyer[i+1]*multiplying_factors[i])*n = remainders[i+2]
		//     =>
		//   pMultiplyer[i+2] = pMultiplyer[i] - pMultiplyer[i+1]*multiplying_factors[i]  and  nMultiplyer[i+2] = nMultiplyer[i] - nMultiplyer[i+1]*multiplying_factors[i]
		
		for( std::size_t multiplying_factors_index = 0; multiplying_factors_index<multiplying_factors.size(); multiplying_factors_index++ )
		{
			// this will be at position multiplying_factors_index + 2
			pMultiplyer.push_back( pMultiplyer.at(multiplying_factors_index) - pMultiplyer.at(multiplying_factors_index+1) * multiplying_factors.at(multiplying_factors_index) );
			nMultiplyer.push_back( nMultiplyer.at(multiplying_factors_index) - nMultiplyer.at(multiplying_factors_index+1) * multiplying_factors.at(multiplying_factors_index) );
		}
		
		std::size_t index_of_remainder_one{ (std::size_t)-1 };
		for( std::size_t remainders_index = 0; remainders_index<remainders.size(); remainders_index++ )
		{
			if( remainders[remainders_index] == 1 )
				index_of_remainder_one = remainders_index;
		}
		if( index_of_remainder_one == -1 )
		{
			// dev error
			throw;
		}
		
		// Because
		//   pMultiplyer[index_of_remainder_one]*p + nMultiplyer[index_of_remainder_one]*n = remainder[index_of_remainder_one] = 1
		//     =>
		//   'the multiplicative inverse of n in this field' = nMultiplyer[index_of_remainder_one] % p
		return ElementOfFiniteFieldP<Prime>{ nMultiplyer[index_of_remainder_one] % Prime };
	}
	
	constexpr ElementOfFiniteFieldP<Prime> operator/(const ElementOfFiniteFieldP<Prime>& a) const{
		return (*this)*a.FindMultiplicativeInverse();
	}
	
	// To illustrate that these are Fields
	constexpr static ElementOfFiniteFieldP<Prime> GetAdditionInvarient()
	{
		return ElementOfFiniteFieldP<Prime>( 0 );
	}
	// To illustrate that these are Fields
	constexpr static ElementOfFiniteFieldP<Prime> GetMultiplicativeInvarient()
	{
		return ElementOfFiniteFieldP<Prime>( 1 );
	}
};

