#include "reed-solomon-decoders/IErrorDecoderSchema.h"
#include "reed-solomon-decoders/GeoDecoderSchema.h"

#include "reed-solomon-codes/EncoderBase.h"

#include "helpers/ErrorIntroduction.h"

#include "finite-fields-polynomials/PolynomialsOverFiniteFieldOfSizePrimeToAPower.h"
#include "reed-solomon-codes/Code.h"
#include "reed-solomon-codes/Codeword.h"

#include "finite-fields-tests/helpers/InitializerHelper.h"

#include "gmock/gmock.h"
#include "gtest/gtest.h"

#include <vector>

class TempDataAndSchema
{
    // GF parameters
    //   - ( irriducible_polynomial is hidden )
    // Block Parameters
public:
    static constexpr integer Prime{ 101 };
    static constexpr integer Exponent{ 2 };
    static constexpr std::size_t n{ 4 };
    static constexpr std::size_t k{ 2 };

    constexpr static BlockCodeParameters code_parameters{ GetReedSolomonParameters( n, k ) };

    // RS parameters - trivial
    //   - ( these could be done by templating on the above )

    using m_Signal = Signal<n,k,Prime,Exponent>;
    // this is function
    static void m_PolynomialToCodeword( const std::array<ElementOfFiniteField<Prime,Exponent>, n>& generating_elements, Codeword<n, k, Prime, Exponent>& blocks, size_t start_index, const PolynomialOverFiniteField<Prime,Exponent,k-1>& generator_polynomial )
    {
        return PolynomialToCodeword<n,k,Prime,Exponent>( generating_elements, blocks, start_index, generator_polynomial );
    }

    // RS parameters
private:
    static constexpr Schema<n, k, Prime, Exponent> GetSchema()
    {
        constexpr ElementOfFiniteField<Prime, Exponent> argument_one{
            (x_to( 9,0 ) + x_to( 8, 1 )).evaluate<PolynomialOverPrimeSizeFiniteField<Prime,k-1>>()
        };

        constexpr ElementOfFiniteField<Prime, Exponent> argument_two{
            (x_to( 10,0 ) + x_to( 11, 1 )).evaluate<PolynomialOverPrimeSizeFiniteField<Prime,k-1>>()
        };

        constexpr ElementOfFiniteField<Prime, Exponent> argument_three{
            (x_to( 12,0 ) + x_to( 13, 1 )).evaluate<PolynomialOverPrimeSizeFiniteField<Prime,k-1>>()
        };

        constexpr ElementOfFiniteField<Prime, Exponent> argument_four{
            (x_to( 14,0 ) + x_to( 15, 1 )).evaluate<PolynomialOverPrimeSizeFiniteField<Prime,k-1>>()
        };

        return {
            std::array<ElementOfFiniteField<Prime, Exponent>,n>{ 
                argument_one, 
                argument_two, 
                argument_three, 
                argument_four 
            }
        };
    }

public:
    const Schema<n, k, Prime, Exponent> generating_elements_schema{ GetSchema() };

    // individual class under test

    using DecoderType = GeoDecoderSchema<n,k,Prime,Exponent>;


    // individual test data
    //   - GF schema dependent
    //   - BlockParameters dependent
    //
    //   - ( potentially whole thing dependent... )

    const std::vector<PolynomialOverFiniteField<Prime,Exponent,k-1>> polynomials
    { 
        PolynomialOverFiniteField<Prime,Exponent,k-1> 
        {
            std::array<ElementOfFiniteField<Prime, Exponent>, 2>
            {
                ElementOfFiniteField<Prime, Exponent>{
                    (x_to( 4,0 ) + x_to( 5, 1 )).evaluate<PolynomialOverPrimeSizeFiniteField<Prime,1>>()
                },
                ElementOfFiniteField<Prime, Exponent>{
                    (x_to( 7,0 ) + x_to( 6, 1 )).evaluate<PolynomialOverPrimeSizeFiniteField<Prime,1>>()
                }
            } 
        },
        PolynomialOverFiniteField<Prime,Exponent,k-1> 
        {
            std::array<ElementOfFiniteField<Prime, Exponent>, 2>
            {
                ElementOfFiniteField<Prime, Exponent>{
                    (x_to( 100,0 ) + x_to( 56, 1 )).evaluate<PolynomialOverPrimeSizeFiniteField<Prime,1>>()
                },
                ElementOfFiniteField<Prime, Exponent>{
                    (x_to( 1,0 ) + x_to( 23, 1 )).evaluate<PolynomialOverPrimeSizeFiniteField<Prime,1>>()
                }
            } 
        },
        PolynomialOverFiniteField<Prime,Exponent,k-1> 
        {
            std::array<ElementOfFiniteField<Prime, Exponent>, 2>
            {
                ElementOfFiniteField<Prime, Exponent>{
                    (x_to( 0,0 ) + x_to( 0, 1 )).evaluate<PolynomialOverPrimeSizeFiniteField<Prime,1>>()
                },
                ElementOfFiniteField<Prime, Exponent>{
                    (x_to( 0,0 ) + x_to( 0, 1 )).evaluate<PolynomialOverPrimeSizeFiniteField<Prime,1>>()
                }
            } 
        },
        PolynomialOverFiniteField<Prime,Exponent,k-1> 
        {
            std::array<ElementOfFiniteField<Prime, Exponent>, 2>
            {
                ElementOfFiniteField<Prime, Exponent>{
                    (x_to( 2,0 ) + x_to( 3, 1 )).evaluate<PolynomialOverPrimeSizeFiniteField<Prime,1>>()
                },
                ElementOfFiniteField<Prime, Exponent>{
                    (x_to( 5,0 ) + x_to( 7, 1 )).evaluate<PolynomialOverPrimeSizeFiniteField<Prime,1>>()
                }
            } 
        },
        PolynomialOverFiniteField<Prime,Exponent,k-1> 
        {
            std::array<ElementOfFiniteField<Prime, Exponent>, 2>
            {
                ElementOfFiniteField<Prime, Exponent>{
                    (x_to( 11,0 ) + x_to( 13, 1 )).evaluate<PolynomialOverPrimeSizeFiniteField<Prime,1>>()
                },
                ElementOfFiniteField<Prime, Exponent>{
                    (x_to( 17,0 ) + x_to( 19, 1 )).evaluate<PolynomialOverPrimeSizeFiniteField<Prime,1>>()
                }
            } 
        },
        PolynomialOverFiniteField<Prime,Exponent,k-1> 
        {
            std::array<ElementOfFiniteField<Prime, Exponent>, 2>
            {
                ElementOfFiniteField<Prime, Exponent>{
                    (x_to( 23,0 ) + x_to( 29, 1 )).evaluate<PolynomialOverPrimeSizeFiniteField<Prime,1>>()
                },
                ElementOfFiniteField<Prime, Exponent>{
                    (x_to( 31,0 ) + x_to( 37, 1 )).evaluate<PolynomialOverPrimeSizeFiniteField<Prime,1>>()
                }
            } 
        },
        PolynomialOverFiniteField<Prime,Exponent,k-1> 
        {
            std::array<ElementOfFiniteField<Prime, Exponent>, 2>
            {
                ElementOfFiniteField<Prime, Exponent>{
                    (x_to( 41,0 ) + x_to( 43, 1 )).evaluate<PolynomialOverPrimeSizeFiniteField<Prime,1>>()
                },
                ElementOfFiniteField<Prime, Exponent>{
                    (x_to( 47,0 ) + x_to( 53, 1 )).evaluate<PolynomialOverPrimeSizeFiniteField<Prime,1>>()
                }
            } 
        }
    };
};


namespace
{
    template <typename T>
    class IErrorDecoderSchemaTests : public testing::Test
    {
    public:
    };

    using IErrorDecoderSchemaImpls = testing::Types<TempDataAndSchema>;

    TYPED_TEST_SUITE( IErrorDecoderSchemaTests, IErrorDecoderSchemaImpls );
}

TYPED_TEST( IErrorDecoderSchemaTests, PolyToSignalToPolyNoErrorCase )
{
    const auto& generating_elements_schema{ TypeParam{}.generating_elements_schema };
    const auto& polynomials{ TypeParam{}.polynomials };

    TypeParam::DecoderType decoder{ generating_elements_schema };

    for( const auto& polynomial : polynomials )
    {
        TypeParam::m_Signal codeword;
        TypeParam::m_PolynomialToCodeword( generating_elements_schema.generating_elements, codeword, 0, polynomial );

        EXPECT_TRUE( decoder.Decode( codeword ).has_value() );
        EXPECT_EQ( polynomial, decoder.Decode( codeword ).value() );
    }
}

