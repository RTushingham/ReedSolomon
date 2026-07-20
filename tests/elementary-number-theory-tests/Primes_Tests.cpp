#include "elementary-number-theory/Primes.h"

#include "gtest/gtest.h"

const std::vector<unsigned> manually_calculated_up_to_121 {2,3,5,7,11,13,17,19,23,29,31,37,41,43,47,53,59,61,67,71,73,79,83,89,97,101,103,107,109,113};

TEST( PrimesTests, AllPrimesUntil121 )
{
	const auto a = AllPrimesUntil(121);

	EXPECT_EQ( AllPrimesUntil(121), manually_calculated_up_to_121 );
}
