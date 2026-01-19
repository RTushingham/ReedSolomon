#include "FiniteFieldsOfSizePrime.h"

#include <iostream>

constexpr integer Prime{ 101 };

int main()
{
	for( integer non_zero_element = 1; non_zero_element < Prime; non_zero_element++ )
	{
		ElementOfFiniteFieldP<Prime> a{ non_zero_element };
		std::cout << "New value: " << a.value << std::endl;
		std::cout << "Inverse value: " << a.FindMultiplicativeInverse().value << std::endl;
		std::cout << "Verification value: " << (a*a.FindMultiplicativeInverse()).value << std::endl;
	}
	
	constexpr ElementOfFiniteFieldP<Prime> a{ 52 };
}

