#pragma once

#include "IntegerPowers.h"
#include "Typedef.h"

bool constexpr IsPrime( unsigned candidate )
{
	if( candidate < 2 )
		return false;

	for( unsigned index = 2; int_pow( index, 2 ) <= candidate; index++ )
	{
		if( candidate % index == 0 )
			return false;
	}

	return true;
}
