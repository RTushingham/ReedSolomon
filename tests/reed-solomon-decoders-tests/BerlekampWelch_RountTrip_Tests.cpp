/*
#include "reed-solomon-decoders/BerlekampWelch.h"

#include "helpers/ErrorIntroduction.h"

#include "tests/finite-fields-tests/binary-helpers/CharToElm.h"

#include "tests/finite-fields-tests/helpers/InitializerHelper.h"
#include "integer-packing-helpers/UIntAtLeast.h"

#include "gmock/gmock.h"
#include "gtest/gtest.h"

#include <bitset>
#include <vector>

constexpr integer Prime{ 2 };

// TODO:
//   - Rename this to decoder tests
namespace TestCaseTwo
{
    // TODO:
    //   - Make this part of config
    constexpr integer Prime{ 2 };
    constexpr integer Exponent{ 8 };
    constexpr std::size_t k{ 4 };
    constexpr std::size_t n{ 8 };

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

	const ElementOfFiniteField<Prime, Exponent> argument_five{
		x_to( 1,4 ).evaluate<PolynomialOverPrimeSizeFiniteField<Prime,Exponent-1>>()
	};

	const ElementOfFiniteField<Prime, Exponent> argument_six{
		x_to( 1,5 ).evaluate<PolynomialOverPrimeSizeFiniteField<Prime,Exponent-1>>()
	};

	const ElementOfFiniteField<Prime, Exponent> argument_seven{
		x_to( 1,6 ).evaluate<PolynomialOverPrimeSizeFiniteField<Prime,Exponent-1>>()
	};

	const ElementOfFiniteField<Prime, Exponent> argument_eight{
		x_to( 1,7 ).evaluate<PolynomialOverPrimeSizeFiniteField<Prime,Exponent-1>>()
	};

	Code<n, k, Prime, Exponent> code{ std::array<ElementOfFiniteField<Prime, Exponent>,n>{ argument_one, argument_two, argument_three, argument_four, argument_five, argument_six, argument_seven, argument_eight } };
	const GeoDecoder<n, k, Prime, Exponent> decoder{ code };


    std::vector<Codeword<n, k, Prime, Exponent>> codewords{
        code.GenerateCodeword(
            std::array<ElementOfFiniteField<Prime,Exponent>, k>{
                char_to_elm<Exponent>( (uint8_t)-1 ),
                char_to_elm<Exponent>( (uint8_t)-1 ),
                char_to_elm<Exponent>( (uint8_t)-1 ),
                char_to_elm<Exponent>( (uint8_t)-1 )
            }
        ),
        code.GenerateCodeword(
            std::array<ElementOfFiniteField<Prime,Exponent>, k>{
                char_to_elm<Exponent>( (uint8_t)0b10000000 ),
                char_to_elm<Exponent>( (uint8_t)0b10001110 ),
                char_to_elm<Exponent>( (uint8_t)0b00010101 ),
                char_to_elm<Exponent>( (uint8_t)0b11010001 )
            }
        ),
        code.GenerateCodeword(
            std::array<ElementOfFiniteField<Prime,Exponent>, k>{
                char_to_elm<Exponent>( (uint8_t)0b00000101 ),
                char_to_elm<Exponent>( (uint8_t)0b00000010 ),
                char_to_elm<Exponent>( (uint8_t)0b11100001 ),
                char_to_elm<Exponent>( (uint8_t)0b11110111 )
            }
        ),
        code.GenerateCodeword(
            std::array<ElementOfFiniteField<Prime,Exponent>, k>{
                char_to_elm<Exponent>( (uint8_t)0b00110000 ),
                char_to_elm<Exponent>( (uint8_t)0b01101110 ),
                char_to_elm<Exponent>( (uint8_t)0b11101110 ),
                char_to_elm<Exponent>( (uint8_t)0b10001110 )
            }
        ),
        code.GenerateCodeword(
            std::array<ElementOfFiniteField<Prime,Exponent>, k>{
                char_to_elm<Exponent>( (uint8_t)0b01100001 ),
                char_to_elm<Exponent>( (uint8_t)0b10101101 ),
                char_to_elm<Exponent>( (uint8_t)0b00110101 ),
                char_to_elm<Exponent>( (uint8_t)0b10100001 )
            }
        ),
        code.GenerateCodeword(
            std::array<ElementOfFiniteField<Prime,Exponent>, k>{
                char_to_elm<Exponent>( (uint8_t)0b11011000 ),
                char_to_elm<Exponent>( (uint8_t)0b11111110 ),
                char_to_elm<Exponent>( (uint8_t)0b11111101 ),
                char_to_elm<Exponent>( (uint8_t)0b00110100 )
            }
        ),
        code.GenerateCodeword(
            std::array<ElementOfFiniteField<Prime,Exponent>, k>{
                char_to_elm<Exponent>( (uint8_t)0b01000010 ),
                char_to_elm<Exponent>( (uint8_t)0b00011001 ),
                char_to_elm<Exponent>( (uint8_t)0b11010110 ),
                char_to_elm<Exponent>( (uint8_t)0b11110011 )
            }
        ),
        code.GenerateCodeword(
            std::array<ElementOfFiniteField<Prime,Exponent>, k>{
                char_to_elm<Exponent>( (uint8_t)86 ),
                char_to_elm<Exponent>( (uint8_t)12 ),
                char_to_elm<Exponent>( (uint8_t)255 ),
                char_to_elm<Exponent>( (uint8_t)32 )
            }
        ),
        code.GenerateCodeword(
            std::array<ElementOfFiniteField<Prime,Exponent>, k>{
                char_to_elm<Exponent>( (uint8_t)53 ),
                char_to_elm<Exponent>( (uint8_t)7 ),
                char_to_elm<Exponent>( (uint8_t)112 ),
                char_to_elm<Exponent>( (uint8_t)187 )
            }
        ),
        code.GenerateCodeword(
            std::array<ElementOfFiniteField<Prime,Exponent>, k>{
                char_to_elm<Exponent>( 0 ),
                char_to_elm<Exponent>( 0 ),
                char_to_elm<Exponent>( 0 ),
                char_to_elm<Exponent>( 0 )
            }
        ),
        code.GenerateCodeword(
            std::array<ElementOfFiniteField<Prime,Exponent>, k>{
                char_to_elm<Exponent>( 'c' ),
                char_to_elm<Exponent>( 'h' ),
                char_to_elm<Exponent>( ',' ),
                char_to_elm<Exponent>( 'o' )
            }
        )
    };

	const BerklekampWelchDecoder<n, k, Prime, Exponent> bw_decoder{ code };

    constexpr std::size_t e = (n-k)/2;
}

TEST( BerlekampWelchTestsTwo, CodewordToCodewordRoundTripSolvable )
{
    for( std::size_t error_count{ 0 }; error_count <= TestCaseTwo::e; error_count++ )
    {
        for( const auto& sent_signal : TestCaseTwo::codewords )
        {
            auto recieved_signal{ sent_signal };
            introduce_any_errors( error_count, recieved_signal );

            EXPECT_TRUE( TestCaseTwo::bw_decoder.Decode( recieved_signal ).has_value() ) << "error count: " << error_count;
            if( TestCaseTwo::bw_decoder.Decode( recieved_signal ).has_value() )
                EXPECT_EQ( sent_signal, TestCaseTwo::code.GenerateCodeword( TestCaseTwo::bw_decoder.Decode( recieved_signal ).value() ) ) << "error count: " << error_count;

            EXPECT_TRUE( TestCaseTwo::decoder.Decode( recieved_signal ).has_value() ) << "error count: " << error_count;
            if( TestCaseTwo::decoder.Decode( recieved_signal ).has_value() )
                EXPECT_EQ( sent_signal, TestCaseTwo::code.GenerateCodeword( TestCaseTwo::decoder.Decode( recieved_signal ).value() ) ) << "error count: " << error_count;
        }
    }
}

TEST( BerlekampWelchTestsTwo, OldUnsolvableCasesOneError )
{
    for( const auto& sent_signal : TestCaseTwo::codewords )
    {
        auto recieved_signal{ sent_signal };
        introduce_errors( std::vector<std::size_t>{6}, recieved_signal );

        // TODO:
        //   - Solve this
        // EXPECT_TRUE( TestCaseTwo::bw_decoder.Decode( recieved_signal ).has_value() );
        // if( TestCaseTwo::bw_decoder.Decode( recieved_signal ).has_value() )
        //     EXPECT_EQ( sent_signal, TestCaseTwo::code.GenerateCodeword( TestCaseTwo::bw_decoder.Decode( recieved_signal ).value() ) );

        EXPECT_TRUE( TestCaseTwo::decoder.Decode( recieved_signal ).has_value() );
        if( TestCaseTwo::decoder.Decode( recieved_signal ).has_value() )
            EXPECT_EQ( sent_signal, TestCaseTwo::code.GenerateCodeword( TestCaseTwo::decoder.Decode( recieved_signal ).value() ) );
    }
}

TEST( BerlekampWelchTestsTwo, OldUnsolvableCasesTwoErrors )
{
    for( const auto& sent_signal : TestCaseTwo::codewords )
    {
        auto recieved_signal{ sent_signal };
        introduce_errors( std::vector<std::size_t>{6,7}, recieved_signal );

        // TODO:
        //   - Solve this
        // EXPECT_TRUE( TestCaseTwo::bw_decoder.Decode( recieved_signal ).has_value() );
        // if( TestCaseTwo::bw_decoder.Decode( recieved_signal ).has_value() )
        //     EXPECT_EQ( sent_signal, TestCaseTwo::code.GenerateCodeword( TestCaseTwo::bw_decoder.Decode( recieved_signal ).value() ) );

        EXPECT_TRUE( TestCaseTwo::decoder.Decode( recieved_signal ).has_value() );
        if( TestCaseTwo::decoder.Decode( recieved_signal ).has_value() )
            EXPECT_EQ( sent_signal, TestCaseTwo::code.GenerateCodeword( TestCaseTwo::decoder.Decode( recieved_signal ).value() ) );
    }
}
*/

