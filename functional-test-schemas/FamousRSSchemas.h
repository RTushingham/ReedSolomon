#pragma once

#include "cpp-helpers/Typedef.h"
#include "reed-solomon-codes/Schema.h"

class BinaryUint8GFUint32MessageUint64Codeword
{
public:
    static constexpr integer Prime{ 2 };
    static constexpr integer Exponent{ 8 };
    static constexpr std::size_t k{ 4 };
    static constexpr std::size_t n{ 8 };

	Schema<n, k, Prime, Exponent> schema;

    BinaryUint8GFUint32MessageUint64Codeword();

private:
    static Schema<n, k, Prime, Exponent> CreateSchema();
};

class BinaryUint16GFUint32MessageUint64Codeword
{
public:
    static constexpr size_t Prime{ 2 };
    static constexpr size_t Exponent{ 16 };
    static constexpr size_t k{ 2 };
    static constexpr size_t n{ 4 };

	Schema<n, k, Prime, Exponent> schema;

    BinaryUint16GFUint32MessageUint64Codeword();

private:
    Schema<n, k, Prime, Exponent> CreateSchema();
};

class PrimePowerGF
{
public:
    static constexpr integer Prime{ 101 };
    static constexpr integer Exponent{ 2 };
    static constexpr std::size_t n{ 4 };
    static constexpr std::size_t k{ 2 };

	Schema<n, k, Prime, Exponent> schema;

    PrimePowerGF();

private:
    Schema<n, k, Prime, Exponent> CreateSchema();
};

