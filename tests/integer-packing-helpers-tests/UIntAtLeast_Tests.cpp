#include "integer-packing-helpers/UIntAtLeast.h"

#include "gtest/gtest.h"

#include <type_traits>

TEST( UintAtLeastTests, SanityChecks )
{
    const bool For1IsSameAsUint8{ std::is_same_v<u_atleast_t<1>, uint8_t> };
    EXPECT_TRUE( For1IsSameAsUint8 );
    
    const bool For9IsSameAsUint16{ std::is_same_v<u_atleast_t<9>, uint16_t> };
    EXPECT_TRUE( For9IsSameAsUint16 );
}

