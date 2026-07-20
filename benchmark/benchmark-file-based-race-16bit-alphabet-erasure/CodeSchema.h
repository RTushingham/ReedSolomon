#pragma once

#include "reed-solomon-codes/SimpleEncoderSchema.h"
#include "reed-solomon-decoders/ErasureDecoderSchema.h"

#include "functional-tests/schemas/FamousRSSchemas.h"
#include "functional-tests/schemas/TestTypes_Erasure.h"

using TestSchema = TestTypes_Erasure<
	BinaryUint16GFUint32MessageUint64Codeword,
	SimpleEncoderSchema< BinaryUint16GFUint32MessageUint64Codeword::n,BinaryUint16GFUint32MessageUint64Codeword::k,BinaryUint16GFUint32MessageUint64Codeword::Prime,BinaryUint16GFUint32MessageUint64Codeword::Exponent >,
	ErasureDecoderSchema< BinaryUint16GFUint32MessageUint64Codeword::n,BinaryUint16GFUint32MessageUint64Codeword::k,BinaryUint16GFUint32MessageUint64Codeword::Prime,BinaryUint16GFUint32MessageUint64Codeword::Exponent >
>;

