#pragma once

#include "elementary-number-theory/Typedef.h"

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
		return value == a.value;
	}
	constexpr bool operator!=(const ElementOfFiniteFieldP<Prime>& a) const
	{
		return ! operator==(a);
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
		//
		// The current implementation of this function has been optimized.
		//   For a more readable version see the corresponding test code.
		
		if( value==0 )
		{
			throw;
		}

		integer larger_remainder = Prime;
		integer smaller_remainder = value;

		integer earlier_nMultiplyer = 0;
		integer newer_nMultiplyer = 1;
        
		while(smaller_remainder != 1)
		{
			const auto new_remainder = larger_remainder % smaller_remainder;
			const auto new_nMultiplyer = earlier_nMultiplyer - newer_nMultiplyer * ( larger_remainder / smaller_remainder );

			larger_remainder = smaller_remainder;
			smaller_remainder = new_remainder;

			earlier_nMultiplyer = newer_nMultiplyer;
			newer_nMultiplyer = new_nMultiplyer;
		}
		
		return ElementOfFiniteFieldP<Prime>{ newer_nMultiplyer % Prime };
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

