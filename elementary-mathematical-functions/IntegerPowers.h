#pragma once

#include "cpp-helpers/Typedef.h"

constexpr unsigned int_pow(unsigned base, unsigned exponent)
{
	return exponent == 0 ? 1 : base*int_pow(base,exponent-1);
}
