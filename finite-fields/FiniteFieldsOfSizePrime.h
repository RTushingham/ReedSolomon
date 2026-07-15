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


#include "PolynomialsOverField.h"

#include "integer-packing-helpers/UIntAtLeast.h"

template<std::size_t MaxDegree>
class PolynomialOverField<MaxDegree, ElementOfFiniteFieldP<2>>
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

// private:
    u_atleast_t<GetCoeffCount()> tmp_coefficients;
	
public:
	constexpr ElementOfFiniteFieldP<2> GetCoeff( std::size_t index ) const
	{
		u_atleast_t<GetCoeffCount()> mask = 1;
		mask <<= index;

		auto b{ (u_atleast_t<GetCoeffCount()>)( tmp_coefficients & mask ) };
		return { (integer) (b >> index) };
	}
	constexpr void SetCoeff( const ElementOfFiniteFieldP<2>& value, std::size_t index )
	{
		u_atleast_t<GetCoeffCount()> mask = (bool) value.value;
		mask <<= index;

		u_atleast_t<GetCoeffCount()> b{ 0 };
		b |= mask;

		tmp_coefficients |= b;
		
		mask = !(bool) value.value;
		mask <<= index;

		b = (u_atleast_t<GetCoeffCount()>)-1;
		b ^= mask;

		tmp_coefficients &= b;
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
	constexpr DefaultSentinal<ElementOfFiniteFieldP<2>> Coeff_Safe( Sentinal<size_t, size_t, (size_t)-1> degree ) const
	{
		if( degree.has_value() )
		{
			return { GetCoeff( degree.value() )};
		}
		
		return { DefaultSentinal<ElementOfFiniteFieldP<2>>{} };
	}
	
	constexpr integer GetDegree() const
	{
		for( size_t reverse_index{ 0 }; reverse_index < GetCoeffCount(); reverse_index++ )
		{
			if( ! GetCoeff( GetMaxDegree() - reverse_index ).IsZero() )
			{
				return (integer)(GetMaxDegree() - reverse_index);
			}
		}
		
		return -1;
	}
	
	template<integer SmallerDegree>
	constexpr PolynomialOverField<SmallerDegree, ElementOfFiniteFieldP<2>> Downsize() const
	{
		static_assert( SmallerDegree <= MaxDegree , "Downsize cannot increase the size of a polynomial." );
		
		PolynomialOverField<SmallerDegree, ElementOfFiniteFieldP<2>> downsize_result{};
		for( size_t downsize_index{ 0 }; downsize_index < downsize_result.GetCoeffCount(); downsize_index++ )
		{
			downsize_result.SetCoeff( GetCoeff( downsize_index ), downsize_index );
		}
		
		return downsize_result;
	}
	template<integer LargerDegree>
	constexpr PolynomialOverField<LargerDegree, ElementOfFiniteFieldP<2>> Oversize() const
	{
		static_assert( LargerDegree >= MaxDegree, "Oversize cannot decrease the size of a polynomial." );

		PolynomialOverField<LargerDegree, ElementOfFiniteFieldP<2>> oversized{};

		for( size_t coefficient_index{ 0 }; coefficient_index < GetCoeffCount(); coefficient_index++ )
		{
			oversized.SetCoeff( GetCoeff( coefficient_index ), coefficient_index );
		}
		
		return oversized;
	}
	template<integer OtherDegree>
	constexpr PolynomialOverField<OtherDegree, ElementOfFiniteFieldP<2>> ToSize() const
	{
		PolynomialOverField<OtherDegree, ElementOfFiniteFieldP<2>> output{};

		const size_t a{ GetCoeffCount() > output.GetCoeffCount() ? output.GetCoeffCount() : GetCoeffCount() };

		for( size_t coefficient_index{ 0 }; coefficient_index < a; coefficient_index++ )
		{
			output.SetCoeff( GetCoeff( coefficient_index ), coefficient_index );
		}
		
		return output;
	}
	template<>
	constexpr PolynomialOverField<MaxDegree, ElementOfFiniteFieldP<2>> ToSize() const
	{
		return *this;
	}

	constexpr PolynomialOverField( std::array<ElementOfFiniteFieldP<2>, GetCoeffCount()> Input )
		: tmp_coefficients{}
	{
		for( std::size_t index{ 0 }; index < GetCoeffCount(); index++ )
		{
			SetCoeff( Input.at( index ), index );
		}
	};
	constexpr PolynomialOverField( u_atleast_t<GetCoeffCount()> Input )
		: tmp_coefficients{ Input }
	{};
	constexpr PolynomialOverField()
		: tmp_coefficients{}
	{};

	constexpr ElementOfFiniteFieldP<2> operator()(const ElementOfFiniteFieldP<2>& a) const
	{
		auto running_result = GetCoeff( GetMaxDegree() );

		for( size_t coeff_index = GetMaxDegree()-1; coeff_index != (size_t)-1; coeff_index-- )
		{
			running_result = ( running_result * a ) + GetCoeff( coeff_index );
		}

		return running_result;
	}
	
	constexpr bool operator==(const PolynomialOverField<MaxDegree, ElementOfFiniteFieldP<2>>& a) const
	{
		return tmp_coefficients == a.tmp_coefficients;
	}
	constexpr bool operator!=(const PolynomialOverField<MaxDegree, ElementOfFiniteFieldP<2>>& a) const
	{
		return ! operator==(a);
	}
	
	constexpr static PolynomialOverField<MaxDegree, ElementOfFiniteFieldP<2>> GetAdditionInvarient()
	{
		return u_atleast_t<GetCoeffCount()>{ 0 };
	}
	constexpr bool IsZero() const
	{
		return 0 == tmp_coefficients;
	}
	constexpr static PolynomialOverField<MaxDegree, ElementOfFiniteFieldP<2>> GetMultiplicativeInvarient()
	{
		return u_atleast_t<GetCoeffCount()>{ 1 };
	}
	constexpr bool IsOne() const
	{
		return 1 == tmp_coefficients;
	}

	constexpr PolynomialOverField<MaxDegree, ElementOfFiniteFieldP<2>> operator+(const PolynomialOverField<MaxDegree, ElementOfFiniteFieldP<2>>& a) const
	{
		return tmp_coefficients ^ a.tmp_coefficients;
	}
	constexpr PolynomialOverField<MaxDegree, ElementOfFiniteFieldP<2>> operator-(const PolynomialOverField<MaxDegree, ElementOfFiniteFieldP<2>>& a) const
	{
		return tmp_coefficients ^ a.tmp_coefficients;
	}
	constexpr PolynomialOverField<MaxDegree, ElementOfFiniteFieldP<2>> ScalarMultiplication( const ElementOfFiniteFieldP<2>& scalar ) const
	{
		if( !scalar.value )
		{
			return GetAdditionInvarient();
		}
		return *this;
	}

	constexpr PolynomialOverField<MaxDegree, ElementOfFiniteFieldP<2>> MultiplyUpToSameDegree( const PolynomialOverField<MaxDegree, ElementOfFiniteFieldP<2>>& a ) const
	{
		u_atleast_t<GetCoeffCount()> running_xor{ 0 };

		for( std::size_t a_index{ 0 }; a_index < a.GetCoeffCount(); a_index++ )
		{
			if( (bool)a.GetCoeff( a_index ).value )
			{
				running_xor ^= ( tmp_coefficients << a_index );
			}
		}

		return running_xor % ( 1 << GetCoeffCount() );
	}

	constexpr PolynomialOverField<MaxDegree-1, ElementOfFiniteFieldP<2>> MultiplicationExcessTerms( const PolynomialOverField<MaxDegree, ElementOfFiniteFieldP<2>>& a ) const
	{
		u_atleast_t<GetCoeffCount()> running_xor{ 0 };
		for( std::size_t shift_index{ 1 }; shift_index < GetCoeffCount(); shift_index++ )
		{
			if( (bool)a.GetCoeff( a.GetCoeffCount()-shift_index ).value )
			{
				running_xor ^= ( tmp_coefficients >> shift_index );
			}
		}
	
		return u_atleast_t<PolynomialOverField<MaxDegree-1, ElementOfFiniteFieldP<2>>::GetCoeffCount()>{ running_xor };
	}

	template<integer OtherMaxDegree>
	constexpr PolynomialOverField<MaxDegree+OtherMaxDegree, ElementOfFiniteFieldP<2>> operator*( const PolynomialOverField<OtherMaxDegree, ElementOfFiniteFieldP<2>>& a ) const
	{
		constexpr std::size_t required_coeff_count{ PolynomialOverField<MaxDegree+OtherMaxDegree, ElementOfFiniteFieldP<2>>::GetCoeffCount() };
	
		u_atleast_t<required_coeff_count> running_xor{ 0 };
		u_atleast_t<required_coeff_count> coefficients_expanded{ tmp_coefficients };

		for( std::size_t a_index{ 0 }; a_index < a.GetCoeffCount(); a_index++ )
		{
			if( (bool)a.GetCoeff( a_index ).value )
			{
				running_xor ^= ( coefficients_expanded << a_index );
			}
		}

		return running_xor % ( 1 << required_coeff_count );
	}
};

