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

template<class ElemType, std::size_t Length>
bool constexpr array_equals( const std::array<ElemType, Length>& lhs, const std::array<ElemType, Length>& rhs )
{
	for( std::size_t index{ 0 }; index < lhs.size(); index++ )
	{
		if( lhs.at( index ) != rhs.at( index ) )
		{
			return false;
		}
	}

	return true;
};

template<class ElemType, std::size_t Length>
bool constexpr array_is_all_mutually_distinct( const std::array<ElemType, Length>& array )
{
	for( std::size_t first_elm_index{ 0 }; first_elm_index < array.size()-1; first_elm_index++ )
	{
		for( std::size_t second_elm_index{ first_elm_index+1 }; second_elm_index < array.size(); second_elm_index++ )
		{
			if( array.at( first_elm_index ) == array.at( second_elm_index ) )
				return false;
		}
	}

	return true;
};

