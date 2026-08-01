#include "functional-tests/schemas/FamousRSSchemas.h"
#include "functional-tests/schemas/TestTypes.h"

#include "reed-solomon-codes/SimpleEncoderSchema.h"
#include "reed-solomon-decoders/BerlekampWelchSchema.h"
#include "reed-solomon-decoders/GeoDecoderSchema.h"

#include "helpers/ErrorIntroduction.h"
#include "test-data/Messages.h"

#include "tests/finite-fields-tests/helpers/InitializerHelper.h"
#include "integer-packing-helpers/UIntAtLeast.h"

#include "gmock/gmock.h"
#include "gtest/gtest.h"

#include <bitset>
#include <vector>

namespace
{
    class Binary8BitAlphabetRaceGeoDecoderSimpleEncoder : public Msgs<BinaryUint8GFUint32MessageUint64Codeword>
    {
    public:
        using TestTypesType = TestTypes<
            BinaryUint8GFUint32MessageUint64Codeword,
            SimpleEncoderSchema< BinaryUint8GFUint32MessageUint64Codeword::n,BinaryUint8GFUint32MessageUint64Codeword::k,BinaryUint8GFUint32MessageUint64Codeword::Prime,BinaryUint8GFUint32MessageUint64Codeword::Exponent >,
            GeoDecoderSchema< BinaryUint8GFUint32MessageUint64Codeword::n,BinaryUint8GFUint32MessageUint64Codeword::k,BinaryUint8GFUint32MessageUint64Codeword::Prime,BinaryUint8GFUint32MessageUint64Codeword::Exponent >
        >;
        TestTypesType testTypes;

        Binary8BitAlphabetRaceGeoDecoderSimpleEncoder()
            : testTypes{}
            {};
    };
    class Binary8BitAlphabetRaceBWDecoderSimpleEncoder : public Msgs<BinaryUint8GFUint32MessageUint64Codeword>
    {
    public:
        using TestTypesType = TestTypes<
            BinaryUint8GFUint32MessageUint64Codeword,
            SimpleEncoderSchema< BinaryUint8GFUint32MessageUint64Codeword::n,BinaryUint8GFUint32MessageUint64Codeword::k,BinaryUint8GFUint32MessageUint64Codeword::Prime,BinaryUint8GFUint32MessageUint64Codeword::Exponent >,
            BerlekampWelchSchema< BinaryUint8GFUint32MessageUint64Codeword::n,BinaryUint8GFUint32MessageUint64Codeword::k,BinaryUint8GFUint32MessageUint64Codeword::Prime,BinaryUint8GFUint32MessageUint64Codeword::Exponent >
        >;
        TestTypesType testTypes;

        Binary8BitAlphabetRaceBWDecoderSimpleEncoder()
            : testTypes{}
            {};
    };
    
    using CodeSchemas = testing::Types<
        Binary8BitAlphabetRaceGeoDecoderSimpleEncoder
        // TODO:
        //   - Fix this for BWDecoder
        // ,
        // Binary8BitAlphabetRaceBWDecoderSimpleEncoder
    >;

    template <typename T>
    class IErrorDecoderTests : public testing::Test
    {
	public:
    };

    TYPED_TEST_SUITE( IErrorDecoderTests, CodeSchemas );
}

TYPED_TEST( IErrorDecoderTests, CodewordToCodewordRoundTripSolvable )
{
    TypeParam param{};
    const auto& code{ param.testTypes.encoder };
    const auto& decoder{ param.testTypes.decoder };

    constexpr size_t e{ GetReedSolomonParameters( TypeParam::TestTypesType::m_RSSchema::n, TypeParam::TestTypesType::m_RSSchema::k ).e };

    ASSERT_TRUE( e >= 0 );
    for( std::size_t error_count{ 0 }; error_count <= e; error_count++ )
    {
        for( const auto& message : param.messages )
        {
            auto sent_signal{ code.GenerateCodeword( message ) };

            auto recieved_signal{ sent_signal };
            introduce_any_errors<
                TypeParam::TestTypesType::m_RSSchema::n,
                TypeParam::TestTypesType::m_RSSchema::k,
                TypeParam::TestTypesType::m_RSSchema::Prime,
                TypeParam::TestTypesType::m_RSSchema::Exponent
                >( error_count, recieved_signal );

            EXPECT_TRUE( decoder.Decode( recieved_signal ).has_value() ) << "error count: " << error_count;
            if( decoder.Decode( recieved_signal ).has_value() )
                EXPECT_EQ( sent_signal, code.GenerateCodeword( decoder.Decode( recieved_signal ).value() ) ) << "error count: " << error_count;
        }
    }
}

// TODO:
//   - Fix this for BWDecoder
TYPED_TEST( IErrorDecoderTests, OldUnsolvableCasesOneError )
{
    TypeParam param{};
    const auto& code{ param.testTypes.encoder };
    const auto& decoder{ param.testTypes.decoder };
    
    for( const auto& message : param.messages )
    {
        auto sent_signal{ code.GenerateCodeword( message ) };
        
        auto recieved_signal{ sent_signal };
        introduce_errors<
            TypeParam::TestTypesType::m_RSSchema::n,
            TypeParam::TestTypesType::m_RSSchema::k,
            TypeParam::TestTypesType::m_RSSchema::Prime,
            TypeParam::TestTypesType::m_RSSchema::Exponent
            >( std::vector<std::size_t>{6}, recieved_signal );

        EXPECT_TRUE( decoder.Decode( recieved_signal ).has_value() );
        if( decoder.Decode( recieved_signal ).has_value() )
            EXPECT_EQ( sent_signal, code.GenerateCodeword( decoder.Decode( recieved_signal ).value() ) );
    }
}

// TODO:
//   - Fix this for BWDecoder
TYPED_TEST( IErrorDecoderTests, OldUnsolvableCasesTwoErrors )
{
    TypeParam param{};
    const auto& code{ param.testTypes.encoder };
    const auto& decoder{ param.testTypes.decoder };
    
    for( const auto& message : param.messages )
    {
        auto sent_signal{ code.GenerateCodeword( message ) };

        auto recieved_signal{ sent_signal };
        introduce_errors<
            TypeParam::TestTypesType::m_RSSchema::n,
            TypeParam::TestTypesType::m_RSSchema::k,
            TypeParam::TestTypesType::m_RSSchema::Prime,
            TypeParam::TestTypesType::m_RSSchema::Exponent
            >( std::vector<std::size_t>{6,7}, recieved_signal );

        EXPECT_TRUE( decoder.Decode( recieved_signal ).has_value() );
        if( decoder.Decode( recieved_signal ).has_value() )
            EXPECT_EQ( sent_signal, code.GenerateCodeword( decoder.Decode( recieved_signal ).value() ) );
    }
}

