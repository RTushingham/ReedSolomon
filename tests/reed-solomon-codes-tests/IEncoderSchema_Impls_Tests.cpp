#include "test-data/EncoderSchemaTestTypes.h"
#include "test-data/Messages.h"

#include "reed-solomon-codes/IEncoderSchema.h"
#include "reed-solomon-codes/SimpleEncoderSchema.h"
#include "reed-solomon-codes/SystematicEncoderSchema.h"

#include "functional-tests/schemas/FamousRSSchemas.h"
#include "tests/finite-fields-tests/helpers/InitializerHelper.h"

#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include <vector>

namespace
{
    class SimpleUint16 : public Msgs<BinaryUint16GFUint32MessageUint64Codeword>
    {
    public:
        using TestTypesType = EncoderSchemaTestTypes<
            BinaryUint16GFUint32MessageUint64Codeword,
            SimpleEncoderSchema< BinaryUint16GFUint32MessageUint64Codeword::n,BinaryUint16GFUint32MessageUint64Codeword::k,BinaryUint16GFUint32MessageUint64Codeword::Prime,BinaryUint16GFUint32MessageUint64Codeword::Exponent >
        >;

        SimpleUint16(){};
    };
    class SystematicUint16 : public Msgs<BinaryUint16GFUint32MessageUint64Codeword>
    {
    public:
        using TestTypesType = EncoderSchemaTestTypes<
            BinaryUint16GFUint32MessageUint64Codeword,
            SystematicEncoderSchema< BinaryUint16GFUint32MessageUint64Codeword::n,BinaryUint16GFUint32MessageUint64Codeword::k,BinaryUint16GFUint32MessageUint64Codeword::Prime,BinaryUint16GFUint32MessageUint64Codeword::Exponent >
        >;

        SystematicUint16(){};
    };

    template <typename T>
    class IEncoderSchemaTests : public testing::Test
    {
    public:
    };

    using IEncoderSchemaImpls = testing::Types<
		SimpleUint16,
        SystematicUint16
	>;

    TYPED_TEST_SUITE( IEncoderSchemaTests, IEncoderSchemaImpls );
}

// Interface Tests

// TODO
//   - Fix this for base two finite fields
// TYPED_TEST( IEncoderSchemaTests, IsConstexprConstructable )
// {
//     constexpr typename TypeParam::TestTypesType::EncoderSchemaType encoder{ TypeParam::TestTypesType::m_RSSchema::schema.generating_elements };
// }

TYPED_TEST( IEncoderSchemaTests, IsLiteralType )
{
	constexpr bool is_literal_type{ std::is_literal_type_v<typename TypeParam::TestTypesType::EncoderSchemaType> };
	ASSERT_TRUE( is_literal_type );
}

// Functionality Tests

TYPED_TEST( IEncoderSchemaTests, EncodeDecodeInvertsCorrectly )
{
    TypeParam param{};
    const typename TypeParam::TestTypesType::EncoderSchemaType encoder{ TypeParam::TestTypesType::m_RSSchema::schema.generating_elements };

    for( const auto& message : param.messages )
    {
        EXPECT_EQ( message, encoder.PolynomialToMessage( encoder.MessageToPolynomial( message ) ) );
    }
}

