#pragma once

#include "Vector.h"; //supeeeeer
#include <iostream>
#include <chrono>
#include <vector>//basic
#include <math.h>

int main() {
	int i;
	unsigned long long int x = 10000;
	vector<int> v1;
	std::vector<int> v2;

	

	for (size_t y = 1; y < 5; y++) {
		std::cout << "Number of elements (pushbacks): " << x << std::endl << std::endl;
		auto start = std::chrono::high_resolution_clock::now(); //laiko matavimo start
		for (i = 0; i < x; ++i)
			v1.push_back(i);
		auto finish = std::chrono::high_resolution_clock::now(); //laiko matavimo start
		std::chrono::duration<double> elapsed = finish - start;
		std::cout << "turbo vector finish: " << elapsed.count() << std::endl;

		start = std::chrono::high_resolution_clock::now(); //laiko matavimo start
		for (i = 0; i < x; ++i)
			v2.push_back(i);
		finish = std::chrono::high_resolution_clock::now(); //laiko matavimo start
		elapsed = finish - start;

		std::cout << "std vector finish:   " << elapsed.count() << std::endl << std::endl;
		x = x * 10;
		
	}
	return 0;
}
