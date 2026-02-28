#pragma once

#include "IntegerPowers.h"

#include "cpp-helpers/Typedef.h"

constexpr unsigned discrete_log_ceiling( unsigned n, unsigned base )
{
    auto running_product{ 1 };
	for( unsigned index = 0; index<=n; index++ )
	{
		if( running_product >= n )
			return index;
        
        running_product *= base;
	}
	return 0;
}
