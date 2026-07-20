#include "reed-solomon-codes/BlockCodeParameters.h"

#include "gtest/gtest.h"

TEST( BlockCodeParametersTests, EvenHammingDistance )
{
    constexpr auto params{ BlockCodeParameters::CreateFromBlockLengthMessageLengthHammingDistance
        (
            7,
            3,
            4
        )
    };

	EXPECT_EQ( params.n, 7 );
	EXPECT_EQ( params.k, 3 );
	EXPECT_EQ( params.d, 4 );
	EXPECT_EQ( params.e, 1 );
}

TEST( BlockCodeParametersTests, OddHammingDistance )
{
    constexpr auto params{ BlockCodeParameters::CreateFromBlockLengthMessageLengthHammingDistance
        (
            7,
            2,
            5
        )
    };

	EXPECT_EQ( params.n, 7 );
	EXPECT_EQ( params.k, 2 );
	EXPECT_EQ( params.d, 5 );
	EXPECT_EQ( params.e, 2 );
}
