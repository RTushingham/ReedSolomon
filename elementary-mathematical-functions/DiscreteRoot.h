#pragma once

#include "IntegerPowers.h"

#include "cpp-helpers/Typedef.h"

#include <exception>

constexpr unsigned discrete_root_ceiling( unsigned target, unsigned exponent )
{
	if( exponent == 0 )
	{
		throw std::exception( "Roots to the 0th power are undefined" );
	}

	for( unsigned index = 0; index <= target; index++ )
	{
		if( int_pow( index, exponent ) >= target )
			return index;
	}
	return 0;
}

constexpr unsigned discrete_sqrt_ceiling( unsigned target )
{
	return discrete_root_ceiling( target, 2 );
}

