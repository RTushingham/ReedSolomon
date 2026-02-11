#include "elementary-number-theory/IsPrime.h"

#include "gtest/gtest.h"

const std::vector<unsigned> manually_calculated_up_to_121 {2,3,5,7,11,13,17,19,23,29,31,37,41,43,47,53,59,61,67,71,73,79,83,89,97,101,103,107,109,113};

TEST( IsPrimeTests, AllPrimesUntil121 )
{
	EXPECT_FALSE( IsPrime( 0 ) );
	EXPECT_FALSE( IsPrime( 1 ) );

	for( const auto prime : manually_calculated_up_to_121 )
	{
		EXPECT_TRUE( IsPrime( prime ) );
	}
	
	EXPECT_FALSE( IsPrime( 4 ) );
}
