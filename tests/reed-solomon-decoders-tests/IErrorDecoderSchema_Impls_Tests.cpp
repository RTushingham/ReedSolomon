#include "reed-solomon-decoders/IErrorDecoderSchema.h"
#include "reed-solomon-decoders/BerlekampWelchSchema.h"
#include "reed-solomon-decoders/GeoDecoderSchema.h"

#include "helpers/ErrorIntroduction.h"
#include "test-data/DecoderSchemaTestTypes.h"
#include "test-data/PolynomialMessages.h"

#include "finite-fields-polynomials/PolynomialsOverFiniteFieldOfSizePrimeToAPower.h"
#include "reed-solomon-codes/Codeword.h"
#include "reed-solomon-codes/EncoderBase.h"
#include "reed-solomon-codes/ReedSolomonBlockCodeParameters.h"

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
        using TestTypesType = DecoderSchemaTestTypes<
            BinaryUint16GFUint32MessageUint64Codeword,
            GeoDecoderSchema< BinaryUint16GFUint32MessageUint64Codeword::n,BinaryUint16GFUint32MessageUint64Codeword::k,BinaryUint16GFUint32MessageUint64Codeword::Prime,BinaryUint16GFUint32MessageUint64Codeword::Exponent >
        >;

        C(){};
    };

    class D : public Po<PrimePowerGF>
    {
    public:
        using TestTypesType = DecoderSchemaTestTypes<
            PrimePowerGF,
            BerlekampWelchSchema< PrimePowerGF::n,PrimePowerGF::k,PrimePowerGF::Prime,PrimePowerGF::Exponent >
        >;

        D(){};
    };
    class E : public Po<BinaryUint8GFUint32MessageUint64Codeword>
    {
    public:
        using TestTypesType = DecoderSchemaTestTypes<
            BinaryUint8GFUint32MessageUint64Codeword,
            BerlekampWelchSchema< BinaryUint8GFUint32MessageUint64Codeword::n,BinaryUint8GFUint32MessageUint64Codeword::k,BinaryUint8GFUint32MessageUint64Codeword::Prime,BinaryUint8GFUint32MessageUint64Codeword::Exponent >
        >;

        E(){};
    };
    class F : public Po<BinaryUint16GFUint32MessageUint64Codeword>
    {
    public:
        using TestTypesType = DecoderSchemaTestTypes<
            BinaryUint16GFUint32MessageUint64Codeword,
            BerlekampWelchSchema< BinaryUint16GFUint32MessageUint64Codeword::n,BinaryUint16GFUint32MessageUint64Codeword::k,BinaryUint16GFUint32MessageUint64Codeword::Prime,BinaryUint16GFUint32MessageUint64Codeword::Exponent >
        >;

        F(){};
    };

    template <typename T>
    class IErrorDecoderSchemaTests : public testing::Test
    {
    public:
    };

    using IErrorDecoderSchemaImpls = testing::Types<
		A,
        B,
        C,
        D,
        E,
        F
    >;

    TYPED_TEST_SUITE( IErrorDecoderSchemaTests, IErrorDecoderSchemaImpls );
}

// Interface Tests

// TODO
//   - Fix this for base two finite fields
// TYPED_TEST( IErrorDecoderSchemaTests, IsConstexprConstructable )
// {
//     constexpr typename TypeParam::TestTypesType::DecoderSchemaType decoder{ TypeParam::TestTypesType::m_RSSchema::schema };
// }

TYPED_TEST( IErrorDecoderSchemaTests, IsLiteralType )
{
	constexpr bool is_literal_type{ std::is_literal_type_v<typename TypeParam::TestTypesType::DecoderSchemaType> };
	ASSERT_TRUE( is_literal_type );
}

// Functionality Tests

TYPED_TEST( IErrorDecoderSchemaTests, PolyToSignalToPolyNoErrorCase )
{
    TypeParam param{};
    const typename TypeParam::TestTypesType::DecoderSchemaType decoder{ TypeParam::TestTypesType::m_RSSchema::schema };
    const auto& generating_elements{ TypeParam::TestTypesType::m_RSSchema::schema.generating_elements };

    ASSERT_THAT( param.polynomials, ::testing::Not( ::testing::IsEmpty() ) );
    for( const auto& polynomial : param.polynomials )
    {
        typename BlockCodeOverFiniteFieldSchema<TypeParam::TestTypesType::m_RSSchema>::Signal codeword{};
        PolynomialToCodeword<
            TypeParam::TestTypesType::m_RSSchema::n,
            TypeParam::TestTypesType::m_RSSchema::k,
            TypeParam::TestTypesType::m_RSSchema::Prime,
            TypeParam::TestTypesType::m_RSSchema::Exponent
            >( generating_elements, codeword, 0, polynomial );

        EXPECT_TRUE( decoder.Decode( codeword ).has_value() );
        EXPECT_EQ( polynomial, decoder.Decode( codeword ).value() );
    }
}

TYPED_TEST( IErrorDecoderSchemaTests, PolyToSignalToPolyFewerThanOrEqualToErrorCorrectingValueErrors )
{
    TypeParam param{};
    const typename TypeParam::TestTypesType::DecoderSchemaType decoder{ TypeParam::TestTypesType::m_RSSchema::schema };
    const auto& generating_elements{ TypeParam::TestTypesType::m_RSSchema::schema.generating_elements };

    constexpr size_t e{ GetReedSolomonParameters( TypeParam::TestTypesType::m_RSSchema::n, TypeParam::TestTypesType::m_RSSchema::k ).e };

    ASSERT_TRUE( e-1 >= 0 );
    for( size_t errors{ 1 }; errors <= e; errors++ )
    {
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

            introduce_any_errors<
                TypeParam::TestTypesType::m_RSSchema::n,
                TypeParam::TestTypesType::m_RSSchema::k,
                TypeParam::TestTypesType::m_RSSchema::Prime,
                TypeParam::TestTypesType::m_RSSchema::Exponent
                >( errors, signal );

            EXPECT_TRUE( decoder.Decode( signal ).has_value() );
            EXPECT_EQ( polynomial, decoder.Decode( signal ).value() );
        }
    }
}

TYPED_TEST( IErrorDecoderSchemaTests, PolyToSignalToPolyUnrecoverableSituation )
{
    TypeParam param{};
    const typename TypeParam::TestTypesType::DecoderSchemaType decoder{ TypeParam::TestTypesType::m_RSSchema::schema };
    const auto& generating_elements{ TypeParam::TestTypesType::m_RSSchema::schema.generating_elements };

    constexpr auto parameters{ GetReedSolomonParameters( TypeParam::TestTypesType::m_RSSchema::n, TypeParam::TestTypesType::m_RSSchema::k ) };
    
    ASSERT_TRUE( parameters.d % 2 == 1 );
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

        // There is no guarantee that these are actually unrecoverable
        introduce_any_errors<
            TypeParam::TestTypesType::m_RSSchema::n,
            TypeParam::TestTypesType::m_RSSchema::k,
            TypeParam::TestTypesType::m_RSSchema::Prime,
            TypeParam::TestTypesType::m_RSSchema::Exponent
            >( parameters.e+1, signal );

        EXPECT_FALSE( decoder.Decode( signal ).has_value() );
    }
}

// TODO:
//   - Not all of these correct to a different value
// TYPED_TEST( IErrorDecoderSchemaTests, PolyToSignalToPolyIncorrectlyRecovered )
// {
//     TypeParam param{};
//     const typename TypeParam::TestTypesType::DecoderSchemaType decoder{ TypeParam::TestTypesType::m_RSSchema::schema };
//     const auto& generating_elements{ TypeParam::TestTypesType::m_RSSchema::schema.generating_elements };
// 
//     constexpr size_t e{ GetReedSolomonParameters( TypeParam::TestTypesType::m_RSSchema::n, TypeParam::TestTypesType::m_RSSchema::k ).e };
//     
//     ASSERT_THAT( param.polynomials, ::testing::Not( ::testing::IsEmpty() ) );
//     for( const auto& polynomial : param.polynomials )
//     {
//         typename BlockCodeOverFiniteFieldSchema<TypeParam::TestTypesType::m_RSSchema>::Signal signal{};
//         PolynomialToCodeword<
//             TypeParam::TestTypesType::m_RSSchema::n,
//             TypeParam::TestTypesType::m_RSSchema::k,
//             TypeParam::TestTypesType::m_RSSchema::Prime,
//             TypeParam::TestTypesType::m_RSSchema::Exponent
//             >( generating_elements, signal, 0, polynomial );
// 
//         // There is no guarantee that these are actually incorrectly recovered
//         introduce_any_errors<
//             TypeParam::TestTypesType::m_RSSchema::n,
//             TypeParam::TestTypesType::m_RSSchema::k,
//             TypeParam::TestTypesType::m_RSSchema::Prime,
//             TypeParam::TestTypesType::m_RSSchema::Exponent
//             >( e+2, signal );
// 
//         EXPECT_TRUE( decoder.Decode( signal ).has_value() );
//         EXPECT_NE( polynomial, decoder.Decode( signal ).value() );
//     }
// }

