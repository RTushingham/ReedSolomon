#pragma once

#include "IntegerPowers.h"
#include "IsPrime.h"
#include "Typedef.h"

constexpr unsigned discrete_sqrt_ceiling( unsigned n )
{
	for( unsigned index = 0; index<=n; index++ )
	{
		if( int_pow( index, 2 ) >= n )
			return index;
	}
	return 0;
}

constexpr unsigned discrete_log_ceiling( unsigned n, unsigned base )
{
	for( unsigned index = 0; index<=n; index++ )
	{
		if( int_pow( base, index ) >= n )
			return index;
	}
	return 0;
}

struct PrimeFactorAndWeight
{
	unsigned PrimeFactor{ 0 };
	unsigned Weight{ 0 };
};

constexpr PrimeFactorAndWeight PrimeFactorisation_SingleFactor( unsigned n )
{
	for( unsigned index = 2; index<discrete_sqrt_ceiling(n); index++ )
	{
		if( IsPrime(index) )
		{
			if( n % index == 0 )
			{
				PrimeFactorAndWeight prime_factor_weight{};
				prime_factor_weight.PrimeFactor = index;

				auto prime_raised_to_weight = int_pow( index, 2 );
				for( unsigned last_weight = 1; last_weight < n; last_weight++ )
				{
					if( n % prime_raised_to_weight != 0 )
					{
						prime_factor_weight.Weight = last_weight;
						return prime_factor_weight;
					}
					
					prime_raised_to_weight *= index;
				}
			}
		}
	}

	PrimeFactorAndWeight prime_factor_weight;	
	prime_factor_weight.PrimeFactor = n;
	prime_factor_weight.Weight = 1;
	return prime_factor_weight;
}
