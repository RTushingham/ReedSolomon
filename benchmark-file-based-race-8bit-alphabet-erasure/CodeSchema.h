#pragma once

#include "reed-solomon-codes/SimpleEncoderSchema.h"
#include "reed-solomon-decoders/ErasureDecoderSchema.h"

#include "functional-test-schemas/FamousRSSchemas.h"
#include "functional-test-schemas/TestTypes_Erasure.h"

using TestSchema = TestTypes_Erasure<
	BinaryUint8GFUint32MessageUint64Codeword,
	SimpleEncoderSchema< BinaryUint8GFUint32MessageUint64Codeword::n,BinaryUint8GFUint32MessageUint64Codeword::k,BinaryUint8GFUint32MessageUint64Codeword::Prime,BinaryUint8GFUint32MessageUint64Codeword::Exponent >,
	ErasureDecoderSchema< BinaryUint8GFUint32MessageUint64Codeword::n,BinaryUint8GFUint32MessageUint64Codeword::k,BinaryUint8GFUint32MessageUint64Codeword::Prime,BinaryUint8GFUint32MessageUint64Codeword::Exponent >
>;

