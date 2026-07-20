#include "reed-solomon-codes/IEncoderSchema.h"
#include "reed-solomon-codes/SimpleEncoderSchema.h"
#include "reed-solomon-codes/SystematicEncoderSchema.h"

#include "tests/finite-fields-tests/helpers/InitializerHelper.h"

#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include <vector>

namespace
{
    constexpr integer Prime{ 2 };
    constexpr integer Exponent{ 16 };
    constexpr std::size_t k{ 2 };
    constexpr std::size_t n{ 4 };

    const ElementOfFiniteField<Prime, Exponent> argument_one{
		x_to( 1,0 ).evaluate<PolynomialOverPrimeSizeFiniteField<Prime,Exponent-1>>()
	};

	const ElementOfFiniteField<Prime, Exponent> argument_two{
		x_to( 1,1 ).evaluate<PolynomialOverPrimeSizeFiniteField<Prime,Exponent-1>>()
	};

	const ElementOfFiniteField<Prime, Exponent> argument_three{
		x_to( 1,2 ).evaluate<PolynomialOverPrimeSizeFiniteField<Prime,Exponent-1>>()
	};

	const ElementOfFiniteField<Prime, Exponent> argument_four{
		x_to( 1,3 ).evaluate<PolynomialOverPrimeSizeFiniteField<Prime,Exponent-1>>()
	};

    template <typename T>
    class IEncoderSchemaTests : public testing::Test
    {
    public:
        std::vector<Message<n, k, Prime, Exponent>> messages{
            std::array<ElementOfFiniteField<Prime, Exponent>, k>
            {
                ElementOfFiniteField<Prime, Exponent>{
                    ( x_to( 1,0 ) + x_to( 1,1 ) ).evaluate<PolynomialOverPrimeSizeFiniteField<Prime,Exponent-1>>()
                },
                ElementOfFiniteField<Prime, Exponent>{
                    ( x_to( 1,1 ) + x_to( 1,2 ) ).evaluate<PolynomialOverPrimeSizeFiniteField<Prime,Exponent-1>>()
                }
            },
            std::array<ElementOfFiniteField<Prime, Exponent>, k>
            {
                ElementOfFiniteField<Prime, Exponent>{
                    ( x_to( 1,2 ) + x_to( 1,3 ) ).evaluate<PolynomialOverPrimeSizeFiniteField<Prime,Exponent-1>>()
                },
                ElementOfFiniteField<Prime, Exponent>{
                    ( x_to( 1,3 ) + x_to( 1,4 ) ).evaluate<PolynomialOverPrimeSizeFiniteField<Prime,Exponent-1>>()
                }
            },
            std::array<ElementOfFiniteField<Prime, Exponent>, k>
            {
                ElementOfFiniteField<Prime, Exponent>{
                    ( x_to( 1,0 ) + x_to( 1,2 ) ).evaluate<PolynomialOverPrimeSizeFiniteField<Prime,Exponent-1>>()
                },
                ElementOfFiniteField<Prime, Exponent>{
                    ( x_to( 1,1 ) + x_to( 1,4 ) ).evaluate<PolynomialOverPrimeSizeFiniteField<Prime,Exponent-1>>()
                }
            },
            std::array<ElementOfFiniteField<Prime, Exponent>, k>
            {
                ElementOfFiniteField<Prime, Exponent>{
                    ( x_to( 1,2 ) + x_to( 1,6 ) ).evaluate<PolynomialOverPrimeSizeFiniteField<Prime,Exponent-1>>()
                },
                ElementOfFiniteField<Prime, Exponent>{
                    ( x_to( 1,3 ) + x_to( 1,0 ) ).evaluate<PolynomialOverPrimeSizeFiniteField<Prime,Exponent-1>>()
                }
            },
            std::array<ElementOfFiniteField<Prime, Exponent>, k>
            {
                ElementOfFiniteField<Prime, Exponent>{
                    ( x_to( 1,2 ) + x_to( 1,3 ) ).evaluate<PolynomialOverPrimeSizeFiniteField<Prime,Exponent-1>>()
                },
                ElementOfFiniteField<Prime, Exponent>{
                    ( x_to( 1,5 ) + x_to( 1,7 ) ).evaluate<PolynomialOverPrimeSizeFiniteField<Prime,Exponent-1>>()
                }
            },
            std::array<ElementOfFiniteField<Prime, Exponent>, k>
            {
                ElementOfFiniteField<Prime, Exponent>{
                    ( x_to( 1,3 ) + x_to( 1,5 ) ).evaluate<PolynomialOverPrimeSizeFiniteField<Prime,Exponent-1>>()
                },
                ElementOfFiniteField<Prime, Exponent>{
                    ( x_to( 1,1 ) + x_to( 1,3 ) ).evaluate<PolynomialOverPrimeSizeFiniteField<Prime,Exponent-1>>()
                }
            },
            std::array<ElementOfFiniteField<Prime, Exponent>, k>
            {
                ElementOfFiniteField<Prime, Exponent>{
                    ( x_to( 0,0 ) + x_to( 0,1 ) ).evaluate<PolynomialOverPrimeSizeFiniteField<Prime,Exponent-1>>()
                },
                ElementOfFiniteField<Prime, Exponent>{
                    ( x_to( 0,0 ) + x_to( 0,1 ) ).evaluate<PolynomialOverPrimeSizeFiniteField<Prime,Exponent-1>>()
                }
            },
            std::array<ElementOfFiniteField<Prime, Exponent>, k>
            {
                ElementOfFiniteField<Prime, Exponent>{
                    ( x_to( 0,0 ) + x_to( 0,1 ) ).evaluate<PolynomialOverPrimeSizeFiniteField<Prime,Exponent-1>>()
                },
                ElementOfFiniteField<Prime, Exponent>{
                    ( x_to( 0,0 ) + x_to( 0,1 ) ).evaluate<PolynomialOverPrimeSizeFiniteField<Prime,Exponent-1>>()
                }
            }
        };

        Schema<n, k, Prime, Exponent> generating_elements_schema{
            std::array<ElementOfFiniteField<Prime, Exponent>,n>{ argument_one, argument_two, argument_three, argument_four }
        };
    };

    using IEncoderSchemaImpls = testing::Types<SimpleEncoderSchema<n,k,Prime,Exponent>, SystematicEncoderSchema<n,k,Prime,Exponent>>;

    TYPED_TEST_SUITE( IEncoderSchemaTests, IEncoderSchemaImpls );
}

TYPED_TEST( IEncoderSchemaTests, EncodeDecodeInvertsCorrectly )
{
    TypeParam encoder{ generating_elements_schema };
    for( const auto& message : messages )
    {
        EXPECT_EQ( message, encoder.PolynomialToMessage( encoder.MessageToPolynomial( message ) ) );
    }
}

