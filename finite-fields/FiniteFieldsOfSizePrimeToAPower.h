#pragma once

#include "IrriduciblePolynomialsOverFiniteFieldOfSizePrime.h"
#include "PolynomialsOverFiniteFieldOfSizePrime.h"

#include "cpp-helpers/Typedef.h"
#include "elementary-number-theory/IsPrime.h"

template <integer Prime, integer Exponent>
class ElementOfFiniteField
{
	static_assert( IsPrime( Prime ), "A prime size Finite Field must have a size which is a prime." );
	static_assert( Exponent > 0, "Size of Finite Field will be Prime**Exponent. As this must be a non-1 integer Exponent must be > 0." );
	
public:
	inline static constexpr PolynomialOverPrimeSizeFiniteField<Prime,Exponent> irriducible_polynomial{ GetIrriduciblePolynomial<Prime,Exponent>() };

public:
	PolynomialOverPrimeSizeFiniteField<Prime,Exponent-1> value;
	
public:
	constexpr ElementOfFiniteField<Prime,Exponent>( const PolynomialOverPrimeSizeFiniteField<Prime,Exponent-1>& value )
		: value { value }
	{}

	// Only used for value-initialization
	//   - leaves class in an error state.
	constexpr ElementOfFiniteField<Prime,Exponent>()
		: value{}
	{}
	
	constexpr ElementOfFiniteField<Prime,Exponent>& operator=( const ElementOfFiniteField<Prime,Exponent>& a ){
		value = a.value;
		return *this;
	}
	
	constexpr bool operator==( const ElementOfFiniteField<Prime, Exponent>& a ) const{
		return value == a.value;
	}
	constexpr bool operator!=( const ElementOfFiniteField<Prime, Exponent>& a ) const
	{
		return ! operator==( a );
	}
	
	constexpr ElementOfFiniteField<Prime, Exponent> operator+( const ElementOfFiniteField<Prime, Exponent>& a ) const{
		return { value + a.value };
	}
	constexpr ElementOfFiniteField<Prime, Exponent> operator-( const ElementOfFiniteField<Prime, Exponent>& a ) const{
		return { value - a.value };
	}
	constexpr ElementOfFiniteField<Prime, Exponent> operator*( const ElementOfFiniteField<Prime, Exponent>& a ) const{
		return { ( value * a.value ) % irriducible_polynomial};
	}

	constexpr ElementOfFiniteField<Prime, Exponent> FindMultiplicativeInverse() const
	{
	    if( value.IsZero() )
	    {
	        throw;
	    }

	    auto first_nMultiplyer{ PolynomialOverPrimeSizeFiniteField<Prime, Exponent-1>::GetAdditionInvarient() };
	    auto second_nMultiplyer{ PolynomialOverPrimeSizeFiniteField<Prime, Exponent-1>::GetMultiplicativeInvarient() };
	    
	    PolynomialOverPrimeSizeFiniteField<Prime,Exponent> larger_remainder{ irriducible_polynomial };
	    PolynomialOverPrimeSizeFiniteField<Prime,Exponent> smaller_remainder{ value.Oversize<Exponent>() };
	    
	    while( smaller_remainder.GetDegree() > 0)
	    {
			const auto result = larger_remainder.LongDivideBy( smaller_remainder );

			const auto temp_remainder{ result.remainder.Oversize<Exponent>() };

			const PolynomialOverPrimeSizeFiniteField<Prime, Exponent-1> new_nMultiplyer{ 
				first_nMultiplyer - second_nMultiplyer.MultiplyUpToSameDegree( result.quotient )
			};
	        
	        larger_remainder = smaller_remainder;
	        smaller_remainder = temp_remainder;

			first_nMultiplyer = second_nMultiplyer;
			second_nMultiplyer = new_nMultiplyer;
	    }
	    
		const PolynomialOverPrimeSizeFiniteField<Prime, 0> final_correcting_factor( 
			std::array<ElementOfFiniteFieldP<Prime>, PolynomialOverPrimeSizeFiniteField<Prime, 0>::GetCapacity()>{
				smaller_remainder.Coeff( 0 ).FindMultiplicativeInverse()
			}
		);
 
	    return ElementOfFiniteField<Prime, Exponent>{ second_nMultiplyer * final_correcting_factor };
	}
	
	constexpr ElementOfFiniteField<Prime, Exponent> operator/( const ElementOfFiniteField<Prime, Exponent>& a ) const{
		return ( *this )*a.FindMultiplicativeInverse();
	}

	constexpr static ElementOfFiniteField<Prime, Exponent> GetAdditionInvarient()
	{
		return ElementOfFiniteField<Prime, Exponent>( PolynomialOverPrimeSizeFiniteField<Prime,Exponent-1>::GetAdditionInvarient() );
	}
	constexpr bool IsZero() const
	{
		return value.IsZero();
	}
	constexpr static ElementOfFiniteField<Prime, Exponent> GetMultiplicativeInvarient()
	{
		return ElementOfFiniteField<Prime, Exponent>{ PolynomialOverPrimeSizeFiniteField<Prime,Exponent-1>::GetMultiplicativeInvarient() };
	}
	constexpr bool IsOne() const
	{
		return value.IsOne();
	}
};

