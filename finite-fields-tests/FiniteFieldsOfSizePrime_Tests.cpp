#include "finite-fields/FiniteFieldsOfSizePrime.h"

#include "gtest/gtest.h"

#include <vector>

constexpr integer Prime{ 101 };

// This is the original implementation of the corresponding method but moved to a free function.
//   I moved it here primarily as an explanation of what the now optimized method version is doing
//   and because I may as well test the new version against this.
template<integer Prime>
ElementOfFiniteFieldP<Prime> FindMultiplicativeInverse_Simple( const ElementOfFiniteFieldP<Prime>& input )
{
    // For all n such that 0 < n < p, we have that n and p are coprime.
    //   Because they are coprime the Greatest Common Denominator is 1.
    //   Using the Extended Euclidean Algorithm we can find an a and b such that a*p + b*n = 1.
    //   Which is equivalent to 1 = a*p + (-b)n which implies (-b)n = 1 modulo p
    //   So ( -b % p ) will be multiplicative inverse of n within this finite field.
    
    if( input.value==0 )
    {
        throw;
    }
    
    std::vector<integer> remainders{ Prime, input.value };
    std::vector<integer> multiplying_factors{};
    
    integer larger_remainder = remainders.at(0);
    integer smaller_remainder = remainders.at(1);
    do
    {
        remainders.push_back( larger_remainder % smaller_remainder );
        multiplying_factors.push_back( larger_remainder / smaller_remainder );
        
        larger_remainder = smaller_remainder;
        smaller_remainder = remainders.back();
    }
    while(remainders.back() != 0);
    
    // I'm going to track things in the form:
    //   pMultiplyer[i]*p + nMultiplyer[i]*n = remainder[i]  (where this is valid from i=0 onwards)
    // Proved that doing so is valid can be done by induction.
    //   Finding the solution is equivalent to providing this explanation.
    //
    // We have the initial values because 
    //   p = remainder[0]  <=>  1*p + 0*n = remainder[0]
    //   n = remainder[1]  <=>  0*p + 1*n = remainder[1]
    std::vector<integer> pMultiplyer{ 1, 0 };
    std::vector<integer> nMultiplyer{ 0, 1 };
    //
    // Because for all i >= 0
    //   remainders[i] = remainders[i+1] * multiplying_factors[i] + remainders[i+2]
    // and if for all k < i+2
    //   pMultiplyer[k]*p + nMultiplyer[k]*n = remainder[k]  (where this is valid from i=0 onwards)
    // we get
    //   pMultiplyer[i]*p + nMultiplyer[i]*n = ( pMultiplyer[i+1]*p + nMultiplyer[i+1]*n ) * multiplying_factors[i] + remainders[i+2]
    //    <=>
    //   (pMultiplyer[i] - pMultiplyer[i+1]*multiplying_factors[i])*p + (nMultiplyer[i] - nMultiplyer[i+1]*multiplying_factors[i])*n = remainders[i+2]
    //     =>
    //   pMultiplyer[i+2] = pMultiplyer[i] - pMultiplyer[i+1]*multiplying_factors[i]  and  nMultiplyer[i+2] = nMultiplyer[i] - nMultiplyer[i+1]*multiplying_factors[i]
    
    for( std::size_t multiplying_factors_index = 0; multiplying_factors_index<multiplying_factors.size(); multiplying_factors_index++ )
    {
        // this will be at position multiplying_factors_index + 2
        pMultiplyer.push_back( pMultiplyer.at(multiplying_factors_index) - pMultiplyer.at(multiplying_factors_index+1) * multiplying_factors.at(multiplying_factors_index) );
        nMultiplyer.push_back( nMultiplyer.at(multiplying_factors_index) - nMultiplyer.at(multiplying_factors_index+1) * multiplying_factors.at(multiplying_factors_index) );
    }
    
    std::size_t index_of_remainder_one{ (std::size_t)-1 };
    for( std::size_t remainders_index = 0; remainders_index<remainders.size(); remainders_index++ )
    {
        if( remainders[remainders_index] == 1 )
            index_of_remainder_one = remainders_index;
    }
    if( index_of_remainder_one == -1 )
    {
        // dev error
        throw;
    }
    
    // Because
    //   pMultiplyer[index_of_remainder_one]*p + nMultiplyer[index_of_remainder_one]*n = remainder[index_of_remainder_one] = 1
    //     =>
    //   'the multiplicative inverse of n in this field' = nMultiplyer[index_of_remainder_one] % p
    return ElementOfFiniteFieldP<Prime>{ nMultiplyer[index_of_remainder_one] % Prime };
}


TEST( PrimeFieldTests, AllInversesAreInverses )
{
	for( integer non_zero_element = 1; non_zero_element < Prime; non_zero_element++ )
	{
		ElementOfFiniteFieldP<Prime> a{ non_zero_element };
        EXPECT_EQ( (a*a.FindMultiplicativeInverse()), 1 ) << "New value: " << a.value << "Inverse value: " << a.FindMultiplicativeInverse().value;
	}
}

TEST( PrimeFieldTests, ClassIsConstexprInstantiable )
{
	constexpr ElementOfFiniteFieldP<Prime> a{ 52 };
}

TEST( PrimeFieldTests, InverseFindingClassMethodAndOriginalImplAgree )
{
	for( integer non_zero_element = 1; non_zero_element < Prime; non_zero_element++ )
    {
        ElementOfFiniteFieldP<Prime> a{ non_zero_element };
        EXPECT_EQ( FindMultiplicativeInverse_Simple<Prime>(a), a.FindMultiplicativeInverse() );
    }
}
