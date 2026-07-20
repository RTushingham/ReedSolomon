#include "Split.h"

std::vector<std::string_view> Split_ToEvenSized( std::size_t a, const std::string_view& string )
{
	std::vector<std::string_view> return_value{};
	return_value.reserve( string.size()/a );

	for( int64_t index{0}; index+(a-1) < string.size(); index+=a )
	{
		return_value.push_back( std::string_view( string.data()+index, a ) );
	}

	return return_value;
}

