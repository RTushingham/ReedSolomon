#pragma once

#include "reed-solomon-codes/SimpleEncoderSchema.h"
#include "reed-solomon-decoders/GeoDecoderSchema.h"

#include "functional-test-schemas/FamousRSSchemas.h"
#include "functional-test-schemas/TestTypes.h"

using TestSchema = TestTypes<
	BinaryUint16GFUint32MessageUint64Codeword,
	SimpleEncoderSchema< BinaryUint16GFUint32MessageUint64Codeword::n,BinaryUint16GFUint32MessageUint64Codeword::k,BinaryUint16GFUint32MessageUint64Codeword::Prime,BinaryUint16GFUint32MessageUint64Codeword::Exponent >,
	GeoDecoderSchema< BinaryUint16GFUint32MessageUint64Codeword::n,BinaryUint16GFUint32MessageUint64Codeword::k,BinaryUint16GFUint32MessageUint64Codeword::Prime,BinaryUint16GFUint32MessageUint64Codeword::Exponent >
>;

