#pragma once

#include <string>

std::string LoadDataFromFile( const std::string& path );

namespace TestDataPaths
{
    const std::string Small_File{ R"(D:\ReedSolomon\functional-tests\data\small\text.txt)" };
    const std::string Large_File{ R"(D:\ReedSolomon\functional-tests\data\large\text.txt)" };
}

