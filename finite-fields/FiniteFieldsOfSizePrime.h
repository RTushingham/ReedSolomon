#pragma once

#include "cpp-helpers/Typedef.h"
#include "elementary-number-theory/IsPrime.h"
#include "integer-packing-helpers/UIntAtLeast.h"
#include "integer-packing-helpers/MaxValueToBits.h"

template <integer Prime>
class ElementOfFiniteFieldP
{
	static_assert( IsPrime( Prime ), "A prime size Finite Field must have a size which is a prime." );

	constexpr static unsigned GetMaxStoredValue() { return Prime-1; };

	using value_type = u_atleast_t<max_value_to_bits(GetMaxStoredValue() * GetMaxStoredValue())>;

	constexpr static bool CanStoreValue( unsigned required_value ){ return 8*sizeof( value ) >= max_value_to_bits( required_value ); };
	
public:
	value_type value;
	
public:
	constexpr ElementOfFiniteFieldP( integer InputValue )
		: value { (value_type) ( ( InputValue + Prime ) % Prime ) }
	{
		static_assert( CanStoreValue( GetMaxStoredValue() + Prime ), "To prevent correctness losing integer overflow the storage type must be able to store the widest possible value for this function." );
	};
	
	constexpr ElementOfFiniteFieldP()
		: ElementOfFiniteFieldP( (value_type)0 )
	{};
	
	constexpr bool operator==( const ElementOfFiniteFieldP<Prime>& a ) const
	{
		return value == a.value;
	}
	constexpr bool operator!=( const ElementOfFiniteFieldP<Prime>& a ) const
	{
		return ! operator==( a );
	}
	
	constexpr ElementOfFiniteFieldP<Prime> operator+( const ElementOfFiniteFieldP<Prime>& a ) const
	{
		static_assert( CanStoreValue( 2 * GetMaxStoredValue() ), "To prevent correctness losing integer overflow the storage type must be able to store the widest possible value for this function." );

		return ( value + a.value) % Prime;
	}
	constexpr ElementOfFiniteFieldP<Prime> operator-( const ElementOfFiniteFieldP<Prime>& a ) const
	{
		static_assert( CanStoreValue( Prime + GetMaxStoredValue() ), "To prevent correctness losing integer overflow the storage type must be able to store the widest possible value for this function." );

		return ( Prime - a.value + value ) % Prime;
	}
	constexpr ElementOfFiniteFieldP<Prime> operator*( const ElementOfFiniteFieldP<Prime>& a ) const
	{
		static_assert( CanStoreValue( GetMaxStoredValue() * GetMaxStoredValue() ), "To prevent correctness losing integer overflow the storage type must be able to store the widest possible value for this function." );

		return ( value * a.value ) % Prime;
	}
	
	constexpr ElementOfFiniteFieldP<Prime> FindMultiplicativeInverse() const
	{
		// This is necessary for Fp to be a field
		//   For all n such that 0 < n < p, we have that n and p are coprime.
		//   Because they are coprime the Greatest Common Denominator is 1.
		//   Using the Extended Euclidean Algorithm we can find an a and b such that a*p + b*n = 1.
		//   Which is equivalent to 1 = a*p + (-b)n which implies (-b)n = 1 modulo p
		//   So ( -b % p ) will be multiplicative inverse of n within this finite field.

		if( value == 0 )
		{
			throw;
		}

		integer larger_remainder = Prime;
		integer smaller_remainder = value;

		integer earlier_nMultiplyer = 0;
		integer newer_nMultiplyer = 1;
        
		while( smaller_remainder != 1 )
		{
			const auto new_remainder = larger_remainder % smaller_remainder;
			const auto new_nMultiplyer = earlier_nMultiplyer - newer_nMultiplyer * ( larger_remainder / smaller_remainder );

			larger_remainder = smaller_remainder;
			smaller_remainder = new_remainder;

			earlier_nMultiplyer = newer_nMultiplyer;
			newer_nMultiplyer = new_nMultiplyer;
		}

		// This can be negative, so I keep the extra modulo here
		return ElementOfFiniteFieldP<Prime>{ newer_nMultiplyer % Prime };
	}
	
	constexpr ElementOfFiniteFieldP<Prime> operator/( const ElementOfFiniteFieldP<Prime>& a ) const{
		return ( *this )*a.FindMultiplicativeInverse();
	}
	
	constexpr static ElementOfFiniteFieldP<Prime> GetAdditionInvarient()
	{
		return ElementOfFiniteFieldP<Prime>( 0 );
	}
	constexpr bool IsZero() const
	{
		return operator==( GetAdditionInvarient() );
	}
	constexpr static ElementOfFiniteFieldP<Prime> GetMultiplicativeInvarient()
	{
		return ElementOfFiniteFieldP<Prime>( 1 );
	}
	constexpr bool IsOne() const
	{
		return operator==( GetMultiplicativeInvarient() );
	}
};

