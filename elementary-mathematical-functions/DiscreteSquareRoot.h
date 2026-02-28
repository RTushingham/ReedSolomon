#pragma once

#include "IntegerPowers.h"

#include "cpp-helpers/Typedef.h"

constexpr unsigned discrete_sqrt_ceiling( unsigned n )
{
	for( unsigned index = 0; index<=n; index++ )
	{
		if( int_pow( index, 2 ) >= n )
			return index;
	}
	return 0;
}
