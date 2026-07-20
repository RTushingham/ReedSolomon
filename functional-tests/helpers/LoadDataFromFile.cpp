#include "LoadDataFromFile.h"

#include <fstream>

std::string LoadDataFromFile( const std::string& path )
{
	std::fstream stream( path );
	std::string text{};

	if( !stream.is_open() )
	{
		throw std::exception( "Test invalid." );
	}
	
	while( !stream.eof() )
	{
		std::string buffer{};
		stream >> buffer;
		text += buffer;
	}

	if( text.empty() )
	{
		throw std::exception( "Test invalid." );
	}

    return text;
}

