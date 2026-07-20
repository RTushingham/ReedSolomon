#pragma once

#include "reed-solomon-codes/SimpleEncoderSchema.h"
#include "reed-solomon-decoders/GeoDecoderSchema.h"

#include "functional-test-schemas/FamousRSSchemas.h"
#include "functional-test-schemas/TestTypes.h"

using TestSchema = TestTypes<
	BinaryUint8GFUint32MessageUint64Codeword,
	SimpleEncoderSchema< BinaryUint8GFUint32MessageUint64Codeword::n,BinaryUint8GFUint32MessageUint64Codeword::k,BinaryUint8GFUint32MessageUint64Codeword::Prime,BinaryUint8GFUint32MessageUint64Codeword::Exponent >,
	GeoDecoderSchema< BinaryUint8GFUint32MessageUint64Codeword::n,BinaryUint8GFUint32MessageUint64Codeword::k,BinaryUint8GFUint32MessageUint64Codeword::Prime,BinaryUint8GFUint32MessageUint64Codeword::Exponent >
>;

