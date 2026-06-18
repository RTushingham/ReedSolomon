#pragma once

#include "FiniteFieldsOfSizePrime.h"
#include "PolynomialsOverFiniteFieldOfSizePrime.h"

#include "container-helpers/ArrayExtensions.h"
#include "elementary-mathematical-functions/DiscreteLog.h"
#include "elementary-number-theory/PrimeFactorisation.h"

template<integer Prime, std::size_t matrix_length>
void constexpr populate_squares_up_to( std::array<std::array<ElementOfFiniteFieldP<Prime>, Prime>, matrix_length>& squares, std::size_t maximum_exponent )
{
	for( std::size_t index_of_arrays = 1; index_of_arrays<maximum_exponent; index_of_arrays++ )
	{
		for( std::size_t index = 0; index<Prime; index++ )
		{
			squares.at(index_of_arrays).at(index) = squares.at(index_of_arrays-1).at(index)*squares.at(index_of_arrays-1).at(index);
		}
	}
};

template<integer Prime, std::size_t matrix_length>
constexpr std::array<ElementOfFiniteFieldP<Prime>, Prime> GetDiscretePowerArray( unsigned exponent, const std::array<std::array<ElementOfFiniteFieldP<Prime>, Prime>, matrix_length>& squares )
{
	std::array<ElementOfFiniteFieldP<Prime>,Prime> a{ ElementOfFiniteFieldP<Prime>::GetMultiplicativeInvarient() };
	
	for( std::size_t bit_index = 0; bit_index<discrete_log_ceiling( exponent, 2 ); bit_index++ )
	{
		if( (1 < bit_index) & exponent )
		{
			for( unsigned index = 0; index<squares.at( bit_index ).size(); index++ )
			{
				a.at( index ) = a.at( index ) * squares.at( bit_index ).at( index );
			}
		}
	}

	return a;
};

template <integer Prime, integer Degree>
constexpr PolynomialOverPrimeSizeFiniteField<Prime,Degree> GetIrriduciblePolynomial()
{
	static_assert( Degree!=1, " This function is aimed at non-trivial case (All polnomails of degree 1 are irriducible) " );
	static_assert( Degree>=0, "Constant polynomials are not irriducible" );

	std::array<std::array<ElementOfFiniteFieldP<Prime>, Prime>, discrete_log_ceiling( Degree, 2 )> squares{
		{ ElementOfFiniteFieldP<Prime>::GetAdditionInvarient() }
	};
	for( std::size_t index = 0; index<Prime; index++ )
	{
		squares.at(0).at(index) = ElementOfFiniteFieldP<Prime>{ (integer)index };
	}

	if( Prime == 2 )
	{
		if( Degree == 2 )
		{
			PolynomialOverPrimeSizeFiniteField<Prime,Degree> irriducible{ PolynomialOverPrimeSizeFiniteField<Prime,Degree>::GetAdditionInvarient() };

			irriducible.SetCoeff( ElementOfFiniteFieldP<Prime>::GetMultiplicativeInvarient(), 0 );
			irriducible.SetCoeff( ElementOfFiniteFieldP<Prime>::GetMultiplicativeInvarient(), 1 );
			irriducible.SetCoeff( ElementOfFiniteFieldP<Prime>::GetMultiplicativeInvarient(), 2 );

			return irriducible;
		}
		else if( Degree == 8 )
		{
			PolynomialOverPrimeSizeFiniteField<Prime,Degree> irriducible{ PolynomialOverPrimeSizeFiniteField<Prime,Degree>::GetAdditionInvarient() };

			irriducible.SetCoeff( ElementOfFiniteFieldP<Prime>::GetMultiplicativeInvarient(), 0 );
			irriducible.SetCoeff( ElementOfFiniteFieldP<Prime>::GetMultiplicativeInvarient(), 2 );
			irriducible.SetCoeff( ElementOfFiniteFieldP<Prime>::GetMultiplicativeInvarient(), 3 );
			irriducible.SetCoeff( ElementOfFiniteFieldP<Prime>::GetMultiplicativeInvarient(), 4 );
			irriducible.SetCoeff( ElementOfFiniteFieldP<Prime>::GetMultiplicativeInvarient(), 8 );

			return irriducible;
		}
		else if( Degree == 16 )
		{
			PolynomialOverPrimeSizeFiniteField<Prime,Degree> irriducible{ PolynomialOverPrimeSizeFiniteField<Prime,Degree>::GetAdditionInvarient() };

			irriducible.SetCoeff( ElementOfFiniteFieldP<Prime>::GetMultiplicativeInvarient(), 0 );
			irriducible.SetCoeff( ElementOfFiniteFieldP<Prime>::GetMultiplicativeInvarient(), 1 );
			irriducible.SetCoeff( ElementOfFiniteFieldP<Prime>::GetMultiplicativeInvarient(), 3 );
			irriducible.SetCoeff( ElementOfFiniteFieldP<Prime>::GetMultiplicativeInvarient(), 12 );
			irriducible.SetCoeff( ElementOfFiniteFieldP<Prime>::GetMultiplicativeInvarient(), 16 );

			return irriducible;
		}
		else
		{
			throw;
		}
	}

	const auto degree_factorization{ PrimeFactorisation_SingleFactor( Degree ) };
	if( Degree != int_pow( degree_factorization.PrimeFactor, degree_factorization.Weight ) )
		throw;	

	if( degree_factorization.PrimeFactor == 2 )
	{
		if( degree_factorization.Weight != 1 )
		{
			throw;
		}

		populate_squares_up_to( squares, discrete_log_ceiling( degree_factorization.PrimeFactor, 2 )  );
		const auto all_powers_of_prime_factor{ GetDiscretePowerArray( degree_factorization.PrimeFactor, squares ) };

		for( unsigned seed = 0; seed<Prime; seed++ )
		{
			const ElementOfFiniteFieldP<Prime> b{ (integer)seed };

			if( false == array_contains( all_powers_of_prime_factor, b ) )
			{
				PolynomialOverPrimeSizeFiniteField<Prime,Degree> irriducible{ PolynomialOverPrimeSizeFiniteField<Prime,Degree>::GetAdditionInvarient() };

				irriducible.SetCoeff( ElementOfFiniteFieldP<Prime>::GetAdditionInvarient() - b, 0 );
				irriducible.SetCoeff( ElementOfFiniteFieldP<Prime>{ (integer)1 }, Degree );

				return irriducible;
			}
		}
	}
	else if( Prime != 2 && degree_factorization.PrimeFactor != 2 )
	{
		populate_squares_up_to( squares, discrete_log_ceiling( degree_factorization.PrimeFactor, 2 ) - 1  );
		const auto all_powers_of_prime_factor{ GetDiscretePowerArray( degree_factorization.PrimeFactor, squares ) };

		for( unsigned seed = 0; seed<Prime; seed++ )
		{
			const ElementOfFiniteFieldP<Prime> b{ (integer)seed };

			if( false == array_contains( all_powers_of_prime_factor, b ) )
			{
				PolynomialOverPrimeSizeFiniteField<Prime,Degree> irriducible{ PolynomialOverPrimeSizeFiniteField<Prime,Degree>::GetAdditionInvarient() };

				irriducible.SetCoeff( ElementOfFiniteFieldP<Prime>::GetAdditionInvarient() - b, 0 );
				irriducible.SetCoeff( ElementOfFiniteFieldP<Prime>{ (integer)1 }, Degree );

				return irriducible;
			}
		}
	}
	else
	{
		throw;
	}

	throw;
}
