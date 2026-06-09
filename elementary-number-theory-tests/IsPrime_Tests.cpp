#include "elementary-number-theory/IsPrime.h"

#include "gtest/gtest.h"

const std::vector<unsigned> manually_calculated_up_to_121 {2,3,5,7,11,13,17,19,23,29,31,37,41,43,47,53,59,61,67,71,73,79,83,89,97,101,103,107,109,113};

TEST( IsPrimeTests, AllPrimesUntil121 )
{
	EXPECT_FALSE( IsPrime( 0 ) ) << "0 is a special case, so is being treates as not prime";
	EXPECT_FALSE( IsPrime( 1 ) ) << "1 is a special case, so is being treates as not prime";

	for( unsigned candidate{ 2 }; candidate < 121; candidate++ )
	{
		if( std::find( manually_calculated_up_to_121.begin(), manually_calculated_up_to_121.end(), candidate ) == manually_calculated_up_to_121.end() )
		{
			EXPECT_FALSE( IsPrime( candidate ) );
		}
		else
		{
			EXPECT_TRUE( IsPrime( candidate ) );
		}
	}
}
