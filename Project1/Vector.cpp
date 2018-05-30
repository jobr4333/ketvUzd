#pragma once

#include "Vector.h"; //supeeeeer
#include "Header.h"; //shitty
#include <iostream>
#include <chrono>
#include <vector>//basic

int main() {
	int i, x = 100000;
	vector<int> v1;
	std::vector<int> v2;
	Vector<int> v3;

	std::cout << x << std::endl;

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
	std::cout << "std vector finish: " << elapsed.count() << std::endl;

	start = std::chrono::high_resolution_clock::now(); //laiko matavimo start
	for (i = 0; i < x; ++i)
		v3.push_back(i);
	finish = std::chrono::high_resolution_clock::now(); //laiko matavimo start
	elapsed = finish - start;
	std::cout << "forum solution vector finish: " << elapsed.count() << std::endl;
	std::cin >> x;
	return 0;
}
