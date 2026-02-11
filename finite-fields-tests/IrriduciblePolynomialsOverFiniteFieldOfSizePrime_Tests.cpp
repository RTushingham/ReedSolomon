#pragma once

#include "finite-fields/IrriduciblePolynomialsOverFiniteFieldOfSizePrime.h"

#include "test-data/IrriduciblePolynomial.h"

#include "gtest/gtest.h"

TEST( irriduciblePolynomialGenerationTest, MatchesPrecalculated )
{
	constexpr const auto output = GetIrriduciblePolynomial<101, 2>();

	EXPECT_EQ( output, irriducible );
}

TEST( irriduciblePolynomialGenerationTest, Slow )
{
	constexpr const auto output = GetIrriduciblePolynomial<101, 27>();

	// haven't calculated this yet
	EXPECT_NE( output, irriducible.Oversize<27>() );
}
