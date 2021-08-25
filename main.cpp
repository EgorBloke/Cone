#include<iostream>
#include"cone.h"

int main() {

	Cone cone(6.5, 3, 12);
	std::cout << cone;

	Cone cone2(7.5, 3., 3);
	std::cout << cone2;

	return 0;
}