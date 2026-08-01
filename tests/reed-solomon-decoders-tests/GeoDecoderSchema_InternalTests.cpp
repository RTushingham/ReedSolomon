#include "reed-solomon-decoders/GeoDecoderSchema.h"

#include "test-data/DecoderSchemaTestTypes.h"
#include "test-data/PolynomialMessages.h"

#include "reed-solomon-codes/EncoderBase.h"
#include "finite-fields-polynomials/PolynomialsOverFiniteFieldOfSizePrimeToAPower.h"

#include "functional-tests/schemas/FamousRSSchemas.h"
#include "tests/finite-fields-tests/helpers/InitializerHelper.h"
#include "tests/reed-solomon-codes-tests/helpers/BlockCodeOverFiniteFieldSchema.h"

#include "gmock/gmock.h"
#include "gtest/gtest.h"

#include <vector>

namespace
{
    class A : public Po<PrimePowerGF>
    {
    public:
        using TestTypesType = DecoderSchemaTestTypes<
            PrimePowerGF,
            GeoDecoderSchema< PrimePowerGF::n,PrimePowerGF::k,PrimePowerGF::Prime,PrimePowerGF::Exponent >
        >;

        A(){};
    };
    class B : public Po<BinaryUint8GFUint32MessageUint64Codeword>
    {
    public:
        using TestTypesType = DecoderSchemaTestTypes<
            BinaryUint8GFUint32MessageUint64Codeword,
            GeoDecoderSchema< BinaryUint8GFUint32MessageUint64Codeword::n,BinaryUint8GFUint32MessageUint64Codeword::k,BinaryUint8GFUint32MessageUint64Codeword::Prime,BinaryUint8GFUint32MessageUint64Codeword::Exponent >
        >;

        B(){};
    };
    class C : public Po<BinaryUint16GFUint32MessageUint64Codeword>
    {
    public:
        // TODO - unnecessary
        using TestTypesType = DecoderSchemaTestTypes<
            BinaryUint16GFUint32MessageUint64Codeword,
            GeoDecoderSchema< BinaryUint16GFUint32MessageUint64Codeword::n,BinaryUint16GFUint32MessageUint64Codeword::k,BinaryUint16GFUint32MessageUint64Codeword::Prime,BinaryUint16GFUint32MessageUint64Codeword::Exponent >
        >;

        C(){};
    };

    using TestSchemaAndData_GeoDecoderSchemaInternalTests = testing::Types<
		A,
        B,
        C
	>;


    template <typename T>
    class GeoDecoderSchemaInternalTests : public testing::Test
    {
	public:
    };

    TYPED_TEST_SUITE( GeoDecoderSchemaInternalTests, TestSchemaAndData_GeoDecoderSchemaInternalTests );
}


TYPED_TEST( GeoDecoderSchemaInternalTests, InitialTermIsAsExpected )
{
    TypeParam param{};
    const typename TypeParam::TestTypesType::DecoderSchemaType geo_decoder{ TypeParam::TestTypesType::m_RSSchema::schema };
    const auto& generating_elements{ TypeParam::TestTypesType::m_RSSchema::schema.generating_elements };

    EXPECT_EQ( geo_decoder.m_initial_term.GetDegree(), generating_elements.size() );
    
    ASSERT_THAT( generating_elements, ::testing::Not( ::testing::IsEmpty() ) );
    for( const auto& generator : generating_elements )
    {
        EXPECT_TRUE( geo_decoder.m_initial_term( generator ).IsZero() );
    }
}

TYPED_TEST( GeoDecoderSchemaInternalTests, LegrangeInterpolationWorks )
{
    TypeParam param{};
    const typename TypeParam::TestTypesType::DecoderSchemaType geo_decoder{ TypeParam::TestTypesType::m_RSSchema::schema };
    const auto& generating_elements{ TypeParam::TestTypesType::m_RSSchema::schema.generating_elements };

    ASSERT_THAT( param.polynomials, ::testing::Not( ::testing::IsEmpty() ) );
    for( const auto& polynomial : param.polynomials )
    {
        typename BlockCodeOverFiniteFieldSchema<TypeParam::TestTypesType::m_RSSchema>::Signal signal{};
        PolynomialToCodeword<
            TypeParam::TestTypesType::m_RSSchema::n,
            TypeParam::TestTypesType::m_RSSchema::k,
            TypeParam::TestTypesType::m_RSSchema::Prime,
            TypeParam::TestTypesType::m_RSSchema::Exponent
            >( generating_elements, signal, 0, polynomial );
        
        const auto l_i_res{ geo_decoder.LagrangeInterpolation( signal ) };

        ASSERT_TRUE( generating_elements.size() >= 0 );
        for( std::size_t generator_index{ 0 }; generator_index < generating_elements.size(); generator_index++ )
        {
            EXPECT_EQ( l_i_res( generating_elements.at( generator_index ) ), signal.at( generator_index ) );
        }
    }
}

