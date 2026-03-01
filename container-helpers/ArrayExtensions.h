#pragma once

#include <array>

template<class ElemType, std::size_t Length, class ValueType>
bool constexpr array_contains( const std::array<ElemType, Length>& array, const ValueType & target )
{
	for( const auto & a : array )
	{
		if( a == target )
			return true;
	}

	return false;
};
