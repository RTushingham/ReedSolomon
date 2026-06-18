
This follows on from my last entry.

My last entry was entirely about block codes, a classification of error-correcting and error-detecting codes which the Reed-Solomon codes classify as.


## Reed-Solomon code block code parameters

First and foremost, Reed-Solomon codes are MDS codes, meaning `d = n - k + 1`, which means that `d` is equal to the theoretical maximum. This is one of the appeals of the Reed-Solomon codes.

One of the limitations of Reed-Solomon codes is that `k < n <= q`.

In our case `q = 2**w`, and so each block will be `w*n <= w*(2**w)` bits long with a message of length `w*k < w*n <= w*(2**w)` bits long.

If `w` is equal to `8` then each alphabet entry is the size of the smallest registry size, a byte. In this case `w*(2**w) = 2048`, so each block (and therefore each message) can be at most 256 bytes long.

Other codes such as _Geometric Goppa codes on the Rational Function Field_ exist which are MDS but have that `n <= q + 1`. From what I have seen that particular code is used far less use than the Reed-Solomon codes. Both codes are "linear codes" and so (from what I understand) have encoding and decoding algorithms in common with one another, but nevertheless one is more popular than the other. What this seems to imply is that specialist highly practical algorithms exist for encoding or decoding specifically Reed-Solomon codes. Otherwise, some other property (such as being cyclic, being highly list decodable, or something unknown to me at the moment) must be more useful in practice. I hope that through my investigation I am able to find out why.


## How do I pick a Reed-Solomon code configuration which optimizes performance? _- Computational complexity of finite field operations_

_This is a topic of ongoing study for me and is entirely self-taught. At the time of reading this may not understand the full extent of my understanding._

To revisit the last post R-S codes work by modelling the "alphabet entries" as elements of a finite field. What that means is that alphabet entries are assigned functions corresponding to addition, and multiplication, where both of these are invertible (thus defining valid subtraction and division functions).

Finite fields can have any size which can be expressed in the form `p**w` where `w` is a positive integer and `p` is a prime. Like before I will focus on the case there `p = 2`.



## Multiplication in finite fields

Each alphabet entry is a series of `w` bits, and is modelled as a polynomial degree at most `w-1` where each coefficient is an integer modulo `p`. Specifically, for multiplication these are modelled as polynomials of integers modulo `p` modulo an irreducible polynomial of degree `w`.

In our case where `p = 2` addition and subtraction on an alphabet entry are easy, it is just a logical `xor` on each of the bits which make up the alphabet entry.

For multiplication the simplest way of explaining what this boils down to is to contrast the modulo polynomial for of multiplication with normal binary integer multiplication modulo some power of `2`:

1. For integer multiplication of `a` and `b` each bit in `a*b` has a position `j`. Each bit in the final representation corresponds the `xor` combination of all pairs of bits in `a` and `b` where the sum of their positions in `a` and `b` sum to `j`. This is known as the Cauchy product.

2. For integer multiplication given `l` there exists `c` and `d < 2**l` such that `a*b = c*(2**l) + d`, and indeed `d = a*b % 2**l`. 

3. For integer multiplication modulo some power of two (say `2**l`) all bits corresponding to the term `c*(2**l)` are discarded and have no impact on `d`.

4. In this case `d` is said to be the "carry-less product" of `a` and `b`.

To change our focus to finite field multiplication:

1. If `l` is the degree of the irreducible polynomial `irr_pol(x)` then the previous calculation of `a*b = c*(2**l) + d` happens.

2. When `c` is non-zero the terms corresponding to `c*(2**l)` correspond to a polynomial `F(x)` of degree `> l-1` and `< 2*l`, specifically one in the form `F(x) = f(x) * x**(l-1)` where `f(x)` is a polynomial of degree `< l`.

3. We then need to find `g(x)` with `deg(g(x)) < l` such that there exists `h(x)` such that for normal polynomial multiplication `F(x) = h(x)*irr_pol(x) + g(x)`. Here `g(x)` is defined to be `F(x) % irr_pol(x)`.

4. `g(x) := F(x) % irr_pol(x)` is guaranteed to be non-zero (if `l > 1`) [1]. So when interpreted as a series of bits `g(x)` will be `h != 0`.

5. Because `d < 2**l` corresponds to a polynomial of degree `< l`, so `"d as a polynomial" % irr_pol(x) = "d as a polynomial"`.

6. So, with this form of multiplication `a*b = h + d` for some `h != 0`.

One way of calculating `h` is by calculating `x**j % irr_pol(x)` for all `l < j < 2l-1`. Because `(a(x) + b(x) % c(x)) = (a(x) % c(x)) + (b(x) % c(x))` for any three polynomials `a(x)`, `b(x)`, and `c(x)`. we can use the expression of `F(x)` as a series of coefficients of powers of `x**j` for many `l < j < 2l-1` to calculate `F(x) % irr_pol(x)`.

To view this as bit manipulation, where integer multiplication modulo some power of 2 differs from finite field multiplication is that the former is equal to the carry-less-product, while the latter is equal to the `xor` product of the carry-less-product and a bunch of precomputed magic numbers which are included or not included depending on what the otherwise discarded terms of the integer multiplication are.

To explain this in pseudo-code:
```
template <std::size_t w>
class ElementOfBinaryFiniteField<w, GF2Polynomial<w> irriducible_polynomial>
{
    GF2Polynomial<w-1> m_value;

	static constexpr std::array<GF2Polynomial<w-1>, w-1> CreateModuloMultiplicationResidues( const GF2Polynomial<w> & for_modulo )
    {
		std::array<GF2Polynomial<w-1>, w-1> residues{};
        for( std::size_t index{ 0 }; index < residues.size(); index++ )
        {
            GF2Polynomial<2*(w-1)> seed_polynomial{};
            seed_polynomial.Coeff( w + index ) = 1;
            residues.at( seed_polynomial % for_modulo );
        }
		return residues;
	};
	static constexpr std::array<GF2Polynomial<w-1>, w-1> residues{ CreateResidues( irriducible_polynomial ) };

public:

	// ...
	
	constexpr ElementOfBinaryFiniteField<w, irriducible_polynomial> operator*( const ElementOfBinaryFiniteField<w, irriducible_polynomial>& a ) const
	{
        GF2Polynomial<w-1> running_sum{};
        running_sum = CarryLessProduct( m_value, a.m_value );

        std::bitset<w-1> discarded_terms{};
        discarded_terms = CauchyProductExcessTerms( m_value, a.m_value );

		for( std::size_t residues_index{ 0 }; residues_index < residues.size(); residues++ )
		{
            if( discarded_terms.test( residues_index ) )
            {
                running_sum += residues.at( residues_index );
            }
		}

		return running_sum;
	}

	// ...
};
```

## Computational complexity of multiplication in finite fields.

_Lots of specialist hardware exists in the world, and hardware with instructions designed to perform finite field multiplication almost certainly exist already. I will talk about the general case here, especially because that corresponds to the general application development practice where binary are compiled to be run on all hardware and therefore do not make use of such specialist instructions._

_This is a topic of ongoing study for me and will not reflect my complete understanding even in the near future._

The computationally expensive part of this is the modulo portion of the calculation. This is because the problem is equivalent to long dividing the product of the two polynomials we wished to multiply by the irreducible polynomial which defines our schema. There are different ways of calculating this:
- One method is by performing long division by the irreducible polynomial on the polynomial you wish to find the modulo value of. This is the current methodology used in my implementation.
    - Similarly, this is a multi-step process, however the number of steps range from `0` to `w-1` steps. In my implementation at each step the degree needs to be calculated for a degree `2w-2` polynomial, perform multiplication on two degree `w-1` polynomials and one subtraction of polynomials of degree `2w-2`.
- The pseudo-code above, which is precomputing `x**j % irriducible_polynomial` for all `w =< j < 2*w-1` then using those values to normalize the polynomial you wish to find the modulo value of _(in this case the product of the two polynomials we are multiplying together)_.
    - This is a `w-1` step process which at each step which effectively performs one integers modulo `2` scalar multiplication by a `w-1` degree polynomial over integers modulo `2` and one polynomial addition for two polynomials of degree `w-1` over the integers modulo `2`. In big-O notation it is `O(w)` in scalar multiplication for a `w-1` degree polynomial and addition for `w-1` degree polynomials. 
    - This is similar to the long division above, but unlike the above this only works when the polynomial is known ahead of time. Additionally, for our `q = 2**w` example this takes up at least `(w-1)*w**2 = w**3 - w**2` bits in memory.

I do not know how calculating the carry-less product scales. It can either be done by a multiplication command which when `w` is equal to a register size does not require any modulo reduction.

Based on my current understanding, setting `w` to be equal to a register size is also significant because the form where a block is loaded into a form where arithmetic operations can be performed on it does not necessarily require any deserializing and unpacking relative to the form it was transferred in.


## Computational complexity of division in finite fields.

Based on my current understanding, dividing elements also becomes increasingly complex as `w` increases. This is because division requires finding the multiplicative inverse of an element, and my current way of doing that is by performing an extended Euclidean algorithm style algorithm between the irreducible polynomial and the polynomial you wish to invert to find the polynomial equivalents of the coefficients in the Bézout's identity.

If you wish to find the inverse of `f(x)` the EEA algorithm is a multi-step process which performs at most `deg( f(x) ) <= w-1` steps. At each step a polynomial long division is performed and a carry-less-product polynomial multiplication is performed. Polynomial long division is itself a multi-step process, however within a multiplicative inverse calculation only at most `deg( f(x) )` steps will be performed. Within each step one scalar division of a polynomial occurs, one carry-less-product multiplication occurs, one polynomial addition and one polynomial subtraction happens.


## Hypothesis: _R-S codes with equivalent message sizes but reduced `w` will be more computationally efficient than those without._

I want to test this, I am going to test two configs, `W,N,K` and `w,n,k`, against one another in a round trip `encoding -> introducing errors -> decoding` test:
 - `W=16`, `N=4`, `K=2` - denoted with upper case letters
 - `w=8`, `n=8`, `k=4` - denoted with lower case letters

I want to test this on my own implementation and on a highly optimized third-party implementation of the Reed-Solomon codes. I think the latter will win.

Here `W = 2*w`, but `2*N = n` and `2*K = k` so that the size in memory of messages and blocks stays the same. For both of these the message size is 32 bits, and the block size is 64 bits.

When well packed both blocks will be able to fit into a `uint64_t` register meaning that pseudo-SIMD operations can be performed on each member of the block. For addition and subtraction that is easy, but the question is what happens for multiplication and division? For the first test case each alphabet entry can fit into a `uint16_t`, from which an `O(W = 2w = 16)` operation will happen, whereas for the second config each alphabet entry can fit into a `uint8_t` from which an `O(w = 8)` operation will happen.

The question is, can multiplication operations be performed in a SIMD way? If not they will both be approximately the same speed because the first config performs half as many operations but takes twice as long relative to the second. If so then both will perform (for the sake of argument) `uint64_t` operations on both, but the latter config will complete them in half as many steps. 

For this reason I want to test this on different implementations, specifically a highly optimized one, because if these operations could be performed in a SIMD way then they are more likely to be done so in a highly performant environment.

Additionally, I have studied some methodologies for encoding and decoding Reed-Solomon codes, however there are many more, and an optimal decoder may have a different order of complexity relative to the block code parameters than mine. Additionally, because the basis for my hypothesis rests on if pseudo-SIMD operations are able to happen, it will be interesting to see how and when the compiler on my machine is able to optimize my implementation enough to do that for me.

The results of this test will inform how I may want to change my implementation to move closer to a more optimal implementation.


## Ramifications of `w` on error correcting capabilities _- how `e` scales in the previously proposed configs_

The configs in this test share a fixed block length in bits and message length in bits, so investigating how the parameters have scaled will inform if there is any advantage to adjusting the 

Interestingly, for the first config `D = N-K+1 = 3`, while for the second config `d = n-k+1 = 5 = 2N-2K+1 < 2*(N-K+1) = 2*D`. so, `d` scales sub-linearly with `n` and `k`.

However, for the first config `E = floor( (D-1)/2 ) = floor( 2/2 ) = 1`, while for the second config `e = floor( (d-1)/2 ) = floor( 4/2 ) = 2 = 2*E`, so `e` has scaled linearly with `n` and `k`. _This is only true because for the first case `N%2 = K%2`, so `E = (N-K)/2`. If this weren't the case then `E = (N-K-1)/2`, while `e = (n-k)/2 = 2*E + 1`, so `e` would increase super-linearly with respect to `n` and `k`._

To switch to the binary form view, because the second config halves the alphabet size, we have that _the maximum number of bits which can be changed while the codeword is decoded correctly_ for the first config equals `E*W = 1*16 = 16`, while for the second config this equals `e*w = 2*8 = 16 = E*W`. _If `N%2 != K%2` then `e*w = (2*E + 1)*W/2 = E*W + W/2 > E*W`, so this will have increased with the fixed block size but smaller alphabet size._

However, _the minimum number of bits which are needed to reach the limit of the error correcting capability of a codeword_ is equal to `E` for the first config and `e` for the second, and `E < e`. So, even though the maximum error correcting capability has stayed equal despite the change in parameters, the config with smaller alphabet size can correctly decode a codeword in strictly more cases.

Therefore, irrespective of my previous hypothesis about decreasing the alphabet size given a fixed message and block size being more efficient doing so will strictly increase a code's error correcting capability.

#
#

[1] `g(x) := F(x) % irr_pol(x)` is zero if and only if `irr_pol(x)` divides `F(x)`. Polynomials over fields are a Unique Factorization Domain, and so each of its elements can be split out into a unique product of irreducible elements. Because `F(x) = f(x) * x**(l-1)` and `x` is irreducible "the irreducible factorization of `F(x)`" will equal "the irreducible factorization of `f(x)` multiplied by `x` raised to the power `l-1`". "The irreducible factorization of `irr_pol(x)`" is just `irr_pol(x)`. Because `deg( irr_pol(x) ) = l > deg( f(x) )` we can conclude that `irr_pol(x)` is not in "the irreducible factorization of `f(x)`". Because `deg( irr_pol(x) ) = l > 1 = deg( x )` therefore `irr_pol(x)` cannot equal `x`. So, to conclude, the irreducible factors of `irr_pol(x)` are not contained within the irreducible factorization of `F(x)` and so `irr_pol(x)` cannot divide `F(x)`, so `F(x) % irr_pol(x)` will always be non-zero.


#
#

## Digression _- Brief illustration of why binary integer multiplication is not invertible and why for Finite field multiplication the modulo polynomial needs to be irreducible_

Regular integer multiplication isn't invertible - `2*` anything is uninvertable.

From my example multiplication in `GF(4) == Z2[x]/(x^2 + x + 1)` will be invertible, and for this to be so `x^2 + x + 1` must be irreducible in `Z2[x]`.

This polynomial needs to be irreducible, consider the counterexample `Z2[x]/(x^2 + 1 == (x+1)*(x+1) )`. In that ring any multiple of `x+1` will be uninvertable.

Regular integer multiplication with xor as addition is equivalent to multiplication and addition in `Z2[x]/(x^2 == (x)*(x))`. From our first example `2` in binary for when interpreted as `Z2[x]` is `x` so will be uninvertable here too.

