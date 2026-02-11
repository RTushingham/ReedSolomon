#include "elementary-number-theory/PrimeFactorisation.h"

#include "gtest/gtest.h"

TEST( DiscreteLogCeilingTests, Powers )
{
	EXPECT_EQ( discrete_log_ceiling( 1, 2 ), 0 );
	EXPECT_EQ( discrete_log_ceiling( 2, 2 ), 1 );
	EXPECT_EQ( discrete_log_ceiling( 4, 2 ), 2 );

	EXPECT_EQ( discrete_log_ceiling( 1, 5 ), 0 );
	EXPECT_EQ( discrete_log_ceiling( 5, 5 ), 1 );
	EXPECT_EQ( discrete_log_ceiling( 25, 5 ), 2 );
	EXPECT_EQ( discrete_log_ceiling( 125, 5 ), 3 );
}

TEST( DiscreteLogCeilingTests, NonPowers )
{
	EXPECT_EQ( discrete_log_ceiling( 3, 2 ), 2 );

	EXPECT_EQ( discrete_log_ceiling( 2, 5 ), 1 );
	EXPECT_EQ( discrete_log_ceiling( 4, 5 ), 1 );
	EXPECT_EQ( discrete_log_ceiling( 6, 5 ), 2 );
	EXPECT_EQ( discrete_log_ceiling( 24, 5 ), 2 );
	EXPECT_EQ( discrete_log_ceiling( 26, 5 ), 3 );
	EXPECT_EQ( discrete_log_ceiling( 124, 5 ), 3 );
	EXPECT_EQ( discrete_log_ceiling( 126, 5 ), 4 );
}

TEST( DiscreteLogCeilingTests, ErrorCase )
{
    EXPECT_EQ( discrete_log_ceiling( 0, 2 ), 0 );
}


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
