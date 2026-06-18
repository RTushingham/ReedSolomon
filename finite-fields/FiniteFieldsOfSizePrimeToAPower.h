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

private:
	static constexpr std::array<PolynomialOverPrimeSizeFiniteField<Prime,Exponent-1>, Exponent-1> CreateModuloMultiplicationResidues( const PolynomialOverPrimeSizeFiniteField<Prime,Exponent> & for_modulo )
    {
		std::array<PolynomialOverPrimeSizeFiniteField<Prime,Exponent-1>, Exponent-1> residues{};
        for( std::size_t index{ 0 }; index < residues.size(); index++ )
        {
            PolynomialOverPrimeSizeFiniteField<Prime,2*(Exponent-1)> seed_polynomial{};
            seed_polynomial.SetCoeff( 1, Exponent + index );
            residues.at( index ) = seed_polynomial % for_modulo;
        }
		return residues;
	};
	static constexpr std::array<PolynomialOverPrimeSizeFiniteField<Prime,Exponent-1>, Exponent-1> residues{ CreateModuloMultiplicationResidues( irriducible_polynomial ) };

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
		auto product{ value * a.value };

        auto running_sum{ product.Downsize<Exponent-1>() };

		PolynomialOverPrimeSizeFiniteField<Prime,0> scallar_multiplyer;
		for( std::size_t residues_index{ 0 }; residues_index < residues.size(); residues_index++ )
		{
			scallar_multiplyer.SetCoeff( product.GetCoeff( Exponent + residues_index ), 0 );

			running_sum = running_sum + ( scallar_multiplyer * residues.at( residues_index ) );
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

		const PolynomialOverPrimeSizeFiniteField<Prime, 0> final_correcting_factor( 
			std::array<ElementOfFiniteFieldP<Prime>, PolynomialOverPrimeSizeFiniteField<Prime, 0>::GetCoeffCount()>{
				eea_result.remainder.GetCoeff( 0 ).FindMultiplicativeInverse()
			}
		);
 
	    return ElementOfFiniteField<Prime, Exponent>{ eea_result.divisor_multiplyer * final_correcting_factor };
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

