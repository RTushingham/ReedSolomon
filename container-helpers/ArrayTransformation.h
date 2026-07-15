#pragma once

#include <array>
#include <bitset>

template<class ElemType, std::size_t TargetLength, std::size_t SourceLength>
constexpr std::array<ElemType, TargetLength> CopyIf( const std::array<ElemType, SourceLength>& source, std::bitset<SourceLength> valid_source_entries )
{
	std::array<ElemType, TargetLength> output{};

	for( std::size_t source_index{ 0 }, output_index{ 0 }; source_index < source.size() && output_index < output.size(); source_index++ )
	{
		if( false == valid_source_entries.test( source_index ) )
		{
			output.at( output_index ) = source.at( source_index );
			output_index++;
		}
	}

	return output;
};

template<class ElemType, std::size_t TargetLength, std::size_t SourceLength>
constexpr std::array<ElemType, TargetLength> CopyFirstKElements( const std::array<ElemType, SourceLength>& source )
{
	std::array<ElemType, TargetLength> return_value{};
	for( std::size_t index{ 0 }; index < TargetLength; index++ )
	{
		return_value.at( index ) = source.at( index );
	}
	return return_value;
}

