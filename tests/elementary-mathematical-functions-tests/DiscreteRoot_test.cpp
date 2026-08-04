#include "elementary-mathematical-functions/DiscreteRoot.h"

#include "gtest/gtest.h"

// discrete_sqrt_ceiling

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
	EXPECT_EQ( discrete_sqrt_ceiling( 2 ), 2 );

	EXPECT_EQ( discrete_sqrt_ceiling( 3 ), 2 );
	EXPECT_EQ( discrete_sqrt_ceiling( 5 ), 3 );

	EXPECT_EQ( discrete_sqrt_ceiling( 8 ), 3 );
	EXPECT_EQ( discrete_sqrt_ceiling( 10 ), 4 );

	EXPECT_EQ( discrete_sqrt_ceiling( 35 ), 6 );
	EXPECT_EQ( discrete_sqrt_ceiling( 37 ), 7 );

	EXPECT_EQ( discrete_sqrt_ceiling( 224 ), 15 );
	EXPECT_EQ( discrete_sqrt_ceiling( 226 ), 16 );
}

TEST( DiscreteSquareRootCeilingTests, IsConstexpr )
{
	constexpr auto result{ discrete_sqrt_ceiling( 8 ) };

	EXPECT_EQ( 3, result );
}


// discrete_root_ceiling

TEST( DiscreteRootCeilingTests, Trivial )
{
	EXPECT_EQ( discrete_root_ceiling( 0, 1 ), 0 );
	EXPECT_EQ( discrete_root_ceiling( 1, 1 ), 1 );
	EXPECT_EQ( discrete_root_ceiling( 8, 1 ), 8 );
	EXPECT_EQ( discrete_root_ceiling( 27, 1 ), 27 );
	EXPECT_EQ( discrete_root_ceiling( 216, 1 ), 216 );
	EXPECT_EQ( discrete_root_ceiling( 3375, 1 ), 3375 );
}

TEST( DiscreteRootCeilingTests, Cubes )
{
	EXPECT_EQ( discrete_root_ceiling( 0, 3 ), 0 );
	EXPECT_EQ( discrete_root_ceiling( 1, 3 ), 1 );
	EXPECT_EQ( discrete_root_ceiling( 8, 3 ), 2 );
	EXPECT_EQ( discrete_root_ceiling( 27, 3 ), 3 );
	EXPECT_EQ( discrete_root_ceiling( 216, 3 ), 6 );
	EXPECT_EQ( discrete_root_ceiling( 3375, 3 ), 15 );
}

TEST( DiscreteRootCeilingTests, NonCubes )
{
	EXPECT_EQ( discrete_root_ceiling( 2, 3 ), 2 );

	EXPECT_EQ( discrete_root_ceiling( 7, 3 ), 2 );
	EXPECT_EQ( discrete_root_ceiling( 9, 3 ), 3 );

	EXPECT_EQ( discrete_root_ceiling( 26, 3 ), 3 );
	EXPECT_EQ( discrete_root_ceiling( 28, 3 ), 4 );

	EXPECT_EQ( discrete_root_ceiling( 215, 3 ), 6 );
	EXPECT_EQ( discrete_root_ceiling( 217, 3 ), 7 );

	EXPECT_EQ( discrete_root_ceiling( 3374, 3 ), 15 );
	EXPECT_EQ( discrete_root_ceiling( 3376, 3 ), 16 );
}

TEST( DiscreteRootCeilingTests, IsConstexpr )
{
	constexpr auto result{ discrete_root_ceiling( 7, 3 ) };

	EXPECT_EQ( 2, result );
}

TEST( DiscreteRootCeilingTests, IfZeroAsExponentThrow )
{
	EXPECT_ANY_THROW( discrete_root_ceiling( 4, 0 ) );
}

#include "elementary-mathematical-functions/IntegerPowers.h"

TEST( DiscreteRootCeilingTests, GeneratedData )
{
	EXPECT_EQ( discrete_root_ceiling( int_pow( 2, 4 ), 4 ), 2 );
	EXPECT_EQ( discrete_root_ceiling( int_pow( 2, 4 )-1, 4 ), 2 );
	EXPECT_EQ( discrete_root_ceiling( int_pow( 2, 4 )+1, 4 ), 3 );

	EXPECT_EQ( discrete_root_ceiling( int_pow( 3, 7 ), 7 ), 3 );
}

