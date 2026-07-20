#include "FamousRSSchemas.h"

#include "finite-fields-polynomials/PolynomialsOverFiniteFieldOfSizePrimeToAPower.h"

#include "tests/finite-fields-tests/helpers/InitializerHelper.h"

Schema<
    BinaryUint8GFUint32MessageUint64Codeword::n,
    BinaryUint8GFUint32MessageUint64Codeword::k,
    BinaryUint8GFUint32MessageUint64Codeword::Prime,
    BinaryUint8GFUint32MessageUint64Codeword::Exponent
> BinaryUint8GFUint32MessageUint64Codeword::CreateSchema()
{
    const ElementOfFiniteField<BinaryUint8GFUint32MessageUint64Codeword::Prime, BinaryUint8GFUint32MessageUint64Codeword::Exponent> argument_one{
		x_to( 1,0 ).evaluate<PolynomialOverPrimeSizeFiniteField<BinaryUint8GFUint32MessageUint64Codeword::Prime,BinaryUint8GFUint32MessageUint64Codeword::Exponent-1>>()
	};

	const ElementOfFiniteField<BinaryUint8GFUint32MessageUint64Codeword::Prime, BinaryUint8GFUint32MessageUint64Codeword::Exponent> argument_two{
		x_to( 1,1 ).evaluate<PolynomialOverPrimeSizeFiniteField<BinaryUint8GFUint32MessageUint64Codeword::Prime,BinaryUint8GFUint32MessageUint64Codeword::Exponent-1>>()
	};

	const ElementOfFiniteField<BinaryUint8GFUint32MessageUint64Codeword::Prime, BinaryUint8GFUint32MessageUint64Codeword::Exponent> argument_three{
		x_to( 1,2 ).evaluate<PolynomialOverPrimeSizeFiniteField<BinaryUint8GFUint32MessageUint64Codeword::Prime,BinaryUint8GFUint32MessageUint64Codeword::Exponent-1>>()
	};

	const ElementOfFiniteField<BinaryUint8GFUint32MessageUint64Codeword::Prime, BinaryUint8GFUint32MessageUint64Codeword::Exponent> argument_four{
		x_to( 1,3 ).evaluate<PolynomialOverPrimeSizeFiniteField<BinaryUint8GFUint32MessageUint64Codeword::Prime,BinaryUint8GFUint32MessageUint64Codeword::Exponent-1>>()
	};

	const ElementOfFiniteField<BinaryUint8GFUint32MessageUint64Codeword::Prime, BinaryUint8GFUint32MessageUint64Codeword::Exponent> argument_five{
		x_to( 1,4 ).evaluate<PolynomialOverPrimeSizeFiniteField<BinaryUint8GFUint32MessageUint64Codeword::Prime,BinaryUint8GFUint32MessageUint64Codeword::Exponent-1>>()
	};

	const ElementOfFiniteField<BinaryUint8GFUint32MessageUint64Codeword::Prime, BinaryUint8GFUint32MessageUint64Codeword::Exponent> argument_six{
		x_to( 1,5 ).evaluate<PolynomialOverPrimeSizeFiniteField<BinaryUint8GFUint32MessageUint64Codeword::Prime,BinaryUint8GFUint32MessageUint64Codeword::Exponent-1>>()
	};

	const ElementOfFiniteField<BinaryUint8GFUint32MessageUint64Codeword::Prime, BinaryUint8GFUint32MessageUint64Codeword::Exponent> argument_seven{
		x_to( 1,6 ).evaluate<PolynomialOverPrimeSizeFiniteField<BinaryUint8GFUint32MessageUint64Codeword::Prime,BinaryUint8GFUint32MessageUint64Codeword::Exponent-1>>()
	};

	const ElementOfFiniteField<BinaryUint8GFUint32MessageUint64Codeword::Prime, BinaryUint8GFUint32MessageUint64Codeword::Exponent> argument_eight{
		x_to( 1,7 ).evaluate<PolynomialOverPrimeSizeFiniteField<BinaryUint8GFUint32MessageUint64Codeword::Prime,BinaryUint8GFUint32MessageUint64Codeword::Exponent-1>>()
	};

	return { std::array<ElementOfFiniteField<BinaryUint8GFUint32MessageUint64Codeword::Prime, BinaryUint8GFUint32MessageUint64Codeword::Exponent>,BinaryUint8GFUint32MessageUint64Codeword::n>{ argument_one, argument_two, argument_three, argument_four, argument_five, argument_six, argument_seven, argument_eight } };
};

BinaryUint8GFUint32MessageUint64Codeword::BinaryUint8GFUint32MessageUint64Codeword()
    : schema{ BinaryUint8GFUint32MessageUint64Codeword::CreateSchema() }
    {};


Schema<
    BinaryUint16GFUint32MessageUint64Codeword::n,
    BinaryUint16GFUint32MessageUint64Codeword::k,
    BinaryUint16GFUint32MessageUint64Codeword::Prime,
    BinaryUint16GFUint32MessageUint64Codeword::Exponent
> BinaryUint16GFUint32MessageUint64Codeword::CreateSchema()
{
	const ElementOfFiniteField<BinaryUint16GFUint32MessageUint64Codeword::Prime, BinaryUint16GFUint32MessageUint64Codeword::Exponent> argument_one{
		x_to( 1,0 ).evaluate<PolynomialOverPrimeSizeFiniteField<BinaryUint16GFUint32MessageUint64Codeword::Prime,BinaryUint16GFUint32MessageUint64Codeword::Exponent-1>>()
	};

	const ElementOfFiniteField<BinaryUint16GFUint32MessageUint64Codeword::Prime, BinaryUint16GFUint32MessageUint64Codeword::Exponent> argument_two{
		x_to( 1,1 ).evaluate<PolynomialOverPrimeSizeFiniteField<BinaryUint16GFUint32MessageUint64Codeword::Prime,BinaryUint16GFUint32MessageUint64Codeword::Exponent-1>>()
	};

	const ElementOfFiniteField<BinaryUint16GFUint32MessageUint64Codeword::Prime, BinaryUint16GFUint32MessageUint64Codeword::Exponent> argument_three{
		x_to( 1,2 ).evaluate<PolynomialOverPrimeSizeFiniteField<BinaryUint16GFUint32MessageUint64Codeword::Prime,BinaryUint16GFUint32MessageUint64Codeword::Exponent-1>>()
	};

	const ElementOfFiniteField<BinaryUint16GFUint32MessageUint64Codeword::Prime, BinaryUint16GFUint32MessageUint64Codeword::Exponent> argument_four{
		x_to( 1,3 ).evaluate<PolynomialOverPrimeSizeFiniteField<BinaryUint16GFUint32MessageUint64Codeword::Prime,BinaryUint16GFUint32MessageUint64Codeword::Exponent-1>>()
	};

	return{ std::array<ElementOfFiniteField<BinaryUint16GFUint32MessageUint64Codeword::Prime, BinaryUint16GFUint32MessageUint64Codeword::Exponent>,BinaryUint16GFUint32MessageUint64Codeword::n>{ argument_one, argument_two, argument_three, argument_four } };
};

BinaryUint16GFUint32MessageUint64Codeword::BinaryUint16GFUint32MessageUint64Codeword()
    : schema{ BinaryUint16GFUint32MessageUint64Codeword::CreateSchema() }
    {};


Schema<
    PrimePowerGF::n,
    PrimePowerGF::k,
    PrimePowerGF::Prime,
    PrimePowerGF::Exponent
> PrimePowerGF::CreateSchema()
{
	const ElementOfFiniteField<PrimePowerGF::Prime, PrimePowerGF::Exponent> argument_one{
		PolynomialOverPrimeSizeFiniteField<PrimePowerGF::Prime,PrimePowerGF::k-1>{
			std::array<ElementOfFiniteFieldP<PrimePowerGF::Prime>,PolynomialOverPrimeSizeFiniteField<PrimePowerGF::Prime,PrimePowerGF::k-1>::GetCoeffCount()>{
				ElementOfFiniteFieldP<PrimePowerGF::Prime>{ 9 },
				ElementOfFiniteFieldP<PrimePowerGF::Prime>{ 8 }
			} 
		}
	};

	const ElementOfFiniteField<PrimePowerGF::Prime, PrimePowerGF::Exponent> argument_two{
		PolynomialOverPrimeSizeFiniteField<PrimePowerGF::Prime,PrimePowerGF::k-1>{
			std::array<ElementOfFiniteFieldP<PrimePowerGF::Prime>,PolynomialOverPrimeSizeFiniteField<PrimePowerGF::Prime,PrimePowerGF::k-1>::GetCoeffCount()>{
				ElementOfFiniteFieldP<PrimePowerGF::Prime>{ 10 },
				ElementOfFiniteFieldP<PrimePowerGF::Prime>{ 11 }
			} 
		}
	};

	const ElementOfFiniteField<PrimePowerGF::Prime, PrimePowerGF::Exponent> argument_three{
		PolynomialOverPrimeSizeFiniteField<PrimePowerGF::Prime,PrimePowerGF::k-1>{
			std::array<ElementOfFiniteFieldP<PrimePowerGF::Prime>,PolynomialOverPrimeSizeFiniteField<PrimePowerGF::Prime,PrimePowerGF::k-1>::GetCoeffCount()>{
				ElementOfFiniteFieldP<PrimePowerGF::Prime>{ 12 },
				ElementOfFiniteFieldP<PrimePowerGF::Prime>{ 13 }
			} 
		}
	};

	const ElementOfFiniteField<PrimePowerGF::Prime, PrimePowerGF::Exponent> argument_four{
		PolynomialOverPrimeSizeFiniteField<PrimePowerGF::Prime,PrimePowerGF::k-1>{
			std::array<ElementOfFiniteFieldP<PrimePowerGF::Prime>,PolynomialOverPrimeSizeFiniteField<PrimePowerGF::Prime,PrimePowerGF::k-1>::GetCoeffCount()>{
				ElementOfFiniteFieldP<PrimePowerGF::Prime>{ 14 },
				ElementOfFiniteFieldP<PrimePowerGF::Prime>{ 15 }
			} 
		}
	};

	return{ std::array<ElementOfFiniteField<PrimePowerGF::Prime, PrimePowerGF::Exponent>,PrimePowerGF::n>{ argument_one, argument_two, argument_three, argument_four } };
};

PrimePowerGF::PrimePowerGF()
    : schema{ PrimePowerGF::CreateSchema() }
    {};

