#pragma once

#include "IrriduciblePolynomialsOverFiniteFieldOfSizePrime.h"
#include "PolynomialsOverFieldAlgorithms.h"
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

private:
	static constexpr std::array<PolynomialOverPrimeSizeFiniteField<Prime,Exponent-1>, Exponent-1> CreateModuloMultiplicationResidues( const PolynomialOverPrimeSizeFiniteField<Prime,Exponent> & for_modulo )
    {
		std::array<PolynomialOverPrimeSizeFiniteField<Prime,Exponent-1>, Exponent-1> residues{};
        for( std::size_t index{ 0 }; index < residues.size(); index++ )
        {
            PolynomialOverPrimeSizeFiniteField<Prime,2*(Exponent-1)> seed_polynomial{};
            seed_polynomial.SetCoeff( 1, Exponent + index );
            residues.at( index ) = LongDivideBy( seed_polynomial, for_modulo ).remainder.Downsize<Exponent-1>();
        }
		return residues;
	};
	static constexpr std::array<PolynomialOverPrimeSizeFiniteField<Prime,Exponent-1>, Exponent-1> residues{ CreateModuloMultiplicationResidues( irriducible_polynomial ) };

public:
	PolynomialOverPrimeSizeFiniteField<Prime,Exponent-1> value;
	
	constexpr ElementOfFiniteField<Prime,Exponent>( const PolynomialOverPrimeSizeFiniteField<Prime,Exponent-1>& value )
		: value { value }
	{}

	// Only used for value-initialization
	//   - leaves class in an error state.
	constexpr ElementOfFiniteField<Prime,Exponent>()
		: value{}
	{}
	
	constexpr ElementOfFiniteField<Prime,Exponent>& operator=( const ElementOfFiniteField<Prime,Exponent>& a ) = default;
	
	constexpr bool operator==( const ElementOfFiniteField<Prime, Exponent>& a ) const
	{
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
		const auto excess_terms{ value.MultiplicationExcessTerms( a.value ) };
		// auto product{ value * a.value };
	
        auto running_sum{ value.MultiplyUpToSameDegree( a.value ) };
		// auto running_sum{ product.Downsize<Exponent-1>() };
		
		// Why is MultiplicationExcessTerms better despite creating twice the number of operations?
		//   + Avoids Downsize = avoids copy of data.
		//   + RVO? 
		//       - Requires 
		//   - Doubles the number of operations 

		for( std::size_t residues_index{ 0 }; residues_index < residues.size(); residues_index++ )
		{
			running_sum = running_sum + residues.at( residues_index ).ScalarMultiplication( excess_terms.GetCoeff( residues_index ) );
			// running_sum = running_sum + residues.at( residues_index ).ScalarMultiplication( product.GetCoeff( Exponent + residues_index ) );
		}
	
		return running_sum;
	}

	constexpr ElementOfFiniteField<Prime, Exponent> FindMultiplicativeInverse() const
	{
	    if( value.IsZero() )
	    {
	        throw;
	    }

		const auto eea_result{ ExtendedEuclideanAlgorithm( 0, irriducible_polynomial, value ) };

	    return ElementOfFiniteField<Prime, Exponent>{ eea_result.divisor_multiplyer.ScalarMultiplication( eea_result.remainder.GetCoeff( 0 ).FindMultiplicativeInverse() ) };
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


#include "PolynomialsOverField.h"

template<std::size_t MaxDegree, std::size_t Exponent>
class PolynomialOverField<MaxDegree, ElementOfFiniteField<2,Exponent>>
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
	
private:
	static constexpr size_t Size_in_bits{ GetCoeffCount()*Exponent };

	static constexpr size_t CeilingDiv( std::size_t numerator, std::size_t denominator )
	{
		return (numerator+(denominator-1))/denominator;
	}

	template<size_t return_size>
	static constexpr u_atleast_t<return_size> GGG( uint64_t value, size_t index )
	{
		return (u_atleast_t<return_size>)( value >> (index*return_size) );
	}

	static constexpr size_t reg_count{ CeilingDiv( Size_in_bits, 64 ) };

	std::array<uint64_t, reg_count> values;

public:
	constexpr ElementOfFiniteField<2,Exponent> GetCoeff( std::size_t index ) const
	{
		size_t values_index{ index / (64/Exponent) };
		size_t value_index{ index % (64/Exponent) };

		return GGG<Exponent>( values.at( values_index ), value_index );
	}
	constexpr void SetCoeff( const ElementOfFiniteField<2,Exponent>& value, std::size_t index )
	{
		uint64_t* begin{ values.data() };
		u_atleast_t<Exponent>* begin_u8{ reinterpret_cast<u_atleast_t<Exponent>*>( begin ) }; 
		u_atleast_t<Exponent>* target_u8{ begin_u8 + index }; 

		*target_u8 = value.value.tmp_coefficients;
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
	constexpr DefaultSentinal<ElementOfFiniteField<2,Exponent>> Coeff_Safe( Sentinal<size_t, size_t, (size_t)-1> degree ) const
	{
		if( degree.has_value() )
		{
			return { GetCoeff( degree.value() )};
		}
		
		return { DefaultSentinal<ElementOfFiniteField<2,Exponent>>{} };
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
	constexpr PolynomialOverField<SmallerDegree, ElementOfFiniteField<2,Exponent>> Downsize() const
	{
		static_assert( SmallerDegree <= MaxDegree , "Downsize cannot increase the size of a polynomial." );
		
		PolynomialOverField<SmallerDegree, ElementOfFiniteField<2,Exponent>> downsize_result{};
		for( size_t downsize_index{ 0 }; downsize_index < downsize_result.GetCoeffCount(); downsize_index++ )
		{
			downsize_result.SetCoeff( GetCoeff( downsize_index ), downsize_index );
		}
		
		return downsize_result;
	}
	template<integer LargerDegree>
	constexpr PolynomialOverField<LargerDegree, ElementOfFiniteField<2,Exponent>> Oversize() const
	{
		static_assert( LargerDegree >= MaxDegree, "Oversize cannot decrease the size of a polynomial." );

		PolynomialOverField<LargerDegree, ElementOfFiniteField<2,Exponent>> oversized{};

		for( size_t coefficient_index{ 0 }; coefficient_index < GetCoeffCount(); coefficient_index++ )
		{
			oversized.SetCoeff( GetCoeff( coefficient_index ), coefficient_index );
		}
		
		return oversized;
	}
	template<integer OtherDegree>
	constexpr PolynomialOverField<OtherDegree, ElementOfFiniteField<2,Exponent>> ToSize() const
	{
		PolynomialOverField<OtherDegree, ElementOfFiniteField<2,Exponent>> output{};

		const size_t a{ GetCoeffCount() > output.GetCoeffCount() ? output.GetCoeffCount() : GetCoeffCount() };

		for( size_t coefficient_index{ 0 }; coefficient_index < a; coefficient_index++ )
		{
			output.SetCoeff( GetCoeff( coefficient_index ), coefficient_index );
		}
		
		return output;
	}
	template<>
	constexpr PolynomialOverField<MaxDegree, ElementOfFiniteField<2,Exponent>> ToSize() const
	{
		return *this;
	}

	constexpr PolynomialOverField( std::array<ElementOfFiniteField<2,Exponent>, GetCoeffCount()> Input )
		: values{}
	{
		for( std::size_t index{ 0 }; index < GetCoeffCount(); index++ )
		{
			SetCoeff( Input.at( index ), index );
		}
	};
	constexpr PolynomialOverField( std::array<uint64_t, reg_count> Input )
		: values{ Input }
	{};
	constexpr PolynomialOverField()
		: values{}
	{};

	constexpr ElementOfFiniteField<2,Exponent> operator()(const ElementOfFiniteField<2,Exponent>& a) const
	{
		auto running_result = GetCoeff( GetMaxDegree() );

		for( size_t coeff_index = GetMaxDegree()-1; coeff_index != (size_t)-1; coeff_index-- )
		{
			running_result = ( running_result * a ) + GetCoeff( coeff_index );
		}

		return running_result;
	}
	
	constexpr bool operator==(const PolynomialOverField<MaxDegree, ElementOfFiniteField<2,Exponent>>& a) const
	{
		return values == a.values;
	}
	constexpr bool operator!=(const PolynomialOverField<MaxDegree, ElementOfFiniteField<2,Exponent>>& a) const
	{
		return ! operator==(a);
	}
	
	constexpr static PolynomialOverField<MaxDegree, ElementOfFiniteField<2,Exponent>> GetAdditionInvarient()
	{
		return std::array<uint64_t, reg_count>{ 0 };
	}
	constexpr bool IsZero() const
	{
		for( const auto& val : values )
		{
			if( val != 0 )
			{
				return false;
			}
		}
		return true;
	}
	constexpr static PolynomialOverField<MaxDegree, ElementOfFiniteField<2,Exponent>> GetMultiplicativeInvarient()
	{
		std::array<uint64_t, reg_count> ret{ 0 };
		ret.at( 0 ) = 1;
		return ret;
	}
	constexpr bool IsOne() const
	{
		for( size_t index{ 1 }; index < values.size(); index++ )
		{
			if( values.at( index ) != 0 )
			{
				return false;
			}
		}
		return values.at( 0 ) == 1;
	}

	constexpr PolynomialOverField<MaxDegree, ElementOfFiniteField<2,Exponent>> operator+(const PolynomialOverField<MaxDegree, ElementOfFiniteField<2,Exponent>>& a) const
	{
		std::array<uint64_t, reg_count> ret{ 0 };
		for( size_t values_index{ 0 }; values_index < values.size(); values_index++ )
		{
			ret.at( values_index ) = values.at( values_index ) ^ a.values.at( values_index );
		}
		return ret;
	}
	constexpr PolynomialOverField<MaxDegree, ElementOfFiniteField<2,Exponent>> operator-(const PolynomialOverField<MaxDegree, ElementOfFiniteField<2,Exponent>>& a) const
	{
		std::array<uint64_t, reg_count> ret{ 0 };
		for( size_t values_index{ 0 }; values_index < values.size(); values_index++ )
		{
			ret.at( values_index ) = values.at( values_index ) ^ a.values.at( values_index );
		}
		return ret;
	}

	constexpr PolynomialOverField<MaxDegree, ElementOfFiniteField<2,Exponent>> MultiplyUpToSameDegree( const PolynomialOverField<MaxDegree, ElementOfFiniteField<2,Exponent>>& a ) const
	{
		auto return_value{ PolynomialOverField<MaxDegree, ElementOfFiniteField<2,Exponent>>::GetAdditionInvarient() };
		
		for( size_t a_index = 0; a_index < a.GetCoeffCount(); a_index++ )
		{
			for( size_t this_index = 0; this_index < GetCoeffCount() - a_index; this_index++ )
			{
				return_value.SetCoeff( return_value.GetCoeff( a_index + this_index ) + ( a.GetCoeff( a_index ) * GetCoeff( this_index ) ), a_index + this_index );
			}
		}

		return return_value;
	}
	constexpr PolynomialOverField<MaxDegree-1, ElementOfFiniteField<2,Exponent>> MultiplicationExcessTerms( const PolynomialOverField<MaxDegree, ElementOfFiniteField<2,Exponent>>& a ) const
	{
		auto return_value{ PolynomialOverField<MaxDegree-1, ElementOfFiniteField<2,Exponent>>::GetAdditionInvarient() };
		
		for( size_t a_index = 1; a_index < a.GetCoeffCount(); a_index++ )
		{
			for( size_t this_index = GetCoeffCount() - a_index; this_index < GetCoeffCount(); this_index++ )
			{
				return_value.SetCoeff( return_value.GetCoeff( a_index + this_index - GetCoeffCount() ) + ( a.GetCoeff( a_index ) * GetCoeff( this_index ) ), a_index + this_index - GetCoeffCount() );
			}
		}

		return return_value;
	}
	constexpr PolynomialOverField<MaxDegree, ElementOfFiniteField<2,Exponent>> ScalarMultiplication( const ElementOfFiniteField<2,Exponent>& scalar ) const
	{
		auto return_value{ GetAdditionInvarient() };
		
		for( size_t index = 0; index < GetCoeffCount(); index++ )
		{
			return_value.SetCoeff( GetCoeff( index ) * scalar, index );
		}
	
		return return_value;
	}
	template<integer OtherMaxDegree>
	constexpr PolynomialOverField<MaxDegree+OtherMaxDegree, ElementOfFiniteField<2,Exponent>> operator*( const PolynomialOverField<OtherMaxDegree, ElementOfFiniteField<2,Exponent>>& a ) const
	{
		auto return_value{ PolynomialOverField<MaxDegree+OtherMaxDegree, ElementOfFiniteField<2,Exponent>>::GetAdditionInvarient() };
		
		for( size_t a_index = 0; a_index < a.GetCoeffCount(); a_index++ )
		{
			for( size_t this_index = 0; this_index < GetCoeffCount(); this_index++ )
			{
				return_value.SetCoeff( return_value.GetCoeff( a_index + this_index ) + ( a.GetCoeff( a_index ) * GetCoeff( this_index ) ), a_index + this_index );
			}
		}
		
		return return_value;
	}
};

