#pragma once

#include "IsPrime.h"

#include "elementary-mathematical-functions/DiscreteLog.h"
#include "elementary-mathematical-functions/DiscreteRoot.h"
#include "cpp-helpers/Typedef.h"

struct PrimeFactorAndWeight
{
	unsigned PrimeFactor{ 0 };
	unsigned Weight{ 0 };
};

constexpr PrimeFactorAndWeight PrimeFactorisation_SingleFactor( unsigned target )
{
	PrimeFactorAndWeight return_value{};
	return_value.PrimeFactor = target;

	for( unsigned candidate_factor = 2; candidate_factor <= discrete_sqrt_ceiling( target ); candidate_factor++ )
	{
		if( IsPrime( candidate_factor ) && ( target % candidate_factor == 0 ) )
		{
			return_value.PrimeFactor = candidate_factor;
			break;
		}
	}

	return_value.Weight = discrete_log_ceiling( target, return_value.PrimeFactor );
	return return_value;
}

