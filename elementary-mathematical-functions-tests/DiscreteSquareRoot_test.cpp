#include "elementary-mathematical-functions/DiscreteSquareRoot.h"

#include "gtest/gtest.h"

TEST( DiscreteSquareRootCeilingTests, Squares )
{
	EXPECT_EQ( discrete_sqrt_ceiling( 0 ), 0 );
	EXPECT_EQ( discrete_sqrt_ceiling( 1 ), 1 );
	EXPECT_EQ( discrete_sqrt_ceiling( 4 ), 2 );
	EXPECT_EQ( discrete_sqrt_ceiling( 9 ), 3 );
	EXPECT_EQ( discrete_sqrt_ceiling( 36 ), 6 );
	EXPECT_EQ( discrete_sqrt_ceiling( 225 ), 15 );
}

TEST( DiscreteSquareRootCeilingTests, NonSquares )
{
	EXPECT_EQ( discrete_sqrt_ceiling( 1 ), 1 );
	EXPECT_EQ( discrete_sqrt_ceiling( 2 ), 2 );
	EXPECT_EQ( discrete_sqrt_ceiling( 3 ), 2 );
	EXPECT_EQ( discrete_sqrt_ceiling( 5 ), 3 );
	EXPECT_EQ( discrete_sqrt_ceiling( 8 ), 3 );
	EXPECT_EQ( discrete_sqrt_ceiling( 10 ), 4 );
	EXPECT_EQ( discrete_sqrt_ceiling( 35 ), 6 );
	EXPECT_EQ( discrete_sqrt_ceiling( 212 ), 15 );
	EXPECT_EQ( discrete_sqrt_ceiling( 226 ), 16 );
}

