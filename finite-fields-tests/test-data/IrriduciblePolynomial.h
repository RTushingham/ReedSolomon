#include "finite-fields/FiniteFieldsOfSizePrimeToAPower.h"

const PolynomialOverPrimeSizeFiniteField<101,2> irriducible{
	std::array<ElementOfFiniteFieldP<101>,PolynomialOverPrimeSizeFiniteField<101,2>::GetCapacity()>{
		ElementOfFiniteFieldP<101>{ -2 },
		ElementOfFiniteFieldP<101>{ 0 },
		ElementOfFiniteFieldP<101>{ 1 }
	} 
};
