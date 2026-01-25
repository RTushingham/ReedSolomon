#include "Primes.h"

#include <iostream>

// #include "IsPrime.h"

std::vector<unsigned> manually_calculated_up_to_121 {2,3,5,7,11,13,17,19,23,29,31,37,41,43,47,53,59,61,67,71,73,79,83,89,97,101,103,107,109,113};

int main()
{
	auto a = AllPrimesUntil(121);
	
	std::cout << "mine == first: " << (manually_calculated_up_to_121 == a) << std::endl;
	
	for(const auto p : manually_calculated_up_to_121)
	{
		std::cout << p << std::endl;
	}
	for(const auto p : a)
	{
		std::cout << p << std::endl;
	}
}

